#define _GNU_SOURCE
#include "codegen.h"
#include "lexer.h"
#include "types.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static FILE *out;

static int label_counter;
static int spill_depth;

#define SPILL_BASE 0  /* spill slots start at sp+0 */

static int fresh_label(void)
{
    return label_counter++;
}

static void emit(const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    vfprintf(out, fmt, ap);
    va_end(ap);
}

/* ================================================================
 *  Symbol table — stack locals with sp-relative offsets
 * ================================================================ */

#define MAX_LOCALS 64

static struct {
    char *name;
    int   offset;
    Type  type;
} syms[MAX_LOCALS];

static int sym_count;
static int frame_used;

static int sym_lookup(const char *name)
{
    for (int i = 0; i < sym_count; i++)
        if (strcmp(syms[i].name, name) == 0)
            return syms[i].offset;
    return -1;
}

static void sym_add(const char *name)
{
    /* Don't add if already present (multiple references to same var) */
    if (sym_lookup(name) >= 0)
        return;
    syms[sym_count].name   = strdup(name);
    /* Locals start at sp + 16 (4 spill slots of 4 bytes each) */
    syms[sym_count].offset = 16 + 4 * sym_count;
    syms[sym_count].type   = type_make_int();
    sym_count++;
}

static void sym_set_type(const char *name, Type t)
{
    for (int i = 0; i < sym_count; i++)
        if (strcmp(syms[i].name, name) == 0) {
            syms[i].type = t;
            return;
        }
}

static Type sym_lookup_type(const char *name)
{
    for (int i = 0; i < sym_count; i++)
        if (strcmp(syms[i].name, name) == 0)
            return syms[i].type;
    return type_make_int();
}

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

static int global_lookup(const char *name)
{
    for (int i = 0; i < global_count; i++)
        if (strcmp(globals[i].name, name) == 0)
            return globals[i].offset;
    return -1;
}

static Type global_lookup_type(const char *name)
{
    for (int i = 0; i < global_count; i++)
        if (strcmp(globals[i].name, name) == 0)
            return globals[i].type;
    return type_make_int();
}

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

/* ================================================================
 *  Pass 1 — compute stack-frame size (recursive into if/while bodies)
 * ================================================================ */

static void count_vars(ASTNode *list)
{
    for (ASTNode *s = list; s; s = s->next) {
        if (s->type == AST_VAR_DECL) {
            sym_add(s->name);
            /* Set type including array_size or ptr_level */
            if (s->var_type.array_size > 0 || s->var_type.ptr_level > 0)
                sym_set_type(s->name, s->var_type);
        }
        else if (s->type == AST_IF) {
            if (s->body) count_vars(s->body);
            if (s->right) count_vars(s->right);
        }
        else if (s->type == AST_WHILE && s->body)
            count_vars(s->body);
    }
}

/* Calculate total bytes needed for all locals (arrays use size*4) */
static int sym_get_total_size(void)
{
    int total = 0;
    for (int i = 0; i < sym_count; i++) {
        if (syms[i].type.array_size > 0)
            total += syms[i].type.array_size * 4;
        else
            total += 4;
    }
    return total;
}

/* Recalculate offsets accounting for array sizes */
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

static int count_frame(ASTNode *fn)
{
    sym_count = 0;
    /* Register parameters first */
    for (ASTNode *p = fn->right; p; p = p->next) {
        sym_add(p->name);
        if (p->var_type.array_size > 0 || p->var_type.ptr_level > 0)
            sym_set_type(p->name, p->var_type);
    }
    /* Then register body local variables */
    count_vars(fn->body);
    /* Recalculate offsets accounting for arrays */
    sym_recalc_offsets();
    /* Calculate total local size */
    int local_size = sym_get_total_size();
    /* 4 spill(16) + locals + arg area(32) + ra(4) */
    int frame_size = 16 + local_size + 36;
    frame_size = (frame_size + 15) & ~15;
    return frame_size;
}

