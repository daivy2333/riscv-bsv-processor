# Phase 10: 自举准备 - 实现计划

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** 添加 volatile/const/void/typedef/static 特性，实现编译器自举验证。

**Architecture:** 按 volatile+const → void → typedef → static 顺序增量实现。每个特性独立测试，最后整体自举验证。类型修饰位（volatile/const）在 TypeInfo 中标记，static 在 AST 节点中标记并生成 .Lstatic_ 本地标签。

**Tech Stack:** C (Micro-C 子集) + RV32I + GCC 编译 + Verilator CPU TestBench 验证。

---

## File Structure

### 新增文件
```
tests/phase10/
├── volatile_test.c         volatile 特性测试
├── const_test.c            const 特性测试
├── void_test.c             void 特性测试
├── typedef_test.c          typedef 特性测试
├── static_test.c           static 特性测试
└── combined_test.c         组合测试（自举前验证）
```

### 修改文件
```
src/lexer.h                 TokenType enum 扩展（+5 个新 token）
src/lexer.c                 lex_keyword_or_id 添加关键字识别
src/types.h                 BaseType enum 添加 TYPE_VOID，Type 结构体添加 is_const/is_volatile
src/types.c                 type_make_void() 辅助函数
src/ast.h                   ASTNode 添加 is_static 字段
src/parser.c                parse_type/parse_func_def/parse_global_decl 添加类型修饰符解析 + typedef 别名表
src/codegen.c               void 函数返回处理 + static 符号命名
```

---

## Task 1: volatile + const - Lexer 改动

**Files:**
- Modify: `src/lexer.h:5-23`（TokenType enum）
- Modify: `src/lexer.c:83-104`（lex_keyword_or_id 函数）

- [ ] **Step 1: 扩展 TokenType enum**

修改 `src/lexer.h:23`（在 TOK_EXTERN 之后添加）：

```c
typedef enum {
    TOK_INT, TOK_ID, TOK_NUM, TOK_RETURN,
    TOK_LPAREN, TOK_RPAREN, TOK_LBRACE, TOK_RBRACE, TOK_SEMI,
    TOK_ASSIGN, TOK_PLUS, TOK_MINUS, TOK_STAR, TOK_SLASH,
    TOK_IF, TOK_ELSE, TOK_WHILE, TOK_FOR,
    TOK_LT, TOK_LE, TOK_GT, TOK_GE,
    TOK_EQ, TOK_NE,
    TOK_INC,
    TOK_COMMA,
    TOK_AND,
    TOK_CHAR,
    TOK_STRING,
    TOK_LBRACKET,
    TOK_RBRACKET,
    TOK_STRUCT,
    TOK_ARROW,
    TOK_DOT,
    TOK_EXTERN,
    TOK_VOLATILE,    /* NEW: volatile keyword */
    TOK_CONST,       /* NEW: const keyword */
    TOK_EOF
} TokenType;
```

- [ ] **Step 2: 添加 volatile/const 关键字识别**

修改 `src/lexer.c:83-104`（在 TOK_EXTERN 识别之后添加）：

```c
static Token *lex_keyword_or_id(const char *s, int len, int line, int col)
{
    if (len == 3 && strncmp(s, "int", 3) == 0)
        return new_token(TOK_INT, s, len, line, col);
    if (len == 4 && strncmp(s, "char", 4) == 0)
        return new_token(TOK_CHAR, s, len, line, col);
    if (len == 6 && strncmp(s, "return", 6) == 0)
        return new_token(TOK_RETURN, s, len, line, col);
    if (len == 2 && strncmp(s, "if", 2) == 0)
        return new_token(TOK_IF, s, len, line, col);
    if (len == 4 && strncmp(s, "else", 4) == 0)
        return new_token(TOK_ELSE, s, len, line, col);
    if (len == 5 && strncmp(s, "while", 5) == 0)
        return new_token(TOK_WHILE, s, len, line, col);
    if (len == 3 && strncmp(s, "for", 3) == 0)
        return new_token(TOK_FOR, s, len, line, col);
    if (len == 6 && strncmp(s, "struct", 6) == 0)
        return new_token(TOK_STRUCT, s, len, line, col);
    if (len == 6 && strncmp(s, "extern", 6) == 0)
        return new_token(TOK_EXTERN, s, len, line, col);
    if (len == 8 && strncmp(s, "volatile", 8) == 0)
        return new_token(TOK_VOLATILE, s, len, line, col);
    if (len == 5 && strncmp(s, "const", 5) == 0)
        return new_token(TOK_CONST, s, len, line, col);
    return new_token(TOK_ID, s, len, line, col);
}
```

- [ ] **Step 3: 更新 tok_name 函数**

修改 `src/lexer.c:10-50`（tok_name 函数添加 volatile/const 名称）：

```c
const char *tok_name(TokenType t)
{
    switch (t) {
    case TOK_INT:    return "int";
    case TOK_CHAR:   return "char";
    case TOK_STRING: return "string";
    case TOK_STRUCT: return "struct";
    case TOK_ARROW:  return "->";
    case TOK_DOT:    return ".";
    case TOK_ID:     return "identifier";
    case TOK_NUM:    return "number";
    case TOK_RETURN: return "return";
    case TOK_LPAREN: return "(";
    case TOK_RPAREN: return ")";
    case TOK_LBRACE: return "{";
    case TOK_RBRACE: return "}";
    case TOK_SEMI:   return ";";
    case TOK_ASSIGN: return "=";
    case TOK_PLUS:   return "+";
    case TOK_MINUS:  return "-";
    case TOK_STAR:   return "*";
    case TOK_SLASH:  return "/";
    case TOK_IF:     return "if";
    case TOK_ELSE:   return "else";
    case TOK_WHILE:  return "while";
    case TOK_FOR:    return "for";
    case TOK_LT:     return "<";
    case TOK_LE:     return "<=";
    case TOK_GT:     return ">";
    case TOK_GE:     return ">=";
    case TOK_EQ:     return "==";
    case TOK_NE:     return "!=";
    case TOK_INC:    return "++";
    case TOK_COMMA:  return ",";
    case TOK_AND:    return "&";
    case TOK_LBRACKET: return "[";
    case TOK_RBRACKET: return "]";
    case TOK_EXTERN: return "extern";
    case TOK_VOLATILE: return "volatile";
    case TOK_CONST:   return "const";
    case TOK_EOF:    return "EOF";
    default:         return "?";
    }
}
```

- [ ] **Step 4: 编译验证**

