# Phase 6: Array Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-step. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Add array support to RV32I compiler, verified by `arr_sum(arr, 5)` test returning 15.

**Architecture:** Extend existing modules (lexer, types, parser, codegen) to support array declaration, subscript access, and pointer arithmetic. Arrays allocated on stack with contiguous layout.

**Tech Stack:** C99, RV32I assembly, CPU TestBench verification.

---

## File Structure

| File | Action | Responsibility |
|------|--------|----------------|
| `src/lexer.h` | Modify | Add `TOK_LBRACKET`, `TOK_RBRACKET` |
| `src/lexer.c` | Modify | Recognize `[` and `]` characters |
| `src/types.h` | Modify | Add `array_size` field to Type struct |
| `src/types.c` | Modify | Add array helper functions |
| `src/ast.h` | Modify | Add `AST_ARRAY_ACCESS`, extend `AST_ASSIGN` for arrays |
| `src/parser.c` | Modify | Parse array declaration, subscript, and assignment |
| `src/codegen.c` | Modify | Generate array code, handle pointer arithmetic |
| `Makefile` | Modify | Add phase6 test targets |
| `tests/phase6/test_array.c` | Create | Verification test file |

---

## Task 1: Add TOK_LBRACKET and TOK_RBRACKET to Lexer

**Files:**
- Modify: `src/lexer.h:5-10` (enum)
- Modify: `src/lexer.c:25-35` (tok_name), `src/lexer.c:175-180` (single-char tokens)

- [ ] **Step 1: Add tokens to lexer.h enum**

```c
// src/lexer.h - Modify enum TokenType
typedef enum {
    TOK_INT, TOK_ID, TOK_NUM, TOK_RETURN,
    TOK_LPAREN, TOK_RPAREN, TOK_LBRACE, TOK_RBRACE, TOK_SEMI,
    TOK_ASSIGN, TOK_PLUS, TOK_MINUS, TOK_STAR, TOK_SLASH,
    TOK_IF, TOK_ELSE, TOK_WHILE, TOK_FOR, TOK_LT, TOK_INC,
    TOK_COMMA,
    TOK_AND,
    TOK_LBRACKET,    // NEW: '[' for array subscript
    TOK_RBRACKET,    // NEW: ']' for array subscript
    TOK_EOF
} TokenType;
```

- [ ] **Step 2: Add names in tok_name function**

```c
// src/lexer.c - Add cases to tok_name()
case TOK_LBRACKET: return "[";
case TOK_RBRACKET: return "]";
```

- [ ] **Step 3: Add `[` and `]` recognition in tokenizer**

```c
// src/lexer.c - Add cases to single-char token switch
case '[': t = TOK_LBRACKET; break;
case ']': t = TOK_RBRACKET; break;
```

- [ ] **Step 4: Build and verify**

```bash
make clean && make
```

Expected: Compilation succeeds.

- [ ] **Step 5: Commit**

```bash
git add src/lexer.h src/lexer.c
git commit -m "feat(lexer): add TOK_LBRACKET and TOK_RBRACKET for array subscript"
```

---

## Task 2: Extend Type Struct with array_size Field

**Files:**
- Modify: `src/types.h`
- Modify: `src/types.c`

- [ ] **Step 1: Add array_size to Type struct**

```c
// src/types.h - Modify Type struct
typedef struct {
    int base_type;    /* 0 = int */
    int ptr_level;    /* Pointer level: 0 = int, 1 = int* */
    int array_size;   /* Array size: 0 = not array, >0 = array elements count */
} Type;
```

- [ ] **Step 2: Add array helper functions**

```c
// src/types.h - Add new function declarations
Type type_make_array(int size);     /* Create array type with given size */
int  type_is_array(Type t);         /* Check if type is array */
```

- [ ] **Step 3: Implement array helpers in types.c**

```c
// src/types.c - Add new functions
Type type_make_array(int size)
{
    Type t = { .base_type = 0, .ptr_level = 0, .array_size = size };
    return t;
}

int type_is_array(Type t)
{
    return t.array_size > 0;
}
```

- [ ] **Step 4: Build and verify**

```bash
make clean && make
```

Expected: Compilation succeeds.

- [ ] **Step 5: Commit**