/* ================================================================
 *  Expression codegen — result always lands in t0
 * ================================================================ */

static void gen_expr(ASTNode *n)
{
    switch (n->type) {

    case AST_INT_LIT:
        emit("    li t0, %d\n", n->int_val);
        break;

    case AST_STRING_LIT: {
        /* Register string and get label */
        int label = register_string_literal(n->str_val);
        n->str_label = label;
        emit("    la t0, .Lstr%d\n", label);
        break;
    }

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
                emit("    addi t0, sp, %d\n", off);  /* t0 = &arr[0] */
            } else {
                emit("    lw t0, %d(sp)\n", off);  /* t0 = value */
            }
        }
        break;
    }

    case AST_ARRAY_ACCESS: {
        /* arr[i] → compute address and load */
        int base = sym_lookup(n->name);
        int is_global = 0;
        Type arr_type;

        if (base < 0) {
            /* Check if global array */
            base = global_lookup(n->name);
            if (base >= 0) {
                is_global = 1;
                arr_type = global_lookup_type(n->name);
            } else {
                fprintf(stderr, "codegen error: undefined array '%s'\n", n->name);
                return;
            }
        } else {
            arr_type = sym_lookup_type(n->name);
        }

        /* Get array base address */
        if (is_global) {
            emit("    la t1, .global_%s\n", n->name);  /* t1 = &arr[0] */
        } else if (type_is_array(arr_type)) {
            /* Local array: base address is stack offset */
            emit("    addi t1, sp, %d\n", base);  /* t1 = &arr[0] */
        } else {
            /* Pointer parameter: load pointer value first */
            emit("    lw t1, %d(sp)\n", base);  /* t1 = arr (pointer value) */
        }

        /* Evaluate index expression */
        gen_expr(n->array_index);  /* index in t0 */
        emit("    slli t0, t0, 2\n");  /* t0 = index * 4 (byte offset) */
        emit("    add t0, t1, t0\n");  /* t0 = &arr[i] */
        emit("    lw t0, 0(t0)\n");  /* t0 = arr[i] */
        break;
    }

    case AST_BIN_OP: {
        /* Check if left operand is pointer (for arithmetic) */
        int is_ptr_left = 0;
        if (n->left->type == AST_VAR_REF) {
            int global_off = global_lookup(n->left->name);
            Type left_type;
            if (global_off >= 0) {
                left_type = global_lookup_type(n->left->name);
            } else {
                left_type = sym_lookup_type(n->left->name);
            }
            is_ptr_left = type_is_array(left_type) || type_is_ptr(left_type);
        } else if (n->left->type == AST_ADDR) {
            is_ptr_left = 1;
        }

        gen_expr(n->left);
        int my_off = spill_depth * 4;
        spill_depth++;
        emit("    sw t0, %d(sp)\n", my_off);
        gen_expr(n->right);
        spill_depth--;
        emit("    mv t1, t0\n");
        emit("    lw t0, %d(sp)\n", my_off);

        if (n->op == TOK_PLUS) {
            if (is_ptr_left) {
                /* Pointer arithmetic: p + n → p + n*4 */
                emit("    slli t1, t1, 2\n");  /* t1 = n * 4 */
            }
            emit("    add t0, t0, t1\n");
        } else if (n->op == TOK_MINUS)
            emit("    sub t0, t0, t1\n");
        else if (n->op == TOK_STAR) {
            emit("    mv a0, t0\n");
            emit("    mv a1, t1\n");
            emit("    jal ra, __mulsi3\n");
            emit("    mv t0, a0\n");
        } else if (n->op == TOK_SLASH) {
            emit("    mv a0, t0\n");
            emit("    mv a1, t1\n");
            emit("    jal ra, __udivsi3\n");
            emit("    mv t0, a0\n");
        } else if (n->op == TOK_LT) {
            emit("    slt t0, t0, t1\n");
        }
        break;
    }

    case AST_FUNC_CALL: {
        int arg_idx = 0;
        /* evaluate each arg and store to outgoing arg area */
        int arg_base = frame_used - 36; /* args[0..7] below ra */
        for (ASTNode *arg = n->left; arg; arg = arg->next) {
            gen_expr(arg);
            emit("    sw t0, %d(sp)\n", arg_base + arg_idx * 4);
            arg_idx++;
        }
        /* load args into a0-a7 */
        for (int i = 0; i < arg_idx; i++)
            emit("    lw a%d, %d(sp)\n", i, arg_base + i * 4);
        /* call */
        emit("    jal ra, %s\n", n->name);
        /* result a0 → t0 */
        emit("    mv t0, a0\n");
        break;
    }

    case AST_ADDR: {
        /* &x → get address of variable x (stack offset or global) */
        if (n->left->type != AST_VAR_REF) {
            fprintf(stderr, "codegen error: & operator requires variable\n");
            return;
        }
        int global_off = global_lookup(n->left->name);
        if (global_off >= 0) {
            /* Global variable - address is label */
            emit("    la t0, .global_%s\n", n->left->name);
        } else {
            int off = sym_lookup(n->left->name);
            if (off < 0) {
                fprintf(stderr, "codegen error: undefined variable '%s'\n", n->left->name);
                return;
            }
            emit("    addi t0, sp, %d\n", off);  /* t0 = address of x */
        }
        break;
    }

    case AST_DEREF: {
        /* *p → load from address computed by p */
        gen_expr(n->left);  /* Evaluate pointer expression, result in t0 */
        emit("    lw t0, 0(t0)\n");  /* t0 = *t0 (load from address) */
        break;
    }

    default:
        break;
    }
}