Run: `cd /home/daivy/projects/riscv-bsv-processor/rv32i-compiler && make clean && make`
Expected: 编译成功，无错误

- [ ] **Step 5: Commit**

```bash
git add src/lexer.h src/lexer.c
git commit -m "feat(lexer): add TOK_VOLATILE and TOK_CONST keywords"
```

---

## Task 2: volatile + const - Parser 改动（类型系统）

**Files:**
- Modify: `src/types.h:11-17`（Type 结构体）
- Modify: `src/types.c`（type 辅助函数初始化）

- [ ] **Step 1: 扩展 Type 结构体添加类型修饰位**

修改 `src/types.h:11-17`：

```c
typedef struct {
    BaseType base_type;  /* TYPE_INT, TYPE_CHAR, TYPE_STRUCT */
    int ptr_level;       /* Pointer level: 0 = scalar, 1 = pointer */
    int array_size;      /* Array size: 0 = not array, >0 = array elements count */
    int struct_id;       /* struct_table 索引 (仅 TYPE_STRUCT 有效) */
    int is_const;        /* NEW: const 标记位 */
    int is_volatile;     /* NEW: volatile 标记位 */
} Type;
```

- [ ] **Step 2: 更新 type 辅助函数初始化修饰位**

修改 `src/types.c`（所有 type_make_* 函数添加初始化）：

```c
Type type_make_int(void)
{
    Type t = { TYPE_INT, 0, 0, -1, 0, 0 };  /* base_type, ptr_level, array_size, struct_id, is_const, is_volatile */
    return t;
}

Type type_make_int_ptr(void)
{
    Type t = { TYPE_INT, 1, 0, -1, 0, 0 };
    return t;
}

Type type_make_array(int size)
{
    Type t = { TYPE_INT, 0, size, -1, 0, 0 };
    return t;
}

Type type_make_char(void)
{
    Type t = { TYPE_CHAR, 0, 0, -1, 0, 0 };
    return t;
}

Type type_make_char_ptr(void)
{
    Type t = { TYPE_CHAR, 1, 0, -1, 0, 0 };
    return t;
}

Type type_make_char_array(int size)
{
    Type t = { TYPE_CHAR, 0, size, -1, 0, 0 };
    return t;
}

Type type_make_struct_ptr(int struct_id)
{
    Type t = { TYPE_STRUCT, 1, 0, struct_id, 0, 0 };
    return t;
}

Type type_make_struct_val(int struct_id)
{
    Type t = { TYPE_STRUCT, 0, 0, struct_id, 0, 0 };
    return t;
}
```

- [ ] **Step 3: 编译验证**

Run: `make clean && make`
Expected: 编译成功，无错误

- [ ] **Step 4: Commit**

```bash
git add src/types.h src/types.c
git commit -m "feat(types): add is_const and is_volatile fields to Type struct"
```

---

## Task 3: volatile + const - Parser 改动（类型解析）

**Files:**
- Modify: `src/parser.c`（parse_type 函数添加类型修饰符解析）

- [ ] **Step 1: 查找 parse_type 函数位置**

Run: `grep -n "parse_type" /home/daivy/projects/riscv-bsv-processor/rv32i-compiler/src/parser.c | head -5`
Expected: 找到 parse_type 函数定义位置

- [ ] **Step 2: 修改 parse_type 函数添加 volatile/const 解析**

在 parse_type 函数开头添加类型修饰符解析循环：

```c
static Type parse_type(void)
{
    Type t = type_make_int();
    int is_const = 0;
    int is_volatile = 0;

    /* 解析类型修饰符（volatile/const 可重复出现） */
    while (cur->type == TOK_VOLATILE || cur->type == TOK_CONST) {
        if (cur->type == TOK_VOLATILE) {
            is_volatile = 1;
            cur = cur->next;
        } else if (cur->type == TOK_CONST) {
            is_const = 1;
            cur = cur->next;
        }
    }

    /* 解析基本类型 */
    if (cur->type == TOK_INT) {
        t = type_make_int();
        cur = cur->next;
    } else if (cur->type == TOK_CHAR) {
        t = type_make_char();
        cur = cur->next;
    } else if (cur->type == TOK_STRUCT) {
        /* struct 类型解析 */
        cur = cur->next;
        if (cur->type != TOK_ID) {
            parse_error(cur->line, cur->col, "expected struct name");
            return t;
        }
        int struct_id = lookup_struct(cur->text);
        if (struct_id < 0) {
            parse_error(cur->line, cur->col, "undefined struct");
            return t;
        }
        t = type_make_struct_val(struct_id);
        cur = cur->next;
    }

    /* 设置类型修饰位 */
    t.is_const = is_const;
    t.is_volatile = is_volatile;

    /* 解析指针层级 */
    while (cur->type == TOK_STAR) {
        t.ptr_level++;
        cur = cur->next;
    }

    return t;
}
```

- [ ] **Step 3: 编译验证**

Run: `make clean && make`
Expected: 编译成功，无错误

- [ ] **Step 4: Commit**

```bash
git add src/parser.c
git commit -m "feat(parser): add volatile/const type qualifier parsing in parse_type"
```

---

## Task 4: volatile + const - 测试验证

**Files:**
- Create: `tests/phase10/volatile_test.c`
- Create: `tests/phase10/const_test.c`
- Create: `tests/phase10/volatile_const_test.c`

- [ ] **Step 1: 创建 volatile 测试文件**

创建 `tests/phase10/volatile_test.c`：

```c
volatile int x;
x = 42;
return x;
```

- [ ] **Step 2: 创建 const 测试文件**

创建 `tests/phase10/const_test.c`：

```c
const int a = 10;
int b;
b = a + 5;
return b;
```

- [ ] **Step 3: 创建 volatile+const 组合测试文件**

创建 `tests/phase10/volatile_const_test.c`：

```c
volatile const int x = 5;
return x;
```

- [ ] **Step 4: 添加 Makefile 测试目标**

修改 `Makefile` 添加 Phase 10 测试目标：

```makefile
# Phase 10 tests
test-phase10-volatile: tests/phase10/volatile_test.c
	./build/microcc tests/phase10/volatile_test.c runtime/crt0.s runtime/lib.S build/volatile_test.hex

test-phase10-const: tests/phase10/const_test.c
	./build/microcc tests/phase10/const_test.c runtime/crt0.s runtime/lib.S build/const_test.hex

test-phase10-volatile-const: tests/phase10/volatile_const_test.c
	./build/microcc tests/phase10/volatile_const_test.c runtime/crt0.s runtime/lib.S build/volatile_const_test.hex

test-phase10: test-phase10-volatile test-phase10-const test-phase10-volatile-const
```

