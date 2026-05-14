# Phase 5: Pointer Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Add pointer support to RV32I compiler, verified by `swap(&a, &b)` test.

**Architecture:** Extend existing modules (lexer, parser, codegen) + add new types.h/c. Single-level pointer only, no multi-level or pointer arithmetic.

**Tech Stack:** C99, RV32I assembly, CPU TestBench verification.

---

## File Structure

| File | Action | Responsibility |
|------|--------|----------------|
| `src/lexer.h` | Modify | Add `TOK_AND` token |
| `src/lexer.c` | Modify | Recognize `&` character |
| `src/types.h` | Create | Define `Type` struct |
| `src/types.c` | Create | Type helper functions |
| `src/ast.h` | Modify | Add `AST_ADDR`, `AST_DEREF` nodes |
| `src/ast.c` | Modify | Handle new node types |
| `src/parser.c` | Modify | Parse pointer declarations and `&`/`*` expressions |
| `src/codegen.c` | Modify | Generate address/dereference code |
| `Makefile` | Modify | Add phase5 test targets |
| `tests/phase5/test_swap.c` | Create | Verification test file |

---

## Task 1: Add TOK_AND Token to Lexer

**Files:**
- Modify: `src/lexer.h:5-10` (enum)
- Modify: `src/lexer.c:25-35` (tok_name), `src/lexer.c:175-180` (single-char tokens)

- [ ] **Step 1: Add TOK_AND to lexer.h enum**

```c
// src/lexer.h - Modify enum TokenType
typedef enum {
    TOK_INT, TOK_ID, TOK_NUM, TOK_RETURN,
    TOK_LPAREN, TOK_RPAREN, TOK_LBRACE, TOK_RBRACE, TOK_SEMI,
    TOK_ASSIGN, TOK_PLUS, TOK_MINUS, TOK_STAR, TOK_SLASH,
    TOK_IF, TOK_ELSE, TOK_WHILE, TOK_FOR, TOK_LT, TOK_INC,
    TOK_COMMA,
    TOK_AND,       // NEW: 取地址操作符 '&'
    TOK_EOF
} TokenType;
```

- [ ] **Step 2: Add name for TOK_AND in tok_name function**

```c
// src/lexer.c - Add case to tok_name()
case TOK_AND:    return "&";
```

- [ ] **Step 3: Add `&` recognition in tokenizer**

```c
// src/lexer.c - Add case to single-char token switch (around line 175)
case '&': t = TOK_AND; break;
```

- [ ] **Step 4: Build and verify lexer compiles**

```bash
cd /home/daivy/projects/riscv-bsv-processor/rv32i-compiler
make clean && make
```

Expected: Compilation succeeds with no errors.

- [ ] **Step 5: Commit**

```bash
git add src/lexer.h src/lexer.c
git commit -m "feat(lexer): add TOK_AND token for address-of operator"
```

---

## Task 2: Create Type System (types.h/c)

**Files:**
- Create: `src/types.h`
- Create: `src/types.c`

- [ ] **Step 1: Create types.h**

```c
// src/types.h - New file
#ifndef TYPES_H
#define TYPES_H

/* Type structure for variable/parameter type tracking */
typedef struct {
    int base_type;    /* 0 = int (future: 1 = struct, 2 = array) */
    int ptr_level;    /* Pointer level: 0 = int, 1 = int*, 2 = int** */
} Type;

/* Type helper functions */
Type type_make_int(void);           /* Create int type (ptr_level=0) */
Type type_make_int_ptr(void);       /* Create int* type (ptr_level=1) */
int  type_is_ptr(Type t);           /* Check if type is pointer */
void type_check_single_ptr(Type t); /* Error if ptr_level > 1 */

#endif /* TYPES_H */
```

- [ ] **Step 2: Create types.c**

