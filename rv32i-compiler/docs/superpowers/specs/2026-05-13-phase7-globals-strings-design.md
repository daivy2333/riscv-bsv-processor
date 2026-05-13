# 阶段 7：全局变量与字符串 — 设计文档

> 创建日期：2026-05-13
> 设计目标：支持全局变量声明、字符串字面量，为 mini-os 和自举做准备

## 设计决策

| 问题 | 决策 | 理由 |
|------|------|------|
| 字符字面量类型 | 引入 `char` 类型 | RISC-V ABI 兼容，字符串遍历每字符 1 字节 |
| 全局变量初始化 | 常量表达式初始化 | 支持 `0x10000000`、`BASE+4` 等地址计算 |
| 内存分段 | 双段架构（.text + .data） | 标准 ABI 布局，代码区与数据区分离 |
| 字符串存储 | .data 段，`\0` 终止 | 统一放置全局数据，简化链接器 |

## 内存布局

```
地址空间布局（连续）：

.text 段（代码区）         0x80000000
  ├─ crt0.s 启动代码
  ├─ lib.S 运行时库
  └─ 用户函数代码

.data 段（数据区）         0x80000000 + text_size
  ├─ 全局变量（带初始化）
  └─ 字符串字面量（\0 终止）
```

## 类型系统扩展

### 新增基础类型

```c
// types.h
typedef enum { TYPE_INT, TYPE_CHAR } BaseType;

typedef struct {
    BaseType base_type;  // TYPE_INT or TYPE_CHAR
    int ptr_level;       // 0 = scalar, 1 = pointer
    int array_size;      // 0 = scalar, >0 = array elements
} Type;

// 新增 helper
Type type_make_char(void);       // char 类型（ptr_level=0, array_size=0）
Type type_make_char_ptr(void);   // char* 类型（ptr_level=1）
Type type_make_char_array(int);  // char[n] 类型
```

### 类型语义

| C 声明 | Type 表示 |
|--------|-----------|
| `int x` | `{base=INT, ptr=0, arr=0}` |
| `int *p` | `{base=INT, ptr=1, arr=0}` |
| `int arr[5]` | `{base=INT, ptr=0, arr=5}` |
| `char c` | `{base=CHAR, ptr=0, arr=0}` |
| `char *s` | `{base=CHAR, ptr=1, arr=0}` |
| `char buf[64]` | `{base=CHAR, ptr=0, arr=64}` |

## Lexer 扩展

### 新增 Token

```c
// lexer.h TokenType
TOK_CHAR,     // 关键字 "char"
TOK_STRING,   // 字符串字面量 "hello"
```

### 字符串 Token 结构

```c
typedef struct Token {
    TokenType type;
    char *text;     // 字符串内容（不含引号，已处理转义）
    int line, col;
    struct Token *next;
} Token;
```

### 词法规则

```
"char"       → TOK_CHAR
"hello"      → TOK_STRING (text="hello", 含转义处理)
```

转义字符支持：`\n` → newline, `\0` → null, `\\` → backslash

## Parser 扩展

### 新增 AST 节点

```c
// ast.h
AST_GLOBAL_DECL    // 全局变量声明
AST_STRING_LIT     // 字符串字面量
```

### AST 结构扩展

```c
typedef struct ASTNode {
    ASTNodeType type;
    // ...

    // AST_GLOBAL_DECL
    char *name;          // 变量名
    Type var_type;       // 类型（int/char/ptr/array）
    ASTNode *init;       // 初始化表达式（可为 NULL）
    int int_val;         // 常量初始值（简化处理）
    char *str_val;       // 字符串初始值（仅用于 char* = "..."）

    // AST_STRING_LIT
    char *str_val;       // 字符串内容
} ASTNode;
```

### Grammar 扩展

```
program = (global-decl | func-def)*

global-decl = ("int" | "char") ["*"] identifier ["[" num "]"]
              ["=" (expr | string-lit)] ";"

expr-primary = ... | string-lit

string-lit = TOK_STRING
```

### 解析策略

