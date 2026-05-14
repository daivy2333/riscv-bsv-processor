# 项目快照

> 最后更新：2026-05-14

## 当前状态

- **阶段**: 阶段 1-7 ✅ 完成（全局变量与字符串支持）
- **状态**: 全局变量、字符串字面量验证通过 (5个测试)
- **下一步**: 阶段 8：结构体支持

## 项目结构

```
rv32i-compiler/
├── CLAUDE.md              项目入口文档
├── Makefile               构建系统（含 phase2/phase3/phase4/phase5/phase6 测试目标）
├── .claude/
│   └── docs/              文档体系 (7份)
├── src/
│   ├── main.c             入口，驱动各阶段
│   ├── lexer.c/h          词法分析 (含 func/param/comma/bracket 标记)
│   ├── parser.c/h         语法分析 (多参数函数、函数调用、语法糖、指针、数组)
│   ├── ast.c/h            AST节点定义 (含 AST_FUNC_CALL, AST_ADDR, AST_DEREF, AST_ARRAY_ACCESS)
│   ├── codegen.c/h        代码生成 (调用约定、参数溢出区、递归栈帧、指针、数组访问)
│   ├── asm.c/h            汇编器 (二遍 全RV32I指令集)
│   ├── linker.c/h         链接器 (拼接 crt0+lib+用户代码)
│   └── types.c/h          类型系统 (base_type, ptr_level, array_size)
├── runtime/
│   ├── crt0.s             启动代码 (栈 4096 字节)
│   └── lib.S              运行时算术库
├── tests/
│   ├── test.c             回归测试
│   ├── phase2/            阶段2测试 (a-g, 7个)
│   ├── phase3/            阶段3测试 (6个)
│   ├── phase4/            阶段4测试 (4个)
│   ├── phase5/            阶段5测试 (swap, 1个)
│   ├── phase6/            阶段6测试 (array, 1个)
│   └── phase7/            阶段7测试 (5个)
└── build/
    ├── microcc            编译器可执行文件
    ├── test.hex           编译产出hex
    ├── *_*.hex            各测试hex
    └── _*_*.s             中间汇编文本
```

## 技术栈

| 类别 | 技术 | 说明 |
|------|------|------|
| 实现语言 | C (Micro-C 子集) | 自举要求 |
| 目标 ISA | RV32I + Zicsr | 32-bit, 无浮点/乘除法 |
| 寄存器分配 | 栈溢出 + 4级溢出槽 | 阶段1-3使用，阶段4+引入寄存器分配 |
| 乘除法 | 软件例程 (lib.S) | CPU无M扩展 |
| 函数调用 | RISC-V ABI (a0-a7, jal, a0返回) | 递归支持，独立栈帧 |
| 栈空间 | crt0.s 4096 字节 | 支持 fib(10) 递归 90+ 深度 |
| 汇编器 | 二遍 + 标签解析 | 支持R/I/S/B/U/J全指令格式 |
| 类型系统 | base_type + ptr_level + array_size | 支持指针和数组类型 |
| 测试验证 | CPU TestBench | tohost机制 (0x80001000) |
| 编译器输出 | Verilog hex | 小端字节序，用于hex_to_bsv.py |

## Git 状态

- **当前分支**: main
- **父项目**: ../ (riscv-bsv-processor)
- **状态**: 阶段1-6完成，18个测试全部通过

## 编译器流水线

```
源文件(.c)
  ↓ Lexer (tokenize + 关键字识别 + ++多字符检测 + 括号)
Token流 (含 if/else/while/for/++/lt/and/bracket 等共22种标记)
  ↓ Parser (三级递归下降 + 控制流语法糖展开 + 指针 + 数组)
AST (FUNC_DEF, RETURN, INT_LIT, BIN_OP, VAR_DECL, VAR_REF, ASSIGN, IF, WHILE, NOOP, ADDR, DEREF, ARRAY_ACCESS)
  ↓ Codegen (符号表 + 标签生成 + 多级溢出槽 + 分支/跳转 + 指针操作 + 数组访问)
RV32I汇编文本 (含 .L0/.L1 标签和 beqz/j 分支)
  ↓ Assembler (二遍：标签解析+指令编码)
二进制words (uint32_t[])
  ↓ Linker (拼接 crt0.s + lib.S + 用户代码 → 一次汇编)
Flat binary (小端)
  ↓ 输出hex格式
.hex (用于CPU TestBench)
```

