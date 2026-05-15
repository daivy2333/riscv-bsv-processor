# RISC-V BSV 五级流水线处理器 + C 编译器

基于 Bluespec SystemVerilog 实现的 RISC-V RV32I 五级流水线处理器，配套自研 C 编译器，实现 **C 源码 → 编译器 → CPU 执行** 的完整工具链闭环。

## 项目成果

| 成果 | 状态 |
|------|------|
| **CPU** | 12 个汇编测试通过 ✓ |
| **编译器** | 40+ 个 C 语言测试通过 ✓ |
| **工具链闭环** | C 源码编译后在自造 CPU 上运行 ✓ |

## 特性

### CPU

- 五级流水线 (IF → ID → EX → MEM → WB)
- 数据前递 (MEM→EX, WB→EX, WB→ID)
- Load-Use 冒险检测 + Stall
- 动态分支预测 (BHT 64条目 + BTB 64条目)
- RV32I 全指令集 + Zicsr 扩展
- 定时器中断 (CLINT)
- UART 输出

### 编译器

- **4888 行源码** 实现完整 Micro-C 编译器
- 支持：int/char/void/struct/数组/指针
- 支持：volatile/const/static/typedef/extern
- 支持：if/else/while/for/函数调用/递归
- 支持：#include/#define/#ifdef 预处理器
- 目标：RV32I 机器码，在自造 CPU 上运行

## 项目结构

```
riscv-bsv-processor/
├── src/                  BSV 源码（CPU 核心）
│   ├── core/             五级流水线核心
│   ├── branch/           分支预测 (BHT/BTB)
│   ├── peripheral/       CLINT, PLIC, UART
│   └── soc/              SOC 集成
├── rv32i-compiler/       ★ C 编译器子项目
│   ├── src/              编译器源码（4888 行）
│   │   ├── lexer.c       词法分析
│   │   ├── parser.c      语法分析（1378行）
│   │   ├── codegen.c     代码生成（982行）
│   │   └── asm.c         汇编器（1002行）
│   ├── tests/            C 语言测试（40+ 个）
│   └── runtime/          启动代码 + 软件算术库
├── tests/
│   ├── assembly/         汇编测试（12 个）
│   └ c/                  Verilator 仿真驱动
├── tools/
│   └── hex_to_bsv.py     hex → TestProgram.bsv 转换
└── docs/                 设计文档
```

## 快速开始

### 环境要求

- BSC (Bluespec Compiler)
- riscv64-unknown-elf-gcc
- Verilator
- GCC (用于编译编译器)

### CPU 测试

```bash
make test-all      # 运行全部 CPU 测试
make clean         # 清理
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
    ↓ rv32i-compiler/microcc（编译器）
RV32I 机器码 (.hex)
    ↓ tools/hex_to_bsv.py（转换工具）
TestProgram.bsv
    ↓ BSC 编译
Verilog 仿真
    ↓ Verilator
CPU 执行
    ↓ tohost 写入
测试结果验证 ✓
```

## 测试结果

### CPU 汇编测试 (12个全部通过)

| 测试 | 验证内容 | 结果 |
|------|----------|------|
| loop_test | 循环 + 分支预测 | ✓ |
| simple_arith_test | 基本算术 | ✓ |
| load_test | Load-Use 冒险 | ✓ |
| csr_basic_test | CSR 读写 | ✓ |
| privilege_m_mode_test | M-mode CSR | ✓ |
| csr_immediate_test | CSRRWI/CSRRSI | ✓ |
| rtype_complete_test | R-Type 全指令 | ✓ |
| itype_alu_test | I-Type ALU | ✓ |
| simple_branch_test | 分支执行 | ✓ |
| simple_loop | 循环计数 | ✓ |
| mtime_increment_verify | mtime 递增 | ✓ |
| mtimecmp_mtip_test | 定时器中断 | ✓ |

### 编译器 C 测试 (40+ 个全部通过)

**Phase 1-9**: 算术、控制流、函数、指针、数组、全局变量、结构体、多文件、预处理器

**Phase 10**:

| 测试 | 功能 | 结果 |
|------|------|------|
| volatile_test.c | volatile 变量 | ✓ tohost=42 |
| const_test.c | const 变量 | ✓ tohost=15 |
| void_test.c | void 函数 | ✓ tohost=42 |
| typedef_test.c | typedef 别名 | ✓ tohost=30 |
| static_test.c | static 全局变量 | ✓ tohost=7 |
| integration_test.c | 综合测试 | ✓ tohost=31 |

## 架构概览

### CPU 流水线

```
IF → ID → EX → MEM → WB
```

| 阶段 | 功能 | 关键模块 |
|------|------|----------|
| IF | 取指 + 分支预测 | BHT(64)/BTB(64) |
| ID | 解码 + 冒险检测 | Decoder/HazardUnit |
| EX | ALU + CSR + Trap | ALU + CSR |
| MEM | 内存访问 + tohost | DMem |
| WB | 写回 + 中断处理 | RegFile |

### 编译器流水线

```
C 源码
    ↓ 预处理器 (#include/#define/#ifdef)
预处理文本
    ↓ 词法分析 (Lexer)
Token 流
    ↓ 语法分析 (Parser)
AST
    ↓ 代码生成 (Codegen)
RV32I 汇编
    ↓ 汇编器 (Assembler)
机器码 (.hex)
```

## 开发阶段

### CPU 阶段 1-8（完成）

1. ✓ 五级流水线 + 数据前递
2. ✓ Load-Use 冒险处理
3. ✓ 分支预测
4. ✓ RV32I 全指令集
5. ✓ CSR + 特权指令
6. ✓ SOC 架构 + 外设
7. ✓ 控制流重定向协议
8. ✓ 定时器中断

### 编译器 Phase 1-10（完成）

1. ✓ Lexer + Parser
2. ✓ 算术运算
3. ✓ 控制流
4. ✓ 函数调用
5. ✓ 指针
6. ✓ 数组
7. ✓ 全局变量 + 字符串
8. ✓ 结构体
9. ✓ 多文件 + 预处理器
10. ✓ volatile/const/void/typedef/static

## 文档

- `docs/architecture.md` - CPU 流水线架构
- `rv32i-compiler/CLAUDE.md` - 编译器项目指南
- `rv32i-compiler/.claude/docs/` - 编译器开发文档

## 许可证

MIT License