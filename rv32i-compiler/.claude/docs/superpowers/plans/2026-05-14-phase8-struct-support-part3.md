# 阶段 8：结构体支持实现计划 - Part 3

> 续 Part 2 (Task 7-9)，本部分包含 Task 10-11

---

## Task 10: codegen.c 扩展 - AST_MEMBER_ACCESS 和全局 struct 变量

**Files:**
- Modify: `src/codegen.c`

- [ ] **Step 1: 添加 get_expr_type 函数**

```c
// src/codegen.c 在 find_member 之后添加
static Type get_expr_type(ASTNode *n)
{
    if (n->type == AST_VAR_REF) {
        int global_off = global_lookup(n->name);
        if (global_off >= 0) return global_lookup_type(n->name);
        return sym_lookup_type(n->name);
    }
    if (n->type == AST_MEMBER_ACCESS) {
        Type target_type = get_expr_type(n->target_expr);
        if (target_type.ptr_level > 0) {
            /* p->member: target 是指针，struct_id 在指针类型中 */
            MemberInfo *mi = find_member(target_type.struct_id, n->member_name);
            if (mi) return mi->type;
        } else {
            /* n.member: target 是值类型 */
            MemberInfo *mi = find_member(target_type.struct_id, n->member_name);
            if (mi) return mi->type;
        }
    }
    return type_make_int();  /* 默认 */
}
```

- [ ] **Step 2: 在 gen_expr 中添加 AST_MEMBER_ACCESS 处理**

```c
// src/codegen.c gen_expr 函数 switch 中添加
case AST_MEMBER_ACCESS: {
    /* 1. 计算目标地址 */
    gen_expr(n->target_expr);  /* t0 = p (指针值) 或 &n (全局地址) */

    /* 2. 查询成员偏移 */
    Type target_type = get_expr_type(n->target_expr);
    int struct_id = target_type.struct_id;
    int offset = get_member_offset(struct_id, n->member_name);

    /* 3. 计算成员地址 */
    emit("    addi t0, t0, %d\n", offset);  /* t0 = &target->member */

    /* 4. 加载成员值 */
    MemberInfo *mi = find_member(struct_id, n->member_name);
    if (mi->type.ptr_level > 0 || mi->type.base_type == TYPE_INT) {
        emit("    lw t0, 0(t0)\n");  /* 加载指针或 int */
    } else if (mi->type.base_type == TYPE_CHAR) {
        emit("    lb t0, 0(t0)\n");  /* 加载 char */
    }
    /* struct 值类型成员返回地址（用于赋值） */
    break;
}
```

- [ ] **Step 3: 修改 collect_globals 处理全局 struct 变量**

```c
// src/codegen.c collect_globals 函数中添加 struct 处理
static void collect_globals(ASTNode *prog)
{
    global_count = 0;
    data_offset = 0;
    /* ... 现有初始化 */

    for (ASTNode *n = prog; n; n = n->next) {
        if (n->type == AST_GLOBAL_DECL) {
            globals[global_count].name = strdup(n->name);
            globals[global_count].type = n->var_type;
            globals[global_count].offset = data_offset;
            globals[global_count].init_val = 0;
            globals[global_count].init_str = NULL;
            globals[global_count].str_len = 0;

            /* 处理 struct 类型全局变量 */
            if (n->var_type.base_type == TYPE_STRUCT) {
                StructInfo *si = get_struct_info(n->var_type.struct_id);
                if (si) data_offset += si->total_size;
                else data_offset += 4;  /* fallback */
            } else if (n->var_type.array_size > 0) {
                /* 现有数组逻辑 */
                data_offset += n->var_type.array_size * 4;
            } else {
                data_offset += 4;
            }
            global_count++;
        }
    }
}
```

- [ ] **Step 4: 修改 emit_data_segment 输出全局 struct 变量**

