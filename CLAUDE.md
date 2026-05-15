# CLAUDE.md

Claude Code 项目指南。

## 项目概述

RISC-V RV32I 五级流水线处理器，使用 BSV 实现，Verilator 仿真。目标是支持 FreeRTOS/uClinux。

**当前状态**: 
- **CPU**: 阶段 1-8 全部完成，架构稳定，12 个测试全部通过 ✓
- **编译器**: Phase 1-10 全部完成，4888 行源码，40+ 测试通过 ✓
- **项目闭环**: CPU + 编译器 + 测试链完整，可从 C 源码编译到 CPU 执行

## 项目结构

```
riscv-bsv-processor/
├── src/                    BSV 源码（CPU 核心）
│   ├── core/               五级流水线核心
│   ├── soc/                SOC 集成 + 外设
│   ├── memory/             内存模块
│   ├── peripheral/         CLINT/PLIC/UART
│   └── branch/             分支预测
├── tests/
│   ├── assembly/           汇编测试（12 个）
│   └── c/                  Verilator test_bench.cpp
├── rv32i-compiler/         ★ C 编译器子项目
│   ├── src/                编译器源码（4888 行）
│   ├── tests/              C 语言测试（40+ 个）
│   ├── runtime/            启动代码 + 软件算术库
│   └── build/microcc       编译器可执行文件
├── tools/
│   └── hex_to_bsv.py       hex → TestProgram.bsv 转换
├── firmware/               汇编测试 hex 文件
└── docs/                   架构文档
```

## 快速开始

### CPU 测试

```bash
# 查看帮助
make help

# 运行所有测试
make test-all

# 编译并运行
make all && make run
```

### 编译器测试

```bash
cd rv32i-compiler

# 编译 C 源码
./build/microcc tests/test.c build/test.hex

# 返回 CPU 目录运行
cd ..
python3 tools/hex_to_bsv.py rv32i-compiler/build/test.hex > src/soc/TestProgram.bsv
make all && make run
```

## 完整工具链

```
C 源码 (.c)
    ↓ rv32i-compiler/microcc
RV32I 机器码 (.hex)
    ↓ tools/hex_to_bsv.py
TestProgram.bsv
    ↓ BSC 编译
Verilog 仿真
    ↓ Verilator
CPU 执行
    ↓ tohost 写入
测试结果验证
```

**工具链验证**: 从 C 源码 → CPU 执行全流程可用 ✓

## CPU 测试结果

### 基线测试（10个）

| 测试文件 | 验证内容 | 结果 |
|----------|----------|------|
| `loop_test.s` | 循环 + 分支预测 | ✓ PASSED |
| `simple_arith_test.s` | 基本算术 + li 指令 | ✓ PASSED |
| `load_test.s` | Load-Use 冒险 | ✓ PASSED |
| `csr_basic_test.s` | CSR 读写 | ✓ PASSED |
| `privilege_m_mode_test.s` | M-mode CSR 操作 | ✓ PASSED |
| `csr_immediate_test.s` | CSRRWI/CSRRSI/CSRRCI | ✓ PASSED |
| `rtype_complete_test.s` | R-Type 全指令集 | ✓ PASSED |
| `itype_alu_test.s` | 立即数 ALU 指令 | ✓ PASSED |
| `simple_branch_test.s` | 分支预测和执行 | ✓ PASSED |
| `simple_loop.s` | 循环计数 | ✓ PASSED |

### 定时器中断测试（2个）

| 测试文件 | 验证内容 | 结果 |
|----------|----------|------|
| `mtime_increment_verify.s` | mtime 每周期递增 | ✓ PASSED |
| `mtimecmp_mtip_test.s` | MTIP 定时器中断触发 | ✓ PASSED |

**CPU 总计**: 12 个汇编测试，全部通过 ✓

## 编译器测试结果

### Phase 1-9 测试（30+ 个）

基础功能：算术运算、控制流、函数调用、指针、数组、全局变量、结构体、多文件编译、预处理器

### Phase 10 测试（9个）