1. `parse_program()` 首先检查是否为全局声明（`int/char` 后跟标识符但无 `(`）
2. 全局声明存入全局 AST 链表（在函数定义之前）
3. 字符串字面量作为 `AST_STRING_LIT` 节点

## Codegen 扩展

### 全局符号表

```c
// codegen.c
#define MAX_GLOBALS 64

static struct {
    char *name;
    int   data_offset;    // .data 段偏移（字节）
    Type  type;
    int   init_val;       // 整数初始值（int 类型）
    char *init_str;       // 字符串初始值（char* 类型）
    int   str_len;        // 字符串长度（含 \0）
} globals[MAX_GLOBALS];

static int global_count;
static int data_offset;   // 当前 .data 段累计偏移
```

### 字符串标签管理

```c
static int string_label_counter;  // .Lstr0, .Lstr1, ...

static int emit_string_literal(const char *str) {
    int label = string_label_counter++;
    // 记录到字符串表，后续统一输出
    return label;
}
```

### 代码生成流程

**Pass 1：收集全局符号**

```
遍历 AST：
  - AST_GLOBAL_DECL → 添加到全局符号表，计算 data_offset
  - AST_FUNC_DEF → 收集局部符号（现有流程）
  - AST_STRING_LIT（在表达式内）→ 分配字符串标签

输出：
  - data_size（.data 段总大小）
  - 全局符号表填充完毕
```

**Pass 2：输出汇编**

```asm
    .data
.global_g_count:
    .word 42

.Lstr0:
    .byte 'h','e','l','l','o',0
    .align 4

.Lstr1:
    .byte 'w','o','r','l','d',0
    .align 4

    .text
    .globl main
main:
    ...
```

### 全局变量访问

```asm
# 读取全局变量 g_count
la t0, .global_g_count    # t0 = 地址
lw t0, 0(t0)              # t0 = 值

# 写入全局变量
la t0, .global_g_count
li t1, 100
sw t1, 0(t0)

# 获取字符串地址
la t0, .Lstr0             # t0 = "hello" 的地址
```

### 表达式中的字符串

```c
case AST_STRING_LIT:
    emit("    la t0, .Lstr%d\n", n->str_label);
    break;
```

## Linker 扩展

### 输入处理

现有链接器接收单个 ASM 文件。扩展后：

```c
// linker.c
int linker_link(
    const char *text_asm,    // .text 段汇编
    const char *data_asm,    // .data 段汇编（可选，可为空字符串）
    const char *crt0_asm,
    const char *lib_asm,
    const char *out_hex
);
```

### 段拼接逻辑

```
1. 汇编 .text 段 → text_words[], text_count
2. 汇编 .data 段 → data_words[], data_count
3. 计算 .data 基址 = 0x80000000 + text_count * 4
4. 调整 .data 段内标签地址（加上基址偏移）
5. 输出 hex：
   - text_words @ 0x80000000
   - data_words @ .data 基址
```

### 标签地址重定位

问题：`.data` 段标签（如 `.Lstr0`）在汇编时假设基址为 0，需调整。

解决方案：

**方案 A：二遍汇编重定位**

1. 第一遍：记录所有标签位置
2. 第二遍：输出指令时，对 `la` 指令的目标地址加上 `.data` 基址

**方案 B：汇编时预设基址**

在 `.data` 段开头添加 `.org` 指令指定基址：

```asm
.data
.org 0x80000100    # 预设基址（由链接器计算后填入）
.Lstr0:
    ...
```

**选择方案 A**，因为：
- 汇编器已有二遍架构，改动最小
- 符合标准链接器行为

### 汇编器扩展

```c
// asm.c 新增
// 第二遍时，对 .data 段内的标签地址加上 data_base 偏移
void asm_set_data_base(uint32_t base);
```

## 完整数据流

