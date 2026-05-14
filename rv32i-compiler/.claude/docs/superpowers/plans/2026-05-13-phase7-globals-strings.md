# Phase 7: Global Variables and Strings Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Add global variable declarations and string literal support for mini-os compatibility.

**Architecture:** Dual-segment (.text + .data), global symbol table separate from local, strings stored in .data with `\0` termination, introduce `char` type for ABI-compatible string handling.

**Tech Stack:** C (Micro-C subset), RV32I target, existing compiler pipeline (Lexer → Parser → Codegen → Assembler → Linker).

---

## File Structure

| File | Changes |
|------|---------|
| `src/types.h` | Add `BaseType` enum, `char` helpers |
| `src/types.c` | Implement `type_make_char()`, `type_make_char_ptr()` |
| `src/lexer.h` | Add `TOK_CHAR`, `TOK_STRING` tokens |
| `src/lexer.c` | Add `char` keyword, string literal parsing |
| `src/ast.h` | Add `AST_GLOBAL_DECL`, `AST_STRING_LIT` node types |
| `src/parser.c` | Add global declaration parsing, string expression |
| `src/codegen.c` | Add global symbol table, .data output, `la` instruction |
| `src/asm.c` | Add `la` pseudo-instruction (auipc + addi) |
| `src/linker.c` | No changes needed (existing two-pass handles .data labels) |
| `Makefile` | Add phase7 test targets |
| `tests/phase7/*.c` | 6 test files |

---

### Task 1: Type System Extension

**Files:**
- Modify: `src/types.h:1-19`
- Modify: `src/types.c:1-37`

- [ ] **Step 1: Add BaseType enum to types.h**

Replace the existing `Type` struct definition with the new one that includes `BaseType`:

```c
/* Type structure for variable/parameter type tracking */
typedef enum {
    TYPE_INT = 0,
    TYPE_CHAR = 1
} BaseType;

typedef struct {
    BaseType base_type;  /* TYPE_INT or TYPE_CHAR */
    int ptr_level;       /* Pointer level: 0 = scalar, 1 = pointer */
    int array_size;      /* Array size: 0 = not array, >0 = array elements count */
} Type;

/* Type helper functions */
Type type_make_int(void);           /* Create int type */
Type type_make_int_ptr(void);       /* Create int* type */
Type type_make_array(int size);     /* Create int array type */
Type type_make_char(void);          /* Create char type */
Type type_make_char_ptr(void);      /* Create char* type */
Type type_make_char_array(int size);/* Create char array type */
int  type_is_ptr(Type t);           /* Check if type is pointer */
int  type_is_array(Type t);         /* Check if type is array */
int  type_is_char(Type t);          /* Check if base type is char */
void type_check_single_ptr(Type t); /* Error if ptr_level > 1 */
```

- [ ] **Step 2: Add char type helpers to types.c**

Add the new helper functions after `type_make_array()`:

```c
Type type_make_char(void)
{
    Type t = { .base_type = TYPE_CHAR, .ptr_level = 0, .array_size = 0 };
    return t;
}

Type type_make_char_ptr(void)
{
    Type t = { .base_type = TYPE_CHAR, .ptr_level = 1, .array_size = 0 };
    return t;
}

Type type_make_char_array(int size)
{
    Type t = { .base_type = TYPE_CHAR, .ptr_level = 0, .array_size = size };
    return t;
}

int type_is_char(Type t)
{
    return t.base_type == TYPE_CHAR;
}
```

Update `type_make_int()` to explicitly set `base_type`:

```c
Type type_make_int(void)
{
    Type t = { .base_type = TYPE_INT, .ptr_level = 0, .array_size = 0 };
    return t;
}

Type type_make_int_ptr(void)
{
    Type t = { .base_type = TYPE_INT, .ptr_level = 1, .array_size = 0 };
    return t;
}

Type type_make_array(int size)
{
    Type t = { .base_type = TYPE_INT, .ptr_level = 0, .array_size = size };
    return t;
}
```

- [ ] **Step 3: Build and verify compilation**

Run: `make clean && make`
Expected: Compiles without errors

- [ ] **Step 4: Commit**

```bash
git add src/types.h src/types.c
git commit -m "feat(types): add char type support with BaseType enum"
```

---

### Task 2: Lexer Extension (char keyword + string literal)

**Files:**
- Modify: `src/lexer.h:1-28`
- Modify: `src/lexer.c:1-196`

- [ ] **Step 1: Add TOK_CHAR and TOK_STRING to lexer.h**

Add new tokens to the enum after `TOK_AND`:

```c
typedef enum {
    TOK_INT, TOK_ID, TOK_NUM, TOK_RETURN,
    TOK_LPAREN, TOK_RPAREN, TOK_LBRACE, TOK_RBRACE, TOK_SEMI,
    TOK_ASSIGN, TOK_PLUS, TOK_MINUS, TOK_STAR, TOK_SLASH,
    TOK_IF, TOK_ELSE, TOK_WHILE, TOK_FOR, TOK_LT, TOK_INC,
    TOK_COMMA,
    TOK_AND,
    TOK_CHAR,       /* NEW: char keyword */
    TOK_STRING,     /* NEW: string literal */
    TOK_LBRACKET,
    TOK_RBRACKET,
    TOK_EOF
} TokenType;
```

- [ ] **Step 2: Add char to tok_name() in lexer.c**

Add case for `TOK_CHAR` and `TOK_STRING` in the switch:

```c
const char *tok_name(TokenType t)
{
    switch (t) {
    case TOK_INT:    return "int";
    case TOK_CHAR:   return "char";      /* NEW */
    case TOK_STRING: return "string";    /* NEW */
    case TOK_ID:     return "identifier";
    /* ... rest unchanged ... */
    }
}
```

- [ ] **Step 3: Add char keyword to lex_keyword_or_id()**

Add recognition for `char` keyword:

```c
static Token *lex_keyword_or_id(const char *s, int len, int line, int col)
{
    if (len == 3 && strncmp(s, "int", 3) == 0)
        return new_token(TOK_INT, s, len, line, col);
    if (len == 4 && strncmp(s, "char", 4) == 0)
        return new_token(TOK_CHAR, s, len, line, col);  /* NEW */
    if (len == 6 && strncmp(s, "return", 6) == 0)
        return new_token(TOK_RETURN, s, len, line, col);
    /* ... rest unchanged ... */
}
```

- [ ] **Step 4: Add string literal parsing in tokenize()**

Add string parsing before the identifier section (around line 154):

```c
/* string literals: "..." with escape handling */
if (c == '"') {
    char *start = p; int start_col = col;
    p++; col++;  /* skip opening quote */
    char *str_buf = malloc(256);
    int str_len = 0;
    while (*p && *p != '"' && str_len < 255) {
        if (*p == '\\' && p[1]) {
            /* escape sequences */
            p++; col++;
            switch (*p) {
                case 'n': str_buf[str_len++] = '\n'; break;
                case 't': str_buf[str_len++] = '\t'; break;
                case '0': str_buf[str_len++] = '\0'; break;
                case '\\': str_buf[str_len++] = '\\'; break;
                case '"': str_buf[str_len++] = '"'; break;
                default: str_buf[str_len++] = *p; break;
            }
            p++; col++;
        } else {
            str_buf[str_len++] = *p;
            p++; col++;
        }
    }
    if (*p != '"') {
        lex_error(line, start_col, "unterminated string literal");
    } else {
        p++; col++;  /* skip closing quote */
    }
    str_buf[str_len] = '\0';
    tail->next = new_token(TOK_STRING, str_buf, str_len, line, start_col);
    tail = tail->next;
    free(str_buf);
    continue;
}
```

- [ ] **Step 5: Build and verify compilation**

Run: `make clean && make`
Expected: Compiles without errors

- [ ] **Step 6: Commit**

```bash
git add src/lexer.h src/lexer.c
git commit -m "feat(lexer): add char keyword and string literal tokens"
```

---

### Task 3: AST Extension (AST_GLOBAL_DECL, AST_STRING_LIT)

**Files:**
- Modify: `src/ast.h:1-52`

- [ ] **Step 1: Add new AST node types**

Add `AST_GLOBAL_DECL` and `AST_STRING_LIT` to the enum:

```c
typedef enum {
    AST_GLOBAL_DECL,   /* NEW: global variable declaration */
    AST_FUNC_DEF,
    AST_RETURN,
    AST_INT_LIT,
    AST_STRING_LIT,    /* NEW: string literal expression */
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
    AST_ARRAY_ACCESS
} ASTNodeType;
```

- [ ] **Step 2: Extend ASTNode struct for global/string fields**

Add fields to the struct for global declarations and strings:

```c
typedef struct ASTNode {
    ASTNodeType type;
    /* type-specific data */
    char *func_name;       /* for FUNC_DEF */
    struct ASTNode *body;  /* for FUNC_DEF: statement list */
    int int_val;           /* for INT_LIT */
    int op;                /* for BIN_OP: TokenType */
    struct ASTNode *left;  /* for BIN_OP: left operand */
    struct ASTNode *right; /* for BIN_OP: right operand / FUNC_DEF: params */
    char *name;            /* for VAR_DECL, VAR_REF, ASSIGN, GLOBAL_DECL: variable name */
    Type  var_type;        /* for VAR_DECL, GLOBAL_DECL: variable type */
    int   is_deref_assign; /* for ASSIGN: 1 if assigning to *p */
    int   is_array_assign; /* for ASSIGN: 1 if assigning to arr[i] */
    char  *array_name;     /* for ASSIGN/ARRAY_ACCESS: array name */
    struct ASTNode *array_index; /* for ASSIGN/ARRAY_ACCESS: index expr */
    struct ASTNode *deref_target; /* for ASSIGN: pointer expr for *p = */
    struct ASTNode *init;  /* for VAR_DECL, GLOBAL_DECL: initializer (NULL if none) */
    struct ASTNode *expr;  /* for ASSIGN: right-hand side expression */
    /* NEW: global declaration fields */
    int   is_global;       /* for GLOBAL_DECL: marker (1) */
    /* NEW: string literal fields */
    char *str_val;         /* for STRING_LIT: string content */
    int   str_label;       /* for STRING_LIT: assigned label index */
    struct ASTNode *next;  /* linked-list chain */
} ASTNode;
```

- [ ] **Step 3: Build and verify compilation**

Run: `make`
Expected: Compiles without errors (parser.c may need updates, but ast.h alone should compile)

- [ ] **Step 4: Commit**

```bash
git add src/ast.h
git commit -m "feat(ast): add AST_GLOBAL_DECL and AST_STRING_LIT node types"
```

---

### Task 4: Parser Extension (global declarations + string expressions)

**Files:**
- Modify: `src/parser.c:1-635`

- [ ] **Step 1: Add parse_global_decl() function**

Add the function after `parse_func_def()` (around line 608):

```c
/* global-decl = ("int" | "char") ["*"] identifier ["[" num "]"] ["=" (expr | string-lit)] ";" */
static ASTNode *parse_global_decl(void)
{
    Type var_type;
    if (cur->type == TOK_INT) {
        var_type = type_make_int();
        cur = cur->next; /* skip "int" */
    } else if (cur->type == TOK_CHAR) {
        var_type = type_make_char();
        cur = cur->next; /* skip "char" */
    } else {
        parse_error(cur->line, cur->col, "expected 'int' or 'char' for declaration");
        return NULL;
    }

    /* Pointer declaration */
    if (cur->type == TOK_STAR) {
        if (var_type.base_type == TYPE_INT)
            var_type = type_make_int_ptr();
        else
            var_type = type_make_char_ptr();
        cur = cur->next; /* skip '*' */
    }

    if (cur->type != TOK_ID) {
        parse_error(cur->line, cur->col, "expected identifier");
        return NULL;
    }
    ASTNode *n = ast_new(AST_GLOBAL_DECL);
    n->name = strdup(cur->text);
    n->var_type = var_type;
    n->is_global = 1;
    n->init = NULL;
    n->str_val = NULL;
    cur = cur->next;

    /* Array declaration: int arr[n] */
    if (cur->type == TOK_LBRACKET) {
        cur = cur->next; /* skip '[' */
        if (cur->type != TOK_NUM) {
            parse_error(cur->line, cur->col, "expected array size");
            return NULL;
        }
        int size = atoi(cur->text);
        if (var_type.base_type == TYPE_INT)
            var_type = type_make_array(size);
        else
            var_type = type_make_char_array(size);
        n->var_type = var_type;
        cur = cur->next; /* skip size */
        if (cur->type != TOK_RBRACKET) {
            parse_error(cur->line, cur->col, "expected ']' after array size");
            return NULL;
        }
        cur = cur->next; /* skip ']' */
    }

    /* Initializer */
    if (cur->type == TOK_ASSIGN) {
        cur = cur->next; /* skip '=' */
        if (cur->type == TOK_STRING) {
            /* char *s = "hello" or char arr[] = "hello" */
            n->str_val = strdup(cur->text);
            cur = cur->next;
        } else {
            /* int x = 42 or int x = 10+5 */
            n->init = parse_expr();
        }
    }

    if (cur->type != TOK_SEMI) {
        parse_error(cur->line, cur->col, "expected ';' after global declaration");
    } else {
        cur = cur->next;
    }
    return n;
}
```

- [ ] **Step 2: Add string literal to parse_primary()**

Add case for `TOK_STRING` in `parse_primary()` (around line 57):

```c
if (cur->type == TOK_STRING) {
    ASTNode *n = ast_new(AST_STRING_LIT);
    n->str_val = strdup(cur->text);
    n->str_label = -1;  /* assigned later by codegen */
    cur = cur->next;
    return n;
}
```

