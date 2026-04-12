# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

A RISC-V RV32I five-stage pipeline processor implemented in Bluespec SystemVerilog (BSV). Uses Verilator for simulation.

## Build Commands

```bash
# Compile BSV to Verilog
make compile

# Build and run Verilator simulation
rm -rf obj_dir && verilator --cc --exe --build -o VmkTestBench build/mkTestBench.v /opt/bsc/lib/Verilog/FIFO2.v tests/c/test_bench.cpp -Wno-STMTDLY -Wno-WIDTH

# Run simulation
./obj_dir/VmkTestBench

# Clean
make clean
```

## Toolchain Requirements

- **BSC** (Bluespec Compiler) - compiles .bsv files to Verilog
- **riscv64-unknown-elf-gcc** - compiles assembly tests to firmware
- **Verilator** - converts Verilog to C++ simulation

## Architecture

### 五级流水线

```
IF → ID → EX → MEM → WB
```

- **IF**: 指令获取 + 分支预测 (BHT/BTB)
- **ID**: 指令解码 + 寄存器读取
- **EX**: ALU执行 + 分支判断 + 数据前递
- **MEM**: 内存访问
- **WB**: 寄存器写回

### 模块结构

- `src/core/Core.bsv` - 五级流水线核心
- `src/core/ALU.bsv` - 算术逻辑单元
- `src/core/RegFile.bsv` - 32个通用寄存器
- `src/core/Decoder.bsv` - RISC-V指令解码
- `src/branch/BHT.bsv` - 分支历史表 (64条目, 2位饱和计数器)
- `src/branch/BTB.bsv` - 分支目标缓冲区 (64条目)
- `src/common/Types.bsv` - 类型定义和流水线数据包

### 已实现功能

- [x] 五级流水线 (IF, ID, EX, MEM, WB)
- [x] 数据前递 (EX→EX, MEM→EX, WB→EX)
- [x] 动态分支预测 (BHT + BTB)
- [x] 基本RISC-V指令 (ADD, ADDI, LUI, LW, SW, BEQ, BNE, JAL, JALR)
- [x] 哈佛架构 (分离IMem/DMem)
- [x] DecodedInstr use_rs1/use_rs2 字段（用于冒险检测）
- [x] Load-Use 冒险检测框架（ID阶段检测，气泡插入机制）

### 待验证功能

1. **Load-Use冒险修复验证**: 代码已实现，需要运行测试验证 x3=10, x4=20
2. **多指令依赖测试**: 验证 Load 后多条指令依赖的情况
3. **分支与Load-Use组合测试**: 验证 lw 后分支指令判断 Load 结果的场景

### Core 重构待完成项（详见 docs/superpowers/specs/2026-04-12-load-use-hazard-fix-design.md）

1. **HazardUnit 未被调用** - 已实例化但检测逻辑是内联的，未使用接口方法
2. **检测时机偏差** - 当前检查 id2ex（EX阶段），设计要求检查 ex2mem（MEM阶段）
3. **ID_EX_Packet 缺少 is_load** - 用 mem_op 判断，建议添加字段保持一致
4. **多指令依赖测试用例** - Task 4 的 sub 指令测试未添加

### 已知问题

1. **ELF加载工具**: `tools/elf_to_bsv.py` 还在开发中，有解析问题需要修复
2. **内存边界**: dmem是512字(2KB)，lw使用addr[10:2]索引，需要确保地址 < 2048

### 待完成功能

1. **Load-Use冒险最终验证**: 运行仿真确认实现正确
2. **ELF程序加载**: 修复`tools/elf_to_bsv.py`实现从ELF文件加载程序
3. **更多RISC-V指令**: SUB, SLL, SRL, SRA, SLT, SLTU, AND, OR, XOR等
4. **ecall处理**: 实现系统调用支持
5. **异常和中断处理**: 实现基本的异常处理机制
6. **性能计数器**: 添加 CPI、分支预测准确率等性能统计

### 测试程序格式

TestBench使用硬编码测试程序:
```bsv
function Vector#(1024, Word) testProgram();
    Vector#(1024, Word) prog = replicate(0);
    prog[0] = 32'h00a00093;    // li x1, 10
    prog[1] = 32'h01400113;    // li x2, 20
    // ...
    return prog;
endfunction
```

### 关键寄存器映射

- `imem[1024]` - 指令内存 (4KB)
- `dmem[512]` - 数据内存 (2KB), 使用addr[10:2]索引
- PC从0x80000000开始

### BSV Patterns

- Packages import with `import Types::*;`
- Modules use `mkReg`, `mkFIFO`, `mkRegFile` constructors
- FIFOs for pipeline registers: `FIFO#(PacketType)`
- `Vector#(n, Reg#(type))` for register arrays
- Structs use `deriving (Bits, Eq, FShow)`

## Memory Layout

- IMem starts at 0x80000000 (4KB)
- DMem: 512 words (2KB), indexed by addr[10:2]
- Test programs loaded at offset 0 in imem

## 后续方向

### 目标：支持嵌入式操作系统（FreeRTOS/uClinux）

详细路线图见：`docs/roadmap-embedded-os.md`

### 短期任务（阶段 1，1-2 周）
1. **验证 Load-Use 冒险修复** - 运行仿真确认实现正确
2. **添加 LB/LH/LBU/LHU 指令** - 字节/半字加载
3. **添加 SB/SH 指令** - 字节/半字存储
4. **扩展内存到 64KB**
5. **运行 RISC-V 官方测试**

### 中期任务（阶段 2-4，2-3 月）
- 特权级架构 (M/S/U mode)
- CSR 寄存器组
- 异常/中断陷入机制

### 长期目标（阶段 5-8，3-4 月）
- CLINT 定时器
- PLIC 中断控制器
- UART 控制台
- 内存扩展 (16MB)
- 首次启动 FreeRTOS/uClinux
