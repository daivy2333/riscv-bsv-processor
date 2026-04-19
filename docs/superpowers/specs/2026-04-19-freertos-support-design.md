# FreeRTOS 支持设计规范

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** 在 RV32I 五级流水线处理器上移植 FreeRTOS，支持多任务调度、定时器中断、UART 调试输出。

**Architecture:** Direct mtvec + MTIP tick + ecall yield + UART TX-only，分阶段验证

**Tech Stack:** BSV (Core/SOC), Verilator仿真, FreeRTOS RISC-V port, RISC-V GCC toolchain

---

## 系统配置

| 参数 | 值 | 说明 |
|------|-----|------|
| IMem | 32KB (8K words) | .text + 启动代码 |
| DMem | 256KB (64K words) | .rodata/.data/.bss/.heap/.stack |
| FreeRTOS 堆 | 16KB | pvPortMalloc |
| tick 周期 | 10ms (100Hz) | mtimecmp 配置 |
| 中断源 | MTIP + ecall | 定时器 + yield |
| mtvec | Direct mode | 统一 trap handler |

---

## 内存布局

### 物理地址映射

| 区域 | 地址范围 | 大小 | 用途 |
|------|----------|------|------|
| IMem | 0x80000000 - 0x80007FFF | 32KB | 取指（.text） |
| DMem | 0x80000000 - 0x8003FFFF | 256KB | load/store |
| CLINT | 0x02000000 - 0x0200FFFF | 64KB | mtime/mtimecmp/msip |
| UART | 0x10000000 - 0x10000FFF | 4KB | TXDATA |

**注意**: IMem 和 DMem 地址重叠，但物理分离。取指访问 IMem，load/store 访问 DMem。

### Linker Script 布局

```
IMem 区域 (仅存放指令):
  - .text    @ 0x80000000  # FreeRTOS kernel + 应用代码

DMem 区域 (存放数据):
  - .rodata  @ 0x80000000  # 常量、字符串（通过 load 读取）
  - .data    @ 0x80002000  # 已初始化全局变量
  - .bss     @ 0x80004000  # 未初始化全局变量（startup 清零）
  - .heap    @ 0x80008000  # FreeRTOS 堆 (16KB)
  - .stack   @ 0x0003F000  # 任务栈（相对 DMem 基址，实际 0x8003F000）
```

### 启动镜像生成

```
构建流程:
  1. GCC 编译 → imem.hex (含 .text) + dmem.hex (含 .rodata/.data)
  2. tools/hex_to_bsv.py → TestProgram.bsv
  3. startup 代码: 清零 .bss，初始化 sp，跳转 main
```

---

## CLINT 定时器

### 寄存器映射（RV32 兼容）

| 寄存器 | 地址 | 位宽 | 说明 |
|--------|------|------|------|
| mtime_lo | 0x0200BFF8 | 32-bit | mtime 低 32 位 |
| mtime_hi | 0x0200BFFC | 32-bit | mtime 高 32 位 |
| mtimecmp_lo | 0x02004000 | 32-bit | mtimecmp 低 32 位 |
| mtimecmp_hi | 0x02004004 | 32-bit | mtimecmp 高 32 位 |
| msip | 0x02000000 | 32-bit | 软件中断触发（bit 0） |

### mtime 行为

```
mtime 每时钟周期自增 1
MTIP = (mtime >= mtimecmp)
```

### mtimecmp 安全更新（三步法）

```
Step 1: mtimecmp_lo ← 0xFFFFFFFF  # 先设低位为最大值
Step 2: mtimecmp_hi ← new_hi      # 更新高位
Step 3: mtimecmp_lo ← new_lo      # 最后更新低位

目的: 避免中间态导致 mtimecmp 短暂变小而伪触发
```

---

## UART TX（无 backpressure）

### 寄存器

| 寄存器 | 地址 | 说明 |
|--------|------|------|
| TXDATA | 0x10000000 | 写入立即输出 |

### 行为

