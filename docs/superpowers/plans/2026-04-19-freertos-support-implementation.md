# FreeRTOS Support Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-step. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** 在 RV32I 五级流水线处理器上移植 FreeRTOS，支持多任务调度、定时器中断、UART 调试输出。

**Architecture:** Direct mtvec + MTIP tick + ecall yield + UART TX-only，分阶段验证（bare-metal → linker → port → FreeRTOS）

**Tech Stack:** BSV (Core/SOC), Verilator 仿真, FreeRTOS RISC-V port, riscv64-unknown-elf-gcc

---

## File Structure

```
创建/修改文件:

硬件层 (BSV):
├── src/memory/IMem.bsv       # 扩展 32KB
├── src/memory/DMem.bsv       # 扩展 256KB, 地址路由
├── src/soc/SOC.bsv           # DMem decode 范围
├── src/core/Core.bsv         # trap 语义完善
└── src/peripheral/CLINT.bsv  # mtimecmp 地址

裸机测试:
├── tests/assembly/bare_metal_uart.s      # UART 测试
├── tests/assembly/bare_metal_mtime.s     # mtime 测试
├── tests/assembly/bare_metal_timer.s     # timer 中断测试
├── tests/assembly/bare_metal_trap.s      # trap+mret 测试

软件层:
├── firmware/linker.ld        # 内存布局
├── firmware/startup.S        # 启动代码
├── firmware/FreeRTOS/        # FreeRTOS 源码
├── firmware/port/
│   ├── portmacro.h           # 类型定义
│   ├── port.c                # tick/临界区
│   ├── portASM.S             # trap/上下文切换
│   └── FreeRTOSConfig.h      # 配置
├── firmware/freertos_demo.c  # demo 任务
└── tools/hex_to_bsv.py       # (现有) hex 转换
```

---

## Phase 6.1: Bare-metal 验证

### Task 1: 扩展 IMem 到 32KB

**Files:**
- Modify: `src/memory/IMem.bsv`

- [ ] **Step 1: 修改 IMem 大小和索引**

```bsv
// src/memory/IMem.bsv
package IMem;

import Types::*;
import Vector::*;

// 指令内存（32KB, 8K words）
module mkIMem(IMem);
    // 使用 Verilog 直接定义大内存，避免 BSC OOM
    // 32KB = 8192 words
    Vector#(8192, Reg#(Word)) memory <- replicateM(mkReg(0));

    method Word read(Addr addr);
        Bit#(13) index = addr[14:2];  // 13位索引 (32KB = 8K words)
        return memory[index];
    endmethod

    method Action write(Addr addr, Word data);
        Bit#(13) index = addr[14:2];
        memory[index] <= data;
    endmethod
endmodule

endpackage
```

- [ ] **Step 2: 编译验证 BSC 不 OOM**

Run: `make compile`
Expected: 编译成功，无 OOM 错误

- [ ] **Step 3: Commit**

```bash
git add src/memory/IMem.bsv
git commit -m "feat(imem): expand to 32KB (8K words)

Co-Authored-By: Claude Opus 4.7 <noreply@anthropic.com>"
```

---

### Task 2: 扩展 DMem 到 256KB

**Files:**
- Modify: `src/memory/DMem.bsv`
- Modify: `src/soc/SOC.bsv`

- [ ] **Step 1: 修改 DMem 大小和索引**

```bsv
// src/memory/DMem.bsv
package DMem;

import Types::*;
import Vector::*;

interface DMem;
    method Word read(Addr addr);
    method Action write(Addr addr, Word data);
    method Bool tohostWritten();
    method Word tohostValue();
endinterface

module mkDMem(DMem);
    // 256KB内存 (64K words)
    // 注意：使用 Verilog 生成，BSC replicateM 可能 OOM
    // 如果编译失败，改用 Verilog 直接定义
    Vector#(65536, Reg#(Word)) memory <- replicateM(mkReg(0));

    Reg#(Bool) tohost_written_reg <- mkReg(False);
    Reg#(Word) tohost_value_reg <- mkReg(0);

    function Addr tohostAddr(); return 32'h80001000; endfunction

    method Word read(Addr addr);
        Bit#(16) index = addr[17:2];  // 16位索引 (256KB = 64K words)
        return memory[index];
    endmethod

    method Action write(Addr addr, Word data);
        Bit#(16) index = addr[17:2];
        memory[index] <= data;

        if (addr == tohostAddr()) begin
            tohost_written_reg <= True;
            tohost_value_reg <= data;
        end
    endmethod

    method Bool tohostWritten();
        return tohost_written_reg;
    endmethod

    method Word tohostValue();
        return tohost_value_reg;
    endmethod
endmodule

endpackage
```

- [ ] **Step 2: 更新 SOC DMem 地址范围**

```bsv
// src/soc/SOC.bsv 中 handle_mem_req rule
// 修改 DMem 地址判断
end else if (addr >= 32'h80000000 && addr < 32'h80040000) begin
    // RAM (256KB: 0x80000000 - 0x8003FFFF)
    if (req.op == MEM_READ)
        rdata = dmem.read(addr);
    else if (req.op == MEM_WRITE)
        dmem.write(addr, req.wdata);
end
```

- [ ] **Step 3: 编译验证**

Run: `make compile`
Expected: 编译成功。如果 OOM，需要改用 Verilog 直接定义内存。