```c
// src/codegen.c emit_data_segment 函数中添加 struct 输出
static void emit_data_segment(void)
{
    if (global_count == 0 && string_lit_count == 0) return;
    emit("    .data\n");

    for (int i = 0; i < global_count; i++) {
        emit(".global_%s:\n", globals[i].name);

        if (globals[i].type.base_type == TYPE_STRUCT && globals[i].type.ptr_level == 0) {
            /* struct 值类型全局变量 - 输出 total_size 字节的 0 */
            StructInfo *si = get_struct_info(globals[i].type.struct_id);
            if (si) {
                int words = si->total_size / 4;
                for (int j = 0; j < words; j++)
                    emit("    .word 0\n");
            }
        } else if (globals[i].init_str) {
            /* 现有字符串逻辑 */
            emit("    .byte ");
            for (int j = 0; j < globals[i].str_len; j++) {
                unsigned char c = (unsigned char)globals[i].init_str[j];
                if (j > 0) emit(",");
                emit("%d", c);
            }
            emit("\n");
            emit("    .align 4\n");
        } else {
            emit("    .word %d\n", globals[i].init_val);
        }
    }
    /* ... 现有 string literals 输出 */
}
```

- [ ] **Step 5: 修改 gen_stmt AST_ASSIGN 处理成员赋值**

在 `gen_stmt` 的 `AST_ASSIGN` case 中添加成员赋值处理：

```c
// src/codegen.c gen_stmt 函数 AST_ASSIGN case
case AST_ASSIGN:
    gen_expr(n->expr);  /* 右值 → t0 */

    /* 成员访问赋值: p->member = value 或 n.member = value */
    if (n->target_expr && n->target_expr->type == AST_MEMBER_ACCESS) {
        int my_off = spill_depth * 4;
        emit("    sw t0, %d(sp)\n", my_off);  /* 保存右值 */
        gen_expr(n->target_expr);  /* t0 = &target->member */
        emit("    lw t1, %d(sp)\n", my_off);  /* t1 = 右值 */
        emit("    sw t1, 0(t0)\n");  /* 存储到成员 */
        break;
    }

    /* 现有 array_assign / deref_assign / global_assign / local_assign 逻辑保持 */
    /* ... */
    break;
```

需要修改 `parse_assign` 将成员访问的 target 存储到 `n->target_expr`。

- [ ] **Step 6: 修改 codegen_gen 调用 register_structs**

```c
// src/codegen.c codegen_gen 函数开头
int codegen_gen(ASTNode *prog, const char *outfile)
{
    out = fopen(outfile, "w");
    if (!out) { fprintf(stderr, "cannot open %s\n", outfile); return 1; }

    /* Pass 0.5: 注册结构体定义 */
    register_structs(prog);

    /* Pass 0: collect globals */
    collect_globals(prog);

    /* 现有逻辑... */
}
```

- [ ] **Step 7: Commit**

```bash
git add src/codegen.c
git commit -m "feat(phase8): add AST_MEMBER_ACCESS codegen and global struct support"
```

---

## Task 11: parser.c 扩展 - 成员赋值解析

**Files:**
- Modify: `src/parser.c`

- [ ] **Step 1: 修改 parse_assign 支持成员赋值**

在 `parse_assign()` 中识别成员访问作为赋值目标：

```c
// src/parser.c parse_assign 函数开头添加成员赋值分支
static ASTNode *parse_assign(void)
{
    ASTNode *n = ast_new(AST_ASSIGN);
    n->is_deref_assign = 0;
    n->is_array_assign = 0;
    n->target_expr = NULL;

    /* 成员赋值: p->member = value 或 n.member = value */
    if (cur->type == TOK_ID && cur->next &&
        (cur->next->type == TOK_ARROW || cur->next->type == TOK_DOT)) {
        /* 解析成员访问表达式作为 target */
        ASTNode *ref = ast_new(AST_VAR_REF);
        ref->name = strdup(cur->text);
        cur = cur->next;  /* skip identifier */

        n->target_expr = parse_member_access(ref);  /* 解析 p->member */

        if (cur->type != TOK_ASSIGN) {
            parse_error(cur->line, cur->col, "expected '=' after member access");
            return NULL;
        }
        cur = cur->next;  /* skip '=' */
        n->expr = parse_expr();
        expect(TOK_SEMI);
        return n;
    }

    /* 现有 deref_assign / array_assign / normal assign 逻辑保持 */
    /* ... */
}
```

