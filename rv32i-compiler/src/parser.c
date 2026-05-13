#define _GNU_SOURCE
#include "parser.h"
#include "types.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static Token *cur;
static int has_errors;

static ASTNode *parse_term(void);
static ASTNode *parse_addsub(void);
static ASTNode *parse_expr(void);
static ASTNode *parse_stmt(void);
static ASTNode *parse_compound(void);
static ASTNode *parse_if_stmt(void);
static ASTNode *parse_while_stmt(void);
static ASTNode *parse_for_stmt(void);

static void parse_error(int line, int col, const char *msg)
{
    fprintf(stderr, "parse error at %d:%d: %s\n", line, col, msg);
    has_errors = 1;
}

static int expect(TokenType t)
{
    if (cur->type != t) {
        parse_error(cur->line, cur->col, "expected token");
        return 0;
    }
    cur = cur->next;
    return 1;
}

/* primary = integer-literal | identifier | "&" primary | "*" primary | "(" expression ")" */
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
        ASTNode *n = ast_new(AST_INT_LIT);
        n->int_val = atoi(cur->text);
        cur = cur->next;
        return n;
    }
    if (cur->type == TOK_ID) {
        char *name = strdup(cur->text);
        cur = cur->next;
        if (cur->type == TOK_LPAREN) {
            /* Function call: name(arg, arg, ...) */
            cur = cur->next; /* skip '(' */
            ASTNode *args = NULL, *tail = NULL;
            if (cur->type != TOK_RPAREN) {
                do {
                    if (cur->type == TOK_COMMA)
                        cur = cur->next;
                    ASTNode *arg = parse_expr();
                    if (!args) args = tail = arg;
                    else { tail->next = arg; tail = arg; }
                } while (cur->type == TOK_COMMA);
            }
            expect(TOK_RPAREN);
            ASTNode *call = ast_new(AST_FUNC_CALL);
            call->name = name;
            call->left = args;
            return call;
        }
        /* Variable reference */
        ASTNode *n = ast_new(AST_VAR_REF);
        n->name = name;
        return n;
    }
    if (cur->type == TOK_LPAREN) {
        cur = cur->next;
        ASTNode *n = parse_expr();
        if (cur->type != TOK_RPAREN) {
            parse_error(cur->line, cur->col, "expected ')'");
        } else {
            cur = cur->next;
        }
        return n;
    }
    parse_error(cur->line, cur->col, "expected expression");
    return NULL;
}

/* term = primary { ("*" | "/") primary } */
static ASTNode *parse_term(void)
{
    ASTNode *left = parse_primary();
    if (!left) return NULL;

    while (cur->type == TOK_STAR || cur->type == TOK_SLASH) {
        TokenType op = cur->type;
        cur = cur->next;
        ASTNode *right = parse_primary();
        if (!right) return NULL;

        ASTNode *bin = ast_new(AST_BIN_OP);
        bin->op = (int)op;
        bin->left = left;
        bin->right = right;
        left = bin;
    }
    return left;
}

/* addsub = term { ("+" | "-") term } */
static ASTNode *parse_addsub(void)
{
    ASTNode *left = parse_term();
    if (!left) return NULL;

    while (cur->type == TOK_PLUS || cur->type == TOK_MINUS) {
        TokenType op = cur->type;
        cur = cur->next;
        ASTNode *right = parse_term();
        if (!right) return NULL;

        ASTNode *bin = ast_new(AST_BIN_OP);
        bin->op = (int)op;
        bin->left = left;
        bin->right = right;
        left = bin;
    }
    return left;
}

/* expression = addsub { "<" addsub } */
static ASTNode *parse_expr(void)
{
    ASTNode *left = parse_addsub();
    if (!left) return NULL;

    while (cur->type == TOK_LT) {
        TokenType op = cur->type;
        cur = cur->next;
        ASTNode *right = parse_addsub();
        if (!right) return NULL;

        ASTNode *bin = ast_new(AST_BIN_OP);
        bin->op = (int)op;
        bin->left = left;
        bin->right = right;
        left = bin;
    }
    return left;
}

/* return-stmt = "return" expression ";" */
static ASTNode *parse_return(void)
{
    cur = cur->next; /* skip "return" */
    ASTNode *n = ast_new(AST_RETURN);
    n->body = parse_expr();
    expect(TOK_SEMI);
    return n;
}

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
    n->var_type = var_type;
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