- [ ] **Step 4: 如果 OOM，使用 Verilog 方案**

如果 BSC OOM，修改 DMem 使用外部 Verilog：

```verilog
// build/DMem.v (手动创建)
module mkDMem(
    input [31:0] addr,
    output [31:0] rdata,
    input [31:0] wdata,
    input wen
);
    reg [31:0] memory [0:65535];
    
    assign rdata = memory[addr[17:2]];
    
    always @(posedge CLK) begin
        if (wen)
            memory[addr[17:2]] <= wdata;
    end
endmodule
```

然后修改 BSV 调用外部 Verilog 模块。

- [ ] **Step 5: Commit**

```bash
git add src/memory/DMem.bsv src/soc/SOC.bsv
git commit -m "feat(dmem): expand to 256KB (64K words), update SOC address range

Co-Authored-By: Claude Opus 4.7 <noreply@anthropic.com>"
```

---

### Task 3: UART TX putchar 测试

**Files:**
- Create: `tests/assembly/bare_metal_uart.s`

- [ ] **Step 1: 编写 UART putchar 测试汇编**

```asm
# tests/assembly/bare_metal_uart.s
# UART TX putchar 测试

.section .text
.global _start

_start:
    # 写入 'A' 到 UART TXDATA (0x10000000)
    li x5, 0x10000000      # UART 基地址
    li x6, 65              # 'A' ASCII
    sw x6, 0(x5)           # 写入 TXDATA
    
    # 写入 'B'
    li x6, 66              # 'B' ASCII
    sw x6, 0(x5)
    
    # 写入 '\n'
    li x6, 10              # newline
    sw x6, 0(x5)
    
    # 结束: tohost = 1
    li x5, 0x80001000
    li x6, 1
    sw x6, 0(x5)

end:
    j end
```

- [ ] **Step 2: 编译为 hex**

Run: `riscv64-unknown-elf-gcc -march=rv32i_zicsr -nostdlib -Ttext=0x80000000 -o bare_metal_uart.elf tests/assembly/bare_metal_uart.s && riscv64-unknown-elf-objcopy -O verilog bare_metal_uart.elf firmware/bare_metal_uart.hex`
Expected: 生成 firmware/bare_metal_uart.hex

- [ ] **Step 3: 转换为 BSV**

Run: `python3 tools/hex_to_bsv.py firmware/bare_metal_uart.hex > src/soc/TestProgram.bsv`
Expected: 生成 TestProgram.bsv

- [ ] **Step 4: 运行仿真**

Run: `make compile && rm -rf obj_dir && verilator --cc --exe --build -o VmkTestBench build/mkTestBench.v /opt/bsc/lib/Verilog/FIFO2.v tests/c/test_bench.cpp -Wno-STMTDLY -Wno-WIDTH && ./obj_dir/VmkTestBench`
Expected: UART 输出 "AB\n"，测试 PASSED

- [ ] **Step 5: Commit**

```bash
git add tests/assembly/bare_metal_uart.s firmware/bare_metal_uart.hex src/soc/TestProgram.bsv
git commit -m "test: add UART TX putchar bare-metal test

Co-Authored-By: Claude Opus 4.7 <noreply@anthropic.com>"
```

---

### Task 4: mtime 单调递增测试

**Files:**
- Create: `tests/assembly/bare_metal_mtime.s`

- [ ] **Step 1: 编写 mtime 测试汇编**

```asm
# tests/assembly/bare_metal_mtime.s
# mtime 单调递增 + 64位读取测试

.section .text
.global _start

_start:
    # 读取 mtime_lo (0x0200BFF8)
    li x5, 0x0200BFF8
    lw x6, 0(x5)           # mtime_lo
    
    # 等待几个周期
    li x7, 100
wait1:
    addi x7, x7, -1
    bne x7, x0, wait1
    
    # 再次读取 mtime_lo
    lw x8, 0(x5)
    
    # 检查 mtime 是否增加 (x8 > x6)
    blt x8, x6, fail       # 如果没增加，失败
    
    # 读取 mtime_hi (0x0200BFFC)
    li x5, 0x0200BFFC
    lw x9, 0(x5)           # mtime_hi
    
    # 组合 64位值检查非零
    or x10, x6, x9         # 低32位 OR 高32位
    beq x10, x0, fail      # 如果都是0，失败
    
    # 成功
    li x5, 0x80001000
    li x6, 1
    sw x6, 0(x5)
    j end

fail:
    li x5, 0x80001000
    li x6, 2               # 失败码
    sw x6, 0(x5)

end:
    j end
```

- [ ] **Step 2: 编译、转换、运行**

Run: 
```bash
riscv64-unknown-elf-gcc -march=rv32i_zicsr -nostdlib -Ttext=0x80000000 -o bare_metal_mtime.elf tests/assembly/bare_metal_mtime.s
riscv64-unknown-elf-objcopy -O verilog bare_metal_mtime.elf firmware/bare_metal_mtime.hex
python3 tools/hex_to_bsv.py firmware/bare_metal_mtime.hex > src/soc/TestProgram.bsv
make test
```
Expected: PASSED (tohost=1)

- [ ] **Step 3: Commit**