```
源码 (.c)
  ↓ Lexer（识别 char 关键字 + 字符串字面量）
Token 流
  ↓ Parser（全局声明 + 字符串表达式 → AST）
AST（AST_GLOBAL_DECL 链 + AST_FUNC_DEF 链 + AST_STRING_LIT）
  ↓ Codegen Pass 1（收集全局符号 + 计算布局）
全局符号表 + 字符串表 + data_size
  ↓ Codegen Pass 2（输出 .data 段 + 输出 .text 段）
汇编文本（含 .data/.text 分段标记）
  ↓ Linker（分别汇编 → 计算基址 → 重定位 → 拼接）
最终 .hex（连续地址空间）
```

## 验证测试

### Phase 7 测试集

| 测试名 | 代码 | 验证点 | 预期 tohost |
|--------|------|--------|-------------|
| `global_int` | `int g_x = 42; int main() { return g_x; }` | 全局 int 读取 | 42 |
| `global_write` | `int g_y; int main() { g_y = 100; return g_y; }` | 全局 int 写入 | 100 |
| `global_addr` | `int g_base = 0x10000000; int main() { return g_base; }` | 常量初始化（大地址） | 0x10000000 → 268435456 |
| `global_expr` | `int g_val = 10 + 5; int main() { return g_val; }` | 常量表达式初始化 | 15 |
| `string_arg` | `int len(char *s) { int n=0; while(*s){n++;s++;} return n; } int main() { return len("hello"); }` | 字符串作为参数 | 5 |
| `string_assign` | `char *g_msg; int main() { g_msg = "world"; return len(g_msg); }` | 字符串赋给全局指针 | 5 |

### 测试目录结构

```
tests/phase7/
├── global_int.c
├── global_write.c
├── global_addr.c
├── global_expr.c
├── string_arg.c
└── string_assign.c
```

## 实现任务分解

### Task 1：类型系统扩展

- 修改 `types.h`：添加 `BaseType` enum 和 `char` 相关 helper
- 修改 `types.c`：实现 `type_make_char()`, `type_make_char_ptr()`
- 添加 `type_is_char()` 判断函数

### Task 2：Lexer 扩展

- 修改 `lexer.h`：添加 `TOK_CHAR`, `TOK_STRING`
- 修改 `lexer.c`：
  - 添加 `char` 关键字识别
  - 添加字符串字面量解析（含转义处理）

### Task 3：Parser 扩展（全局声明）

- 修改 `ast.h`：添加 `AST_GLOBAL_DECL`, `AST_STRING_LIT`
- 修改 `parser.c`：
  - `parse_program()` 支持 `global-decl | func-def`
  - 添加 `parse_global_decl()` 函数
  - 扩展 `parse_primary()` 支持字符串字面量

### Task 4：Codegen 扩展（全局符号表）

- 修改 `codegen.c`：
  - 添加全局符号表结构和访问函数
  - 添加字符串标签管理
  - Pass 1 收集全局声明
  - Pass 2 输出 `.data` 段

### Task 5：Linker 扩展（段拼接）

- 修改 `linker.c`：支持 `.data` 段输入和拼接
- 修改 `asm.c`：添加 `asm_set_data_base()` 支持地址重定位

### Task 6：测试验证

- 创建 `tests/phase7/` 目录和测试文件
- 修改 `Makefile` 添加 `test-phase7` 目标
- 运行全部测试验证

## 风险与边界

### 已知限制

- 不支持字符串拼接 `"hello" " world"`
- 不支持字符串数组初始化 `char arr[6] = "hello"`（仅支持指针赋值）
- 不支持全局变量动态初始化（仅常量表达式）
- 转义字符仅支持 `\n`, `\0`, `\\`, `\t`（基础覆盖）

### 后续阶段依赖

- 阶段 8（结构体）需扩展全局符号表支持结构体布局
- 阶段 9（多文件）需处理跨文件全局符号引用

## 参考设计

- RISC-V ABI：全局数据放在 `.data` 段，字符串通常 `.rodata`（本设计合并到 `.data` 简化）
- GCC 字符串布局：`\0` 终止，`char*` 指向首个字符
- mini-os 需求：`printf`、`strlen`、`strcmp` 等函数需字符串参数支持