- [ ] **Step 3: Modify parse_program() for global declarations**

Replace `parse_program()` to handle both global declarations and function definitions:

```c
/* program = (global-decl | func-def)* */
static ASTNode *parse_program(void)
{
    ASTNode dummy = {0};
    ASTNode *tail = &dummy;

    while (cur->type != TOK_EOF) {
        ASTNode *node = NULL;
        
        /* Check if this is a global declaration or function definition */
        if (cur->type == TOK_INT || cur->type == TOK_CHAR) {
            /* Look ahead to distinguish global decl from func def */
            Token *next = cur->next;
            int is_func = 0;
            
            /* Skip pointer marker if present */
            if (next && next->type == TOK_STAR)
                next = next->next;
            
            /* If next is identifier followed by '(' → function definition */
            if (next && next->type == TOK_ID && next->next && next->next->type == TOK_LPAREN)
                is_func = 1;
            
            if (is_func) {
                node = parse_func_def();
            } else {
                node = parse_global_decl();
            }
        } else {
            parse_error(cur->line, cur->col, "expected declaration or function definition");
            break;
        }
        
        if (!node) break;
        tail->next = node;
        tail = node;
    }
    return dummy.next;
}
```

- [ ] **Step 4: Build and verify compilation**

Run: `make`
Expected: Compiles without errors

- [ ] **Step 5: Commit**

```bash
git add src/parser.c
git commit -m "feat(parser): add global declaration and string literal parsing"
```

---

### Task 5: Codegen Extension (global symbol table + .data output)

**Files:**
- Modify: `src/codegen.c:1-459`

This is the largest task. Break into sub-steps.

- [ ] **Step 1: Add global symbol table structures**

Add after the local symbol table definitions (around line 42):

```c
/* ================================================================
 *  Global symbol table — .data segment with absolute offsets
 * ================================================================ */

#define MAX_GLOBALS 64
#define MAX_STRING_LITS 64

static struct {
    char *name;
    int   offset;       /* .data segment offset (bytes) */
    Type  type;
    int   init_val;     /* integer initializer value */
    char *init_str;     /* string initializer (for char*) */
    int   str_len;      /* string length including \0 */
} globals[MAX_GLOBALS];

static int global_count;
static int data_offset;  /* current .data offset */

static struct {
    char *content;
    int   len;
    int   label;        /* .LstrN label number */
} string_lits[MAX_STRING_LITS];

static int string_lit_count;
static int string_label_counter;
```

- [ ] **Step 2: Add global symbol lookup functions**

Add helper functions for global symbols:

```c
static int global_lookup(const char *name)
{
    for (int i = 0; i < global_count; i++)
        if (strcmp(globals[i].name, name) == 0)
            return globals[i].offset;
    return -1;
}

static int global_is_string(const char *name)
{
    for (int i = 0; i < global_count; i++)
        if (strcmp(globals[i].name, name) == 0)
            return globals[i].init_str != NULL;
    return 0;
}

static Type global_lookup_type(const char *name)
{
    for (int i = 0; i < global_count; i++)
        if (strcmp(globals[i].name, name) == 0)
            return globals[i].type;
    return type_make_int();
}
```

- [ ] **Step 3: Add string label registration function**

```c
static int register_string_literal(const char *str)
{
    /* Check if already registered */
    for (int i = 0; i < string_lit_count; i++) {
        if (strcmp(string_lits[i].content, str) == 0)
            return string_lits[i].label;
    }
    
    /* Register new string */
    int label = string_label_counter++;
    string_lits[string_lit_count].content = strdup(str);
    string_lits[string_lit_count].len = strlen(str) + 1;  /* include \0 */
    string_lits[string_lit_count].label = label;
    string_lit_count++;
    return label;
}
```

- [ ] **Step 4: Add Pass 0 for collecting globals**

Add a function to collect all global declarations before code generation:

```c
/* Pass 0: collect global declarations */
static void collect_globals(ASTNode *prog)
{
    global_count = 0;
    data_offset = 0;
    string_lit_count = 0;
    string_label_counter = 0;

    for (ASTNode *n = prog; n; n = n->next) {
        if (n->type == AST_GLOBAL_DECL) {
            globals[global_count].name = strdup(n->name);
            globals[global_count].type = n->var_type;
            globals[global_count].offset = data_offset;
            globals[global_count].init_val = 0;
            globals[global_count].init_str = NULL;
            globals[global_count].str_len = 0;

            /* Handle initializer */
            if (n->str_val) {
                /* char* = "hello" - store string content */
                globals[global_count].init_str = strdup(n->str_val);
                globals[global_count].str_len = strlen(n->str_val) + 1;
                data_offset += globals[global_count].str_len;
                /* Align to 4 bytes */
                while (data_offset % 4 != 0) data_offset++;
            } else if (n->init) {
                /* int = expr - evaluate constant expression */
                if (n->init->type == AST_INT_LIT) {
                    globals[global_count].init_val = n->init->int_val;
                } else if (n->init->type == AST_BIN_OP) {
                    /* Simple constant expression evaluation */
                    int left = (n->init->left->type == AST_INT_LIT) ? n->init->left->int_val : 0;
                    int right = (n->init->right->type == AST_INT_LIT) ? n->init->right->int_val : 0;
                    if (n->init->op == TOK_PLUS)
                        globals[global_count].init_val = left + right;
                    else if (n->init->op == TOK_MINUS)
                        globals[global_count].init_val = left - right;
                    else if (n->init->op == TOK_STAR)
                        globals[global_count].init_val = left * right;
                }
                data_offset += 4;  /* int takes 4 bytes */
            } else {
                /* No initializer - default to 0, allocate space */
                if (n->var_type.array_size > 0) {
                    data_offset += n->var_type.array_size * 4;
                } else {
                    data_offset += 4;
                }
            }
            global_count++;
        }
    }
}
```

- [ ] **Step 5: Add .data segment output function**

```c
static void emit_data_segment(void)
{
    if (global_count == 0 && string_lit_count == 0)
        return;

    emit("    .data\n");

    /* Output global variables */
    for (int i = 0; i < global_count; i++) {
        emit(".global_%s:\n", globals[i].name);
        if (globals[i].init_str) {
            /* Output string bytes */
            emit("    .byte ");
            for (int j = 0; j < globals[i].str_len; j++) {
                unsigned char c = (unsigned char)globals[i].init_str[j];
                if (j > 0) emit(",");
                emit("%d", c);
            }
            emit("\n");
            emit("    .align 4\n");
        } else {
            /* Output integer word */
            emit("    .word %d\n", globals[i].init_val);
        }
    }

    /* Output string literals used in expressions */
    for (int i = 0; i < string_lit_count; i++) {
        emit(".Lstr%d:\n", string_lits[i].label);
        emit("    .byte ");
        for (int j = 0; j < string_lits[i].len; j++) {
            unsigned char c = (unsigned char)string_lits[i].content[j];
            if (j > 0) emit(",");
            emit("%d", c);
        }
        emit("\n");
        emit("    .align 4\n");
    }
}
```

- [ ] **Step 6: Modify gen_expr() for global var access and strings**

Update the `AST_VAR_REF` case and add `AST_STRING_LIT` case:

```c
case AST_VAR_REF: {
    /* Check if global first */
    int global_off = global_lookup(n->name);
    if (global_off >= 0) {
        /* Global variable - use la instruction */
        emit("    la t0, .global_%s\n", n->name);
        Type t = global_lookup_type(n->name);
        if (!type_is_array(t) && !type_is_ptr(t)) {
            emit("    lw t0, 0(t0)\n");  /* load value */
        }
        /* For array/pointer, t0 already holds address */
    } else {
        /* Local variable */
        int off = sym_lookup(n->name);
        if (off < 0) {
            fprintf(stderr, "codegen error: undefined variable '%s'\n", n->name);
            return;
        }
        Type t = sym_lookup_type(n->name);
        if (type_is_array(t)) {
            emit("    addi t0, sp, %d\n", off);
        } else {
            emit("    lw t0, %d(sp)\n", off);
        }
    }
    break;
}

case AST_STRING_LIT: {
    /* Register string and get label */
    int label = register_string_literal(n->str_val);
    n->str_label = label;
    emit("    la t0, .Lstr%d\n", label);
    break;
}
```

- [ ] **Step 7: Modify gen_stmt() for global assignment**

Update `AST_ASSIGN` case to handle global variable assignment:

```c
case AST_ASSIGN:
    gen_expr(n->expr);

    if (n->is_array_assign || n->is_deref_assign) {
        /* Existing array/deref assignment logic unchanged */
        /* ... keep existing code ... */
    } else {
        /* Check if global */
        int global_off = global_lookup(n->name);
        if (global_off >= 0) {
            /* Global assignment */
            emit("    la t1, .global_%s\n", n->name);
            emit("    sw t0, 0(t1)\n");
        } else {
            /* Local assignment */
            int off = sym_lookup(n->name);
            if (off < 0) {
                fprintf(stderr, "codegen error: undefined variable '%s'\n", n->name);
                return;
            }
            emit("    sw t0, %d(sp)\n", off);
        }
    }
    break;
```

- [ ] **Step 8: Modify codegen_gen() to call Pass 0 and emit .data**

