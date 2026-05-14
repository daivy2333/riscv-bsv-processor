# 阶段 8：结构体支持设计文档

> 日期：2026-05-14 | 状态：Approved | 验证目标：链表求和

## 1. 目标与范围

### 1.1 目标

为 RV32I C 编译器添加完整结构体支持，最终实现编译器编译自身（编译器源码使用链表/树结构）。

### 1.2 范围

| 功能 | 支持 | 说明 |
|------|------|------|
| struct 定义 | ✓ | `struct Node { int value; struct Node* next; };` |
| struct 指针变量声明 | ✓ | `struct Node* p;` (局部/全局) |
| struct 值类型变量声明 | ✓ | `struct Node n;` (仅全局) |
| 成员访问 `->` | ✓ | `p->value`, `p->next` (指针成员访问) |
| 成员访问 `.` | ✓ | `n.value` (仅全局 struct 变量) |
| struct 作为函数参数 | ✓ | 仅指针传递 `struct Node* p` |
| struct 作为返回值 | ✓ | 仅指针返回 `struct Node* func()` |
| 自引用结构体 | ✓ | `struct Node* next` (链表/树) |

### 1.3 不包含

| 功能 | 原因 |
|------|------|
| 结构体值传递 | 编译器源码几乎不用，实现复杂度高 |
| 局部 struct 值类型变量 | 需要 struct 复制逻辑，推迟到后续阶段 |
| 嵌套嵌入 | `struct A { struct B field; }` 推迟 |
| 匿名结构体 | 编译器源码不常用 |

### 1.4 验证测试

**链表求和测试**：创建 3 节点链表，遍历求和，验证返回值 60。

```c
struct Node {
    int value;
    struct Node* next;
};

struct Node g_n1;
struct Node g_n2;
struct Node g_n3;

int sum_list(struct Node* head) {
    int total = 0;
    struct Node* p = head;
    while (p != 0) {
        total = total + p->value;
        p = p->next;
    }
    return total;
}

int main() {
    g_n1.value = 10;
    g_n1.next = &g_n2;
    g_n2.value = 20;
    g_n2.next = &g_n3;
    g_n3.value = 30;
    g_n3.next = 0;
    return sum_list(&g_n1);
}
```

---

## 2. 架构设计

### 2.1 核心设计：全局结构体表

结构体定义信息存储在全局表中，类似于现有的全局变量表 (`globals[]`)。

**设计理由**：
- 符合现有"全局符号表"架构风格
- Parser 解析时注册，Codegen 生成时查询
- 改动集中，增量实现

### 2.2 数据流

```
源码 struct Node { ... };
    ↓ Parser (parse_struct_def)
注册到 struct_table[]
    ↓ Parser (parse_struct_decl)
Type.struct_id 指向 struct_table 索引
    ↓ Codegen (AST_MEMBER_ACCESS)
查询 struct_table → 获取 member.offset → 生成 addi + lw
```

---

## 3. 类型系统扩展

### 3.1 BaseType 新增

```c
// types.h
typedef enum {
    TYPE_INT = 0,
    TYPE_CHAR = 1,
    TYPE_STRUCT = 2  // 新增
} BaseType;
```

### 3.2 Type 结构体扩展

```c
// types.h
typedef struct {
    BaseType base_type;
    int ptr_level;       // 0=值类型, 1=指针
    int array_size;
    int struct_id;       // 新增：struct_table 索引 (仅 TYPE_STRUCT 有效)
} Type;
```

### 3.3 StructInfo 定义

```c
// types.h 或 codegen.h
typedef struct MemberInfo {
    char *name;         // 成员名称
    Type type;          // 成员类型
    int offset;         // 字节偏移 (自动计算)
} MemberInfo;

typedef struct StructInfo {
    char *name;         // 结构体名称
    MemberInfo *members; // 成员数组 (动态分配)
    int member_count;   // 成员数量
    int total_size;     // 总字节大小
} StructInfo;
```

### 3.4 辅助函数新增

