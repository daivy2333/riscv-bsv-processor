# 项目快照

> 最后更新：2026-05-15

## 当前状态

- **阶段**: Phase 1-10 ✅ 全部完成
- **状态**: 所有测试通过，编译器具备自举所需特性
- **下一步**: 预处理器增强（支持 `#include <file>` 系统头文件）

## 项目结构

```
rv32i-compiler/
├── CLAUDE.md              项目入口文档
├── Makefile               构建系统（含 phase1-10 测试目标）
├── .claude/
│   └── docs/              文档体系 (7份)
├── src/
│   ├── main.c             入口，驱动各阶段（支持多文件输入）
│   ├── preprocess.h       预处理器接口声明
│   ├── preprocessor.c     预处理器实现（#include/#define/#ifdef）
│   ├── lexer.c/h          词法分析 (含 volatile/const/void/typedef/static)
│   ├── parser.c/h         语法分析 (typedef别名表、static声明)
│   ├── ast.c/h            AST节点定义 (含 is_static字段)
│   ├── codegen.c/h        代码生成 (.Lstatic_标签、隐式返回)
│   ├── asm.c/h            汇编器 (二遍 全RV32I指令集)
│   ├── linker.c/h         链接器 (linker_link_multi 多文件拼接)
│   └── types.c/h          类型系统 (is_const/is_volatile, TYPE_VOID)
├── runtime/
│   ├── crt0.s             启动代码 (栈 4096 字节)
│   └── lib.S              运行时算术库
├── tests/
│   ├── test.c             回归测试
│   ├── phase2/            阶段2测试 (7个)
│   ├── phase3/            阶段3测试 (6个)
│   ├── phase4/            阶段4测试 (4个)
│   ├── phase5/            阶段5测试 (1个)
│   ├── phase6/            阶段6测试 (1个)
│   ├── phase7/            阶段7测试 (5个)
│   ├── phase8/            阶段8测试 (2个)
│   ├── phase9/            阶段9测试 (多文件+预处理)
│   └── phase10/           阶段10测试 (volatile/const/void/typedef/static)
└── build/
    ├── microcc            编译器可执行文件 (4888行源码)
    ├── test.hex           编译产出hex
    ├── *_*.hex            各测试hex
    └── _*_*.s             中间汇编文本
```

## 技术栈

| 类别 | 技术 | 说明 |
|------|------|------|
| 实现语言 | C (Micro-C 子集) | 4888行，自举准备完成 |
| 目标 ISA | RV32I + Zicsr | 32-bit, 无浮点/乘除法 |
| 预处理器 | #include/#define/#ifdef/#ifndef/#else/#endif | 递归文件包含、宏替换、条件编译栈 |
| 类型限定符 | volatile/const | 标记位，无 codegen 影响 |
| 存储类 | extern/static/typedef | extern跳过生成、static用.Lstatic_标签 |
| void 支持 | void返回、void(void)参数、空return | parse_type统一处理 |
| typedef | 结构体别名 | typedef_alias表 + lookup |
| 多文件编译 | linker_link_multi | 多汇编文件拼接 + 统一汇编 |
| 寄存器分配 | 栈溢出 + 4级溢出槽 | 阶段1-3使用，阶段4+引入寄存器分配 |
| 乘除法 | 软件例程 (lib.S) | CPU无M扩展 |
| 函数调用 | RISC-V ABI (a0-a7, jal, a0返回) | 递归支持，独立栈帧 |
| 栈空间 | crt0.s 4096 字节 | 支持 fib(10) 递归 90+ 深度 |
| 汇编器 | 二遍 + 标签解析 | 支持R/I/S/B/U/J全指令格式 |
| 类型系统 | base_type + ptr_level + array_size + struct_id + is_const + is_volatile | 完整类型信息 |
| 结构体 | StructInfo + MemberInfo | 全局结构体表 + 成员偏移计算 |
| 比较运算 | slt/slti + xor/sub | 支持 <, <=, >, >=, ==, != |
| 测试验证 | CPU TestBench | tohost机制 (0x80001000) |
| 编译器输出 | Verilog hex | 小端字节序，用于hex_to_bsv.py |

## Git 状态