/* ================================================================
 *  Statement codegen — includes full epilogue for return
 * ================================================================ */

static void gen_stmt(ASTNode *n)
{
    switch (n->type) {

    case AST_FUNC_CALL:
        /* Function call as statement - evaluate and discard result */
        gen_expr(n);
        break;

    case AST_VAR_DECL:
        if (n->init) {
            gen_expr(n->init);
            int off = sym_lookup(n->name);
            emit("    sw t0, %d(sp)\n", off);
        }
        break;

    case AST_ASSIGN:
        gen_expr(n->expr);  /* Evaluate right side, result in t0 */

        if (n->is_array_assign) {
            /* Array assignment: arr[i] = value */
            int my_off = spill_depth * 4;
            emit("    sw t0, %d(sp)\n", my_off);  /* save value */

            int base = sym_lookup(n->array_name);
            int is_global = 0;
            Type arr_type;

            if (base < 0) {
                base = global_lookup(n->array_name);
                if (base >= 0) {
                    is_global = 1;
                    arr_type = global_lookup_type(n->array_name);
                } else {
                    fprintf(stderr, "codegen error: undefined array '%s'\n", n->array_name);
                    return;
                }
            } else {
                arr_type = sym_lookup_type(n->array_name);
            }

            /* Get array base address */
            if (is_global) {
                emit("    la t1, .global_%s\n", n->array_name);
            } else if (type_is_array(arr_type)) {
                emit("    addi t1, sp, %d\n", base);  /* t1 = &arr[0] */
            } else {
                emit("    lw t1, %d(sp)\n", base);  /* t1 = arr (pointer value) */
            }

            gen_expr(n->array_index);  /* index in t0 */
            emit("    slli t0, t0, 2\n");  /* t0 = index * 4 */
            emit("    add t0, t1, t0\n");  /* t0 = &arr[i] */
            emit("    lw t1, %d(sp)\n", my_off);  /* t1 = value */
            emit("    sw t1, 0(t0)\n");  /* arr[i] = value */
        } else if (n->is_deref_assign) {
            /* Dereference assignment: *p = expr */
            int my_off = spill_depth * 4;
            emit("    sw t0, %d(sp)\n", my_off);  /* Save value */
            gen_expr(n->deref_target);  /* Evaluate pointer, get address in t0 */
            emit("    lw t1, %d(sp)\n", my_off);  /* Load saved value to t1 */
            emit("    sw t1, 0(t0)\n");  /* Store value at address */
        } else {
            /* Check if global */
            int global_off = global_lookup(n->name);
            if (global_off >= 0) {
                /* Global assignment */
                emit("    la t1, .global_%s\n", n->name);
                emit("    sw t0, 0(t1)\n");
            } else {
                /* Local variable assignment */
                int off = sym_lookup(n->name);
                if (off < 0) {
                    fprintf(stderr, "codegen error: undefined variable '%s'\n", n->name);
                    return;
                }
                emit("    sw t0, %d(sp)\n", off);
            }
        }
        break;

    case AST_RETURN:
        gen_expr(n->body);
        emit("    mv a0, t0\n");
        emit("    lw ra, %d(sp)\n", frame_used - 4);
        emit("    addi sp, sp, %d\n", frame_used);
        emit("    jalr x0, x1, 0\n");
        break;

    case AST_IF: {
        int else_lbl = fresh_label();
        int end_lbl = fresh_label();
        gen_expr(n->left);
        if (n->right) {
            emit("    beqz t0, .L%d\n", else_lbl);
            for (ASTNode *s = n->body; s; s = s->next)
                gen_stmt(s);
            emit("    j .L%d\n", end_lbl);
            emit(".L%d:\n", else_lbl);
            for (ASTNode *s = n->right; s; s = s->next)
                gen_stmt(s);
            emit(".L%d:\n", end_lbl);
        } else {
            emit("    beqz t0, .L%d\n", end_lbl);
            for (ASTNode *s = n->body; s; s = s->next)
                gen_stmt(s);
            emit(".L%d:\n", end_lbl);
        }
        break;
    }

    case AST_WHILE: {
        int loop_lbl = fresh_label();
        int end_lbl = fresh_label();
        emit(".L%d:\n", loop_lbl);
        gen_expr(n->left);
        emit("    beqz t0, .L%d\n", end_lbl);
        for (ASTNode *s = n->body; s; s = s->next)
            gen_stmt(s);
        emit("    j .L%d\n", loop_lbl);
        emit(".L%d:\n", end_lbl);
        break;
    }

    case AST_NOOP:
        break;

    default:
        break;
    }
}