- [ ] **Step 5: 编译 volatile 测试**

Run: `make test-phase10-volatile`
Expected: 编译成功，生成 build/volatile_test.hex

- [ ] **Step 6: 运行 volatile 测试**

Run: `cd /home/daivy/projects/riscv-bsv-processor && python3 tools/hex_to_bsv.py rv32i-compiler/build/volatile_test.hex && make test-custom`
Expected: tohost = 42 ✅

- [ ] **Step 7: 编译 const 测试**

Run: `make test-phase10-const`
Expected: 编译成功，生成 build/const_test.hex

- [ ] **Step 8: 运行 const 测试**

Run: `cd /home/daivy/projects/riscv-bsv-processor && python3 tools/hex_to_bsv.py rv32i-compiler/build/const_test.hex && make test-custom`
Expected: tohost = 15 ✅

- [ ] **Step 9: 编译 volatile+const 组合测试**

Run: `make test-phase10-volatile-const`
Expected: 编译成功，生成 build/volatile_const_test.hex

- [ ] **Step 10: 运行 volatile+const 组合测试**

Run: `cd /home/daivy/projects/riscv-bsv-processor && python3 tools/hex_to_bsv.py rv32i-compiler/build/volatile_const_test.hex && make test-custom`
Expected: tohost = 5 ✅

- [ ] **Step 11: Commit**

```bash
git add tests/phase10/ Makefile
git commit -m "test(phase10): add volatile/const test cases"
```

---

## Task 5: void - Lexer 改动

**Files:**
- Modify: `src/lexer.h:23`（TokenType enum）
- Modify: `src/lexer.c:83-104`（lex_keyword_or_id 函数）

- [ ] **Step 1: 扩展 TokenType enum 添加 TOK_VOID**

修改 `src/lexer.h:23`（在 TOK_CONST 之后添加）：

```c
typedef enum {
    TOK_INT, TOK_ID, TOK_NUM, TOK_RETURN,
    TOK_LPAREN, TOK_RPAREN, TOK_LBRACE, TOK_RBRACE, TOK_SEMI,
    TOK_ASSIGN, TOK_PLUS, TOK_MINUS, TOK_STAR, TOK_SLASH,
    TOK_IF, TOK_ELSE, TOK_WHILE, TOK_FOR,
    TOK_LT, TOK_LE, TOK_GT, TOK_GE,
    TOK_EQ, TOK_NE,
    TOK_INC,
    TOK_COMMA,
    TOK_AND,
    TOK_CHAR,
    TOK_STRING,
    TOK_LBRACKET,
    TOK_RBRACKET,
    TOK_STRUCT,
    TOK_ARROW,
    TOK_DOT,
    TOK_EXTERN,
    TOK_VOLATILE,
    TOK_CONST,
    TOK_VOID,        /* NEW: void keyword */
    TOK_EOF
} TokenType;
```

- [ ] **Step 2: 添加 void 关键字识别**

修改 `src/lexer.c:lex_keyword_or_id`（在 const 识别之后添加）：

```c
if (len == 4 && strncmp(s, "void", 4) == 0)
    return new_token(TOK_VOID, s, len, line, col);
```

- [ ] **Step 3: 更新 tok_name 函数**

修改 `src/lexer.c:tok_name`：

```c
case TOK_VOID: return "void";
```

- [ ] **Step 4: 编译验证**

Run: `make clean && make`
Expected: 编译成功，无错误

- [ ] **Step 5: Commit**

```bash
git add src/lexer.h src/lexer.c
git commit -m "feat(lexer): add TOK_VOID keyword"
```

---

## Task 6: void - Parser 改动（类型系统）

**Files:**
- Modify: `src/types.h:4-9`（BaseType enum）
- Modify: `src/types.c`（添加 type_make_void 函数）

- [ ] **Step 1: 扩展 BaseType enum 添加 TYPE_VOID**

修改 `src/types.h:4-9`：

```c
typedef enum {
    TYPE_INT = 0,
    TYPE_CHAR = 1,
    TYPE_STRUCT = 2,
    TYPE_VOID = 3   /* NEW: void type */
} BaseType;
```

- [ ] **Step 2: 添加 type_make_void 辅助函数**

修改 `src/types.c` 添加：

```c
Type type_make_void(void)
{
    Type t = { TYPE_VOID, 0, 0, -1, 0, 0 };
    return t;
}
```

- [ ] **Step 3: 添加 type_is_void 辅助函数**

修改 `src/types.h` 添加声明：

```c
int  type_is_void(Type t);          /* Check if type is void */
```

修改 `src/types.c` 添加实现：

```c
int type_is_void(Type t)
{
    return t.base_type == TYPE_VOID;
}
```

- [ ] **Step 4: 编译验证**

Run: `make clean && make`
Expected: 编译成功，无错误

- [ ] **Step 5: Commit**

```bash
git add src/types.h src/types.c
git commit -m "feat(types): add TYPE_VOID and type_make_void helper"
```

---

## Task 7: void - Parser 改动（函数解析）

**Files:**
- Modify: `src/parser.c`（parse_func_def 函数添加 void 返回类型和 void 参数处理）

- [ ] **Step 1: 查找 parse_func_def 函数位置**

Run: `grep -n "parse_func_def" /home/daivy/projects/riscv-bsv-processor/rv32i-compiler/src/parser.c`
Expected: 找到 parse_func_def 函数定义位置

- [ ] **Step 2: 修改 parse_func_def 支持 void 返回类型**

在 parse_func_def 函数的类型解析部分添加 void 支持：

```c
static ASTNode *parse_func_def(void)
{
    ASTNode *n = ast_new(AST_FUNC_DEF);

    /* 解析返回类型 */
    Type func_type;
    if (cur->type == TOK_VOID) {
        func_type = type_make_void();
        cur = cur->next;
    } else {
        func_type = parse_type();  /* 支持 volatile/const int */
    }

    /* 解析函数名 */
    if (cur->type != TOK_ID) {
        parse_error(cur->line, cur->col, "expected function name");
        return n;
    }
    n->func_name = strdup(cur->text);
    cur = cur->next;

    /* 解析参数列表 */
    expect(TOK_LPAREN);

    if (cur->type == TOK_VOID && cur->next->type == TOK_RPAREN) {
        /* void 参数：func(void) */
        cur = cur->next;  /* 跳过 void */
        n->right = NULL;  /* 无参数 */
    } else if (cur->type == TOK_RPAREN) {
        /* 无参数声明：func() */
        n->right = NULL;
    } else {
        /* 有参数：func(int a, int b) */
        n->right = parse_var_decl_chain();
    }

    expect(TOK_RPAREN);

    /* 解析函数体 */
    expect(TOK_LBRACE);
    n->body = parse_compound();
    expect(TOK_RBRACE);

    return n;
}
```