```c
// types.h
Type type_make_struct_ptr(int struct_id);  // 创建 struct Name* 类型
Type type_make_struct_val(int struct_id);  // 创建 struct Name 类型 (用于全局变量)
int type_is_struct(Type t);                // 检查是否为结构体类型

// codegen.c 或单独文件
StructInfo* get_struct_info(int struct_id);    // 获取结构体信息
int register_struct(char *name, MemberInfo *members, int count); // 注册结构体
int lookup_struct(const char *name);            // 查找结构体 ID
int get_member_offset(int struct_id, const char *member_name);  // 获取成员偏移
```

---

## 4. AST 扩展

### 4.1 新增节点类型

```c
// ast.h
typedef enum {
    // ... 现有类型
    AST_STRUCT_DEF,      // struct 定义语句
    AST_MEMBER_ACCESS    // 成员访问表达式 (p->member 或 n.member)
} ASTNodeType;
```

### 4.2 ASTNode 新增字段

```c
// ast.h ASTNode 结构体
typedef struct ASTNode {
    // ... 现有字段

    // for AST_STRUCT_DEF
    char *struct_name;        // 结构体名称
    ASTNode *members;         // 成员链表 (每个成员是 AST_VAR_DECL)
    int struct_id;            // 注册后的结构体 ID

    // for AST_MEMBER_ACCESS
    ASTNode *target_expr;     // 目标表达式 (p 或 n)
    char *member_name;        // 成员名称
    int is_arrow;             // 1=p->member, 0=n.member
} ASTNode;
```

---

## 5. Parser 解析逻辑

### 5.1 新增 Token 类型

```c
// lexer.h
typedef enum {
    // ... 现有类型
    TOK_STRUCT,    // "struct" 关键字
    TOK_ARROW      // "->" 操作符
} TokenType;
```

Lexer 需识别：
- `struct` 关键字 → `TOK_STRUCT`
- `->` 操作符 → `TOK_ARROW`

### 5.2 新增解析函数

**parse_struct_def()**：
```c
// 解析 struct Name { member-list };
static ASTNode *parse_struct_def(void)
{
    cur = cur->next;  // skip "struct"

    char *name = strdup(cur->text);  // 结构体名称
    cur = cur->next;

    expect(TOK_LBRACE);

    // 解析成员列表
    ASTNode *members = NULL, *tail = NULL;
    int offset = 0;

    while (cur->type != TOK_RBRACE) {
        ASTNode *member = parse_member_decl();  // 解析单个成员
        member->var_type.offset = offset;       // 设置偏移
        offset += get_type_size(member->var_type);  // int=4, pointer=4

        if (!members) members = tail = member;
        else { tail->next = member; tail = member; }
    }

    expect(TOK_RBRACE);
    expect(TOK_SEMI);

    ASTNode *n = ast_new(AST_STRUCT_DEF);
    n->struct_name = name;
    n->members = members;
    return n;
}
```