/* assign-stmt = identifier "=" expression ";" OR "*" primary "=" expression ";" */
static ASTNode *parse_assign(void)
{
    ASTNode *n = ast_new(AST_ASSIGN);
    n->is_deref_assign = 0;  /* default: normal assignment */

    /* Check for dereference assignment: *p = expr */
    if (cur->type == TOK_STAR) {
        n->is_deref_assign = 1;
        cur = cur->next; /* skip '*' */
        n->deref_target = parse_primary();  /* Get pointer expression */
        n->name = NULL;  /* no name for deref assignment */

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

/* if-stmt = "if" "(" expression ")" statement ["else" statement] */
static ASTNode *parse_if_stmt(void)
{
    cur = cur->next; /* skip "if" */
    if (cur->type != TOK_LPAREN) {
        parse_error(cur->line, cur->col, "expected '(' after 'if'");
        return NULL;
    }
    cur = cur->next; /* skip '(' */
    ASTNode *cond = parse_expr();
    if (!cond) return NULL;
    if (cur->type != TOK_RPAREN) {
        parse_error(cur->line, cur->col, "expected ')' after condition");
        return NULL;
    }
    cur = cur->next; /* skip ')' */
    ASTNode *then_body = parse_stmt();

    ASTNode *n = ast_new(AST_IF);
    n->left = cond;     /* condition */
    n->body = then_body; /* then-body (may be NULL for empty compound) */

    if (cur->type == TOK_ELSE) {
        cur = cur->next; /* skip "else" */
        n->right = parse_stmt(); /* else-body */
    }
    return n;
}

/* while-stmt = "while" "(" expression ")" statement */
static ASTNode *parse_while_stmt(void)
{
    cur = cur->next; /* skip "while" */
    if (cur->type != TOK_LPAREN) {
        parse_error(cur->line, cur->col, "expected '(' after 'while'");
        return NULL;
    }
    cur = cur->next; /* skip '(' */
    ASTNode *cond = parse_expr();
    if (!cond) return NULL;
    if (cur->type != TOK_RPAREN) {
        parse_error(cur->line, cur->col, "expected ')' after condition");
        return NULL;
    }
    cur = cur->next; /* skip ')' */
    ASTNode *body = parse_stmt();

    ASTNode *n = ast_new(AST_WHILE);
    n->left = cond;   /* condition */
    n->body = body;   /* loop body (may be NULL for empty compound) */
    return n;
}

/* for-stmt = "for" "(" [init] ";" [cond] ";" [inc] ")" statement
 * Desugared to: { init; while(cond) { body; inc; } } */
static ASTNode *parse_for_stmt(void)
{
    cur = cur->next; /* skip "for" */
    if (cur->type != TOK_LPAREN) {
        parse_error(cur->line, cur->col, "expected '(' after 'for'");
        return NULL;
    }
    cur = cur->next; /* skip '(' */

    /* Parse init clause — expression statement (e.g., i=0) */
    ASTNode *init_stmt = NULL;
    if (cur->type != TOK_SEMI) {
        init_stmt = parse_stmt();
        /* parse_stmt (via parse_assign/parse_var_decl) already consumed the trailing ';' */
    } else {
        cur = cur->next; /* skip ';' (empty init clause) */
    }

    /* Parse condition clause (e.g., i<3) */
    ASTNode *cond = NULL;
    if (cur->type != TOK_SEMI) {
        cond = parse_expr();
    }
    if (!cond) {
        parse_error(cur->line, cur->col, "for loop requires a condition");
        return NULL;
    }

    if (cur->type != TOK_SEMI) {
        parse_error(cur->line, cur->col, "expected ';' in for loop");
        return NULL;
    }
    cur = cur->next; /* skip ';' */

    /* Parse increment clause (e.g., i++) */
    ASTNode *inc_stmt = NULL;
    if (cur->type != TOK_RPAREN) {
        if (cur->type == TOK_ID && cur->next && cur->next->type == TOK_INC) {
            /* Handle i++ directly — desugar to i = i + 1 (no ';' after) */
            char *inc_name = strdup(cur->text);
            cur = cur->next; /* skip identifier */
            cur = cur->next; /* skip '++' */
            ASTNode *ref = ast_new(AST_VAR_REF);
            ref->name = inc_name;
            ASTNode *one = ast_new(AST_INT_LIT);
            one->int_val = 1;
            ASTNode *add = ast_new(AST_BIN_OP);
            add->op = (int)TOK_PLUS;
            add->left = ref;
            add->right = one;
            ASTNode *asgn = ast_new(AST_ASSIGN);
            asgn->name = strdup(inc_name);
            asgn->expr = add;
            inc_stmt = asgn;
        } else {
            inc_stmt = parse_stmt();
        }
    }

    if (cur->type != TOK_RPAREN) {
        parse_error(cur->line, cur->col, "expected ')' after for clauses");
        return NULL;
    }
    cur = cur->next; /* skip ')' */

    /* Parse body statement */
    ASTNode *body_stmt = parse_stmt();

    /* Build the desugared AST:
     * for(init; cond; inc) body
     *   →
     * { init; while(cond) { body; inc; } }
     */
    ASTNode *while_node = ast_new(AST_WHILE);
    while_node->left = cond;  /* condition */

    /* Build while body chain: body → inc */
    if (body_stmt && inc_stmt) {
        ASTNode *tail = body_stmt;
        while (tail->next) tail = tail->next;
        tail->next = inc_stmt;
        while_node->body = body_stmt;
    } else if (body_stmt) {
        while_node->body = body_stmt;
    } else if (inc_stmt) {
        while_node->body = inc_stmt;
    }

    /* Build the result: init → while chain */
    if (init_stmt) {
        ASTNode *tail = init_stmt;
        while (tail->next) tail = tail->next;
        tail->next = while_node;
        return init_stmt;
    }
    return while_node;
}

/* statement = ";" | "{" ... "}" | if-stmt | while-stmt | for-stmt | return-stmt | var-decl | assign-stmt */
static ASTNode *parse_stmt(void)
{
    if (cur->type == TOK_SEMI) {
        cur = cur->next;
        return ast_new(AST_NOOP);
    }
    if (cur->type == TOK_LBRACE) {
        cur = cur->next; /* skip '{' — parse_compound expects it already consumed */
        ASTNode *body = parse_compound();
        expect(TOK_RBRACE);
        return body ? body : ast_new(AST_NOOP); /* empty compound → NOOP */
    }
    if (cur->type == TOK_IF)
        return parse_if_stmt();
    if (cur->type == TOK_WHILE)
        return parse_while_stmt();
    if (cur->type == TOK_FOR)
        return parse_for_stmt();
    if (cur->type == TOK_RETURN)
        return parse_return();
    if (cur->type == TOK_INT)
        return parse_var_decl();
    /* Dereference assignment: *p = expr */
    if (cur->type == TOK_STAR)
        return parse_assign();
    if (cur->type == TOK_ID && cur->next && cur->next->type == TOK_INC) {
        /* desugar i++ → i = i + 1 */
        char *name = strdup(cur->text);
        cur = cur->next;      /* skip identifier */
        cur = cur->next;      /* skip '++' */
        if (cur->type != TOK_SEMI) {
            parse_error(cur->line, cur->col, "expected ';' after expression");
            free(name);
            return NULL;
        }
        cur = cur->next;      /* skip ';' */
        ASTNode *ref = ast_new(AST_VAR_REF);
        ref->name = name;
        ASTNode *one = ast_new(AST_INT_LIT);
        one->int_val = 1;
        ASTNode *add = ast_new(AST_BIN_OP);
        add->op = (int)TOK_PLUS;
        add->left = ref;
        add->right = one;
        ASTNode *asgn = ast_new(AST_ASSIGN);
        asgn->name = strdup(name);
        asgn->expr = add;
        return asgn;
    }
    if (cur->type == TOK_ID) {
        Token *next = cur->next;
        if (next && next->type == TOK_ASSIGN)
            return parse_assign();
        /* Function call statement: func(args); */
        if (next && next->type == TOK_LPAREN) {
            /* Parse function call expression, then expect ';' */
            ASTNode *call = parse_primary();  /* parse_primary handles function call */
            if (cur->type != TOK_SEMI) {
                parse_error(cur->line, cur->col, "expected ';' after function call");
            } else {
                cur = cur->next;  /* skip ';' */
            }
            return call;
        }
        parse_error(cur->line, cur->col, "expected statement");
        return NULL;
    }
    parse_error(cur->line, cur->col, "expected statement");
    return NULL;
}

/* compound-stmt = "{" statement* "}" */
static ASTNode *parse_compound(void)
{
    ASTNode dummy = {0};
    ASTNode *tail = &dummy;

    while (cur->type != TOK_RBRACE && cur->type != TOK_EOF) {
        ASTNode *s = parse_stmt();
        if (!s) break;
        tail->next = s;
        /* walk to end of chain in case s itself is multi-node (for-loop desugaring) */
        while (tail->next) tail = tail->next;
    }
    return dummy.next;
}

/* func-def = "int" identifier "(" [param-list] ")" compound-stmt */
static ASTNode *parse_func_def(void)
{
    expect(TOK_INT);
    ASTNode *n = ast_new(AST_FUNC_DEF);
    n->func_name = strdup(cur->text);
    cur = cur->next; /* skip identifier */
    expect(TOK_LPAREN);
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
            p->var_type = param_type;
            cur = cur->next; /* skip identifier */
            if (!params) params = tail = p;
            else { tail->next = p; tail = p; }
        } while (cur->type == TOK_COMMA);
    }
    expect(TOK_RPAREN);
    n->right = params; /* params chain stored in .right */
    expect(TOK_LBRACE);
    n->body = parse_compound();
    expect(TOK_RBRACE);
    return n;
}

/* program = func-def* */
static ASTNode *parse_program(void)
{
    ASTNode dummy = {0};
    ASTNode *tail = &dummy;

    while (cur->type != TOK_EOF) {
        ASTNode *f = parse_func_def();
        if (!f) break;
        tail->next = f;
        tail = f;
    }
    return dummy.next;
}

ASTNode *parse(Token *tokens)
{
    cur = tokens;
    has_errors = 0;
    ASTNode *prog = parse_program();
    if (has_errors) {
        ast_free_all(prog);
        return NULL;
    }
    return prog;
}