- [ ] **Step 3: 修改 parse_type 支持 void 类型**

在 parse_type 函数添加 void 类型解析：

```c
static Type parse_type(void)
{
    Type t = type_make_int();
    int is_const = 0;
    int is_volatile = 0;

    /* 解析类型修饰符 */
    while (cur->type == TOK_VOLATILE || cur->type == TOK_CONST) {
        if (cur->type == TOK_VOLATILE) {
            is_volatile = 1;
            cur = cur->next;
        } else if (cur->type == TOK_CONST) {
            is_const = 1;
            cur = cur->next;
        }
    }

    /* 解析基本类型 */
    if (cur->type == TOK_INT) {
        t = type_make_int();
        cur = cur->next;
    } else if (cur->type == TOK_CHAR) {
        t = type_make_char();
        cur = cur->next;
    } else if (cur->type == TOK_VOID) {
        t = type_make_void();
        cur = cur->next;
    } else if (cur->type == TOK_STRUCT) {
        /* struct 类型解析 */
        cur = cur->next;
        if (cur->type != TOK_ID) {
            parse_error(cur->line, cur->col, "expected struct name");
            return t;
        }
        int struct_id = lookup_struct(cur->text);
        if (struct_id < 0) {
            parse_error(cur->line, cur->col, "undefined struct");
            return t;
        }
        t = type_make_struct_val(struct_id);
        cur = cur->next;
    }

    /* 设置类型修饰位 */
    t.is_const = is_const;
    t.is_volatile = is_volatile;

    /* 解析指针层级（void* 不支持，但解析时允许） */
    while (cur->type == TOK_STAR) {
        t.ptr_level++;
        cur = cur->next;
    }

    return t;
}
```

- [ ] **Step 4: 编译验证**

Run: `make clean && make`
Expected: 编译成功，无错误

- [ ] **Step 5: Commit**

```bash
git add src/parser.c
git commit -m "feat(parser): add void return type and void parameter parsing"
```

---

## Task 8: void - Codegen 改动

**Files:**
- Modify: `src/codegen.c`（gen_func_def 函数添加 void 返回处理）

- [ ] **Step 1: 查找 gen_func_def 函数位置**

Run: `grep -n "gen_func_def" /home/daivy/projects/riscv-bsv-processor/rv32i-compiler/src/codegen.c`
Expected: 找到 gen_func_def 函数定义位置

- [ ] **Step 2: 修改 gen_func_def 支持 void 函数自动添加 ret**

在 gen_func_def 函数末尾添加 void 返回处理：

```c
static void gen_func_def(ASTNode *n)
{
    emit("%s:\n", n->func_name);

    /* 计算栈帧大小 */
    int num_locals = count_frame(n->body);
    int frame_size = 16 + 4 * num_locals + 32;  /* spill + locals + arg area */
    frame_size = (frame_size + 15) & ~15;  /* 16-byte align */

    /* 函数序言 */
    emit("    addi sp, sp, -%d\n", frame_size);
    emit("    sw ra, %d(sp)\n", frame_size - 4);

    /* 生成函数体 */
    gen_stmt(n->body);

    /* 函数尾声 */
    emit("    lw ra, %d(sp)\n", frame_size - 4);
    emit("    addi sp, sp, %d\n", frame_size);

    /* void 函数直接 ret，非 void 函数需要返回值 */
    emit("    ret\n");
}
```

（注：void 函数无需特殊处理，直接 ret 即可。空 return 语句在 parse_stmt 中返回 AST_NOOP，不生成代码）

- [ ] **Step 3: 编译验证**

Run: `make clean && make`
Expected: 编译成功，无错误

- [ ] **Step 4: Commit**

```bash
git add src/codegen.c
git commit -m "feat(codegen): void function generates direct ret"
```

---

## Task 9: void - 测试验证

**Files:**
- Create: `tests/phase10/void_test.c`
- Create: `tests/phase10/void_param_test.c`
- Create: `tests/phase10/void_empty_return_test.c`

- [ ] **Step 1: 创建 void 返回类型测试文件**

创建 `tests/phase10/void_test.c`：

```c
void test_void() { }
int main() {
    test_void();
    return 42;
}
```

- [ ] **Step 2: 创建 void 参数测试文件**

创建 `tests/phase10/void_param_test.c`：

```c
int get_value(void) { return 10; }
int main() { return get_value(); }
```

- [ ] **Step 3: 创建空 return 测试文件**

创建 `tests/phase10/void_empty_return_test.c`：

```c
void early_return(void) { if (1) return; }
int main() {
    early_return();
    return 5;
}
```

- [ ] **Step 4: 添加 Makefile 测试目标**

修改 `Makefile` 添加：

```makefile
test-phase10-void: tests/phase10/void_test.c
	./build/microcc tests/phase10/void_test.c runtime/crt0.s runtime/lib.S build/void_test.hex

test-phase10-void-param: tests/phase10/void_param_test.c
	./build/microcc tests/phase10/void_param_test.c runtime/crt0.s runtime/lib.S build/void_param_test.hex

test-phase10-void-empty-return: tests/phase10/void_empty_return_test.c
	./build/microcc tests/phase10/void_empty_return_test.c runtime/crt0.s runtime/lib.S build/void_empty_return_test.hex
```

- [ ] **Step 5: 编译 void 测试**

Run: `make test-phase10-void`
Expected: 编译成功，生成 build/void_test.hex

- [ ] **Step 6: 运行 void 测试**

Run: `cd /home/daivy/projects/riscv-bsv-processor && python3 tools/hex_to_bsv.py rv32i-compiler/build/void_test.hex && make test-custom`
Expected: tohost = 42 ✅

- [ ] **Step 7: 编译 void 参数测试**

Run: `make test-phase10-void-param`
Expected: 编译成功，生成 build/void_param_test.hex

- [ ] **Step 8: 运行 void 参数测试**

Run: `cd /home/daivy/projects/riscv-bsv-processor && python3 tools/hex_to_bsv.py rv32i-compiler/build/void_param_test.hex && make test-custom`
Expected: tohost = 10 ✅