```bash
git add tests/assembly/bare_metal_mtime.s firmware/bare_metal_mtime.hex src/soc/TestProgram.bsv
git commit -m "test: add mtime monotonic increment bare-metal test

Co-Authored-By: Claude Opus 4.7 <noreply@anthropic.com>"
```

---

### Task 5: mtimecmp 触发 MTIP 测试

**Files:**
- Create: `tests/assembly/bare_metal_timer.s`
- Modify: `src/peripheral/CLINT.bsv` (确保 MTIP 触发)

- [ ] **Step 1: 检查 CLINT MTIP 实现**

检查 `src/peripheral/CLINT.bsv` 中：
- mtime 每周期自增
- MTIP = (mtime >= mtimecmp)
- mtimecmp 地址正确 (0x02004000/0x02004004)

如果不符合，修改：

```bsv
// src/peripheral/CLINT.bsv
rule increment_mtime;
    mtime <= mtime + 1;
endrule

// MTIP 触发
method Bool timerIRQ();
    return mtime >= mtimecmp;
endmethod
```

- [ ] **Step 2: 编写 timer 中断测试汇编**

```asm
# tests/assembly/bare_metal_timer.s
# mtimecmp 触发 MTIP 测试

.section .text
.global _start

_start:
    # 设置 mie.MTIE (bit 7) = 1
    li x5, 0x304           # mie CSR 地址
    li x6, 0x80            # bit 7
    csrw mie, x6
    
    # 设置 mstatus.MIE (bit 3) = 1
    li x5, 0x300           # mstatus CSR 地址
    li x6, 0x8             # bit 3
    csrw mstatus, x6
    
    # 设置 mtvec (Direct mode, 基地址 0x80000100)
    li x5, 0x80000100
    csrw mtvec, x5
    
    # 设置 mtimecmp = mtime + 100 (触发点)
    li x5, 0x0200BFF8      # mtime_lo
    lw x6, 0(x5)           # 读当前 mtime_lo
    addi x6, x6, 100       # +100
    
    # 三步安全更新 mtimecmp
    li x5, 0x02004004      # mtimecmp_hi
    li x7, 0xFFFFFFFF
    sw x7, 0(x5)           # Step 1: 设低位最大
    
    li x7, 0
    sw x7, 0(x5)           # Step 2: 高位 = 0
    
    li x5, 0x02004000      # mtimecmp_lo
    sw x6, 0(x5)           # Step 3: 低位置目标值
    
    # 等待中断触发
    li x7, 1000
wait:
    addi x7, x7, -1
    bne x7, x0, wait
    
    # 如果没触发中断，失败
    li x5, 0x80001000
    li x6, 2
    sw x6, 0(x5)
    j end

# trap handler (地址 0x80000100)
.org 0x80000100
trap_handler:
    # 检查 mcause 是否是 timer interrupt
    csrr x5, mcause
    li x6, 0x80000007      # interrupt=1, cause=7
    bne x5, x6, trap_fail
    
    # 成功，tohost = 1
    li x5, 0x80001000
    li x6, 1
    sw x6, 0(x5)
    mret

trap_fail:
    li x5, 0x80001000
    li x6, 3
    sw x6, 0(x5)
    mret

.org 0x80000000 + 32
end:
    j end
```

- [ ] **Step 3: 编译、运行**

```bash
riscv64-unknown-elf-gcc -march=rv32i_zicsr -nostdlib -Ttext=0x80000000 -o bare_metal_timer.elf tests/assembly/bare_metal_timer.s
riscv64-unknown-elf-objcopy -O verilog bare_metal_timer.elf firmware/bare_metal_timer.hex
python3 tools/hex_to_bsv.py firmware/bare_metal_timer.hex > src/soc/TestProgram.bsv
make test
```
Expected: PASSED (tohost=1)，中断触发，mcause = 0x80000007

- [ ] **Step 4: Commit**

```bash
git add tests/assembly/bare_metal_timer.s firmware/bare_metal_timer.hex src/soc/TestProgram.bsv src/peripheral/CLINT.bsv
git commit -m "test: add timer interrupt (MTIP) bare-metal test

Co-Authored-By: Claude Opus 4.7 <noreply@anthropic.com>"
```

---

### Task 6: trap + mret 返回测试

**Files:**
- Create: `tests/assembly/bare_metal_trap.s`
- Modify: `src/core/Core.bsv` (确保 trap 语义完整)

- [ ] **Step 1: 检查 Core trap 语义**

检查 `src/core/Core.bsv`：
- mepc 设置正确（中断：恢复点 PC；异常：faulting PC）
- mcause 最高位 = interrupt flag
- mstatus.MPIE ← MIE, MIE ← 0
- mret: MIE ← MPIE, PC ← mepc

如果不符合设计规范，修改 executeStage 中的 trap 处理逻辑。

- [ ] **Step 2: 编写 trap+mret 测试汇编**

