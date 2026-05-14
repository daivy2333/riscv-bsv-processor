# 阶段 8：结构体支持实现计划

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** 为 RV32I C 编译器添加完整结构体支持，验证链表求和测试。

**Architecture:** 全局结构体表 + Parser 注册 + Codegen 查询生成成员偏移。

**Tech Stack:** C (Micro-C), RV32I + Zicsr, CPU TestBench + tohost

---

## Task 1: types.h 扩展 - TYPE_STRUCT 和结构体信息结构

**Files:**
- Modify: `src/types.h`

- [ ] **Step 1: 添加 TYPE_STRUCT 到 BaseType 枚举**

```c
// src/types.h 第 4-8 行，修改 BaseType 定义
typedef enum {
    TYPE_INT = 0,
    TYPE_CHAR = 1,
    TYPE_STRUCT = 2  /* 新增：结构体类型 */
} BaseType;
```

- [ ] **Step 2: 添加 struct_id 字段到 Type 结构体**

```c
// src/types.h 第 10-14 行，修改 Type 定义
typedef struct {
    BaseType base_type;  /* TYPE_INT, TYPE_CHAR, TYPE_STRUCT */
    int ptr_level;       /* Pointer level: 0 = scalar, 1 = pointer */
    int array_size;      /* Array size: 0 = not array, >0 = array elements count */
    int struct_id;       /* 新增：struct_table 索引 (仅 TYPE_STRUCT 有效) */
} Type;
```

- [ ] **Step 3: 添加 MemberInfo 和 StructInfo 结构体定义**

```c
// src/types.h 在 Type 结构体定义之后添加
/* 结构体成员信息 */
typedef struct MemberInfo {
    char *name;         /* 成员名称 */
    Type type;          /* 成员类型 */
    int offset;         /* 字节偏移 */
} MemberInfo;

/* 结构体定义信息 */
typedef struct StructInfo {
    char *name;         /* 结构体名称 */
    MemberInfo *members; /* 成员数组 */
    int member_count;   /* 成员数量 */
    int total_size;     /* 总字节大小 */
} StructInfo;
```

- [ ] **Step 4: 添加新辅助函数声明**

```c
// src/types.h 在现有函数声明之后添加
/* 结构体类型辅助函数 */
Type type_make_struct_ptr(int struct_id);  /* 创建 struct Name* 类型 */
Type type_make_struct_val(int struct_id);  /* 创建 struct Name 类型 */
int  type_is_struct(Type t);                /* 检查是否为结构体类型 */
```

- [ ] **Step 5: Commit**

```bash
git add src/types.h
git commit -m "feat(phase8): add TYPE_STRUCT and StructInfo/MemberInfo definitions"
```

---

## Task 2: types.c 扩展 - 结构体类型辅助函数实现

**Files:**
- Modify: `src/types.c`

- [ ] **Step 1: 实现 type_make_struct_ptr**

```c
// src/types.c 在文件末尾添加
Type type_make_struct_ptr(int struct_id)
{
    Type t = { .base_type = TYPE_STRUCT, .ptr_level = 1, .array_size = 0, .struct_id = struct_id };
    return t;
}
```

- [ ] **Step 2: 实现 type_make_struct_val**

```c
// src/types.c 在 type_make_struct_ptr 之后添加
Type type_make_struct_val(int struct_id)
{
    Type t = { .base_type = TYPE_STRUCT, .ptr_level = 0, .array_size = 0, .struct_id = struct_id };
    return t;
}
```

- [ ] **Step 3: 实现 type_is_struct**

```c
// src/types.c 在 type_make_struct_val 之后添加
int type_is_struct(Type t)
{
    return t.base_type == TYPE_STRUCT;
}
```

- [ ] **Step 4: Commit**

```bash
git add src/types.c
git commit -m "feat(phase8): implement struct type helper functions"
```

---

## Task 3: lexer.h 扩展 - 新增 Token 类型

**Files:**
- Modify: `src/lexer.h`

- [ ] **Step 1: 添加 TOK_STRUCT, TOK_ARROW, TOK_DOT 到 TokenType 枚举**

```c
// src/lexer.h TokenType 枚举定义，在现有类型末尾添加
typedef enum {
    // ... 现有类型 (TOK_EOF, TOK_NUM, TOK_ID, TOK_INT, TOK_CHAR, ...)
    TOK_STRUCT,    /* "struct" 关键字 */
    TOK_ARROW,     /* "->" 操作符 */
    TOK_DOT        /* "." 成员访问操作符 */
} TokenType;
```

- [ ] **Step 2: Commit**

```bash
git add src/lexer.h
git commit -m "feat(phase8): add TOK_STRUCT, TOK_ARROW, TOK_DOT token types"
```

---

## Task 4: lexer.c 扩展 - 识别 struct 关键字和 -> 操作符

**Files:**
- Modify: `src/lexer.c`

- [ ] **Step 1: 在关键字表中添加 "struct"**

先读取 lexer.c 确认关键字表位置。

```c
// src/lexer.c 关键字识别逻辑（通常在 tokenize 函数内）
// 在识别 "int", "char", "return" 等关键字的地方添加：
if (strcmp(text, "struct") == 0) return TOK_STRUCT;
```