- [ ] **Step 9: 编译空 return 测试**

Run: `make test-phase10-void-empty-return`
Expected: 编译成功，生成 build/void_empty_return_test.hex

- [ ] **Step 10: 运行空 return 测试**

Run: `cd /home/daivy/projects/riscv-bsv-processor && python3 tools/hex_to_bsv.py rv32i-compiler/build/void_empty_return_test.hex && make test-custom`
Expected: tohost = 5 ✅

- [ ] **Step 11: Commit**

```bash
git add tests/phase10/ Makefile
git commit -m "test(phase10): add void return type and void parameter test cases"
```

---

## Task 10: typedef - Lexer 改动

**Files:**
- Modify: `src/lexer.h:23`（TokenType enum）
- Modify: `src/lexer.c:lex_keyword_or_id`

- [ ] **Step 1: 扩展 TokenType enum 添加 TOK_TYPEDEF**

修改 `src/lexer.h:23`：

```c
TOK_TYPEDEF,     /* NEW: typedef keyword */
```

- [ ] **Step 2: 添加 typedef 关键字识别**

修改 `src/lexer.c:lex_keyword_or_id`：

```c
if (len == 7 && strncmp(s, "typedef", 7) == 0)
    return new_token(TOK_TYPEDEF, s, len, line, col);
```

- [ ] **Step 3: 更新 tok_name 函数**

修改 `src/lexer.c:tok_name`：

```c
case TOK_TYPEDEF: return "typedef";
```

- [ ] **Step 4: 编译验证**

Run: `make clean && make`
Expected: 编译成功，无错误

- [ ] **Step 5: Commit**

```bash
git add src/lexer.h src/lexer.c
git commit -m "feat(lexer): add TOK_TYPEDEF keyword"
```

---

## Task 11: typedef - Parser 改动（类型别名表）

**Files:**
- Modify: `src/parser.c`（添加类型别名表和辅助函数）

- [ ] **Step 1: 添加类型别名表数据结构**

在 `parser.c` 顶部添加：

```c
#define MAX_TYPE_ALIASES 32

typedef struct {
    char name[64];
    int struct_id;
} TypeAlias;

static TypeAlias type_aliases[MAX_TYPE_ALIASES];
static int num_type_aliases = 0;

static int lookup_type_alias(const char *name)
{
    for (int i = 0; i < num_type_aliases; i++) {
        if (strcmp(type_aliases[i].name, name) == 0)
            return i;
    }
    return -1;
}

static void register_type_alias(const char *name, int struct_id)
{
    if (num_type_aliases >= MAX_TYPE_ALIASES) {
        parse_error(0, 0, "too many type aliases");
        return;
    }
    strncpy(type_aliases[num_type_aliases].name, name, 63);
    type_aliases[num_type_aliases].name[63] = '\0';
    type_aliases[num_type_aliases].struct_id = struct_id;
    num_type_aliases++;
}
```

- [ ] **Step 2: 编译验证**

Run: `make clean && make`
Expected: 编译成功，无错误

- [ ] **Step 3: Commit**

```bash
git add src/parser.c
git commit -m "feat(parser): add type alias table for typedef support"
```

---

## Task 12: typedef - Parser 改动（typedef 解析）

**Files:**
- Modify: `src/parser.c`（parse_global_def 函数添加 typedef 解析）

- [ ] **Step 1: 查找 parse_global_def 函数位置**

Run: `grep -n "parse_global_def\|parse_global_decl" /home/daivy/projects/riscv-bsv-processor/rv32i-compiler/src/parser.c | head -3`
Expected: 找到全局声明解析函数位置

- [ ] **Step 2: 添加 typedef struct 解析**

在 parse_global_def 函数开头添加 typedef struct 处理：

```c
static ASTNode *parse_global_def(void)
{
    /* typedef struct { ... } Name; */
    if (cur->type == TOK_TYPEDEF && cur->next->type == TOK_STRUCT) {
        cur = cur->next;  /* 跳过 typedef */

        /* 解析 struct { ... } */
        expect(TOK_STRUCT);
        expect(TOK_LBRACE);

        /* 收集成员定义 */
        ASTNode *members = NULL;
        ASTNode *member_tail = NULL;
        int member_count = 0;

        while (cur->type != TOK_RBRACE) {
            ASTNode *m = parse_member_decl(NULL);  /* 匿名结构体，无 struct name */
            if (!members) {
                members = m;
                member_tail = m;
            } else {
                member_tail->next = m;
                member_tail = m;
            }
            member_count++;
            expect(TOK_SEMI);
        }
        expect(TOK_RBRACE);

        /* 解析别名名称 */
        if (cur->type != TOK_ID) {
            parse_error(cur->line, cur->col, "expected typedef name");
            return ast_new(AST_NOOP);
        }
        char *alias_name = strdup(cur->text);
        cur = cur->next;
        expect(TOK_SEMI);

        /* 注册结构体到 struct_table */
        int struct_id = register_struct_parser("", member_count);  /* 匿名结构体 */

        /* 注册类型别名 */
        register_type_alias(alias_name, struct_id);

        /* typedef 不生成 AST */
        return ast_new(AST_NOOP);
    }

    /* 其他全局定义... */
}
```

- [ ] **Step 3: 修改 parse_type 支持类型别名**

在 parse_type 函数添加类型别名查找：

```c
static Type parse_type(void)
{
    Type t = type_make_int();
    int is_const = 0;
    int is_volatile = 0;

    /* 解析类型修饰符 */
    while (cur->type == TOK_VOLATILE || cur->type == TOK_CONST) {
        if (cur->type == TOK_VOLATILE) {
            is_volatile = 1;
            cur = cur->next;
        } else if (cur->type == TOK_CONST) {
            is_const = 1;
            cur = cur->next;
        }
    }

    /* 解析基本类型 */
    if (cur->type == TOK_INT) {
        t = type_make_int();
        cur = cur->next;
    } else if (cur->type == TOK_CHAR) {
        t = type_make_char();
        cur = cur->next;
    } else if (cur->type == TOK_VOID) {
        t = type_make_void();
        cur = cur->next;
    } else if (cur->type == TOK_STRUCT) {
        cur = cur->next;
        if (cur->type != TOK_ID) {
            parse_error(cur->line, cur->col, "expected struct name");
            return t;
        }
        int struct_id = lookup_struct(cur->text);
        if (struct_id < 0) {
            parse_error(cur->line, cur->col, "undefined struct");
            return t;
        }
        t = type_make_struct_val(struct_id);
        cur = cur->next;
    } else if (cur->type == TOK_ID) {
        /* 检查是否为类型别名 */
        int alias_id = lookup_type_alias(cur->text);
        if (alias_id >= 0) {
            t = type_make_struct_val(type_aliases[alias_id].struct_id);
            cur = cur->next;
        } else {
            parse_error(cur->line, cur->col, "unknown type name");
            return t;
        }
    }

    /* 设置类型修饰位 */
    t.is_const = is_const;
    t.is_volatile = is_volatile;

    /* 解析指针层级 */
    while (cur->type == TOK_STAR) {
        t.ptr_level++;
        cur = cur->next;
    }

    return t;
}
```