```
写入 TXDATA → $display 输出字符（仿真）
无 ready 检查，无阻塞
软件约定: 直接写入，不轮询 ready
```

### 软件接口

```c
void putchar(char c) {
    *((volatile uint32_t*)0x10000000) = c;
}

void puts(const char *s) {
    while (*s) putchar(*s++);
}
```

---

## Trap 处理

### mstatus 关键位

| 位 | 名称 | 说明 |
|----|------|------|
| 3 | MIE | 全局中断使能 |
| 7 | MPIE | trap 前中断使能状态 |
| 12:11 | MPP | trap 前特权模式 |

### Trap Entry 时序

```
1. mepc ← 恢复点 PC
   - 异常: faulting instruction PC
   - 中断: 将要恢复执行的指令 PC
   
2. mcause ← interrupt_flag(最高位) + cause_code
   - 最高位=1: 中断
   - 最高位=0: 异常
   
3. mstatus.MPIE ← mstatus.MIE
4. mstatus.MIE ← 0
5. mstatus.MPP ← current_mode (M_MODE)
6. PC ← mtvec_base (Direct mode)
```

### Trap Return (mret) 时序

```
1. PC ← mepc
2. mstatus.MIE ← mstatus.MPIE
3. mstatus.MPIE ← 1
4. mstatus.MPP ← M_MODE (返回到 Machine mode)
```

### mcause 分发

```
trap handler:
  if (mcause[31] == 1):  # 中断
    switch (mcause[4:0]):
      case 7:  timer_interrupt_handler()
      case 3:  software_interrupt_handler()  # 预留
      
  else:  # 异常
    switch (mcause[4:0]):
      case 11: ecall_handler()  # yield
      default: exception_handler()  # 报错
```

### tick handler 内重装 mtimecmp

```
timer_interrupt_handler:
  1. mtimecmp += tick_delta  # 先重装下一次 compare
  2. 调用 FreeRTOS tick handler
  3. mret  # 避免 repeat trigger
```

---

## 任务栈帧

### 统一栈帧布局（trap 保存 = 任务初始栈）

```
栈帧结构 (从高地址向下):

Offset  内容           说明
+28     mepc           任务恢复地址 / trap 返回地址
+24     mstatus        按 mret 语义构造
+20     x31            
+16     x30            
+12     x29            
+8      x28            
+4      x27-x1         (除 x2/sp)
+0      (sp 指向此处)

约定:
  - x2(sp) 不入栈，由约定处理
  - 保存顺序: x1, x3-x31, mstatus, mepc
  - sp 最终指向栈帧顶部 (mepc + 28)
```

### 首任务栈初始化

```
首任务栈帧构造 (portASM.S):
  - mepc    = 任务函数入口
  - mstatus = 按 mret 启动语义构造:
      - MIE   = 0  (mret 后被 MPIE 替换)
      - MPIE  = 1  (mret 后 MIE = 1)
      - MPP   = 3  (返回到 M-mode)
  - 所有 GPR = 0 (除 sp)
```

### portASM.S 寄存器保存顺序

```
trap_entry:
  1. sp ← sp - 32  # 预留栈帧 (8 words: mepc/mstatus/x1-x31除x2)
  2. 存储 x1  @ sp+0
  3. 存储 x3  @ sp+4
  4. 存储 x4  @ sp+8
  ...
  5. 存储 x31 @ sp+28
  6. 存储 mstatus @ sp+32
  7. 存储 mepc    @ sp+36
  8. sp ← sp + 36  # sp 指向 mepc
  
trap_return:
  1. 从 sp 恢复 mepc, mstatus, x1-x31
  2. sp ← sp + 36  # 恢复 sp
  3. mret
```

---

## FreeRTOS 移植文件

### 文件列表

| 文件 | 职责 |
|------|------|
| portmacro.h | 类型定义 (BaseType_t, UBaseType_t, StackType_t) |
| port.c | tick 配置, vPortSetupTick, 临界区开关 |
| portASM.S | trap 入口, 上下文保存/恢复, 首任务栈伪造, mret |
| FreeRTOSConfig.h | 堆大小(16KB), tick频率(100Hz), configUSE_PREEMPTION=1 |