- [ ] **Step 2: 添加 "->" 操作符识别**

```c
// src/lexer.c 在操作符识别逻辑中添加
// 在识别 "-" 之后，检查下一个字符是否为 '>'：
if (c == '-' && peek() == '>') {
    advance(); advance();
    return TOK_ARROW;
}
```

- [ ] **Step 3: 添加 "." 操作符识别**

```c
// src/lexer.c 在操作符识别逻辑中添加
if (c == '.') {
    advance();
    return TOK_DOT;
}
```

- [ ] **Step 4: Commit**

```bash
git add src/lexer.c
git commit -m "feat(phase8): lexer recognize 'struct' keyword and '->' operator"
```

---

## Task 5: ast.h 扩展 - 新增 AST 节点类型和字段

**Files:**
- Modify: `src/ast.h`

- [ ] **Step 1: 添加 AST_STRUCT_DEF 和 AST_MEMBER_ACCESS 到 ASTNodeType**

```c
// src/ast.h ASTNodeType 枚举定义，在现有类型末尾添加
typedef enum {
    // ... 现有类型 (AST_GLOBAL_DECL, AST_FUNC_DEF, ...)
    AST_STRUCT_DEF,      /* struct 定义语句 */
    AST_MEMBER_ACCESS    /* 成员访问表达式 p->member 或 n.member */
} ASTNodeType;
```

- [ ] **Step 2: 添加新字段到 ASTNode 结构体**

```c
// src/ast.h ASTNode 结构体定义，在现有字段后添加
typedef struct ASTNode {
    // ... 现有字段

    /* for AST_STRUCT_DEF */
    char *struct_name;        /* 结构体名称 */
    struct ASTNode *members;  /* 成员链表 (每个成员是 AST_VAR_DECL) */
    int struct_id;            /* 注册后的结构体 ID */

    /* for AST_MEMBER_ACCESS */
    struct ASTNode *target_expr; /* 目标表达式 (p 或 n) */
    char *member_name;        /* 成员名称 */
    int is_arrow;             /* 1=p->member, 0=n.member */

    struct ASTNode *next;     /* linked-list chain */
} ASTNode;
```

- [ ] **Step 3: Commit**

```bash
git add src/ast.h
git commit -m "feat(phase8): add AST_STRUCT_DEF and AST_MEMBER_ACCESS node types"
```

---

## Task 6: parser.c 扩展 - struct 定义和成员声明解析（Part 1）

**Files:**
- Modify: `src/parser.c`

- [ ] **Step 1: 添加全局结构体表和查找函数**

```c
// src/parser.c 在文件开头全局变量区域添加
#define MAX_STRUCTS 32

static StructInfo parser_struct_table[MAX_STRUCTS];
static int parser_struct_count;

/* 在 Parser 中查找结构体定义 */
static int lookup_struct(const char *name)
{
    for (int i = 0; i < parser_struct_count; i++)
        if (strcmp(parser_struct_table[i].name, name) == 0)
            return i;
    return -1;
}

/* 在 Parser 中注册结构体（简化版，仅记录名称和成员数量） */
static int register_struct_parser(const char *name, int member_count)
{
    parser_struct_table[parser_struct_count].name = strdup(name);
    parser_struct_table[parser_struct_count].member_count = member_count;
    parser_struct_table[parser_struct_count].total_size = 0;  /* Codegen 计算实际大小 */
    parser_struct_table[parser_struct_count].members = NULL;  /* Codegen 从 AST 获取 */
    return parser_struct_count++;
}
```

- [ ] **Step 2: 添加 parse_member_decl 函数**

```c
// src/parser.c 在 parse_var_decl 之后添加
/* 成员声明: int name 或 struct Name* name */
static ASTNode *parse_member_decl(void)
{
    Type member_type;

    if (cur->type == TOK_INT) {
        member_type = type_make_int();
        cur = cur->next;
    } else if (cur->type == TOK_CHAR) {
        member_type = type_make_char();
        cur = cur->next;
    } else if (cur->type == TOK_STRUCT) {
        cur = cur->next;  /* skip "struct" */
        if (cur->type != TOK_ID) {
            parse_error(cur->line, cur->col, "expected struct name");
            return NULL;
        }
        char *struct_name = strdup(cur->text);
        cur = cur->next;

        int struct_id = lookup_struct(struct_name);
        if (struct_id < 0) {
            parse_error(cur->line, cur->col, "undefined struct type");
            return NULL;
        }

        if (cur->type == TOK_STAR) {
            member_type = type_make_struct_ptr(struct_id);
            cur = cur->next;
        } else {
            member_type = type_make_struct_val(struct_id);
        }
    } else {
        parse_error(cur->line, cur->col, "expected member type (int/char/struct)");
        return NULL;
    }

    if (cur->type != TOK_ID) {
        parse_error(cur->line, cur->col, "expected member name");
        return NULL;
    }

    ASTNode *n = ast_new(AST_VAR_DECL);
    n->name = strdup(cur->text);
    n->var_type = member_type;
    cur = cur->next;
    expect(TOK_SEMI);

    return n;
}
```

- [ ] **Step 3: Commit**

```bash
git add src/parser.c
git commit -m "feat(phase8): add parser struct table and parse_member_decl"
```