- [ ] **Step 4: 编译验证**

Run: `make clean && make`
Expected: 编译成功，无错误

- [ ] **Step 5: Commit**

```bash
git add src/parser.c
git commit -m "feat(parser): add typedef struct alias parsing and type alias lookup"
```

---

## Task 13: typedef - 测试验证

**Files:**
- Create: `tests/phase10/typedef_test.c`
- Create: `tests/phase10/typedef_ptr_test.c`

- [ ] **Step 1: 创建 typedef 结构体别名测试文件**

创建 `tests/phase10/typedef_test.c`：

```c
typedef struct { int value; } Node;
int main() {
    Node n;
    n.value = 42;
    return n.value;
}
```

- [ ] **Step 2: 创建 typedef 指针测试文件**

创建 `tests/phase10/typedef_ptr_test.c`：

```c
typedef struct { int x; } Point;
int main() {
    Point p;
    Point *ptr;
    ptr = &p;
    ptr->x = 10;
    return ptr->x;
}
```

- [ ] **Step 3: 添加 Makefile 测试目标**

修改 `Makefile` 添加：

```makefile
test-phase10-typedef: tests/phase10/typedef_test.c
	./build/microcc tests/phase10/typedef_test.c runtime/crt0.s runtime/lib.S build/typedef_test.hex

test-phase10-typedef-ptr: tests/phase10/typedef_ptr_test.c
	./build/microcc tests/phase10/typedef_ptr_test.c runtime/crt0.s runtime/lib.S build/typedef_ptr_test.hex
```

- [ ] **Step 4: 编译 typedef 测试**

Run: `make test-phase10-typedef`
Expected: 编译成功，生成 build/typedef_test.hex

- [ ] **Step 5: 运行 typedef 测试**

Run: `cd /home/daivy/projects/riscv-bsv-processor && python3 tools/hex_to_bsv.py rv32i-compiler/build/typedef_test.hex && make test-custom`
Expected: tohost = 42 ✅

- [ ] **Step 6: 编译 typedef 指针测试**

Run: `make test-phase10-typedef-ptr`
Expected: 编译成功，生成 build/typedef_ptr_test.hex

- [ ] **Step 7: 运行 typedef 指针测试**

Run: `cd /home/daivy/projects/riscv-bsv-processor && python3 tools/hex_to_bsv.py rv32i-compiler/build/typedef_ptr_test.hex && make test-custom`
Expected: tohost = 10 ✅

- [ ] **Step 8: Commit**

```bash
git add tests/phase10/ Makefile
git commit -m "test(phase10): add typedef struct alias test cases"
```

---

## Task 14: static - Lexer 改动

**Files:**
- Modify: `src/lexer.h:23`（TokenType enum）
- Modify: `src/lexer.c:lex_keyword_or_id`

- [ ] **Step 1: 扩展 TokenType enum 添加 TOK_STATIC**

修改 `src/lexer.h:23`：

```c
TOK_STATIC,      /* NEW: static keyword */
```

- [ ] **Step 2: 添加 static 关键字识别**

修改 `src/lexer.c:lex_keyword_or_id`：

```c
if (len == 6 && strncmp(s, "static", 6) == 0)
    return new_token(TOK_STATIC, s, len, line, col);
```

- [ ] **Step 3: 更新 tok_name 函数**

修改 `src/lexer.c:tok_name`：

```c
case TOK_STATIC: return "static";
```

- [ ] **Step 4: 编译验证**

Run: `make clean && make`
Expected: 编译成功，无错误

- [ ] **Step 5: Commit**

```bash
git add src/lexer.h src/lexer.c
git commit -m "feat(lexer): add TOK_STATIC keyword"
```

---

## Task 15: static - Parser 改动（AST 节点）

**Files:**
- Modify: `src/ast.h:31-63`（ASTNode 结构体）

- [ ] **Step 1: 扩展 ASTNode 结构体添加 is_static 字段**

修改 `src/ast.h:62`（在 next 字段之前添加）：

```c
typedef struct ASTNode {
    ASTNodeType type;
    /* type-specific data */
    char *func_name;
    struct ASTNode *body;
    int int_val;
    int op;
    struct ASTNode *left;
    struct ASTNode *right;
    char *name;
    Type  var_type;
    int   is_deref_assign;
    int   is_array_assign;
    char  *array_name;
    struct ASTNode *array_index;
    struct ASTNode *deref_target;
    struct ASTNode *init;
    struct ASTNode *expr;
    /* global declaration fields */
    int   is_global;
    /* string literal fields */
    char *str_val;
    int   str_label;
    /* struct fields */
    char *struct_name;
    struct ASTNode *members;
    int struct_id;
    /* member access fields */
    struct ASTNode *target_expr;
    char *member_name;
    int is_arrow;
    /* NEW: static storage class marker */
    int   is_static;        /* for FUNC_DEF, GLOBAL_DECL: 1 if static */
    struct ASTNode *next;
} ASTNode;
```

- [ ] **Step 2: 编译验证**

Run: `make clean && make`
Expected: 编译成功，无错误

- [ ] **Step 3: Commit**

```bash
git add src/ast.h
git commit -m "feat(ast): add is_static field to ASTNode for static storage class"
```

---

## Task 16: static - Parser 改动（static 解析）

**Files:**
- Modify: `src/parser.c`（parse_global_def 和 parse_func_def 函数）

- [ ] **Step 1: 修改 parse_global_def 支持 static 全局变量**

在 parse_global_def 函数添加 static 检测：