```asm
# tests/assembly/bare_metal_trap.s
# trap 入口 + mret 返回测试

.section .text
.global _start

_start:
    # 设置 mtvec
    li x5, 0x80000100
    csrw mtvec, x5
    
    # 设置 mstatus.MIE = 1
    li x5, 0x8
    csrw mstatus, x5
    
    # 保存预期返回地址
    la x10, after_ecall
    
    # 执行 ecall 触发 trap
    ecall
    
    # ecall 返回后应该到这里
after_ecall:
    # 检查是否正确返回
    la x11, after_ecall
    bne x10, x11, fail     # 地址不一致则失败
    
    # 检查 mepc 是否是 ecall 指令地址
    csrr x5, mepc
    la x6, ecall_addr
    bne x5, x6, fail
    
    # 检查 mstatus.MIE 是否恢复
    csrr x5, mstatus
    andi x5, x5, 0x8       # 检查 bit 3
    beq x5, x0, fail       # 如果 MIE=0，失败
    
    # 成功
    li x5, 0x80001000
    li x6, 1
    sw x6, 0(x5)
    j end

ecall_addr:
    ecall                  # 这个标签用于 mepc 检查

fail:
    li x5, 0x80001000
    li x6, 2
    sw x6, 0(x5)

end:
    j end

# trap handler (地址 0x80000100)
.org 0x80000100
trap_handler:
    # 检查 mcause (exception, cause=11 for ecall)
    csrr x5, mcause
    li x6, 11              # environment call from M-mode
    bne x5, x6, trap_fail
    
    # 设置 mepc 为返回地址 (跳过 ecall)
    csrr x5, mepc
    addi x5, x5, 4         # 跳过 ecall 指令
    csrw mepc, x5
    
    mret

trap_fail:
    li x5, 0x80001000
    li x6, 3
    sw x6, 0(x5)
    mret
```

- [ ] **Step 3: 编译、运行**

```bash
riscv64-unknown-elf-gcc -march=rv32i_zicsr -nostdlib -Ttext=0x80000000 -o bare_metal_trap.elf tests/assembly/bare_metal_trap.s
riscv64-unknown-elf-objcopy -O verilog bare_metal_trap.elf firmware/bare_metal_trap.hex
python3 tools/hex_to_bsv.py firmware/bare_metal_trap.hex > src/soc/TestProgram.bsv
make test
```
Expected: PASSED (tohost=1)，ecall 触发 trap，mret 正确返回

- [ ] **Step 4: Commit**

```bash
git add tests/assembly/bare_metal_trap.s firmware/bare_metal_trap.hex src/soc/TestProgram.bsv src/core/Core.bsv
git commit -m "test: add trap entry + mret return bare-metal test

Co-Authored-By: Claude Opus 4.7 <noreply@anthropic.com>"
```

---

## Phase 6.2: Linker + Startup

### Task 7: 创建 Linker Script

**Files:**
- Create: `firmware/linker.ld`

- [ ] **Step 1: 编写 linker script**

```ld
/* firmware/linker.ld */
OUTPUT_ARCH(riscv)
ENTRY(_start)

MEMORY
{
    IMEM (rx)  : ORIGIN = 0x80000000, LENGTH = 32K
    DMEM (rwx) : ORIGIN = 0x80000000, LENGTH = 256K
}

SECTIONS
{
    .text : {
        *(.text)
        *(.text.*)
    } > IMEM
    
    .rodata : {
        *(.rodata)
        *(.rodata.*)
    } > DMEM
    
    .data : {
        *(.data)
        *(.data.*)
    } > DMEM
    
    .bss : {
        __bss_start = .;
        *(.bss)
        *(.bss.*)
        *(COMMON)
        __bss_end = .;
    } > DMEM
    
    .heap (NOLOAD) : {
        . = ALIGN(8);
        __heap_start = .;
        . = . + 16K;
        __heap_end = .;
    } > DMEM
    
    .stack (NOLOAD) : {
        . = ALIGN(8);
        __stack_bottom = .;
        . = . + 4K;  /* 4KB per task stack */
        __stack_top = .;
    } > DMEM
    
    /DISCARD/ : {
        *(.comment)
        *(.note*)
    }
}
```

- [ ] **Step 2: 验证 linker script**

创建简单 C 测试验证 linker：

```c
// firmware/test_linker.c
int global_var = 42;
const char msg[] = "Hello";

void _start() {
    volatile int *uart = (volatile int*)0x10000000;
    *uart = 'O';
    *uart = 'K';
    
    // 结束
    volatile int *tohost = (volatile int*)0x80001000;
    *tohost = 1;
    
    while(1);
}
```

编译：
```bash
riscv64-unknown-elf-gcc -march=rv32i_zicsr -nostdlib -T firmware/linker.ld -o test_linker.elf firmware/test_linker.c
riscv64-unknown-elf-objdump -h test_linker.elf
```
Expected: .text 在 0x80000000，.data/.bss 在 DMem 范围

- [ ] **Step 3: Commit**

```bash
git add firmware/linker.ld firmware/test_linker.c
git commit -m "feat: add linker script for FreeRTOS

Co-Authored-By: Claude Opus 4.7 <noreply@anthropic.com>"
```

---

### Task 8: 创建 Startup 代码

**Files:**
- Create: `firmware/startup.S`

- [ ] **Step 1: 编写 startup 汇编**

```asm
/* firmware/startup.S */
.section .text
.global _start
.type _start, @function

_start:
    /* 禁用中断 */
    csrw mie, zero
    
    /* 设置栈指针 */
    la sp, __stack_top
    
    /* 清零 .bss */
    la t0, __bss_start
    la t1, __bss_end
clear_bss:
    beq t0, t1, bss_done
    sw zero, 0(t0)
    addi t0, t0, 4
    j clear_bss
bss_done:
    
    /* 跳转到 main */
    call main
    
    /* main 返回后无限循环 */
halt:
    j halt

.size _start, . - _start
```