| 测试 | 功能 | tohost | 结果 |
|------|------|--------|------|
| volatile_test.c | volatile 变量 | 42 | ✓ |
| const_test.c | const 变量 | 15 | ✓ |
| void_test.c | void 函数 | 42 | ✓ |
| void_param_test.c | void(void) 参数 | 15 | ✓ |
| void_no_return.c | 空 return | 5 | ✓ |
| typedef_test.c | typedef 别名 | 30 | ✓ |
| static_test.c | static 全局变量 | 7 | ✓ |
| integration_test.c | 综合测试 | 31 | ✓ |

**编译器总计**: 40+ 个 C 语言测试，全部通过 ✓

## 编译器能力

### 支持的 C 特性

| 类别 | 特性 |
|------|------|
| **类型** | int, char, void, struct, 数组, 指针, typedef |
| **限定符** | volatile, const |
| **存储类** | extern, static, typedef |
| **控制流** | if/else, while, for, return (含空 return) |
| **表达式** | 算术、比较、逻辑、赋值、取地址 |
| **函数** | 定义、调用、递归、void 函数、extern 原型 |
| **结构体** | 定义、成员访问 (`.`/`->`) |
| **预处理器** | #include "file", #define, #ifdef/#endif |

### 不支持特性

- `#include <stdio.h>` 系统头文件（预处理器限制）
- 浮点数（CPU 无 FPU）
- 多级指针（仅一级）
- switch/case, union, enum

## CPU 架构要点

### 五级流水线

```
IF → ID → EX → MEM → WB
```

| 阶段 | 功能 | 关键模块 |
|------|------|----------|
| IF | 取指 + 分支预测 | BHT(64)/BTB(64) |
| ID | 解码 + 冒险检测 | Decoder/HazardUnit |
| EX | ALU 执行 + 前递 + CSR + 陷阱处理 | ALU + CSR |
| MEM | 内存访问 + tohost 检测 | DMem |
| WB | 寄存器写回 | RegFile |

### 已实现指令

| 类型 | 指令 | 状态 |
|------|------|------|
| R-Type | ADD, SUB, SLL, SRL, SRA, SLT, SLTU, AND, OR, XOR | ✓ |
| I-Type ALU | ADDI, SLTI, SLTIU, ANDI, ORI, XORI, SLLI, SRLI, SRAI | ✓ |
| I-Type Load | LB, LH, LW, LBU, LHU | ✓ |
| S-Type | SB, SH, SW | ✓ |
| B-Type | BEQ, BNE, BLT, BGE, BLTU, BGEU | ✓ |
| U-Type | LUI, AUIPC | ✓ |
| J-Type | JAL, JALR | ✓ |
| Zicsr | CSRRW, CSRRS, CSRRC, CSRRWI, CSRRSI, CSRRCI | ✓ |
| 特权 | ECALL, EBREAK, MRET | ✓ |

## 开发阶段

### CPU 阶段 1-8（全部完成）

1. ✓ 五级流水线 + 数据前递
2. ✓ Load-Use 冒险处理
3. ✓ 分支预测 + 预测失败处理
4. ✓ RV32I 全指令集
5. ✓ CSR + 特权指令 + 陷阱处理
6. ✓ SOC 架构 + 外设框架
7. ✓ 控制流重定向协议重构
8. ✓ 定时器中断支持

### 编译器 Phase 1-10（全部完成）

1. ✓ Lexer + Parser + 基本表达式
2. ✓ 算术运算与变量
3. ✓ 控制流 + 比较运算
4. ✓ 函数调用 + 递归
5. ✓ 指针基础
6. ✓ 数组
7. ✓ 全局变量 + 字符串 + char
8. ✓ 结构体 + 成员访问
9. ✓ 多文件编译 + 预处理器
10. ✓ volatile/const/void/typedef/static（自举准备）

## 项目成果

| 成果 | 状态 |
|------|------|
| RV32I CPU | 12 个测试通过 ✓ |
| C 编译器 | 40+ 个测试通过 ✓ |
| 工具链闭环 | C 源码 → CPU 执行 ✓ |
| 代码量 | CPU BSV + 编译器 C |

**下一步**: 预处理器增强（支持 `#include <stdio.h>`），实现编译器完整自举

## 相关文档

- `docs/architecture.md` - CPU 流水线架构
- `rv32i-compiler/CLAUDE.md` - 编译器项目指南
- `rv32i-compiler/.claude/docs/` - 编译器开发文档

---

请用"架构/协议审查"的方式分析 CPU/SoC 问题。