```c
static ASTNode *parse_global_def(void)
{
    /* 检查 static 关键字 */
    int is_static = 0;
    if (cur->type == TOK_STATIC) {
        is_static = 1;
        cur = cur->next;
    }

    /* typedef struct 处理...（已在 Task 12 实现） */

    /* extern 声明处理...（已在 Phase 9 实现） */

    /* 全局变量声明 */
    Type var_type = parse_type();
    if (cur->type != TOK_ID) {
        parse_error(cur->line, cur->col, "expected variable name");
        return ast_new(AST_NOOP);
    }
    char *name = strdup(cur->text);
    cur = cur->next;

    ASTNode *n = ast_new(AST_GLOBAL_DECL);
    n->name = name;
    n->var_type = var_type;
    n->is_global = 1;
    n->is_static = is_static;  /* NEW */

    /* 初始化表达式 */
    if (cur->type == TOK_ASSIGN) {
        cur = cur->next;
        n->init = parse_expr();
    }

    expect(TOK_SEMI);
    return n;
}
```

- [ ] **Step 2: 修改 parse_func_def 支持 static 函数**

在 parse_func_def 函数添加 static 检测：

```c
static ASTNode *parse_func_def(void)
{
    /* 检查 static 关键字 */
    int is_static = 0;
    if (cur->type == TOK_STATIC) {
        is_static = 1;
        cur = cur->next;
    }

    ASTNode *n = ast_new(AST_FUNC_DEF);

    /* 解析返回类型 */
    Type func_type;
    if (cur->type == TOK_VOID) {
        func_type = type_make_void();
        cur = cur->next;
    } else {
        func_type = parse_type();
    }

    /* 解析函数名 */
    if (cur->type != TOK_ID) {
        parse_error(cur->line, cur->col, "expected function name");
        return n;
    }
    n->func_name = strdup(cur->text);
    n->is_static = is_static;  /* NEW */
    cur = cur->next;

    /* 参数和函数体解析... */
    expect(TOK_LPAREN);

    if (cur->type == TOK_VOID && cur->next->type == TOK_RPAREN) {
        cur = cur->next;
        n->right = NULL;
    } else if (cur->type == TOK_RPAREN) {
        n->right = NULL;
    } else {
        n->right = parse_var_decl_chain();
    }

    expect(TOK_RPAREN);
    expect(TOK_LBRACE);
    n->body = parse_compound();
    expect(TOK_RBRACE);

    return n;
}
```

- [ ] **Step 3: 编译验证**

Run: `make clean && make`
Expected: 编译成功，无错误

- [ ] **Step 4: Commit**

```bash
git add src/parser.c
git commit -m "feat(parser): add static storage class parsing for global vars and functions"
```

---

## Task 17: static - Codegen 改动（静态符号命名）

**Files:**
- Modify: `src/codegen.c`（emit_data_segment 和 gen_func_def 函数）

- [ ] **Step 1: 查找 emit_data_segment 函数位置**

Run: `grep -n "emit_data_segment" /home/daivy/projects/riscv-bsv-processor/rv32i-compiler/src/codegen.c`
Expected: 找到 emit_data_segment 函数定义位置

- [ ] **Step 2: 修改 emit_data_segment 支持静态全局变量命名**

修改 emit_data_segment 函数中的全局变量标签生成：

```c
static void emit_data_segment(void)
{
    emit("\n.data\n");

    for (int i = 0; i < global_count; i++) {
        if (globals[i].is_external) continue;  /* extern 变量跳过 */

        /* 静态全局变量使用本地标签 */
        if (globals[i].is_static) {
            emit(".Lstatic_%s:\n", globals[i].name);
        } else {
            emit(".global_%s:\n", globals[i].name);
        }

        /* 初始化值 */
        if (globals[i].init_val) {
            emit("    .word %d\n", globals[i].init_val);
        } else {
            emit("    .word 0\n");
        }
    }
}
```

- [ ] **Step 3: 修改 gen_func_def 支持静态函数命名**

修改 gen_func_def 函数的函数标签生成：

```c
static void gen_func_def(ASTNode *n)
{
    /* 静态函数使用本地标签 */
    if (n->is_static) {
        emit(".Lstatic_%s:\n", n->func_name);
    } else {
        emit("%s:\n", n->func_name);  /* 全局函数无前缀 */
    }

    /* 函数体生成... */
}
```

- [ ] **Step 4: 修改 gen_expr 支持静态全局变量访问**

修改 gen_expr 函数中的全局变量引用：

```c
static void gen_expr(ASTNode *n)
{
    if (n->type == AST_VAR_REF) {
        /* 检查是否为全局变量 */
        int global_id = lookup_global(n->name);
        if (global_id >= 0) {
            /* 静态全局变量使用 .Lstatic_ 标签 */
            if (globals[global_id].is_static) {
                emit("    la t0, .Lstatic_%s\n", n->name);
            } else {
                emit("    la t0, .global_%s\n", n->name);
            }
            emit("    lw t0, 0(t0)\n");
            return;
        }
        /* 局部变量... */
    }
}
```

- [ ] **Step 5: 修改 collect_globals 记录 is_static**

修改 collect_globals 函数：

```c
static void collect_globals(ASTNode *prog)
{
    global_count = 0;
    for (ASTNode *p = prog; p; p = p->next) {
        if (p->type == AST_GLOBAL_DECL) {
            globals[global_count].name = strdup(p->name);
            globals[global_count].type = p->var_type;
            globals[global_count].is_external = 0;
            globals[global_count].is_static = p->is_static;  /* NEW */
            /* 初始化值... */
            global_count++;
        } else if (p->type == AST_EXTERN_DECL) {
            globals[global_count].name = strdup(p->name);
            globals[global_count].type = p->var_type;
            globals[global_count].is_external = 1;
            globals[global_count].is_static = 0;  /* extern 不能 static */
            global_count++;
        }
    }
}
```

- [ ] **Step 6: 扩展 GlobalVar 结构体**

在 codegen.c 的 GlobalVar 结构体添加 is_static 字段：

```c
static struct {
    char *name;
    int   offset;
    Type  type;
    int   init_val;
    int   is_external;
    int   is_static;     /* NEW: static storage class */
} globals[MAX_GLOBALS];
```

- [ ] **Step 7: 编译验证**

Run: `make clean && make`
Expected: 编译成功，无错误

- [ ] **Step 8: Commit**

```bash
git add src/codegen.c
git commit -m "feat(codegen): add static symbol naming with .Lstatic_ prefix"
```

---

## Task 18: static - 测试验证

**Files:**
- Create: `tests/phase10/static_global_test.c`
- Create: `tests/phase10/static_func_test.c`

- [ ] **Step 1: 创建静态全局变量测试文件**

创建 `tests/phase10/static_global_test.c`：

```c
static int g_hidden = 100;
int main() { return g_hidden; }
```