```c
// src/types.c - New file
#include "types.h"
#include <stdio.h>

Type type_make_int(void)
{
    Type t = { .base_type = 0, .ptr_level = 0 };
    return t;
}

Type type_make_int_ptr(void)
{
    Type t = { .base_type = 0, .ptr_level = 1 };
    return t;
}

int type_is_ptr(Type t)
{
    return t.ptr_level > 0;
}

void type_check_single_ptr(Type t)
{
    if (t.ptr_level > 1) {
        fprintf(stderr, "error: multi-level pointer not supported in phase 5\n");
    }
}
```

- [ ] **Step 3: Add types.c to Makefile**

```makefile
# Makefile - Add to SRCS and OBJS
SRCS = $(SRCDIR)/main.c $(SRCDIR)/lexer.c $(SRCDIR)/parser.c \
       $(SRCDIR)/codegen.c $(SRCDIR)/asm.c $(SRCDIR)/linker.c \
       $(SRCDIR)/ast.c $(SRCDIR)/types.c

OBJS = $(BUILDDIR)/main.o $(BUILDDIR)/lexer.o $(BUILDDIR)/parser.o \
       $(BUILDDIR)/codegen.o $(BUILDDIR)/asm.o $(BUILDDIR)/linker.o \
       $(BUILDDIR)/ast.o $(BUILDDIR)/types.o
```

- [ ] **Step 4: Build and verify**

```bash
make clean && make
```

Expected: Compilation succeeds.

- [ ] **Step 5: Commit**

```bash
git add src/types.h src/types.c Makefile
git commit -m "feat(types): create Type struct for pointer type tracking"
```

---

## Task 3: Add AST_ADDR and AST_DEREF Nodes

**Files:**
- Modify: `src/ast.h:4-17` (enum)
- Modify: `src/ast.c` (if needed for debug)

- [ ] **Step 1: Add node types to ast.h enum**

```c
// src/ast.h - Modify ASTNodeType enum
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
    AST_ADDR,       /* NEW: 取地址 &x */
    AST_DEREF       /* NEW: 解引用 *p */
} ASTNodeType;
```

- [ ] **Step 2: Build and verify**

```bash
make clean && make
```

Expected: Compilation succeeds.

- [ ] **Step 3: Commit**

```bash
git add src/ast.h
git commit -m "feat(ast): add AST_ADDR and AST_DEREF node types"
```

---

## Task 4: Extend Symbol Table with Type Field in Codegen

**Files:**
- Modify: `src/codegen.c:35-60` (symbol table)

- [ ] **Step 1: Add Type field to symbol table**

```c
// src/codegen.c - Modify symbol table struct
#include "types.h"  /* Add at top of file */

#define MAX_LOCALS 64

static struct {
    char *name;
    int   offset;
    Type  type;      /* NEW: type information */
} syms[MAX_LOCALS];
```

- [ ] **Step 2: Initialize type in sym_add**

```c
// src/codegen.c - Modify sym_add function
static void sym_add(const char *name)
{
    if (sym_lookup(name) >= 0)
        return;
    syms[sym_count].name   = strdup(name);
    syms[sym_count].offset = 16 + 4 * sym_count;
    syms[sym_count].type   = type_make_int();  /* Default: int, will be updated by parser */
    sym_count++;
}

/* NEW: Add function to set variable type */
static void sym_set_type(const char *name, Type t)
{
    for (int i = 0; i < sym_count; i++)
        if (strcmp(syms[i].name, name) == 0) {
            syms[i].type = t;
            return;
        }
}
```

- [ ] **Step 3: Add sym_lookup_type helper**

```c
// src/codegen.c - Add new function
static Type sym_lookup_type(const char *name)
{
    for (int i = 0; i < sym_count; i++)
        if (strcmp(syms[i].name, name) == 0)
            return syms[i].type;
    return type_make_int();  /* Default */
}
```

- [ ] **Step 4: Build and verify**

```bash
make clean && make
```

Expected: Compilation succeeds.

- [ ] **Step 5: Commit**

```bash
git add src/codegen.c
git commit -m "feat(codegen): extend symbol table with Type field"
```

---

## Task 5: Parser - Pointer Type in Variable Declaration

**Files:**
- Modify: `src/parser.c:158-181` (parse_var_decl)

- [ ] **Step 1: Add include and type tracking**