- [ ] **Step 2: 验证 startup**

用简单 main 函数测试：

```c
// firmware/test_startup.c
int main() {
    volatile int *uart = (volatile int*)0x10000000;
    *uart = 'S';
    *uart = 'U';
    *uart = 'P';
    
    volatile int *tohost = (volatile int*)0x80001000;
    *tohost = 1;
    
    return 0;
}
```

编译运行：
```bash
riscv64-unknown-elf-gcc -march=rv32i_zicsr -nostdlib -T firmware/linker.ld firmware/startup.S firmware/test_startup.c -o test_startup.elf
riscv64-unknown-elf-objcopy -O verilog test_startup.elf firmware/test_startup.hex
python3 tools/hex_to_bsv.py firmware/test_startup.hex > src/soc/TestProgram.bsv
make test
```
Expected: UART 输出 "SUP"，PASSED

- [ ] **Step 3: Commit**

```bash
git add firmware/startup.S firmware/test_startup.c
git commit -m "feat: add startup code with bss clear and stack init

Co-Authored-By: Claude Opus 4.7 <noreply@anthropic.com>"
```

---

## Phase 6.3: FreeRTOS 移植层

### Task 9: 获取 FreeRTOS 源码

**Files:**
- Download: `firmware/FreeRTOS/`

- [ ] **Step 1: 下载 FreeRTOS**

```bash
cd firmware
git clone --depth 1 https://github.com/FreeRTOS/FreeRTOS-Kernel.git FreeRTOS
```
Expected: FreeRTOS 源码在 firmware/FreeRTOS/

- [ ] **Step 2: 创建移植目录结构**

```bash
mkdir -p firmware/port
```

- [ ] **Step 3: Commit**

```bash
git add firmware/FreeRTOS firmware/port
git commit -m "feat: add FreeRTOS kernel source

Co-Authored-By: Claude Opus 4.7 <noreply@anthropic.com>"
```

---

### Task 10: 创建 portmacro.h

**Files:**
- Create: `firmware/port/portmacro.h`

- [ ] **Step 1: 编写 portmacro.h**

```c
/* firmware/port/portmacro.h */
#ifndef PORTMACRO_H
#define PORTMACRO_H

#include <stdint.h>

/* 数据类型定义 */
#define portSTACK_TYPE  uint32_t
#define portBASE_TYPE   int32_t
#define portUBASE_TYPE  uint32_t
#define portFLOAT_TYPE  float

typedef portSTACK_TYPE StackType_t;
typedef portBASE_TYPE BaseType_t;
typedef portUBASE_TYPE UBaseType_t;

/* 临界区 */
#define portENTER_CRITICAL()  \
    asm volatile("csrw mie, zero")

#define portEXIT_CRITICAL()   \
    asm volatile("csrw mie, %0" :: "r"(0x80))

/* 禁用/启用中断 */
#define portDISABLE_INTERRUPTS()  portENTER_CRITICAL()
#define portENABLE_INTERRUPTS()   portEXIT_CRITICAL()

/* yield */
#define portYIELD()  asm volatile("ecall")

/* 栈对齐 */
#define portSTACK_ALIGNMENT  16

/* tick 频率 */
#define portTICK_RATE_MS  (1000 / configTICK_RATE_HZ)

#endif /* PORTMACRO_H */
```

- [ ] **Step 2: Commit**

```bash
git add firmware/port/portmacro.h
git commit -m "feat(port): add portmacro.h type definitions

Co-Authored-By: Claude Opus 4.7 <noreply@anthropic.com>"
```

---

### Task 11: 创建 FreeRTOSConfig.h

**Files:**
- Create: `firmware/port/FreeRTOSConfig.h`

- [ ] **Step 1: 编写 FreeRTOSConfig.h**

```c
/* firmware/port/FreeRTOSConfig.h */
#ifndef FREERTOSCONFIG_H
#define FREERTOSCONFIG_H

/* 硬件配置 */
#define configCPU_CLOCK_HZ          (10000000)  /* 10 MHz (仿真) */
#define configTICK_RATE_HZ          (100)       /* 10ms tick */

/* 内存配置 */
#define configMINIMAL_STACK_SIZE    (128)       /* words */
#define configTOTAL_HEAP_SIZE       (16384)     /* bytes (16KB) */

/* 功能配置 */
#define configUSE_PREEMPTION        1
#define configUSE_IDLE_HOOK         0
#define configUSE_TICK_HOOK         0
#define configUSE_MALLOC_FAILED_HOOK 0

/* 调度器配置 */
#define configMAX_PRIORITIES        (5)
#define configUSE_TIME_SLICING      1
#define configUSE_TICKLESS_IDLE     0

/* 调试配置 */
#define configUSE_TRACE_FACILITY    0
#define configUSE_STATS_FORMATTING_FUNCTIONS 0

/* 优先级配置 */
#define configKERNEL_INTERRUPT_PRIORITY  0
#define configMAX_SYSCALL_INTERRUPT_PRIORITY 0

/* 包含 portmacro */
#include "portmacro.h"

#endif /* FREERTOSCONFIG_H */
```

- [ ] **Step 2: Commit**