- [ ] **Step 2: Commit**

```bash
git add src/parser.c
git commit -m "feat(phase8): add member assignment parsing"
```

---

## Task 12: 测试 1 - struct 定义与成员访问

**Files:**
- Create: `tests/phase8/test1_member_access.c`

- [ ] **Step 1: 创建测试文件**

```c
// tests/phase8/test1_member_access.c
struct Node {
    int value;
    struct Node* next;
};

struct Node g_n;

int main() {
    g_n.value = 42;
    struct Node* p = &g_n;
    return p->value;  /* 期望 42 */
}
```

- [ ] **Step 2: 编译测试**

```bash
make clean
cd rv32i-compiler
./build/microcc tests/phase8/test1_member_access.c > build/test1_member_access.hex
```

- [ ] **Step 3: 运行测试验证**

```bash
cd ..
python3 tools/hex_to_bsv.py rv32i-compiler/build/test1_member_access.hex > src/soc/TestProgram.bsv
make test
```

期望 tohost = 42。

- [ ] **Step 4: 如果失败，调试并修复**

检查编译器输出汇编、链接器输出 hex、CPU 运行日志。

- [ ] **Step 5: Commit 测试文件**

```bash
git add tests/phase8/test1_member_access.c
git commit -m "test(phase8): add test1 member access"
```

---

## Task 13: 测试 2 - 链表遍历求和

**Files:**
- Create: `tests/phase8/test2_linked_list.c`

- [ ] **Step 1: 创建测试文件**

```c
// tests/phase8/test2_linked_list.c
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
    return sum_list(&g_n1);  /* 期望 60 */
}
```

- [ ] **Step 2: 编译并运行验证**

期望 tohost = 60。

- [ ] **Step 3: Commit 测试文件**

```bash
git add tests/phase8/test2_linked_list.c
git commit -m "test(phase8): add test2 linked list sum"
```

---

## Task 14: Makefile 更新和最终验证

**Files:**
- Modify: `Makefile`

- [ ] **Step 1: 添加 phase8 测试目标**

```makefile
# Makefile 在现有 test 目标附近添加
test-phase8:
	./build/microcc tests/phase8/test1_member_access.c > build/test1.hex
	./build/microcc tests/phase8/test2_linked_list.c > build/test2.hex
	@echo "Phase 8 tests compiled"
```

- [ ] **Step 2: 运行完整回归测试**

确保所有阶段测试（phase1-8）全部通过。

- [ ] **Step 3: Commit Makefile 更新**

```bash
git add Makefile
git commit -m "feat(phase8): add phase8 test targets to Makefile"
```

---

## Self-Review Checklist

完成所有 Task 后，执行以下检查：

- [ ] **Spec coverage**: 设计文档中所有功能是否实现？
  - struct 定义 ✓
  - struct 指针变量声明 ✓
  - struct 值类型全局变量 ✓
  - 成员访问 -> 和 . ✓
  - struct 作为函数参数 ✓
  - struct 作为返回值 ✓
  - 自引用结构体 ✓

- [ ] **Placeholder scan**: 检查代码中是否有 TBD/TODO？

- [ ] **Type consistency**: 函数名、结构体字段名是否一致？
  - `struct_id` vs `structId` (统一使用 snake_case)
  - `target_expr` vs `targetExpr` (统一使用 snake_case)

---

## Execution Handoff

Plan 分三部分写入：
- Part 1: Task 1-6 (types.h/c, lexer.h/c, ast.h, parser.c 基础)
- Part 2: Task 7-9 (parser.c 解析, codegen.c struct_table)
- Part 3: Task 10-14 (codegen 成员访问, 测试)

**执行选项:**

1. **Subagent-Driven (推荐)** - 按任务分批执行，每批完成后 review
2. **Inline Execution** - 在当前 session 执行，checkpoint 控制

选择哪种方式？