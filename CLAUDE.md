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

### 已知问题

1. **Load-Use冒险**: lw紧跟sw/其他指令时可能有结构冒险，MEM阶段同时进行load/store和lw读取可能冲突
2. **ELF加载工具**: `tools/elf_to_bsv.py` 还在开发中，有解析问题需要修复
3. **内存边界**: dmem是512字(2KB)，lw使用addr[10:2]索引，需要确保地址 < 2048

### 待完成功能

1. **完善Load-Use停顿机制**: 需要在MEM阶段正确检测并处理Load-Use冒险
2. **ELF程序加载**: 修复`tools/elf_to_bsv.py`实现从ELF文件加载程序
3. **更多RISC-V指令**: SUB, SLL, SRL, SRA, SLT, SLTU, AND, OR, XOR等
4. **ecall处理**: 实现系统调用支持

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

1. 完善Load-Use停顿机制
2. 修复并测试ELF加载功能
3. 添加更多RISC-V指令支持
4. 实现异常和中断处理
5. 添加性能计数器