```bash
git add src/types.h src/types.c
git commit -m "feat(types): add array_size field and array helper functions"
```

---

## Task 3: Add AST_ARRAY_ACCESS Node

**Files:**
- Modify: `src/ast.h`

- [ ] **Step 1: Add AST_ARRAY_ACCESS to enum**

```c
// src/ast.h - Add to ASTNodeType enum
typedef enum {
    AST_FUNC_DEF,
    AST_RETURN,
    AST_INT_LIT,
    AST_BIN_OP,
    AST_VAR_DECL,
    AST_VAR_REF,
    AST_ASSIGN,
    AST_IF,
    AST_WHILE,
    AST_NOOP,
    AST_FUNC_CALL,
    AST_ADDR,
    AST_DEREF,
    AST_ARRAY_ACCESS    /* NEW: array subscript arr[i] */
} ASTNodeType;
```

- [ ] **Step 2: Add fields for array assignment to ASTNode**

```c
// src/ast.h - Add to ASTNode struct after is_deref_assign
    int   is_array_assign;   /* for ASSIGN: 1 if assigning to arr[i] */
    char  *array_name;       /* for ASSIGN/ARRAY_ACCESS: array variable name */
    struct ASTNode *array_index; /* for ASSIGN/ARRAY_ACCESS: subscript expression */
```

- [ ] **Step 3: Build and verify**

```bash
make clean && make
```

Expected: Compilation succeeds.

- [ ] **Step 4: Commit**

```bash
git add src/ast.h
git commit -m "feat(ast): add AST_ARRAY_ACCESS node and array assignment fields"
```

---

## Task 4: Parser - Array Declaration

**Files:**
- Modify: `src/parser.c:180-210` (parse_var_decl)

- [ ] **Step 1: Modify parse_var_decl to handle `int arr[n]`**

```c
// src/parser.c - Replace parse_var_decl function
/* var-decl = "int" ["*"] identifier ["[" number "]"] ["=" expr] ";" */
static ASTNode *parse_var_decl(void)
{
    cur = cur->next; /* skip "int" */

    /* Check for pointer declaration: int *p */
    Type var_type = type_make_int();
    if (cur->type == TOK_STAR) {
        var_type = type_make_int_ptr();
        cur = cur->next; /* skip '*' */
    }

    if (cur->type != TOK_ID) {
        parse_error(cur->line, cur->col, "expected identifier after 'int'");
        return NULL;
    }
    ASTNode *n = ast_new(AST_VAR_DECL);
    n->name = strdup(cur->text);
    cur = cur->next;

    /* Check for array declaration: int arr[n] */
    if (cur->type == TOK_LBRACKET) {
        cur = cur->next; /* skip '[' */
        if (cur->type != TOK_NUM) {
            parse_error(cur->line, cur->col, "expected array size number");
            return NULL;
        }
        int size = atoi(cur->text);
        var_type = type_make_array(size);
        n->var_type = var_type;
        cur = cur->next; /* skip size */
        if (cur->type != TOK_RBRACKET) {
            parse_error(cur->line, cur->col, "expected ']' after array size");
            return NULL;
        }
        cur = cur->next; /* skip ']' */
    } else {
        n->var_type = var_type;
    }

    /* Check for initializer (not supported for arrays yet) */
    if (cur->type == TOK_ASSIGN) {
        if (type_is_array(n->var_type)) {
            parse_error(cur->line, cur->col, "array initializer not supported");
            return NULL;
        }
        cur = cur->next; /* skip '=' */
        n->init = parse_expr();
    }

    if (cur->type != TOK_SEMI) {
        parse_error(cur->line, cur->col, "expected ';' after variable declaration");
    } else {
        cur = cur->next;
    }
    return n;
}
```

- [ ] **Step 2: Build and verify**

```bash
make clean && make
```

Expected: Compilation succeeds.

- [ ] **Step 3: Commit**

```bash
git add src/parser.c
git commit -m "feat(parser): parse array declaration int arr[n]"
```

---

## Task 5: Parser - Array Subscript Expression

**Files:**
- Modify: `src/parser.c:36-90` (parse_primary)

- [ ] **Step 1: Add array subscript handling in parse_primary**

Find the section where identifier is parsed and add array subscript check:

```c
// src/parser.c - Modify parse_primary, after TOK_ID handling
if (cur->type == TOK_ID) {
    char *name = strdup(cur->text);
    cur = cur->next;
    
    /* Function call: name(args) */
    if (cur->type == TOK_LPAREN) {
        /* ... existing function call code ... */
    }
    
    /* Array subscript: arr[i] */
    if (cur->type == TOK_LBRACKET) {
        cur = cur->next; /* skip '[' */
        ASTNode *index = parse_expr();
        if (cur->type != TOK_RBRACKET) {
            parse_error(cur->line, cur->col, "expected ']' after array index");
        } else {
            cur = cur->next; /* skip ']' */
        }
        ASTNode *n = ast_new(AST_ARRAY_ACCESS);
        n->name = name;
        n->array_index = index;
        return n;
    }
    
    /* Variable reference */
    ASTNode *n = ast_new(AST_VAR_REF);
    n->name = name;
    return n;
}
```

- [ ] **Step 2: Build and verify**

```bash
make clean && make
```

Expected: Compilation succeeds.

- [ ] **Step 3: Commit**

```bash
git add src/parser.c
git commit -m "feat(parser): parse array subscript expression arr[i]"
```

---

## Task 6: Parser - Array Assignment

**Files:**
- Modify: `src/parser.c:211-270` (parse_assign)

- [ ] **Step 1: Add array assignment parsing in parse_assign**

```c
// src/parser.c - Modify parse_assign function
/* assign-stmt = identifier "[" expr "]" "=" expr ";" 
              | identifier "=" expr ";" 
              | "*" primary "=" expr ";" */
static ASTNode *parse_assign(void)
{
    ASTNode *n = ast_new(AST_ASSIGN);
    n->is_deref_assign = 0;
    n->is_array_assign = 0;

    /* Dereference assignment: *p = expr */
    if (cur->type == TOK_STAR) {
        n->is_deref_assign = 1;
        cur = cur->next;
        n->deref_target = parse_primary();
        /* ... rest of deref assignment code ... */
    }

    /* Array assignment: arr[i] = expr */
    if (cur->type == TOK_ID && cur->next && cur->next->type == TOK_LBRACKET) {
        n->is_array_assign = 1;
        n->array_name = strdup(cur->text);
        cur = cur->next; /* skip identifier */
        cur = cur->next; /* skip '[' */
        n->array_index = parse_expr();
        if (cur->type != TOK_RBRACKET) {
            parse_error(cur->line, cur->col, "expected ']' after array index");
            return NULL;
        }
        cur = cur->next; /* skip ']' */
        
        if (cur->type != TOK_ASSIGN) {
            parse_error(cur->line, cur->col, "expected '=' after array subscript");
            return NULL;
        }
        cur = cur->next; /* skip '=' */
        n->expr = parse_expr();
        
        if (cur->type != TOK_SEMI) {
            parse_error(cur->line, cur->col, "expected ';' after assignment");
        } else {
            cur = cur->next;
        }
        return n;
    }

    /* Normal assignment: x = expr */
    n->name = strdup(cur->text);
    cur = cur->next;
    /* ... rest of normal assignment code ... */
}
```

- [ ] **Step 2: Build and verify**

```bash
make clean && make
```

Expected: Compilation succeeds.

- [ ] **Step 3: Commit**

```bash
git add src/parser.c
git commit -m "feat(parser): parse array assignment arr[i] = expr"
```

---

## Task 7: Codegen - Symbol Table Array Size Tracking

**Files:**
- Modify: `src/codegen.c:35-70` (symbol table)

- [ ] **Step 1: Modify sym_add to handle array size**

The symbol table already has Type field, which now includes array_size. Need to update sym_add when processing array declarations:

```c
// src/codegen.c - Modify count_vars to track array sizes
static void count_vars(ASTNode *list)
{
    for (ASTNode *s = list; s; s = s->next) {
        if (s->type == AST_VAR_DECL) {
            sym_add(s->name);
            /* Set type including array_size */
            if (s->var_type.array_size > 0) {
                sym_set_type(s->name, s->var_type);
            }
        }
        /* ... rest of existing code ... */
    }
}
```

- [ ] **Step 2: Build and verify**

