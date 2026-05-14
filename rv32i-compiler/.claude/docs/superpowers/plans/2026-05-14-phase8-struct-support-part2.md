# 阶段 8：结构体支持实现计划 - Part 2

> 续 Part 1 (Task 1-6)，本部分包含 Task 7-11

---

## Task 7: parser.c 扩展 - parse_struct_def 和 parse_struct_decl

**Files:**
- Modify: `src/parser.c`

- [ ] **Step 1: 添加 parse_struct_def 函数**

```c
// src/parser.c 在 parse_member_decl 之后添加
/* struct 定义: struct Name { member-list }; */
static ASTNode *parse_struct_def(void)
{
    cur = cur->next;  /* skip "struct" */

    if (cur->type != TOK_ID) {
        parse_error(cur->line, cur->col, "expected struct name");
        return NULL;
    }
    char *name = strdup(cur->text);
    cur = cur->next;

    expect(TOK_LBRACE);

    /* 解析成员列表 */
    ASTNode *members = NULL, *tail = NULL;
    int member_count = 0;

    while (cur->type != TOK_RBRACE) {
        ASTNode *member = parse_member_decl();
        if (!member) break;
        member_count++;
        if (!members) members = tail = member;
        else { tail->next = member; tail = member; }
    }

    expect(TOK_RBRACE);
    expect(TOK_SEMI);

    /* 注册结构体 */
    int struct_id = register_struct_parser(name, member_count);

    ASTNode *n = ast_new(AST_STRUCT_DEF);
    n->struct_name = name;
    n->members = members;
    n->struct_id = struct_id;
    return n;
}
```

- [ ] **Step 2: 添加 parse_struct_decl 函数**

