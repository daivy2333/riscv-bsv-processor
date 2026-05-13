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
 *  Pass 1 — compute stack-frame size (recursive into if/while bodies)
 * ================================================================ */

static void count_vars(ASTNode *list)
{
    for (ASTNode *s = list; s; s = s->next) {
        if (s->type == AST_VAR_DECL)
            sym_add(s->name);
        else if (s->type == AST_IF) {
            if (s->body) count_vars(s->body);
            if (s->right) count_vars(s->right);
        }
        else if (s->type == AST_WHILE && s->body)
            count_vars(s->body);
    }
}

static int count_frame(ASTNode *fn)
{
    sym_count = 0;
    /* Register parameters first (get lowest local offsets) */
    for (ASTNode *p = fn->right; p; p = p->next)
        sym_add(p->name);
    /* Then register body local variables */
    count_vars(fn->body);
    /* 4 spill(16) + locals(4*N) + arg area(32) + ra(4) */
    int frame_size = 16 + 4 * sym_count + 36;
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

    case AST_VAR_REF: {
        int off = sym_lookup(n->name);
        if (off < 0) {
            fprintf(stderr, "codegen error: undefined variable '%s'\n", n->name);
            return;
        }
        emit("    lw t0, %d(sp)\n", off);
        break;
    }

    case AST_BIN_OP: {
        gen_expr(n->left);
        int my_off = spill_depth * 4;
        spill_depth++;
        emit("    sw t0, %d(sp)\n", my_off);
        gen_expr(n->right);
        spill_depth--;
        emit("    mv t1, t0\n");
        emit("    lw t0, %d(sp)\n", my_off);

        if (n->op == TOK_PLUS)
            emit("    add t0, t0, t1\n");
        else if (n->op == TOK_MINUS)
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

    case AST_VAR_DECL:
        if (n->init) {
            gen_expr(n->init);
            int off = sym_lookup(n->name);
            emit("    sw t0, %d(sp)\n", off);
        }
        break;

    case AST_ASSIGN:
        gen_expr(n->expr);
        {
            int off = sym_lookup(n->name);
            emit("    sw t0, %d(sp)\n", off);
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
 *  Entry point — emit .text, .globl main, then each function
 * ================================================================ */

int codegen_gen(ASTNode *prog, const char *outfile)
{
    out = fopen(outfile, "w");
    if (!out) {
        fprintf(stderr, "cannot open %s for output\n", outfile);
        return 1;
    }

    emit("    .text\n");
    emit("    .globl main\n");

    for (ASTNode *fn = prog; fn; fn = fn->next) {
        if (fn->type == AST_FUNC_DEF)
            gen_func_def(fn);
    }

    fclose(out);
    return 0;
}