Update the entry function:

```c
int codegen_gen(ASTNode *prog, const char *outfile)
{
    out = fopen(outfile, "w");
    if (!out) {
        fprintf(stderr, "cannot open %s for output\n", outfile);
        return 1;
    }

    /* Pass 0: collect global declarations */
    collect_globals(prog);

    /* Emit .data segment first */
    emit_data_segment();

    /* Then emit .text segment */
    emit("    .text\n");
    emit("    .globl main\n");

    for (ASTNode *fn = prog; fn; fn = fn->next) {
        if (fn->type == AST_FUNC_DEF)
            gen_func_def(fn);
    }

    fclose(out);
    return 0;
}
```

- [ ] **Step 9: Build and verify compilation**

Run: `make`
Expected: Compiles without errors

- [ ] **Step 10: Commit**

```bash
git add src/codegen.c
git commit -m "feat(codegen): add global symbol table and .data segment output"
```

---

### Task 6: Assembler Extension (la pseudo-instruction)

**Files:**
- Modify: `src/asm.c:1-832`

- [ ] **Step 1: Add la pseudo-instruction to assemble_line()**

Add the `la` case in the pseudo-instructions section (after `beqz`, around line 256):

```c
if (strcmp(mnemonic, "la") == 0) {     /* la rd, label  →  auipc rd, offset_hi; addi rd, rd, offset_lo */
    char rd_str[16], label_str[128];
    if (sscanf(p, "%15[^,], %127s", rd_str, label_str) != 2) {
        *errmsg = "la: expected rd, label"; return 0;
    }
    int rd = reg_num(rd_str);
    if (rd < 0) { *errmsg = "la: unknown reg"; return 0; }
    int target = lookup_label(label_str, labels, label_count);
    if (target < 0) { *errmsg = "la: undefined label"; return 0; }
    
    /* la expands to two instructions: auipc + addi
     * We need to emit TWO words, but assemble_line only emits one.
     * Solution: emit auipc here, mark that addi follows.
     * Actually, we need a different approach for two-word pseudo-insns.
     * 
     * Alternative: use PC-relative addressing:
     * auipc rd, %hi(label - PC)  → upper 20 bits
     * addi  rd, rd, %lo(label - PC) → lower 12 bits
     * 
     * For simplicity in our assembler, we expand la as:
     * auipc rd, (target - current_addr) >> 12
     * addi  rd, rd, (target - current_addr) & 0xFFF
     * 
     * But we can only return ONE word. We need a mechanism for multi-word.
     * 
     * Simplified approach: Since our .data is contiguous after .text,
     * we can compute absolute address and use lui + addi instead.
     * But la is PC-relative in standard RV32I.
     * 
     * For this phase, we implement la as:
     * lui rd, (target >> 12)
     * addi rd, rd, (target & 0xFFF)
     * 
     * This requires target to be known (absolute address).
     * Our linker outputs absolute addresses (0x80000000 + offset).
     * 
     * However, assemble_line returns ONE word. We need a way to emit TWO.
     * Let's use a global flag to signal "emit extra word next".
     */
    
    /* Alternative approach: single lui for high bits, caller handles addi */
    /* Actually, let's use auipc + addi properly with two-pass */
    
    /* For now, use lui to load upper 20 bits of absolute address */
    int upper = (target >> 12) & 0xFFFFF;
    *word_out = encode_utype(upper, rd, 0x37);  /* lui */
    
    /* Signal that an addi follows - we use a global variable */
    /* This is a hack, but works for our simple assembler */
    extern int la_addi_pending;
    extern int la_addi_rd;
    extern int la_addi_imm;
    la_addi_pending = 1;
    la_addi_rd = rd;
    la_addi_imm = target & 0xFFF;
    
    return 1;  /* returns 1 word, but indicates pending addi */
}
```

- [ ] **Step 2: Add global variables for la expansion**

Add at the top of asm.c:

```c
/* Global state for la pseudo-instruction expansion */
int la_addi_pending = 0;
int la_addi_rd = 0;
int la_addi_imm = 0;
```

- [ ] **Step 3: Modify asm_assemble() to handle pending addi**

In Pass 2, after each instruction is processed, check for pending addi:

```c
/* In Pass 2 loop, after assembling each line: */
for (int i = 0; i < line_count; i++) {
    if (lines[i].kind == 0) continue;
    if (lines[i].kind == 1) continue;

    uint32_t w;
    int rc = assemble_line(lines[i].text, addr,
                           labels, label_count,
                           &w, &errmsg);
    if (rc == 1) {
        if (count >= cap) { cap *= 2; words = realloc(words, cap * sizeof(uint32_t)); }
        words[count++] = w;
        addr += 4;
        
        /* Handle pending la addi */
        if (la_addi_pending) {
            la_addi_pending = 0;
            uint32_t addi_w = encode_itype(la_addi_imm, la_addi_rd, 0, la_addi_rd, 0x13);
            if (count >= cap) { cap *= 2; words = realloc(words, cap * sizeof(uint32_t)); }
            words[count++] = addi_w;
            addr += 4;
        }
    } else if (rc == 0) {
        fprintf(stderr, "asm error: %s\n", errmsg);
        has_error = 1;
    }
}
```

- [ ] **Step 4: Build and verify compilation**

Run: `make`
Expected: Compiles without errors

- [ ] **Step 5: Commit**

```bash
git add src/asm.c
git commit -m "feat(asm): add la pseudo-instruction (lui + addi expansion)"
```

---

### Task 7: Create Test Files

**Files:**
- Create: `tests/phase7/test_global_int.c`
- Create: `tests/phase7/test_global_write.c`
- Create: `tests/phase7/test_global_expr.c`
- Create: `tests/phase7/test_string_arg.c`
- Create: `tests/phase7/test_string_assign.c`

- [ ] **Step 1: Create test_global_int.c**

```c
int g_count = 42;

int main() {
    return g_count;
}
```

- [ ] **Step 2: Create test_global_write.c**

```c
int g_val;

int main() {
    g_val = 100;
    return g_val;
}
```

- [ ] **Step 3: Create test_global_expr.c**

```c
int g_base = 10 + 5;

int main() {
    return g_base;
}
```

- [ ] **Step 4: Create test_string_arg.c**

```c
int strlen(char *s) {
    int n = 0;
    while (*s) {
        n = n + 1;
        s = s + 1;
    }
    return n;
}

int main() {
    return strlen("hello");
}
```

- [ ] **Step 5: Create test_string_assign.c**

```c
char *g_msg;

int strlen(char *s) {
    int n = 0;
    while (*s) {
        n = n + 1;
        s = s + 1;
    }
    return n;
}

int main() {
    g_msg = "world";
    return strlen(g_msg);
}
```

- [ ] **Step 6: Create tests/phase7 directory**

```bash
mkdir -p tests/phase7
```

- [ ] **Step 7: Write all test files**

Write each test file created above to `tests/phase7/`.

- [ ] **Step 8: Commit**

```bash
git add tests/phase7/
git commit -m "test(phase7): add global variable and string test cases"
```

---

### Task 8: Makefile Extension

**Files:**
- Modify: `Makefile:1-169`

- [ ] **Step 1: Add phase7 hex targets**

Add after phase6 section (around line 165):

```makefile
# ----- Phase 7 test hex targets -----
HEX7 = build/phase7_global_int.hex build/phase7_global_write.hex \
       build/phase7_global_expr.hex build/phase7_string_arg.hex \
       build/phase7_string_assign.hex

$(HEX7): build/phase7_%.hex: tests/phase7/test_%.c $(BUILDDIR)/microcc $(RTDIR)/crt0.s $(RTDIR)/lib.S
	@mkdir -p $(BUILDDIR)
	./$(BUILDDIR)/microcc $< $@ $(RTDIR)/crt0.s $(BUILDDIR)/_phase7_$*.s $(RTDIR)/lib.S

# ----- Phase 7 test execution targets -----
test-phase7-global-int: build/phase7_global_int.hex
	@cp $< ../build/test.hex && cd .. && python3 tools/hex_to_bsv.py build/test.hex > src/soc/TestProgram.bsv && $(MAKE) -s compile verilator 2>/dev/null && result=$$(timeout 30 ./obj_dir/VmkTestBench 2>&1 | grep "tohost=") && echo "$$result" && echo "$$result" | grep -q "tohost=0x0000002a" && echo "✓ PASSED (tohost=42)" || echo "✗ FAILED (expected tohost=42)"

test-phase7-global-write: build/phase7_global_write.hex
	@cp $< ../build/test.hex && cd .. && python3 tools/hex_to_bsv.py build/test.hex > src/soc/TestProgram.bsv && $(MAKE) -s compile verilator 2>/dev/null && result=$$(timeout 30 ./obj_dir/VmkTestBench 2>&1 | grep "tohost=") && echo "$$result" && echo "$$result" | grep -q "tohost=0x00000064" && echo "✓ PASSED (tohost=100)" || echo "✗ FAILED (expected tohost=100)"

test-phase7-global-expr: build/phase7_global_expr.hex
	@cp $< ../build/test.hex && cd .. && python3 tools/hex_to_bsv.py build/test.hex > src/soc/TestProgram.bsv && $(MAKE) -s compile verilator 2>/dev/null && result=$$(timeout 30 ./obj_dir/VmkTestBench 2>&1 | grep "tohost=") && echo "$$result" && echo "$$result" | grep -q "tohost=0x0000000f" && echo "✓ PASSED (tohost=15)" || echo "✗ FAILED (expected tohost=15)"

test-phase7-string-arg: build/phase7_string_arg.hex
	@cp $< ../build/test.hex && cd .. && python3 tools/hex_to_bsv.py build/test.hex > src/soc/TestProgram.bsv && $(MAKE) -s compile verilator 2>/dev/null && result=$$(timeout 30 ./obj_dir/VmkTestBench 2>&1 | grep "tohost=") && echo "$$result" && echo "$$result" | grep -q "tohost=0x00000005" && echo "✓ PASSED (tohost=5)" || echo "✗ FAILED (expected tohost=5)"

test-phase7-string-assign: build/phase7_string_assign.hex
	@cp $< ../build/test.hex && cd .. && python3 tools/hex_to_bsv.py build/test.hex > src/soc/TestProgram.bsv && $(MAKE) -s compile verilator 2>/dev/null && result=$$(timeout 30 ./obj_dir/VmkTestBench 2>&1 | grep "tohost=") && echo "$$result" && echo "$$result" | grep -q "tohost=0x00000005" && echo "✓ PASSED (tohost=5)" || echo "✗ FAILED (expected tohost=5)"

test-phase7: test-phase7-global-int test-phase7-global-write test-phase7-global-expr \
             test-phase7-string-arg test-phase7-string-assign
	@echo "=== All Phase 7 tests done ==="
```