```bash
git add firmware/port/FreeRTOSConfig.h
git commit -m "feat(port): add FreeRTOSConfig.h

Co-Authored-By: Claude Opus 4.7 <noreply@anthropic.com>"
```

---

### Task 12: 创建 port.c

**Files:**
- Create: `firmware/port/port.c`

- [ ] **Step 1: 编写 port.c**

```c
/* firmware/port/port.c */
#include "FreeRTOS.h"
#include "task.h"
#include "portmacro.h"

/* CLINT 地址 */
#define MTIME_LO       (*(volatile uint32_t*)0x0200BFF8)
#define MTIME_HI       (*(volatile uint32_t*)0x0200BFFC)
#define MTIMECMP_LO    (*(volatile uint32_t*)0x02004000)
#define MTIMECMP_HI    (*(volatile uint32_t*)0x02004004)

/* tick 周期 (时钟周期数) */
static const uint64_t tick_delta = configCPU_CLOCK_HZ / configTICK_RATE_HZ;

/* 获取 mtime 64位值 */
static inline uint64_t get_mtime(void) {
    uint32_t lo = MTIME_LO;
    uint32_t hi = MTIME_HI;
    return ((uint64_t)hi << 32) | lo;
}

/* 安全设置 mtimecmp (三步法) */
static inline void set_mtimecmp_safe(uint64_t val) {
    /* Step 1: 先设低位为最大值 */
    MTIMECMP_LO = 0xFFFFFFFF;
    /* Step 2: 更新高位 */
    MTIMECMP_HI = (uint32_t)(val >> 32);
    /* Step 3: 最后更新低位 */
    MTIMECMP_LO = (uint32_t)(val & 0xFFFFFFFF);
}

/* tick 初始化 */
void vPortSetupTick(void) {
    uint64_t first_tick = get_mtime() + tick_delta;
    set_mtimecmp_safe(first_tick);
    
    /* 启用 MTIE (bit 7) */
    uint32_t mie = 0x80;
    asm volatile("csrw mie, %0" :: "r"(mie));
    
    /* 启用全局中断 MIE (bit 3) */
    uint32_t mstatus = 0x8;
    asm volatile("csrs mstatus, %0" :: "r"(mstatus));
}

/* tick 中断处理 (由 portASM.S 调用) */
void xPortTimerHandler(void) {
    /* 重装下一次 tick */
    uint64_t next_tick = get_mtime() + tick_delta;
    set_mtimecmp_safe(next_tick);
    
    /* 调用 FreeRTOS tick 处理 */
    xTaskIncrementTick();
}

/* yield 处理 (由 portASM.S 调用) */
void vPortYieldHandler(void) {
    vTaskSwitchContext();
}

/* 临界区进入/退出已由 portmacro.h 定义 */

/* 启动首任务 (由 portASM.S 调用) */
void vPortStartFirstTask(void) {
    /* 设置 mtvec */
    uint32_t mtvec = (uint32_t)&vPortTrapHandler;
    asm volatile("csrw mtvec, %0" :: "r"(mtvec));
    
    /* 启用中断 */
    vPortSetupTick();
    
    /* 跳转到首任务 (由 vTaskStartScheduler 设置) */
    /* 实际由 portASM.S 完成 */
}

/* 堆管理 (使用 FreeRTOS heap_4.c) */
void* pvPortMalloc(size_t xSize);
void vPortFree(void* pv);
size_t xPortGetFreeHeapSize(void);
```

- [ ] **Step 2: Commit**

```bash
git add firmware/port/port.c
git commit -m "feat(port): add port.c tick and yield handlers

Co-Authored-By: Claude Opus 4.7 <noreply@anthropic.com>"
```

---

### Task 13: 创建 portASM.S

**Files:**
- Create: `firmware/port/portASM.S`

- [ ] **Step 1: 编写 portASM.S**