```bash
make clean && make
```

Expected: Compilation succeeds.

- [ ] **Step 3: Commit**

```bash
git add src/codegen.c
git commit -m "feat(codegen): track array size in symbol table"
```

---

## Task 8: Codegen - Array Stack Frame Calculation

**Files:**
- Modify: `src/codegen.c:53-100` (sym_add, count_frame)

- [ ] **Step 1: Modify sym_add to calculate array offset**

```c
// src/codegen.c - Modify sym_add function
static void sym_add(const char *name)
{
    if (sym_lookup(name) >= 0)
        return;
    syms[sym_count].name = strdup(name);
    syms[sym_count].type = type_make_int();  /* default, will be updated */
    syms[sym_count].offset = 16 + 4 * sym_count;  /* placeholder, updated below */
    sym_count++;
}

/* NEW: Add function to compute actual offset accounting for arrays */
static int sym_get_total_size(void)
{
    int total = 0;
    for (int i = 0; i < sym_count; i++) {
        if (syms[i].type.array_size > 0)
            total += syms[i].type.array_size * 4;  /* array: size * 4 bytes */
        else
            total += 4;  /* single variable: 4 bytes */
    }
    return total;
}

/* NEW: Recalculate offsets accounting for array sizes */
static void sym_recalc_offsets(void)
{
    int offset = 16;  /* start after 4 spill slots */
    for (int i = 0; i < sym_count; i++) {
        syms[i].offset = offset;
        if (syms[i].type.array_size > 0)
            offset += syms[i].type.array_size * 4;
        else
            offset += 4;
    }
}
```

- [ ] **Step 2: Modify count_frame to use array-aware calculation**

```c
// src/codegen.c - Modify count_frame
static int count_frame(ASTNode *fn)
{
    sym_count = 0;
    for (ASTNode *p = fn->right; p; p = p->next)
        sym_add(p->name);
    count_vars(fn->body);
    
    /* Update types for all symbols */
    for (ASTNode *p = fn->right; p; p = p->next)
        if (p->var_type.array_size > 0 || p->var_type.ptr_level > 0)
            sym_set_type(p->name, p->var_type);
    for (ASTNode *s = fn->body; s; s = s->next) {
        if (s->type == AST_VAR_DECL && (s->var_type.array_size > 0 || s->var_type.ptr_level > 0))
            sym_set_type(s->name, s->var_type);
    }
    
    /* Recalculate offsets */
    sym_recalc_offsets();
    
    int local_size = sym_get_total_size();
    int frame_size = 16 + local_size + 36;  /* spill + locals + arg_area + ra */
    frame_size = (frame_size + 15) & ~15;
    return frame_size;
}
```

- [ ] **Step 3: Build and verify**

```bash
make clean && make
```

Expected: Compilation succeeds.

- [ ] **Step 4: Commit**

```bash
git add src/codegen.c
git commit -m "feat(codegen): calculate stack frame for arrays"
```

---

## Task 9: Codegen - Array Name as Pointer

**Files:**
- Modify: `src/codegen.c:126-135` (AST_VAR_REF case)

- [ ] **Step 1: Modify AST_VAR_REF to return array address**

```c
// src/codegen.c - Modify AST_VAR_REF case in gen_expr
case AST_VAR_REF: {
    int off = sym_lookup(n->name);
    if (off < 0) {
        fprintf(stderr, "codegen error: undefined variable '%s'\n", n->name);
        return;
    }
    Type t = sym_lookup_type(n->name);
    /* If variable is array, return its address (not load value) */
    if (type_is_array(t)) {
        emit("    addi t0, sp, %d\n", off);  /* t0 = &arr[0] */
    } else {
        emit("    lw t0, %d(sp)\n", off);  /* t0 = value */
    }
    break;
}
```

- [ ] **Step 2: Build and verify**

```bash
make clean && make
```

Expected: Compilation succeeds.

- [ ] **Step 3: Commit**

```bash
git add src/codegen.c
git commit -m "feat(codegen): array name returns address instead of value"
```

---

## Task 10: Codegen - Array Subscript Read

**Files:**
- Modify: `src/codegen.c:118-190` (gen_expr)

- [ ] **Step 1: Add AST_ARRAY_ACCESS case in gen_expr**