- [ ] **Step 2: Update .PHONY line**

Add phase7 targets to `.PHONY`:

```makefile
.PHONY: all test clean test-phase2 ... test-phase6 test-phase6-array \
        test-phase7 test-phase7-global-int test-phase7-global-write \
        test-phase7-global-expr test-phase7-string-arg test-phase7-string-assign
```

- [ ] **Step 3: Commit**

```bash
git add Makefile
git commit -m "feat(makefile): add phase7 test targets"
```

---

### Task 9: Integration Testing

- [ ] **Step 1: Build compiler**

Run: `make clean && make`
Expected: Compiles without errors

- [ ] **Step 2: Run test_global_int**

Run: `make test-phase7-global-int`
Expected: ✓ PASSED (tohost=42)

- [ ] **Step 3: Run test_global_write**

Run: `make test-phase7-global-write`
Expected: ✓ PASSED (tohost=100)

- [ ] **Step 4: Run test_global_expr**

Run: `make test-phase7-global-expr`
Expected: ✓ PASSED (tohost=15)

- [ ] **Step 5: Run test_string_arg**

Run: `make test-phase7-string-arg`
Expected: ✓ PASSED (tohost=5)

- [ ] **Step 6: Run test_string_assign**

Run: `make test-phase7-string-assign`
Expected: ✓ PASSED (tohost=5)

- [ ] **Step 7: Run all phase7 tests**

Run: `make test-phase7`
Expected: All 5 tests pass

- [ ] **Step 8: Verify existing tests still pass**

Run: `make test-phase6`
Expected: ✓ PASSED (tohost=15)

- [ ] **Step 9: Final commit for phase completion**

```bash
git add -A
git commit -m "feat(phase7): global variables and string literals complete"
```

---

## Self-Review Checklist

### Spec Coverage

| Spec Requirement | Covered by Task |
|------------------|-----------------|
| Add `char` type | Task 1 |
| Add `TOK_CHAR`, `TOK_STRING` | Task 2 |
| Add `AST_GLOBAL_DECL`, `AST_STRING_LIT` | Task 3 |
| Parse global declarations | Task 4 |
| Parse string expressions | Task 4 |
| Global symbol table | Task 5 |
| .data segment output | Task 5 |
| `la` instruction | Task 6 |
| Test: global_int | Task 7 |
| Test: global_write | Task 7 |
| Test: global_expr | Task 7 |
| Test: string_arg | Task 7 |
| Test: string_assign | Task 7 |

### Placeholder Scan

- ✅ No "TBD", "TODO", "implement later"
- ✅ All code steps have complete implementations
- ✅ All test cases have complete source code

### Type Consistency

- ✅ `BaseType` enum used consistently in types.h/types.c
- ✅ `Type` struct fields match helper function usage
- ✅ `AST_GLOBAL_DECL` fields match codegen usage
- ✅ `AST_STRING_LIT` fields match codegen usage

---

Plan complete. Ready for execution.