**parse_member_decl()**：
```c
// 解析成员声明: int name 或 struct Name* name
static ASTNode *parse_member_decl(void)
{
    Type member_type;

    if (cur->type == TOK_INT) {
        member_type = type_make_int();
        cur = cur->next;
    } else if (cur->type == TOK_STRUCT) {
        cur = cur->next;  // skip "struct"
        char *struct_name = strdup(cur->text);
        cur = cur->next;

        int struct_id = lookup_struct(struct_name);  // 查找结构体定义

        if (cur->type == TOK_STAR) {
            member_type = type_make_struct_ptr(struct_id);
            cur = cur->next;  // skip "*"
        } else {
            member_type = type_make_struct_val(struct_id);
        }
    }

    if (cur->type != TOK_ID) {
        parse_error(...);
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

**parse_struct_decl()**：
```c
// 解析 struct 变量声明: struct Name* var 或 struct Name var (仅全局)
static ASTNode *parse_struct_decl(int is_global)
{
    cur = cur->next;  // skip "struct"

    char *struct_name = strdup(cur->text);
    cur = cur->next;

    int struct_id = lookup_struct(struct_name);
    if (struct_id < 0) {
        parse_error(...);
        return NULL;
    }

    Type var_type;
    if (cur->type == TOK_STAR) {
        var_type = type_make_struct_ptr(struct_id);
        cur = cur->next;
    } else {
        if (!is_global) {
            parse_error(..., "局部 struct 值类型变量不支持");
            return NULL;
        }
        var_type = type_make_struct_val(struct_id);
    }

    if (cur->type != TOK_ID) {
        parse_error(...);
        return NULL;
    }

    ASTNode *n = ast_new(is_global ? AST_GLOBAL_DECL : AST_VAR_DECL);
    n->name = strdup(cur->text);
    n->var_type = var_type;
    n->is_global = is_global;
    cur = cur->next;
    expect(TOK_SEMI);

    return n;
}
```

**parse_member_access()**：
```c
// 解析 p->member 或 n.member
static ASTNode *parse_member_access(ASTNode *target)
{
    int is_arrow = (cur->type == TOK_ARROW);
    cur = cur->next;  // skip "->" or "."

    if (cur->type != TOK_ID) {
        parse_error(...);
        return NULL;
    }

    ASTNode *n = ast_new(AST_MEMBER_ACCESS);
    n->target_expr = target;
    n->member_name = strdup(cur->text);
    n->is_arrow = is_arrow;
    cur = cur->next;

    return n;
}
```

### 5.3 parse_primary 修改

在 `parse_primary()` 中处理 `->` 和 `.`：

```c
if (cur->type == TOK_ID) {
    char *name = strdup(cur->text);
    cur = cur->next;

    // 函数调用
    if (cur->type == TOK_LPAREN) { ... }

    // 数组访问
    if (cur->type == TOK_LBRACKET) { ... }

    // 成员访问
    if (cur->type == TOK_ARROW || cur->type == TOK_DOT) {
        ASTNode *ref = ast_new(AST_VAR_REF);
        ref->name = name;
        return parse_member_access(ref);
    }

    // 变量引用
    ASTNode *n = ast_new(AST_VAR_REF);
    n->name = name;
    return n;
}
```

### 5.4 parse_program 修改

在顶层区分 struct 定义、struct 全局声明、函数定义：

```c
static ASTNode *parse_program(void)
{
    ASTNode dummy = {0};
    ASTNode *tail = &dummy;

    while (cur->type != TOK_EOF) {
        ASTNode *node = NULL;

        // struct 定义: struct Name { ... };
        if (cur->type == TOK_STRUCT && cur->next && cur->next->next && cur->next->next->type == TOK_LBRACE) {
            node = parse_struct_def();
        }
        // struct 全局声明: struct Name* var; 或 struct Name var;
        else if (cur->type == TOK_STRUCT) {
            node = parse_struct_decl(1);  // is_global=1
        }
        // 函数定义或 int/char 全局声明
        else if (cur->type == TOK_INT || cur->type == TOK_CHAR) {
            // ... 现有逻辑
        }

        if (!node) break;
        tail->next = node;
        tail = node;
    }

    return dummy.next;
}
```

---

## 6. Codegen 生成逻辑

### 6.1 struct_table 注册

在 Pass 0 (`collect_globals`) 后新增 Pass 0.5：注册结构体定义。

```c
#define MAX_STRUCTS 32

static StructInfo struct_table[MAX_STRUCTS];
static int struct_count;