```asm
/* firmware/port/portASM.S */

.section .text
.global vPortTrapHandler
.global vPortStartFirstTaskASM
.global vPortYieldFromISR

/* 统一栈帧大小: 36 bytes (mepc + mstatus + x1-x31 除 x2) */
#define STACK_FRAME_SIZE 36

/* trap handler 入口 */
vPortTrapHandler:
    /* 保存上下文 */
    addi sp, sp, -STACK_FRAME_SIZE
    
    /* 保存 GPR (x1, x3-x31) */
    sw x1,  0(sp)
    sw x3,  4(sp)
    sw x4,  8(sp)
    sw x5,  12(sp)
    sw x6,  16(sp)
    sw x7,  20(sp)
    sw x8,  24(sp)
    sw x9,  28(sp)
    sw x10, 32(sp)
    sw x11, 36(sp)
    sw x12, 40(sp)
    sw x13, 44(sp)
    sw x14, 48(sp)
    sw x15, 52(sp)
    sw x16, 56(sp)
    sw x17, 60(sp)
    sw x18, 64(sp)
    sw x19, 68(sp)
    sw x20, 72(sp)
    sw x21, 76(sp)
    sw x22, 80(sp)
    sw x23, 84(sp)
    sw x24, 88(sp)
    sw x25, 92(sp)
    sw x26, 96(sp)
    sw x27, 100(sp)
    sw x28, 104(sp)
    sw x29, 108(sp)
    sw x30, 112(sp)
    sw x31, 116(sp)
    
    /* 保存 mstatus 和 mepc */
    csrr t0, mstatus
    sw t0, 120(sp)
    csrr t0, mepc
    sw t0, 124(sp)
    
    /* 检查 mcause 分发 */
    csrr t0, mcause
    srli t1, t0, 31       /* 最高位: interrupt flag */
    
    bnez t1, handle_interrupt
    
handle_exception:
    andi t0, t0, 0x1F     /* cause code */
    li t1, 11             /* ecall from M-mode */
    bne t0, t1, trap_error
    
    /* yield 处理 */
    call vPortYieldHandler
    j trap_return
    
handle_interrupt:
    andi t0, t0, 0x1F     /* cause code */
    li t1, 7              /* timer interrupt */
    bne t0, t1, trap_error
    
    /* timer tick 处理 */
    call xPortTimerHandler
    j trap_return
    
trap_error:
    /* 异常处理: 写 tohost = 0xDEAD */
    li t0, 0x80001000
    li t1, 0xDEAD
    sw t1, 0(t0)
    j trap_loop
    
trap_return:
    /* 恢复 mepc 和 mstatus */
    lw t0, 124(sp)
    csrw mepc, t0
    lw t0, 120(sp)
    csrw mstatus, t0
    
    /* 恢复 GPR */
    lw x1,  0(sp)
    lw x3,  4(sp)
    lw x4,  8(sp)
    lw x5,  12(sp)
    lw x6,  16(sp)
    lw x7,  20(sp)
    lw x8,  24(sp)
    lw x9,  28(sp)
    lw x10, 32(sp)
    lw x11, 36(sp)
    lw x12, 40(sp)
    lw x13, 44(sp)
    lw x14, 48(sp)
    lw x15, 52(sp)
    lw x16, 56(sp)
    lw x17, 60(sp)
    lw x18, 64(sp)
    lw x19, 68(sp)
    lw x20, 72(sp)
    lw x21, 76(sp)
    lw x22, 80(sp)
    lw x23, 84(sp)
    lw x24, 88(sp)
    lw x25, 92(sp)
    lw x26, 96(sp)
    lw x27, 100(sp)
    lw x28, 104(sp)
    lw x29, 108(sp)
    lw x30, 112(sp)
    lw x31, 116(sp)
    
    addi sp, sp, STACK_FRAME_SIZE
    mret

trap_loop:
    j trap_loop

/* 启动首任务 */
vPortStartFirstTaskASM:
    /* 设置 mtvec */
    la t0, vPortTrapHandler
    csrw mtvec, t0
    
    /* 启用 MTIE 和全局中断 */
    li t0, 0x80
    csrw mie, t0
    li t0, 0x8
    csrs mstatus, t0
    
    /* 从 pxCurrentTCB 获取任务栈 */
    /* 这里假设栈已伪造好，sp 已设置 */
    la t0, pxCurrentTCB
    lw sp, 0(t0)
    
    /* 从栈恢复 mepc 和 mstatus，跳到任务 */
    lw t1, 124(sp)        /* mepc */
    csrw mepc, t1
    lw t1, 120(sp)        /* mstatus */
    csrw mstatus, t1
    
    /* 恢复 GPR */
    lw x1,  0(sp)
    lw x3,  4(sp)
    lw x4,  8(sp)
    lw x5,  12(sp)
    lw x6,  16(sp)
    lw x7,  20(sp)
    lw x8,  24(sp)
    lw x9,  28(sp)
    lw x10, 32(sp)
    lw x11, 36(sp)
    lw x12, 40(sp)
    lw x13, 44(sp)
    lw x14, 48(sp)
    lw x15, 52(sp)
    lw x16, 56(sp)
    lw x17, 60(sp)
    lw x18, 64(sp)
    lw x19, 68(sp)
    lw x20, 72(sp)
    lw x21, 76(sp)
    lw x22, 80(sp)
    lw x23, 84(sp)
    lw x24, 88(sp)
    lw x25, 92(sp)
    lw x26, 96(sp)
    lw x27, 100(sp)
    lw x28, 104(sp)
    lw x29, 108(sp)
    lw x30, 112(sp)
    lw x31, 116(sp)
    
    addi sp, sp, STACK_FRAME_SIZE
    mret

/* yield from ISR */
vPortYieldFromISR:
    ecall
    ret
```

- [ ] **Step 2: Commit**

```bash
git add firmware/port/portASM.S
git commit -m "feat(port): add portASM.S trap handler and context switch

Co-Authored-By: Claude Opus 4.7 <noreply@anthropic.com>"
```

---

## Phase 6.4: FreeRTOS 验证

### Task 14: 创建 FreeRTOS Demo

**Files:**
- Create: `firmware/freertos_demo.c`

- [ ] **Step 1: 编写 demo 任务**