```c
// src/parser.c - Add at top
#include "types.h"

/* Track current variable's type during declaration */
static Type current_decl_type;
```

- [ ] **Step 2: Modify parse_var_decl to handle `int *p`**

```c
// src/parser.c - Replace parse_var_decl function
/* var-decl = "int" ["*"] identifier ["=" expr] ";" */
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
    n->var_type = var_type;  /* Store type in AST node (need to add field) */
    cur = cur->next;

    if (cur->type == TOK_ASSIGN) {
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

- [ ] **Step 3: Add var_type field to AST_VAR_DECL in ast.h**

```c
// src/ast.h - Add to ASTNode struct after 'name' field
    Type  var_type;     /* for VAR_DECL: variable type (NEW) */
```

- [ ] **Step 4: Build and verify**

```bash
make clean && make
```

Expected: Compilation succeeds.

- [ ] **Step 5: Commit**

```bash
git add src/parser.c src/ast.h
git commit -m "feat(parser): parse pointer type in variable declaration"
```

---

## Task 6: Parser - Pointer Type in Function Parameters

**Files:**
- Modify: `src/parser.c:434-465` (parse_func_def)

- [ ] **Step 1: Modify parameter parsing to handle `int *p`**

```c
// src/parser.c - Modify parse_func_def parameter parsing section
/* Parse parameter list: (int name, int name, ...) OR (int *name, ...) */
ASTNode *params = NULL, *tail = NULL;
if (cur->type != TOK_RPAREN) {
    do {
        if (cur->type == TOK_COMMA)
            cur = cur->next;
        expect(TOK_INT);
        
        /* Check for pointer parameter: int *p */
        Type param_type = type_make_int();
        if (cur->type == TOK_STAR) {
            param_type = type_make_int_ptr();
            cur = cur->next; /* skip '*' */
        }
        
        if (cur->type != TOK_ID) {
            parse_error(cur->line, cur->col, "expected parameter name");
            break;
        }
        ASTNode *p = ast_new(AST_VAR_DECL);
        p->name = strdup(cur->text);
        p->var_type = param_type;  /* Store parameter type */
        cur = cur->next; /* skip identifier */
        if (!params) params = tail = p;
        else { tail->next = p; tail = p; }
    } while (cur->type == TOK_COMMA);
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
git commit -m "feat(parser): parse pointer type in function parameters"
```

---

## Task 7: Parser - Address-of and Dereference Expressions

**Files:**
- Modify: `src/parser.c:36-83` (parse_primary)

- [ ] **Step 1: Add TOK_AND and TOK_STAR handling in parse_primary**

```c
// src/parser.c - Add to parse_primary function (before TOK_NUM case)
/* primary = integer-literal | identifier | "&" primary | "*" primary | "(" expr ")" */
static ASTNode *parse_primary(void)
{
    /* Address-of operator: &x */
    if (cur->type == TOK_AND) {
        cur = cur->next; /* skip '&' */
        ASTNode *operand = parse_primary();
        ASTNode *n = ast_new(AST_ADDR);
        n->left = operand;
        return n;
    }
    
    /* Dereference operator: *p */
    if (cur->type == TOK_STAR) {
        cur = cur->next; /* skip '*' */
        ASTNode *operand = parse_primary();
        ASTNode *n = ast_new(AST_DEREF);
        n->left = operand;
        return n;
    }
    
    if (cur->type == TOK_NUM) {
        /* ... existing code ... */
    }
    /* ... rest of existing parse_primary code ... */
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
git commit -m "feat(parser): parse & (address-of) and * (dereference) expressions"
```

---

## Task 8: Codegen - Generate Address-of Code

**Files:**
- Modify: `src/codegen.c:98-168` (gen_expr)

- [ ] **Step 1: Add AST_ADDR case in gen_expr**

```c
// src/codegen.c - Add to gen_expr switch
case AST_ADDR: {
    /* &x → get address of variable x (stack offset) */
    if (n->left->type != AST_VAR_REF) {
        fprintf(stderr, "codegen error: & operator requires variable\n");
        return;
    }
    int off = sym_lookup(n->left->name);
    if (off < 0) {
        fprintf(stderr, "codegen error: undefined variable '%s'\n", n->left->name);
        return;
    }
    emit("    addi t0, sp, %d\n", off);  /* t0 = address of x */
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
git commit -m "feat(codegen): generate address-of (&) code"
```

---

## Task 9: Codegen - Generate Dereference Read Code

**Files:**
- Modify: `src/codegen.c:98-168` (gen_expr)

- [ ] **Step 1: Add AST_DEREF case in gen_expr (for reading)**

```c
// src/codegen.c - Add to gen_expr switch
case AST_DEREF: {
    /* *p → load from address computed by p */
    gen_expr(n->left);  /* Evaluate pointer expression, result in t0 */
    emit("    lw t0, 0(t0)\n");  /* t0 = *t0 (load from address) */
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
git commit -m "feat(codegen): generate dereference (*) read code"
```

---

## Task 10: Codegen - Handle Dereference on Assignment Left Side

**Files:**
- Modify: `src/codegen.c:186-192` (AST_ASSIGN case in gen_stmt)

- [ ] **Step 1: Modify AST_ASSIGN to handle `*p = expr`**

```c
// src/codegen.c - Replace AST_ASSIGN case in gen_stmt
case AST_ASSIGN: {
    gen_expr(n->expr);  /* Evaluate right side, result in t0 */
    
    /* Check if left side is dereference: *p = expr */
    if (n->is_deref_assign) {  /* NEW: flag set by parser for *p = */
        /* Need to evaluate pointer first */
        gen_expr(n->deref_target);  /* Evaluate p, get address */
        emit("    sw t0, 0(t0)\n");  /* Store value at address */
    } else {
        /* Normal variable assignment: x = expr */
        int off = sym_lookup(n->name);
        if (off < 0) {
            fprintf(stderr, "codegen error: undefined variable '%s'\n", n->name);
            return;
        }
        emit("    sw t0, %d(sp)\n", off);
    }
    break;
}
```

- [ ] **Step 2: Add fields to ASTNode for deref assignment**

```c
// src/ast.h - Add fields for dereference assignment
    int   is_deref_assign;  /* for ASSIGN: 1 if assigning to *p */
    struct ASTNode *deref_target;  /* for ASSIGN: pointer expr for *p = */
```

- [ ] **Step 3: Modify parser to detect and mark dereference assignment**

```c
// src/parser.c - Modify parse_assign function
/* assign-stmt = identifier "=" expression ";" OR "*" primary "=" expression ";" */
static ASTNode *parse_assign(void)
{
    ASTNode *n = ast_new(AST_ASSIGN);
    
    /* Check for dereference assignment: *p = expr */
    if (cur->type == TOK_STAR) {
        n->is_deref_assign = 1;
        cur = cur->next; /* skip '*' */
        n->deref_target = parse_primary();  /* Get pointer expression */
        
        if (cur->type != TOK_ASSIGN) {
            parse_error(cur->line, cur->col, "expected '=' after dereference");
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
    n->is_deref_assign = 0;
    n->name = strdup(cur->text);
    cur = cur->next;

    if (cur->type != TOK_ASSIGN) {
        parse_error(cur->line, cur->col, "expected '=' after identifier");
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
```

- [ ] **Step 4: Also handle `*p` in statement parsing**

```c
// src/parser.c - Modify parse_stmt to handle *p = as assignment
/* statement parsing: handle *p = expr; as assignment */
if (cur->type == TOK_STAR) {
    return parse_assign();  /* *p = expr; */
}
```

- [ ] **Step 5: Build and verify**

```bash
make clean && make
```

Expected: Compilation succeeds.

- [ ] **Step 6: Commit**

```bash
git add src/codegen.c src/ast.h src/parser.c
git commit -m "feat(codegen): handle dereference assignment (*p = expr)"
```

---

## Task 11: Create Phase 5 Test File

**Files:**
- Create: `tests/phase5/test_swap.c`

- [ ] **Step 1: Create test directory**

```bash
mkdir -p tests/phase5
```

- [ ] **Step 2: Create swap.c test file**

```c
// tests/phase5/test_swap.c
void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int main() {
    int x = 1;
    int y = 2;
    swap(&x, &y);
    return x;  /* Should return 2 after swap */
}
```

- [ ] **Step 3: Commit test file**

```bash
git add tests/phase5/test_swap.c
git commit -m "test(phase5): add swap pointer test"
```

---

## Task 12: Add Phase 5 Makefile Targets

**Files:**
- Modify: `Makefile`

- [ ] **Step 1: Add phase5 test targets**

```makefile
# Makefile - Add after phase4 targets

# ----- Phase 5 test hex targets -----
HEX5 = build/phase5_swap.hex

$(HEX5): build/phase5_%.hex: tests/phase5/test_%.c $(BUILDDIR)/microcc $(RTDIR)/crt0.s $(RTDIR)/lib.S
	@mkdir -p $(BUILDDIR)
	./$(BUILDDIR)/microcc $< $@ $(RTDIR)/crt0.s $(BUILDDIR)/_phase5_$*.s $(RTDIR)/lib.S

# ----- Phase 5 test execution targets -----
test-phase5-swap: build/phase5_swap.hex
	@cp $< ../build/test.hex && cd .. && python3 tools/hex_to_bsv.py build/test.hex > src/soc/TestProgram.bsv && $(MAKE) -s compile verilator 2>/dev/null && result=$$(timeout 30 ./obj_dir/VmkTestBench 2>&1 | grep "tohost=") && echo "$$result" && echo "$$result" | grep -q "tohost=0x00000002" && echo "✓ PASSED (tohost=2)" || echo "✗ FAILED (expected tohost=2)"

test-phase5: test-phase5-swap
	@echo "=== All Phase 5 tests done ==="
```

- [ ] **Step 2: Add to .PHONY**

```makefile
# Makefile - Add to .PHONY line
.PHONY: all test clean test-phase2 ... test-phase5 test-phase5-swap
```

- [ ] **Step 3: Commit**

```bash
git add Makefile
git commit -m "feat(makefile): add phase5 test targets"
```

---

## Task 13: Verify Phase 5 Implementation

**Files:**
- Test execution

- [ ] **Step 1: Build compiler**

```bash
make clean && make
```

Expected: `build/microcc` created successfully.

- [ ] **Step 2: Run phase5 test**

```bash
make test-phase5-swap
```

Expected output:
```
tohost=0x00000002
✓ PASSED (tohost=2)
```

- [ ] **Step 3: If failed, debug intermediate assembly**

```bash
cat build/_phase5_swap.s
```

Expected assembly should show:
- `swap:` function with `lw/sw` for dereference
- `main:` with `addi a0/a1, sp, offset` for `&x` and `&y`

- [ ] **Step 4: Final verification - run all tests**

```bash
make test-phase5
```

Expected: All phase 5 tests pass.

- [ ] **Step 5: Commit if passing**

```bash
git add -A
git commit -m "feat(phase5): pointer support complete - swap(&a, &b) verified"
```

---

## Summary

| Task | Module | Key Change |
|------|--------|------------|
| T1 | lexer | TOK_AND token |
| T2 | types | Type struct for pointer tracking |
| T3 | ast | AST_ADDR, AST_DEREF nodes |
| T4 | codegen | Symbol table Type field |
| T5 | parser | `int *p` variable declaration |
| T6 | parser | `int *p` function parameter |
| T7 | parser | `&x`, `*p` expression parsing |
| T8 | codegen | `addi t0, sp, offset` for & |
| T9 | codegen | `lw t0, 0(t0)` for * |
| T10 | codegen | `sw t0, 0(t0)` for *p = |
| T11 | tests | swap.c test file |
| T12 | makefile | phase5 test targets |
| T13 | verify | CPU execution verification |

**Verification Criteria**: `swap(&x, &y)` produces tohost=2, confirming pointer pass-by-reference works correctly.