static void register_structs(ASTNode *prog)
{
    struct_count = 0;

    for (ASTNode *n = prog; n; n = n->next) {
        if (n->type == AST_STRUCT_DEF) {
            StructInfo *si = &struct_table[struct_count];
            si->name = strdup(n->struct_name);
            si->member_count = 0;
            si->total_size = 0;

            // 计算成员数量
            for (ASTNode *m = n->members; m; m = m->next)
                si->member_count++;

            // 分配成员数组
            si->members = malloc(si->member_count * sizeof(MemberInfo));

            // 注册成员并计算偏移
            int offset = 0;
            int idx = 0;
            for (ASTNode *m = n->members; m; m = m->next, idx++) {
                si->members[idx].name = strdup(m->name);
                si->members[idx].type = m->var_type;
                si->members[idx].offset = offset;

                int size = get_type_size(m->var_type);  // int=4, pointer=4
                offset += size;
            }

            si->total_size = offset;
            n->struct_id = struct_count;
            struct_count++;
        }
    }
}
```

### 6.2 get_type_size 实现

```c
static int get_type_size(Type t)
{
    if (t.ptr_level > 0)
        return 4;  // 所有指针都是 4 字节
    if (t.base_type == TYPE_INT)
        return 4;
    if (t.base_type == TYPE_CHAR)
        return 1;
    if (t.base_type == TYPE_STRUCT)
        return struct_table[t.struct_id].total_size;
    return 4;  // 默认
}
```

### 6.3 AST_MEMBER_ACCESS 处理

```c
case AST_MEMBER_ACCESS: {
    // 1. 计算目标地址 (target_expr)
    gen_expr(n->target_expr);  // t0 = p (指针值) 或 &n (全局地址)

    // 2. 查询成员偏移
    Type target_type = get_expr_type(n->target_expr);  // 获取目标类型
    int struct_id = target_type.struct_id;
    int offset = get_member_offset(struct_id, n->member_name);

    // 3. 计算成员地址
    emit("    addi t0, t0, %d\n", offset);  // t0 = &target->member

    // 4. 加载成员值
    MemberInfo *mi = find_member(struct_id, n->member_name);
    if (mi->type.ptr_level > 0 || mi->type.base_type == TYPE_INT) {
        emit("    lw t0, 0(t0)\n");  // 加载指针或 int
    } else if (mi->type.base_type == TYPE_CHAR) {
        emit("    lb t0, 0(t0)\n");  // 加载 char
    }
    // struct 值类型成员不加载，返回地址（用于赋值）
    break;
}
```

### 6.4 全局 struct 变量处理

在 `collect_globals()` 中处理 `AST_GLOBAL_DECL` 且 `var_type.base_type == TYPE_STRUCT`：

```c
// collect_globals 修改
if (n->type == AST_GLOBAL_DECL) {
    globals[global_count].name = strdup(n->name);
    globals[global_count].type = n->var_type;
    globals[global_count].offset = data_offset;

    if (n->var_type.base_type == TYPE_STRUCT) {
        // struct 值类型全局变量
        StructInfo *si = &struct_table[n->var_type.struct_id];
        data_offset += si->total_size;
    } else if (n->var_type.ptr_level > 0 && n->var_type.base_type == TYPE_STRUCT) {
        // struct 指针全局变量 - 4 字节
        data_offset += 4;
    }
    // ... 其他类型
    global_count++;
}
```

在 `emit_data_segment()` 中输出全局 struct 变量：

```c
// emit_data_segment 修改
for (int i = 0; i < global_count; i++) {
    emit(".global_%s:\n", globals[i].name);

    if (globals[i].type.base_type == TYPE_STRUCT && globals[i].type.ptr_level == 0) {
        // struct 值类型 - 输出 total_size 字节的 0
        StructInfo *si = &struct_table[globals[i].type.struct_id];
        for (int j = 0; j < si->total_size / 4; j++)
            emit("    .word 0\n");
    }
    // ... 其他类型
}
```

### 6.5 struct 成员赋值处理

在 `gen_stmt(AST_ASSIGN)` 中处理 `n.member = value` 或 `p->member = value`：

```c
// AST_ASSIGN 处理
case AST_ASSIGN:
    gen_expr(n->expr);  // 右值 → t0

    // 检查是否为成员访问赋值
    if (n->target_expr && n->target_expr->type == AST_MEMBER_ACCESS) {
        int my_off = spill_depth * 4;
        emit("    sw t0, %d(sp)\n", my_off);  // 保存右值

        // 计算成员地址
        gen_expr(n->target_expr);  // t0 = &target->member

        // 存储值
        emit("    lw t1, %d(sp)\n", my_off);  // t1 = 右值
        emit("    sw t1, 0(t0)\n");           // 存储到成员
    }
    // ... 其他赋值处理
    break;
```

---

## 7. 文件改动清单

| 文件 | 改动类型 | 说明 |
|------|----------|------|
| `src/lexer.c/h` | 扩展 | 新增 TOK_STRUCT, TOK_ARROW, TOK_DOT |
| `src/types.c/h` | 扩展 | 新增 TYPE_STRUCT, StructInfo, MemberInfo, 辅助函数 |
| `src/ast.c/h` | 扩展 | 新增 AST_STRUCT_DEF, AST_MEMBER_ACCESS, 新字段 |
| `src/parser.c` | 扩展 | 新增 parse_struct_def/decl/access, 修改 parse_program/primary |
| `src/codegen.c` | 扩展 | 新增 struct_table, register_structs, AST_MEMBER_ACCESS 处理, 全局 struct |
| `tests/phase8/` | 新增 | 链表求和测试 |

---

## 8. 测试计划

### 8.1 测试 1：struct 定义与指针成员访问

```c
struct Node {
    int value;
    struct Node* next;
};