```c
/* firmware/freertos_demo.c */
#include "FreeRTOS.h"
#include "task.h"
#include "portmacro.h"

/* UART 地址 */
#define UART_TX (*(volatile uint32_t*)0x10000000)

/* 简单 putchar */
static void putchar(char c) {
    UART_TX = c;
}

static void puts(const char *s) {
    while (*s) {
        putchar(*s);
        s++;
    }
}

/* Task 1: 每 100ms 打印 */
void Task1(void *param) {
    (void)param;
    int count = 0;
    while (1) {
        puts("Task1: ");
        /* 简单数字打印 */
        int n = count;
        char buf[10];
        int i = 0;
        if (n == 0) buf[i++] = '0';
        else {
            while (n > 0) {
                buf[i++] = '0' + (n % 10);
                n /= 10;
            }
        }
        while (i > 0) putchar(buf[--i]);
        putchar('\n');
        
        count++;
        vTaskDelay(10);  /* 100ms (10 ticks) */
    }
}

/* Task 2: 每 500ms 打印 */
void Task2(void *param) {
    (void)param;
    while (1) {
        puts("Task2 running\n");
        vTaskDelay(50);  /* 500ms (50 ticks) */
    }
}

/* main */
int main() {
    puts("FreeRTOS Demo Start\n");
    
    xTaskCreate(Task1, "Task1", 128, NULL, 2, NULL);
    xTaskCreate(Task2, "Task2", 128, NULL, 1, NULL);
    
    vTaskStartScheduler();
    
    /* 不应该到达这里 */
    puts("Scheduler failed\n");
    while (1);
    
    return 0;
}
```

- [ ] **Step 2: 创建 Makefile**

```makefile
# firmware/Makefile
CC = riscv64-unknown-elf-gcc
AS = riscv64-unknown-elf-as
OBJCOPY = riscv64-unknown-elf-objcopy

CFLAGS = -march=rv32i_zicsr -nostdlib -O2 -I./FreeRTOS/include -I./port
ASFLAGS = -march=rv32i_zicsr
LDFLAGS = -T linker.ld

SRC = startup.S \
      port/portASM.S \
      port/port.c \
      FreeRTOS/tasks.c \
      FreeRTOS/list.c \
      FreeRTOS/queue.c \
      FreeRTOS/portable/MemMang/heap_4.c \
      freertos_demo.c

OBJ = $(SRC:.c=.o)
OBJ := $(OBJ:.S=.o)

TARGET = freertos_demo.elf

all: $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.S
	$(CC) $(ASFLAGS) -c $< -o $@

$(TARGET): $(OBJ)
	$(CC) $(LDFLAGS) $(OBJ) -o $(TARGET)
	$(OBJCOPY) -O verilog $(TARGET) freertos_demo.hex

clean:
	rm -f $(OBJ) $(TARGET) freertos_demo.hex
```

- [ ] **Step 3: 编译 FreeRTOS demo**

```bash
cd firmware
make
```
Expected: 生成 freertos_demo.elf 和 freertos_demo.hex

- [ ] **Step 4: 运行仿真**

```bash
python3 tools/hex_to_bsv.py firmware/freertos_demo.hex > src/soc/TestProgram.bsv
make test
```
Expected: 
- UART 输出 "FreeRTOS Demo Start"
- Task1 每 100ms 打印计数
- Task2 每 500ms 打印 "Task2 running"
- 仿真持续运行（无 timeout）

- [ ] **Step 5: Commit**

```bash
git add firmware/freertos_demo.c firmware/Makefile firmware/freertos_demo.hex src/soc/TestProgram.bsv
git commit -m "feat: add FreeRTOS demo with dual-task scheduling

Co-Authored-By: Claude Opus 4.7 <noreply@anthropic.com>"
```

---

### Task 15: 长期稳定性测试

**Files:**
- Modify: `tests/c/test_bench.cpp` (增加周期限制)

- [ ] **Step 1: 增加仿真周期**

```cpp
// tests/c/test_bench.cpp
uint64_t max_cycles = 500000;  // 增加到 500K cycles (约 50s @10MHz)
```

- [ ] **Step 2: 运行长期测试**

```bash
make test
```
Expected: 
- FreeRTOS 运行 500K cycles 无卡死
- Task1 打印约 5000 次
- Task2 打印约 1000 次

- [ ] **Step 3: 检查栈安全**

在 demo 中添加栈检查代码：

```c
// 添加到 Task1
static void check_stack(void) {
    extern char __stack_bottom;
    extern char __stack_top;
    if ((char*)sp < &__stack_bottom || (char*)sp > &__stack_top) {
        puts("STACK OVERFLOW!\n");
    }
}
```

- [ ] **Step 4: Commit**

```bash
git add tests/c/test_bench.cpp
git commit -m "test: extend simulation cycles for FreeRTOS stability test

Co-Authored-By: Claude Opus 4.7 <noreply@anthropic.com>"
```

---

## 验收标准汇总

| Phase | 任务 | 验收标准 |
|-------|------|----------|
| 6.1 | Task 1-6 | 5 个 bare-metal 测试全部 PASSED |
| 6.2 | Task 7-8 | C 程序执行，UART 输出正确 |
| 6.3 | Task 9-13 | FreeRTOS 编译链接成功 |
| 6.4 | Task 14-15 | 双任务调度正常，500K cycles 无故障 |

---

## 风险控制

| 风险 | 缓解措施 | 任务 |
|------|----------|------|
| BSC 编译 OOM | 大内存用 Verilog 直接定义 | Task 2 |
| mtimecmp 中间态触发 | 三步安全更新 | Task 5 |
| 任务栈帧不一致 | portASM.S 精确布局 | Task 13 |
| mepc 计算错误 | Core.bsv trap 语义完善 | Task 6 |

---

*计划日期: 2026-04-19*