/* ================================================================
 *  Function codegen — prologue + body statements
 * ================================================================ */

static void gen_func_def(ASTNode *fn)
{
    int frame = count_frame(fn);
    frame_used = frame;

    emit("%s:\n", fn->func_name);

    emit("    addi sp, sp, -%d\n", frame);
    emit("    sw ra, %d(sp)\n", frame - 4);

    /* Load parameters from a0-a7 registers into local slots */
    int param_idx = 0;
    for (ASTNode *p = fn->right; p; p = p->next) {
        int off = sym_lookup(p->name);
        emit("    sw a%d, %d(sp)\n", param_idx, off);
        param_idx++;
    }

    for (ASTNode *s = fn->body; s; s = s->next)
        gen_stmt(s);
}

/* ================================================================
 *  Entry point — emit .text first, then .data segment
 * ================================================================ */

int codegen_gen(ASTNode *prog, const char *outfile)
{
    out = fopen(outfile, "w");
    if (!out) {
        fprintf(stderr, "cannot open %s for output\n", outfile);
        return 1;
    }

    /* Pass 0: collect global declarations */
    collect_globals(prog);

    /* Emit .text segment FIRST (code at 0x80000000) */
    emit("    .text\n");
    emit("    .globl main\n");

    for (ASTNode *fn = prog; fn; fn = fn->next) {
        if (fn->type == AST_FUNC_DEF)
            gen_func_def(fn);
    }

    /* Emit .data segment AFTER .text (data at 0x80000000 + text_size) */
    emit_data_segment();

    fclose(out);
    return 0;
}