```c
// src/codegen.c - Add to gen_expr switch
case AST_ARRAY_ACCESS: {
    /* arr[i] → compute address and load */
    int base = sym_lookup(n->name);
    if (base < 0) {
        fprintf(stderr, "codegen error: undefined array '%s'\n", n->name);
        return;
    }
    /* Evaluate index expression */
    gen_expr(n->array_index);  /* index in t0 */
    emit("    slli t0, t0, 2\n");  /* t0 = index * 4 (byte offset) */
    emit("    addi t1, sp, %d\n", base);  /* t1 = base address */
    emit("    add t0, t1, t0\n");  /* t0 = &arr[i] */
    emit("    lw t0, 0(t0)\n");  /* t0 = arr[i] */
    break;
}
```

- [ ] **Step 2: Build and verify**

```bash
make clean && make
```

Expected: Compilation succeeds.

- [ ] **Step 3: Commit**

```bash
git add src/codegen.c
git commit -m "feat(codegen): generate array subscript read code"
```

---

## Task 11: Codegen - Array Assignment

**Files:**
- Modify: `src/codegen.c:228-260` (AST_ASSIGN case)

- [ ] **Step 1: Add array assignment handling in AST_ASSIGN**

```c
// src/codegen.c - Modify AST_ASSIGN case
case AST_ASSIGN:
    gen_expr(n->expr);  /* value in t0 */
    
    if (n->is_array_assign) {
        /* arr[i] = value */
        int my_off = spill_depth * 4;
        emit("    sw t0, %d(sp)\n", my_off);  /* save value */
        
        int base = sym_lookup(n->array_name);
        if (base < 0) {
            fprintf(stderr, "codegen error: undefined array '%s'\n", n->array_name);
            return;
        }
        
        gen_expr(n->array_index);  /* index in t0 */
        emit("    slli t0, t0, 2\n");  /* t0 = index * 4 */
        emit("    addi t1, sp, %d\n", base);  /* t1 = base */
        emit("    add t0, t1, t0\n");  /* t0 = &arr[i] */
        emit("    lw t1, %d(sp)\n", my_off);  /* t1 = value */
        emit("    sw t1, 0(t0)\n");  /* arr[i] = value */
    } else if (n->is_deref_assign) {
        /* *p = value - existing code */
        /* ... */
    } else {
        /* x = value - existing code */
        /* ... */
    }
    break;
```

- [ ] **Step 2: Build and verify**

```bash
make clean && make
```

Expected: Compilation succeeds.

- [ ] **Step 3: Commit**

```bash
git add src/codegen.c
git commit -m "feat(codegen): generate array assignment code"
```

---

## Task 12: Codegen - Pointer Arithmetic

**Files:**
- Modify: `src/codegen.c:136-165` (AST_BIN_OP case)

- [ ] **Step 1: Modify BIN_OP to handle pointer arithmetic**

```c
// src/codegen.c - Modify AST_BIN_OP case
case AST_BIN_OP: {
    gen_expr(n->left);
    int my_off = spill_depth * 4;
    spill_depth++;
    emit("    sw t0, %d(sp)\n", my_off);
    gen_expr(n->right);
    spill_depth--;
    
    /* Check if left operand was pointer */
    Type left_type = type_make_int();  /* default */
    /* We need to track expression types - simplified: check if it was address operation */
    int is_ptr_add = 0;
    /* If left came from array name or address-of, it's pointer */
    if (n->left->type == AST_VAR_REF) {
        left_type = sym_lookup_type(n->left->name);
        is_ptr_add = type_is_array(left_type) || type_is_ptr(left_type);
    } else if (n->left->type == AST_ADDR) {
        is_ptr_add = 1;
    }
    
    emit("    mv t1, t0\n");  /* t1 = right operand */
    emit("    lw t0, %d(sp)\n", my_off);  /* t0 = left operand */
    
    if (n->op == TOK_PLUS) {
        if (is_ptr_add) {
            /* Pointer arithmetic: p + n → p + n*4 */
            emit("    slli t1, t1, 2\n");  /* t1 = n * 4 */
            emit("    add t0, t0, t1\n");  /* t0 = p + n*4 */
        } else {
            emit("    add t0, t0, t1\n");  /* normal integer add */
        }
    }
    /* ... rest of operators unchanged ... */
    break;
}
```