### FreeRTOSConfig.h 关键配置

```c
#define configCPU_CLOCK_HZ          (10000000)  // 10 MHz (仿真)
#define configTICK_RATE_HZ          (100)       // 10ms tick
#define configMINIMAL_STACK_SIZE    (128)       // words
#define configTOTAL_HEAP_SIZE       (16384)     // bytes (16KB)
#define configUSE_PREEMPTION        1
#define configUSE_IDLE_HOOK         0
```

### port.c 关键函数

```c
void vPortSetupTick(void) {
    // 设置首次 mtimecmp
    uint64_t first_tick = get_mtime() + configCPU_CLOCK_HZ / configTICK_RATE_HZ;
    set_mtimecmp_safe(first_tick);
}

void vPortYield(void) {
    // 通过 ecall 触发 trap
    asm volatile("ecall");
}

static inline void set_mtimecmp_safe(uint64_t val) {
    // 三步安全更新
    *((volatile uint32_t*)0x02004004) = 0xFFFFFFFF;
    *((volatile uint32_t*)0x02004000) = (uint32_t)(val >> 32);
    *((volatile uint32_t*)0x02004004) = (uint32_t)(val & 0xFFFFFFFF);
}
```

---

## 实现阶段

### Phase 6.1: Bare-metal 验证

**目标:** 验证硬件基础功能，不涉及 FreeRTOS

**测试用例:**
1. UART putchar → 立即打印 'A'
2. mtime 单调递增 + 64位读取正确
3. mtimecmp 设置后触发 MTIP (mtime >= mtimecmp)
4. trap 入口: mepc/mcause/mstatus 正确设置
5. mret 返回: PC 正确恢复

**验收标准:** 5 个测试全部通过

### Phase 6.2: Linker + Startup

**目标:** 建立 C 程序运行环境

**任务:**
- linker.ld: 定义 .text/.rodata/.data/.bss/.heap/.stack
- startup.S: 清零 .bss，初始化 sp，跳转 main
- 验证: C 函数调用 + 全局变量读写

**验收标准:** C 程序正常执行，UART 输出字符串

### Phase 6.3: FreeRTOS 移植层

**目标:** 完成 FreeRTOS 底层移植

**任务:**
- portmacro.h: 类型定义
- port.c: tick 配置, 临界区
- portASM.S: trap 入口, 上下文切换
- FreeRTOSConfig.h: 配置参数
- 统一栈帧格式

**验收标准:** FreeRTOS 编译链接成功

### Phase 6.4: FreeRTOS 验证

**目标:** 运行 FreeRTOS demo

**测试用例:**
1. 单任务 + vTaskDelay(100) + putchar
2. 双任务不同周期打印 (Task1: 100ms, Task2: 500ms)
3. 10^5 次 tick 无卡死，无栈损坏

**验收标准:** 多任务调度正常，UART 输出稳定

---

## 验收标准汇总

| 阶段 | 验收标准 |
|------|----------|
| 6.1 | 5 个 bare-metal 测试通过 |
| 6.2 | C 程序执行，UART 输出字符串 |
| 6.3 | FreeRTOS 编译链接成功 |
| 6.4 | 多任务调度正常，10^5 tick 无故障 |

---

## 风险控制

| 风险 | 缓解措施 |
|------|----------|
| BSC 编译 OOM | 大内存用 Verilog 直接定义 |
| mtimecmp 中间态触发 | 三步安全更新 |
| 任务栈帧不一致 | 文档固化精确布局 |
| mepc 计算错误 | 流水线精确计算恢复点 |
| IMem/DMem 地址冲突 | 明确取指 vs load/store 路由 |

---

## 未实现功能（后续阶段）

- Vectored mtvec mode
- MEIP + PLIC 完整中断
- UART RX
- 更大内存 (>256KB)
- U/S mode 支持

---

*设计日期: 2026-04-19*