- **当前分支**: main
- **父项目**: ../ (riscv-bsv-processor)
- **状态**: 阶段1-10完成，40+个测试全部通过
- **最近提交**: Phase 10 完成待提交

## 编译器流水线

```
源文件(.c)
  ↓ Preprocessor (pp_process: #include展开 + 宏替换 + 条件编译过滤)
预处理文本
  ↓ Lexer (tokenize + volatile/const/void/typedef/static关键字)
Token流 (含 if/else/while/for/++/lt/and/bracket/struct/arrow/extern/volatile/const/void/typedef/static 共36种标记)
  ↓ Parser (parse_type统一类型解析 + typedef别名表 + static声明)
AST (FUNC_DEF, FUNC_DECL, RETURN, INT_LIT, BIN_OP, VAR_DECL, VAR_REF, ASSIGN, IF, WHILE, NOOP, ADDR, DEREF, ARRAY_ACCESS, STRUCT_DEF, MEMBER_ACCESS, EXTERN_DECL, TYPEDEF_DEF)
  ↓ Codegen (符号表 + .Lstatic_标签 + 隐式返回 + volatile/const跳过)
RV32I汇编文本 (含 .L0/.L1/.Lstatic_ 标签和 beqz/j 分支)
  ↓ Linker (linker_link_multi: 拼接所有 .s + crt0 + lib → 一次汇编)
二进制words (uint32_t[])
  ↓ Assembler (二遍：标签解析+指令编码)
Flat binary (小端)
  ↓ 输出hex格式
.hex (用于CPU TestBench)
```

## 关键文件

| 文件 | 作用 | 状态 |
|------|------|------|
| `src/preprocessor.c` | 预处理器（#include/#define/#ifdef） | ✅ Phase 8-9 |
| `src/lexer.c` | 字符流 → Token 流（含 volatile/const/void/typedef/static） | ✅ Phase 10 |
| `src/parser.c` | Token 流 → AST（parse_type + typedef别名 + static） | ✅ Phase 10 |
| `src/codegen.c` | AST → 汇编（.Lstatic_ + 隐式返回） | ✅ Phase 10 |
| `src/types.h` | 类型系统（is_const/is_volatile + TYPE_VOID） | ✅ Phase 10 |
| `src/ast.h` | AST 节点（is_static字段） | ✅ Phase 10 |
| `src/linker.c` | linker_link_multi 多文件拼接 | ✅ Phase 9 |
| `src/main.c` | 多文件编译驱动 | ✅ Phase 9 |
| `src/asm.c` | 二遍汇编器 | ✅ Phase 2 |
| `runtime/crt0.s` | 启动代码 | ✅ Phase 1 |
| `runtime/lib.S` | 运行时算术库 | ✅ Phase 2 |
| `build/microcc` | 编译器可执行文件 | ✅ 可运行 |

## 验证结果

### 回归测试（阶段1）
- `int main() { return 42; }` → tohost=42 ✅

### 阶段2-9测试（30+个全部通过）
详见各阶段测试目录。

### 阶段10测试（8个全部通过）
| 测试 | 功能 | tohost | 状态 |
|------|------|--------|------|
| volatile_test.c | volatile 变量 | 42 | ✅ |
| const_test.c | const 变量 | 15 | ✅ |
| volatile_const.c | volatile+const 组合 | 5 | ✅ |
| void_test.c | void 函数返回 | 42 | ✅ |
| void_param_test.c | void(void) 参数 | 15 | ✅ |
| void_no_return.c | 空 return 语句 | 5 | ✅ |
| typedef_test.c | typedef 结构体别名 | 30 | ✅ |
| static_test.c | static 全局变量 | 7 | ✅ |
| integration_test.c | 综合测试 (全部特性) | 31 | ✅ |

## 自举状态

**已具备特性**: volatile、const、void、typedef、static（编译器源码使用的全部特性）

**当前限制**: 预处理器不支持 `#include <stdio.h>` 等系统头文件

**下一步**: 增强预处理器支持系统头文件，实现完整自举

## 代码量统计

- 总代码量: 4888 行
- 核心模块: parser.c (1378行), codegen.c (982行), asm.c (1002行)
- 辅助模块: preprocessor.c (540行), lexer.c (285行), types.c (87行)