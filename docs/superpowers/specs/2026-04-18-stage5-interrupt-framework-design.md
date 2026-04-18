# 阶段 5：中断框架与外设模块设计规格

日期：2026-04-18

## 目标

实现完整的中断框架和基础外设，使处理器能够正确响应定时器中断和外部中断，为后续 FreeRTOS 支持奠定基础。

## 中断拓扑

```
Timer/CLINT ──── MTIP ────► CSR (mip[7])
Software IRQ ─── MSIP ────► CSR (mip[3])
UART ──IRQ──► PLIC ──── MEIP ───► CSR (mip[11])
```

**关键原则**：
- Timer 不走 PLIC，直接输出 MTIP
- 外部中断源（UART 等）接 PLIC，统一仲裁后输出 MEIP
- CSR 只接收三个信号：MTIP、MSIP、MEIP

---

## 模块划分

### 新增模块

| 模块 | 文件路径 | 职责 |
|------|----------|------|
| CLINT | `src/peripheral/CLINT.bsv` | mtime 自动递增、mtimecmp 比较、MSIP、输出 MTIP |
| PLIC | `src/peripheral/PLIC.bsv` | 外部中断仲裁、claim/complete MMIO、输出 MEIP |
| UART | `src/peripheral/UART.bsv` | TX/RX、MMIO、IRQ 连接 PLIC |
| SOC | `src/soc/SOC.bsv` | MMIO 地址路由、模块互联 |
| DMem | `src/memory/DMem.bsv` | 独立内存模块 + tohost 监控回调 |

### 修改模块

| 模块 | 文件路径 | 修改内容 |
|------|----------|----------|
| Core | `src/core/Core.bsv` | 提取 DMem、改用请求/响应式内存接口、提交边界检查中断 |
| CSR | `src/core/CSR.bsv` | 接收 MTIP/MSIP/MEIP 信号（接口保持不变） |

---

## 接口定义

### Core <-> Memory 接口（请求/响应式）

```bsv
// MEM 阶段请求包
typedef struct {
    Bool        valid;
    Addr        addr;
    Word        wdata;      // 写数据
    MemOp       op;         // READ/WRITE/NONE
    MemWidth    width;      // BYTE/HALF/WORD
    Bool        unsigned;   // 无符号扩展
} MemReq deriving (Bits, Eq);

// MEM 阶段响应包
typedef struct {
    Bool        valid;
    Word        rdata;      // 读数据（已按 width 扩展）
} MemResp deriving (Bits, Eq);

interface CoreMem;
    method Action sendReq(MemReq req);
    method MemResp getResp();
endinterface
```

**设计原则**：
- 请求发送后，响应可能在下一周期返回（允许 MMIO 延迟）
- `rdata` 已按 `width` 和 `unsigned` 完成字节/半字扩展
- `valid` 信号用于握手，避免阻塞流水线

### CLINT 接口

```bsv
interface CLINT;
    // MMIO 读写
    method Word read(Addr addr);
    method Action write(Addr addr, Word data);
    // 中断输出
    method Bool timerIRQ();             // MTIP: mtime >= mtimecmp
    method Bool softwareIRQStatus();   // MSIP 读状态
    method Action softwareIRQ(Bool v); // MSIP 写入
endinterface
```

**地址映射**：
| 地址 | 名称 | 说明 |
|------|------|------|
| 0x02000000 | msip | 软件中断触发（写 1 触发） |
| 0x0200BFF8 | mtime | 时间计数器（64-bit，低 32-bit） |
| 0x0200BFFC | mtime+4 | 时间计数器（高 32-bit） |
| 0x02004000 | mtimecmp | 时间比较器（64-bit，低 32-bit） |
| 0x02004004 | mtimecmp+4 | 时间比较器（高 32-bit） |

### PLIC 接口

```bsv
interface PLIC;
    // MMIO 读写（claim/complete 通过地址语义实现）
    method Word read(Addr addr);
    method Action write(Addr addr, Word data);
    // 中断输出
    method Bool externalIRQ();          // MEIP
    // 外设 IRQ 输入
    method Action setIRQ(Bit#(32) source_id, Bool v);
endinterface
```

**地址映射**：
| 地址 | 名称 | 说明 |
|------|------|------|
| 0x0C000000 - 0x0C000003 | priority[0] | 上下文 0 优先级阈值 |
| 0x0C000004 - 0x0C001FFF | priority[1-N] | 各中断源优先级 |
| 0x0C002000 - 0x0C002003 | enable[0] | 上下文 0 使能位 |
| 0x0C200004 | claim/complete | claim 读 / complete 写 |

**claim/complete 语义**：
- **读 claim**: 返回当前最高优先级挂起中断号
- **写 complete**: 完成中断处理，清除挂起状态

### UART 接口

```bsv
interface UART;
    // MMIO 读写
    method Word read(Addr addr);
    method Action write(Addr addr, Word data);
    // IRQ 输出（接 PLIC source_id=1）
    method Bool hasIRQ();
endinterface
```

**地址映射**：
| 地址偏移 | 名称 | 说明 |
|----------|------|------|
| 0x00 | TXDATA | 发送数据（写触发发送） |
| 0x04 | RXDATA | 接收数据（读获取数据） |
| 0x08 | TXCTRL | 发送控制 |
| 0x0C | RXCTRL | 接收控制 |
| 0x10 | IE | 中断使能 |
| 0x14 | IP | 中断挂起 |

---

## 地址空间规划