```c
// src/parser.c 在 parse_struct_def 之后添加
/* struct 变量声明: struct Name* var 或 struct Name var (仅全局) */
static ASTNode *parse_struct_decl(int is_global)
{
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

    Type var_type;
    if (cur->type == TOK_STAR) {
        var_type = type_make_struct_ptr(struct_id);
        cur = cur->next;
    } else {
        /* 值类型 struct 变量 */
        if (!is_global) {
            parse_error(cur->line, cur->col, "local struct value type not supported");
            return NULL;
        }
        var_type = type_make_struct_val(struct_id);
    }

    if (cur->type != TOK_ID) {
        parse_error(cur->line, cur->col, "expected variable name");
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

- [ ] **Step 3: Commit**

```bash
git add src/parser.c
git commit -m "feat(phase8): add parse_struct_def and parse_struct_decl"
```

---

## Task 8: parser.c 扩展 - parse_member_access 和 parse_primary/parse_program 改造

**Files:**
- Modify: `src/parser.c`

- [ ] **Step 1: 添加 parse_member_access 函数**

```c
// src/parser.c 在 parse_struct_decl 之后添加
/* 成员访问: p->member 或 n.member */
static ASTNode *parse_member_access(ASTNode *target)
{
    int is_arrow = (cur->type == TOK_ARROW);
    cur = cur->next;  /* skip "->" or "." */

    if (cur->type != TOK_ID) {
        parse_error(cur->line, cur->col, "expected member name");
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

- [ ] **Step 2: 修改 parse_primary 处理成员访问**

在 `parse_primary()` 的 `TOK_ID` 分支中，识别函数调用/数组访问后添加成员访问：

```c
// src/parser.c parse_primary 函数内，TOK_ID 分支
if (cur->type == TOK_ID) {
    char *name = strdup(cur->text);
    cur = cur->next;

    /* 函数调用 */
    if (cur->type == TOK_LPAREN) { ... }  /* 现有逻辑保持 */

    /* 数组访问 */
    if (cur->type == TOK_LBRACKET) { ... }  /* 现有逻辑保持 */

    /* 成员访问: p->member 或 n.member */
    if (cur->type == TOK_ARROW || cur->type == TOK_DOT) {
        ASTNode *ref = ast_new(AST_VAR_REF);
        ref->name = name;
        return parse_member_access(ref);
    }

    /* 变量引用 */
    ASTNode *n = ast_new(AST_VAR_REF);
    n->name = name;
    return n;
}
```

- [ ] **Step 3: 修改 parse_program 顶层解析**

在 `parse_program()` 中区分 struct 定义、struct 全局声明、函数定义：

```c
// src/parser.c parse_program 函数
static ASTNode *parse_program(void)
{
    ASTNode dummy = {0};
    ASTNode *tail = &dummy;

    while (cur->type != TOK_EOF) {
        ASTNode *node = NULL;

        /* struct 定义: struct Name { ... }; */
        if (cur->type == TOK_STRUCT && cur->next && cur->next->next &&
            cur->next->next->type == TOK_LBRACE) {
            node = parse_struct_def();
        }
        /* struct 全局声明: struct Name* var; 或 struct Name var; */
        else if (cur->type == TOK_STRUCT) {
            node = parse_struct_decl(1);  /* is_global=1 */
        }
        /* 函数定义或 int/char 全局声明 */
        else if (cur->type == TOK_INT || cur->type == TOK_CHAR) {
            /* 现有逻辑保持 */
            Token *next = cur->next;
            int is_func = 0;
            if (next && next->type == TOK_STAR) next = next->next;
            if (next && next->type == TOK_ID && next->next && next->next->type == TOK_LPAREN)
                is_func = 1;
            if (is_func) node = parse_func_def();
            else node = parse_global_decl();
        }
        else {
            parse_error(cur->line, cur->col, "expected declaration or function");
            break;
        }

        if (!node) break;
        tail->next = node;
        tail = node;
    }

    return dummy.next;
}
```

- [ ] **Step 4: 修改 parse_var_decl 支持 struct 指针局部变量**

在 `parse_var_decl()` 开头添加 struct 处理：

```c
// src/parser.c parse_var_decl 函数开头
static ASTNode *parse_var_decl(void)
{
    /* 支持 int, char, struct 类型 */
    Type var_type;

    if (cur->type == TOK_INT) {
        var_type = type_make_int();
        cur = cur->next;
    } else if (cur->type == TOK_CHAR) {
        var_type = type_make_char();
        cur = cur->next;
    } else if (cur->type == TOK_STRUCT) {
        return parse_struct_decl(0);  /* is_global=0, 局部变量 */
    } else {
        parse_error(cur->line, cur->col, "expected type (int/char/struct)");
        return NULL;
    }

    /* 后续现有逻辑保持... */
}
```

- [ ] **Step 5: Commit**

```bash
git add src/parser.c
git commit -m "feat(phase8): add member access parsing and program-level struct support"
```

---

## Task 9: codegen.c 扩展 - struct_table 和 register_structs

**Files:**
- Modify: `src/codegen.c`

- [ ] **Step 1: 添加 struct_table 全局变量**

```c
// src/codegen.c 在全局变量区域添加
#define MAX_STRUCTS 32

static StructInfo struct_table[MAX_STRUCTS];
static int struct_count;
```

- [ ] **Step 2: 添加 get_type_size 函数**

```c
// src/codegen.c 在 struct_table 定义之后添加
static int get_type_size(Type t)
{
    if (t.ptr_level > 0)
        return 4;  /* 所有指针 4 字节 */
    if (t.base_type == TYPE_INT)
        return 4;
    if (t.base_type == TYPE_CHAR)
        return 1;
    if (t.base_type == TYPE_STRUCT)
        return struct_table[t.struct_id].total_size;
    return 4;
}
```

- [ ] **Step 3: 添加 register_structs 函数**

```c
// src/codegen.c 在 get_type_size 之后添加
static void register_structs(ASTNode *prog)
{
    struct_count = 0;

    for (ASTNode *n = prog; n; n = n->next) {
        if (n->type == AST_STRUCT_DEF) {
            StructInfo *si = &struct_table[struct_count];
            si->name = strdup(n->struct_name);
            si->member_count = 0;

            /* 计算成员数量 */
            for (ASTNode *m = n->members; m; m = m->next)
                si->member_count++;

            /* 分配成员数组 */
            si->members = malloc(si->member_count * sizeof(MemberInfo));
            if (!si->members) {
                fprintf(stderr, "error: malloc failed for struct members\n");
                return;
            }

            /* 注册成员并计算偏移 */
            int offset = 0;
            int idx = 0;
            for (ASTNode *m = n->members; m; m = m->next, idx++) {
                si->members[idx].name = strdup(m->name);
                si->members[idx].type = m->var_type;
                si->members[idx].offset = offset;

                int size = get_type_size(m->var_type);
                offset += size;
            }

            si->total_size = offset;
            n->struct_id = struct_count;
            struct_count++;
        }
    }
}
```

- [ ] **Step 4: 添加结构体查找函数**

```c
// src/codegen.c 在 register_structs 之后添加
static int lookup_struct_codegen(const char *name)
{
    for (int i = 0; i < struct_count; i++)
        if (strcmp(struct_table[i].name, name) == 0)
            return i;
    return -1;
}

static StructInfo *get_struct_info(int struct_id)
{
    if (struct_id < 0 || struct_id >= struct_count)
        return NULL;
    return &struct_table[struct_id];
}

static MemberInfo *find_member(int struct_id, const char *member_name)
{
    StructInfo *si = get_struct_info(struct_id);
    if (!si) return NULL;
    for (int i = 0; i < si->member_count; i++)
        if (strcmp(si->members[i].name, member_name) == 0)
            return &si->members[i];
    return NULL;
}

static int get_member_offset(int struct_id, const char *member_name)
{
    MemberInfo *mi = find_member(struct_id, member_name);
    if (!mi) {
        fprintf(stderr, "error: member '%s' not found\n", member_name);
        return 0;
    }
    return mi->offset;
}
```

- [ ] **Step 5: Commit**

```bash
git add src/codegen.c
git commit -m "feat(phase8): add struct_table and register_structs"
```