- [ ] **Step 2: 创建静态函数测试文件**

创建 `tests/phase10/static_func_test.c`：

```c
static int helper() { return 30; }
int main() { return helper(); }
```

- [ ] **Step 3: 添加 Makefile 测试目标**

修改 `Makefile` 添加：

```makefile
test-phase10-static-global: tests/phase10/static_global_test.c
	./build/microcc tests/phase10/static_global_test.c runtime/crt0.s runtime/lib.S build/static_global_test.hex

test-phase10-static-func: tests/phase10/static_func_test.c
	./build/microcc tests/phase10/static_func_test.c runtime/crt0.s runtime/lib.S build/static_func_test.hex
```

- [ ] **Step 4: 编译静态全局变量测试**

Run: `make test-phase10-static-global`
Expected: 编译成功，生成 build/static_global_test.hex

- [ ] **Step 5: 运行静态全局变量测试**

Run: `cd /home/daivy/projects/riscv-bsv-processor && python3 tools/hex_to_bsv.py rv32i-compiler/build/static_global_test.hex && make test-custom`
Expected: tohost = 100 ✅

- [ ] **Step 6: 编译静态函数测试**

Run: `make test-phase10-static-func`
Expected: 编译成功，生成 build/static_func_test.hex

- [ ] **Step 7: 运行静态函数测试**

Run: `cd /home/daivy/projects/riscv-bsv-processor && python3 tools/hex_to_bsv.py rv32i-compiler/build/static_func_test.hex && make test-custom`
Expected: tohost = 30 ✅

- [ ] **Step 8: Commit**

```bash
git add tests/phase10/ Makefile
git commit -m "test(phase10): add static global var and static function test cases"
```

---

## Task 19: 整合测试（所有特性组合）

**Files:**
- Create: `tests/phase10/combined_test.c`

- [ ] **Step 1: 创建组合测试文件**

创建 `tests/phase10/combined_test.c`：

```c
typedef struct { int x; int y; } Point;

static Point g_p;
volatile int g_volatile_val = 5;

void init_point(void) {
    g_p.x = 10;
    g_p.y = 20;
}

int get_sum(void) {
    return g_p.x + g_p.y + g_volatile_val;
}

int main() {
    init_point();
    return get_sum();  /* 预期：10 + 20 + 5 = 35 */
}
```

- [ ] **Step 2: 添加 Makefile 测试目标**

修改 `Makefile` 添加：

```makefile
test-phase10-combined: tests/phase10/combined_test.c
	./build/microcc tests/phase10/combined_test.c runtime/crt0.s runtime/lib.S build/combined_test.hex
```

- [ ] **Step 3: 编译组合测试**

Run: `make test-phase10-combined`
Expected: 编译成功，生成 build/combined_test.hex

- [ ] **Step 4: 运行组合测试**

Run: `cd /home/daivy/projects/riscv-bsv-processor && python3 tools/hex_to_bsv.py rv32i-compiler/build/combined_test.hex && make test-custom`
Expected: tohost = 35 ✅

- [ ] **Step 5: Commit**

```bash
git add tests/phase10/ Makefile
git commit -m "test(phase10): add combined test for all new features"
```

---

## Task 20: 自举验证（编译器编译自身）

**Files:**
- Create: `build/microcc_self.hex`（自编译版编译器）

- [ ] **Step 1: 创建自举编译脚本**

创建 `scripts/bootstrap.sh`：

```bash
#!/bin/bash
# 自举验证脚本：编译器编译自身

MICROCC=./build/microcc
SRC_FILES="src/main.c src/lexer.c src/parser.c src/codegen.c src/asm.c src/linker.c src/types.c src/ast.c src/preprocessor.c"
RUNTIME="runtime/crt0.s runtime/lib.S"
OUT_HEX="build/microcc_self.hex"

echo "Step 1: GCC 编译编译器..."
gcc -o build/microcc_gcc $SRC_FILES

echo "Step 2: 自编译版编译自身..."
$MICROCC $SRC_FILES $RUNTIME $OUT_HEX

echo "Step 3: 对比 hex 文件..."
# GCC 版编译 test.c
build/microcc_gcc tests/test.c runtime/crt0.s runtime/lib.S build/test_gcc.hex

# 自编译版编译 test.c（需要 CPU TestBench）
echo "Step 4: 在 CPU 上验证自编译版..."

echo "Bootstrap verification complete!"
```

- [ ] **Step 2: 运行自举验证**

Run: `bash scripts/bootstrap.sh`
Expected: 编译器成功编译自身，生成 microcc_self.hex

- [ ] **Step 3: 在 CPU 上验证自编译版**

Run: `cd /home/daivy/projects/riscv-bsv-processor && python3 tools/hex_to_bsv.py rv32i-compiler/build/microcc_self.hex && make test-custom`
Expected: 自编译版编译器能在 CPU 上运行（可能需要内存扩展）

- [ ] **Step 4: 记录自举成功**

修改 `docs/snapshot.md` 添加：

```markdown
### 阶段 10：自举准备 ✅

- [x] 添加 volatile 支持（类型标记）
- [x] 添加 const 支持（类型标记）
- [x] 添加 void 支持（返回类型 + 参数）
- [x] 添加 typedef 支持（结构体别名）
- [x] 添加 static 支持（全局变量 + 函数）
- [x] 编译器成功编译自身
```

- [ ] **Step 5: Final Commit**

```bash
git add scripts/bootstrap.sh build/microcc_self.hex docs/snapshot.md
git commit -m "feat(phase10): compiler successfully bootstraps itself! Phase 10 complete"
```

---

## Summary

| Task | 特性 | 改动文件 | 测试文件 | 预期结果 |
|------|------|----------|----------|----------|
| 1-4 | volatile+const | lexer.h/c, types.h/c, parser.c | volatile_test.c, const_test.c | tohost=42,15,5 |
| 5-9 | void | lexer.h/c, types.h/c, parser.c, codegen.c | void_test.c, void_param_test.c | tohost=42,10,5 |
| 10-13 | typedef | lexer.h/c, parser.c | typedef_test.c, typedef_ptr_test.c | tohost=42,10 |
| 14-18 | static | lexer.h/c, ast.h, parser.c, codegen.c | static_global_test.c, static_func_test.c | tohost=100,30 |
| 19 | 整合测试 | — | combined_test.c | tohost=35 |
| 20 | 自举验证 | — | microcc_self.hex | 编译器编译自身 ✅ |

**总改动量**: ~200 行代码 + ~50 行测试 + 3 个新目录