| 区域 | 地址范围 | 模块 | 说明 |
|------|----------|------|------|
| CLINT | 0x02000000 - 0x0200FFFF | CLINT | 定时器 + 软件中断 |
| PLIC | 0x0C000000 - 0x0C0FFFFF | PLIC | 外部中断控制器 |
| UART | 0x10000000 - 0x10000FFF | UART | 串口外设 |
| RAM | 0x80000000 - 0x8000FFFF | DMem | 64KB RAM |
| tohost | 0x80001000 | DMem | RAM 内特殊监控地址 |

**tohost 归属明确**：
- 属于 RAM 地址空间
- DMem 正常处理读写
- SOC/TestBench 层监控写入，触发测试结束

---

## 精确中断语义

### 提交边界检查流程

```
1. 先完成当前指令的 WB 写回（RegFile 更新完成）
2. 再检查：mstatus.mie && (mie & mip) != 0
3. 若命中中断：
   - 保存 mepc = 当前指令 PC（下一条应执行指令）
   - 保存 mcause = 中断原因（最高位=1 表示中断）
   - 保存 mtval = 0（中断时通常为 0）
   - flush 比当前指令更年轻的流水线状态（IF/ID/EX）
   - 跳转到 mtvec
```

### 实现位置

**并入 `writebackStage` rule 尾部**，不是独立 rule：

```bsv
rule writebackStage;
    // ... 正常 WB 写回逻辑 ...

    // 提交边界检查中断
    if (csrs.hasPendingInterrupt() && mstatus.mie) begin
        // 保存 trap 信息
        csrs.saveTrapContext(...);
        // flush 流水线
        if2id.clear;
        id2ex.clear;
        ex2mem.clear;
        // 跳转到 mtvec
        pcReg <= csrs.getTrapVector();
    end
endrule
```

### CSR 接口保持不变

CSR 不新增方法，继续使用：
- `hasPendingInterrupt()` - 返回 Bool
- `getPendingInterruptCause()` - 返回最高优先级中断原因

"是否在 commit 边界检查"是 Core 的时序决策，不是 CSR 职责。

---

## SOC 模块设计

### MMIO 路由逻辑

```bsv
module mkSOC(SOC);
    CLINT clint <- mkCLINT;
    PLIC plic <- mkPLIC;
    UART uart <- mkUART;
    DMem dmem <- mkDMem;
    Core core <- mkCore;

    // 内存请求路由
    rule routeMemReq;
        let req = core.memReq;
        Addr addr = req.addr;

        if (addr >= 32'h02000000 && addr < 32'h02010000) begin
            // CLINT
            clint.write(addr, req.wdata);
        end else if (addr >= 32'h0C000000 && addr < 32'h0C100000) begin
            // PLIC
            plic.write(addr, req.wdata);
        end else if (addr >= 32'h10000000 && addr < 32'h10001000) begin
            // UART
            uart.write(addr, req.wdata);
        end else if (addr >= 32'h80000000) begin
            // RAM
            dmem.write(addr, req.wdata);
        end
    endrule

    // 中断信号连接
    rule connectInterrupts;
        csrs.setMTIP(clint.timerIRQ());
        csrs.setMSIP(clint.softwareIRQStatus());
        csrs.setMEIP(plic.externalIRQ());
        plic.setIRQ(1, uart.hasIRQ());  // UART -> PLIC source_id=1
    endrule
endmodule
```

---

## 测试计划

| 测试文件 | 测试内容 | 验证点 |
|----------|----------|--------|
| timer_irq_test.s | 定时器中断触发 + mret | MTIP、trap 响应、mret 返回 |
| plic_test.s | 外部中断 + claim/complete | MEIP、PLIC 仲裁、claim/complete 语义 |
| uart_test.s | UART 收发 + 中断 | TX/RX、UART IRQ、PLIC 路由 |

### timer_irq_test.s 核心流程

```asm
# 1. 设置 mtimecmp = 100（100 周期后触发）
# 2. 设置 mie.MTIE = 1，mstatus.MIE = 1
# 3. 等待中断触发
# 4. trap handler: 读取 mcause，确认是定时器中断
# 5. mret 返回
# 6. 写入 tohost = 1 表示通过
```

### plic_test.s 核心流程

```asm
# 1. 设置 PLIC priority/enable
# 2. 触发外部中断源
# 3. trap handler: claim 获取中断号
# 4. 处理中断
# 5. complete 通知 PLIC
# 6. mret 返回
```

---

## 实现顺序

1. **CLINT.bsv** - mtime 自动递增、MTIP 输出
2. **修改 Core.bsv** - 提取 DMem、请求/响应式接口、提交边界检查
3. **DMem.bsv** - 独立模块、tohost 监控回调
4. **PLIC.bsv** - 外部中断仲裁、claim/complete
5. **UART.bsv** - TX/RX、IRQ 输出
6. **SOC.bsv** - MMIO 路由、模块互联
7. **测试** - timer_irq_test → plic_test → uart_test

---

## 保留功能

- 所有现有 RV32I 指令
- CSR 寄存器（保持接口不变）
- 分支预测（BHT/BTB）
- 数据前递
- Load-Use 冒险处理
- 陷阱处理（ECALL/EBREAK/MRET）

---

## 参考

- `docs/cpu-pipeline-architecture.md` - 流水线架构
- `docs/roadmap-embedded-os.md` - 开发路线图
- RISC-V Privileged Specification v1.10 - CLINT/PLIC 定义