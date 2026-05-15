# 项目快照

> 最后更新：2026-05-15

## 当前状态

- **阶段**: 阶段 1-9 ✅ 全部完成（多文件编译与预处理器）
- **状态**: 所有测试通过，extern 变量引用已修复
- **下一步**: 阶段 10：自举准备（typedef/enum/volatile）

## 项目结构

```
rv32i-compiler/
├── CLAUDE.md              项目入口文档
├── Makefile               构建系统（含 phase1-9 测试目标）
├── .claude/
│   └── docs/              文档体系 (7份)
├── src/
│   ├── main.c             入口，驱动各阶段（支持多文件输入）
│   ├── preprocess.h       预处理器接口声明
│   ├── preprocessor.c     预处理器实现（#include/#define/#ifdef）
│   ├── lexer.c/h          词法分析 (含 extern/struct/arrow 标记)
│   ├── parser.c/h         语法分析 (多参数函数、extern 声明、函数原型)
│   ├── ast.c/h            AST节点定义 (含 AST_FUNC_DECL, AST_NOOP)
│   ├── codegen.c/h        代码生成 (调用约定、extern 跳过)
│   ├── asm.c/h            汇编器 (二遍 全RV32I指令集)
│   ├── linker.c/h         链接器 (linker_link_multi 多文件拼接)
│   └── types.c/h          类型系统 (base_type, ptr_level, array_size)
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
│   └── phase9/            阶段9测试 (多文件+预处理)
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
| 预处理器 | #include/#define/#ifdef/#ifndef/#else/#endif | 递归文件包含、宏替换、条件编译栈 |
| extern 支持 | TOK_EXTERN + parse_extern_decl | extern 声明不生成代码 |
| 多文件编译 | linker_link_multi | 多汇编文件拼接 + 统一汇编 |
| 寄存器分配 | 栈溢出 + 4级溢出槽 | 阶段1-3使用，阶段4+引入寄存器分配 |
| 乘除法 | 软件例程 (lib.S) | CPU无M扩展 |
| 函数调用 | RISC-V ABI (a0-a7, jal, a0返回) | 递归支持，独立栈帧 |
| 栈空间 | crt0.s 4096 字节 | 支持 fib(10) 递归 90+ 深度 |
| 汇编器 | 二遍 + 标签解析 | 支持R/I/S/B/U/J全指令格式 |
| 类型系统 | base_type + ptr_level + array_size + struct_id | 支持指针、数组、结构体类型 |
| 结构体 | StructInfo + MemberInfo | 全局结构体表 + 成员偏移计算 |
| 比较运算 | slt/slti + xor/sub | 支持 <, <=, >, >=, ==, != |
| 测试验证 | CPU TestBench | tohost机制 (0x80001000) |
| 编译器输出 | Verilog hex | 小端字节序，用于hex_to_bsv.py |

## Git 状态

- **当前分支**: main
- **父项目**: ../ (riscv-bsv-processor)
- **状态**: 阶段1-9完成，30+个测试全部通过
- **最近提交**: fix(phase9): extern variable reference + single-file mode assembly path

## 编译器流水线

```
源文件(.c)
  ↓ Preprocessor (pp_process: #include展开 + 宏替换 + 条件编译过滤)
预处理文本
  ↓ Lexer (tokenize + 关键字识别 + ++多字符检测 + 括号)
Token流 (含 if/else/while/for/++/lt/and/bracket/struct/arrow/extern 等共30种标记)
  ↓ Parser (三级递归下降 + 控制流语法糖展开 + 指针 + 数组 + 结构体 + extern + 函数原型)
AST (FUNC_DEF, FUNC_DECL, RETURN, INT_LIT, BIN_OP, VAR_DECL, VAR_REF, ASSIGN, IF, WHILE, NOOP, ADDR, DEREF, ARRAY_ACCESS, STRUCT_DEF, MEMBER_ACCESS, EXTERN_DECL)
  ↓ Codegen (符号表 + 标签生成 + 多级溢出槽 + 分支/跳转 + 指针操作 + 数组访问)
RV32I汇编文本 (含 .L0/.L1 标签和 beqz/j 分支，多个 .s 文件)
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
| `src/preprocessor.c` | 预处理器（#include/#define/#ifdef） | ✅ 阶段9 |
| `src/lexer.c` | 字符流 → Token 流（含 extern） | ✅ 阶段9 |
| `src/parser.c` | Token 流 → AST（含 extern 声明、函数原型） | ✅ 阶段9 |
| `src/codegen.c` | AST → 汇编（extern 跳过生成） | ✅ 阶段9 |
| `src/linker.c` | linker_link_multi 多文件拼接 | ✅ 阶段9 |
| `src/main.c` | 多文件编译驱动 | ✅ 阶段9 |
| `src/ast.h` | AST 节点类型定义（含 AST_FUNC_DECL） | ✅ 阶段9 |
| `src/asm.c` | 二遍汇编器 | ✅ 阶段2 |
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

### 阶段8测试（2个全部通过）
| 测试 | 代码 | tohost | 状态 |
|------|------|--------|------|
| member_access | `struct Node g_n; g_n.value = 42; p->value` | 42 | ✅ |
| linked_list | `sum_list(&g_n1)` 链表遍历求和 (10+20+30) | 60 | ✅ |

### 阶段9测试（多文件编译）✅
| 测试 | 代码 | tohost | 状态 |
|------|------|--------|------|
| multifile | `helper_func() + 5` 跨文件调用 | 15 | ✅ |
| full_test | `get_value() + g_external + 25` extern引用 | 55 | ✅ |

## 下一步

- 阶段 10: 自举准备（typedef/enum/volatile）