int main() {
    struct Node n;
    n.value = 42;
    struct Node* p = &n;
    return p->value;  // 期望 42
}
```

**问题**：局部 struct 值类型变量不支持。

**调整**：使用全局 struct 变量。

```c
struct Node { int value; struct Node* next; };
struct Node g_n;

int main() {
    g_n.value = 42;
    struct Node* p = &g_n;
    return p->value;  // 期望 42
}
```

### 8.2 测试 2：链表遍历

完整链表求和测试（见 1.4）。

### 8.3 测试 3：struct 作为函数参数

```c
struct Node { int value; };

int get_value(struct Node* p) {
    return p->value;
}

int main() {
    struct Node n;
    n.value = 100;
    return get_value(&n);  // 期望 100
}
```

### 8.4 测试 4：struct 作为返回值

```c
struct Node { int value; struct Node* next; };

struct Node* create_node(int v) {
    struct Node n;  // 不支持局部值类型
    n.value = v;
    n.next = 0;
    return &n;  // 返回局部变量地址 - 不安全，编译器应警告或拒绝
}
```

**调整**：使用全局变量工厂模式。

```c
struct Node { int value; struct Node* next; };
struct Node g_pool[10];
int g_idx = 0;

struct Node* create_node(int v) {
    struct Node* n = &g_pool[g_idx];
    g_idx = g_idx + 1;
    n->value = v;
    n->next = 0;
    return n;
}

int main() {
    struct Node* n1 = create_node(10);
    struct Node* n2 = create_node(20);
    return n1->value + n2->value;  // 期望 30
}
```

---

## 9. 风险与缓解

### 9.1 未定义结构体引用

**风险**：代码引用未定义的结构体名称。

**缓解**：Parser 在 `lookup_struct()` 失败时报错，拒绝编译。

### 9.2 成员名称不存在

**风险**：`p->nonexistent` 访问不存在成员。

**缓解**：Codegen 在 `get_member_offset()` 失败时报错。

### 9.3 类型不匹配

**风险**：对非 struct 类型使用 `->` 或 `.`。

**缓解**：Parser 检查目标类型是否为 TYPE_STRUCT。

### 9.4 局部 struct 值类型变量

**风险**：用户尝试声明局部 struct 值类型变量。

**缓解**：Parser 在 `parse_struct_decl(is_global=0)` 时检查 `ptr_level`，拒绝值类型。

---

## 10. 后续扩展方向

### 10.1 阶段 9 预备

- 局部 struct 值类型变量（栈分配 + 复制）
- 结构体值传递（多寄存器传递或栈传递）
- 嵌套嵌入结构体

### 10.2 自举验证

阶段 8 完成后，编译器应能编译包含链表/树结构的数据结构代码。阶段 10 自举时，编译器自身的 AST/Token 结构体代码应可编译。

---

## 附录 A：语法规则总结

```
struct-def      = "struct" identifier "{" member-list "}" ";"
member-list     = member { ";" member }
member          = ("int" | "struct" identifier) ["*"] identifier

struct-decl     = "struct" identifier ["*"] identifier ";"

member-access   = primary ("->" | ".") identifier

primary         = integer-literal
                | string-literal
                | identifier [ "(" args ")" | "[" expr "]" | ("->"|".") identifier ]
                | "&" primary
                | "*" primary
                | "(" expr ")"
```

---

## 附录 B：实现优先级

| 优先级 | 任务 | 依赖 |
|--------|------|------|
| P0 | types.h/c 扩展 | 无 |
| P0 | lexer TOK_STRUCT/ARROW/DOT | 无 |
| P1 | ast.h AST_STRUCT_DEF/MEMBER_ACCESS | P0 |
| P1 | parser parse_struct_def | P0, P1 |
| P1 | parser parse_struct_decl | P1 |
| P2 | codegen struct_table 注册 | P1 |
| P2 | codegen AST_MEMBER_ACCESS | P2 |
| P2 | codegen 全局 struct 变量 | P2 |
| P3 | 测试 1-4 | 全部完成 |