## 关键文件

| 文件 | 作用 | 状态 |
|------|------|------|
| `src/lexer.c` | 字符流 → Token 流 | ✅ 阶段6 |
| `src/parser.c` | Token 流 → AST（指针+数组解析） | ✅ 阶段6 |
| `src/ast.h` | AST 节点类型定义 | ✅ 阶段6 |
| `src/codegen.c` | AST → 汇编（指针+数组代码生成） | ✅ 阶段6 |
| `src/types.h` | 类型系统定义 | ✅ 阶段6 |
| `src/asm.c` | 二遍汇编器 | ✅ 阶段2 |
| `src/linker.c` | 拼接 crt0+lib+用户代码→hex | ✅ 阶段2 |
| `runtime/crt0.s` | 启动代码 | ✅ 阶段1 |
| `runtime/lib.S` | 运行时算术库 | ✅ 阶段2 |
| `build/microcc` | 编译器可执行文件 | ✅ 可运行 |

## 验证结果

### 回归测试（阶段1）
- `int main() { return 42; }` → tohost=42 ✅

### 阶段2测试（7个全部通过）
| 测试 | 代码 | tohost | 状态 |
|------|------|--------|------|
| A | `int x = 1 + 2; return x;` | 3 | ✅ |
| B | `int x = 10 - 3; return x;` | 7 | ✅ |
| C | `int x; x = 42; return x;` | 42 | ✅ |
| D | `int x = 1 + 2 + 3; return x;` | 6 | ✅ |
| E | `int a=5; int b=3; return a-b+2;` | 4 | ✅ |
| F | `int x = 3 * 5; return x;` | 15 | ✅ |
| G | `int x = 10 / 3; return x;` | 3 | ✅ |

### 阶段3测试（6个全部通过）
| 测试 | 代码 | tohost | 状态 |
|------|------|--------|------|
| precedence | `return 1+2*3;` | 7 | ✅ |
| if-true | `if(1) return 3; return 5;` | 3 | ✅ |
| if-false | `if(0) return 3; return 5;` | 5 | ✅ |
| if-else | `if(1) return 3; else return 5;` | 3 | ✅ |
| while | `i=0; while(i<3) i=i+1; return i;` | 3 | ✅ |
| for | `for(i=0;i<3;i++); return i;` | 3 | ✅ |

### 阶段4测试（4个全部通过）
| 测试 | 代码 | tohost | 状态 |
|------|------|--------|------|
| fib | `fib(10)` 递归斐波那契 | 55 | ✅ |
| add | `add(3, 5)` 多参数函数 | 8 | ✅ |
| call | `get42()` 无参调用 | 42 | ✅ |
| multi | `sum3(1, 2, 3)` 3参数调用 | 6 | ✅ |

### 阶段5测试（1个通过）
| 测试 | 代码 | tohost | 状态 |
|------|------|--------|------|
| swap | `swap(&x, &y)` 指针传参 | 2 | ✅ |

### 阶段6测试（1个通过）
| 测试 | 代码 | tohost | 状态 |
|------|------|--------|------|
| array | `arr_sum(arr, 5)` 数组求和 | 15 | ✅ |

### 阶段7测试（5个全部通过）
| 测试 | 代码 | tohost | 状态 |
|------|------|--------|------|
| global_int | `int g_count = 42; return g_count;` | 42 | ✅ |
| global_write | `int g_val; g_val = 100; return g_val;` | 100 | ✅ |
| global_expr | `int g_base = 10 + 5; return g_base;` | 15 | ✅ |
| string_arg | `strlen("hello")` | 5 | ✅ |
| string_assign | `char *g_msg = "world"; strlen(g_msg)` | 5 | ✅ |

## 下一步

- 阶段 8: 结构体支持（验证：简单结构体操作）