- [ ] **Step 2: Build and verify**

```bash
make clean && make
```

Expected: Compilation succeeds.

- [ ] **Step 3: Commit**

```bash
git add src/codegen.c
git commit -m "feat(codegen): handle pointer arithmetic p + n"
```

---

## Task 13: Create Test File

**Files:**
- Create: `tests/phase6/test_array.c`

- [ ] **Step 1: Create test directory and file**

```bash
mkdir -p tests/phase6
```

```c
// tests/phase6/test_array.c
int arr_sum(int *arr, int n) {
    int sum = 0;
    int i = 0;
    while (i < n) {
        sum = sum + arr[i];
        i = i + 1;
    }
    return sum;
}

int main() {
    int arr[5];
    arr[0] = 1;
    arr[1] = 2;
    arr[2] = 3;
    arr[3] = 4;
    arr[4] = 5;
    return arr_sum(arr, 5);
}
```

- [ ] **Step 2: Commit test file**

```bash
git add tests/phase6/test_array.c
git commit -m "test(phase6): add array sum test"
```

---

## Task 14: Add Makefile Targets

**Files:**
- Modify: `Makefile`

- [ ] **Step 1: Add phase6 test targets**

```makefile
# Makefile - Add after phase5 targets

# ----- Phase 6 test hex targets -----
HEX6 = build/phase6_array.hex

$(HEX6): build/phase6_%.hex: tests/phase6/test_%.c $(BUILDDIR)/microcc $(RTDIR)/crt0.s $(RTDIR)/lib.S
	@mkdir -p $(BUILDDIR)
	./$(BUILDDIR)/microcc $< $@ $(RTDIR)/crt0.s $(BUILDDIR)/_phase6_$*.s $(RTDIR)/lib.S

# ----- Phase 6 test execution targets -----
test-phase6-array: build/phase6_array.hex
	@cp $< ../build/test.hex && cd .. && python3 tools/hex_to_bsv.py build/test.hex > src/soc/TestProgram.bsv && $(MAKE) -s compile verilator 2>/dev/null && result=$$(timeout 30 ./obj_dir/VmkTestBench 2>&1 | grep "tohost=") && echo "$$result" && echo "$$result" | grep -q "tohost=0x0000000f" && echo "✓ PASSED (tohost=15)" || echo "✗ FAILED (expected tohost=15)"

test-phase6: test-phase6-array
	@echo "=== All Phase 6 tests done ==="
```

- [ ] **Step 2: Add to .PHONY**

```makefile
.PHONY: ... test-phase6 test-phase6-array
```

- [ ] **Step 3: Commit**

```bash
git add Makefile
git commit -m "feat(makefile): add phase6 test targets"
```

---

## Task 15: Verify Implementation

**Files:**
- Test execution

- [ ] **Step 1: Build compiler**

```bash
make clean && make
```

Expected: `build/microcc` created.

- [ ] **Step 2: Run phase6 test**

```bash
make test-phase6-array
```

Expected output:
```
tohost=0x0000000f
✓ PASSED (tohost=15)
```

- [ ] **Step 3: If passing, commit**

```bash
git add -A
git commit -m "feat(phase6): array support complete - arr_sum verified"
```

---

## Summary

| Task | Module | Key Change |
|------|--------|------------|
| T1 | lexer | TOK_LBRACKET/RBRACKET |
| T2 | types | array_size field |
| T3 | ast | AST_ARRAY_ACCESS |
| T4 | parser | `int arr[n]` declaration |
| T5 | parser | `arr[i]` expression |
| T6 | parser | `arr[i] = val` assignment |
| T7 | codegen | Symbol table array tracking |
| T8 | codegen | Stack frame for arrays |
| T9 | codegen | Array name → address |
| T10 | codegen | Subscript read |
| T11 | codegen | Subscript write |
| T12 | codegen | Pointer arithmetic |
| T13 | tests | test_array.c |
| T14 | makefile | phase6 targets |
| T15 | verify | CPU execution |

**Verification**: `arr_sum(arr, 5)` → tohost=15, confirming array declaration, subscript, and pointer pass work correctly.