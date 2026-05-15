#define _GNU_SOURCE
#include "parser.h"
#include "types.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static Token *cur;
static int has_errors;

#define MAX_STRUCTS 32
#define MAX_TYPEDEF_ALIASES 32

static StructInfo parser_struct_table[MAX_STRUCTS];
static int parser_struct_count;

/* typedef 别名表：Alias -> struct_id */
typedef struct {
    char *alias_name;   /* 别名名称 */
    int struct_id;      /* 对应的 struct 索引 */
} TypedefAlias;

static TypedefAlias typedef_aliases[MAX_TYPEDEF_ALIASES];
static int typedef_alias_count;

/* 在 Parser 中查找结构体定义 */
static int lookup_struct(const char *name)
{
    for (int i = 0; i < parser_struct_count; i++)
        if (strcmp(parser_struct_table[i].name, name) == 0)
            return i;
    return -1;
}

/* 在 Parser 中注册结构体（简化版） */
static int register_struct_parser(const char *name, int member_count)
{
    parser_struct_table[parser_struct_count].name = strdup(name);
    parser_struct_table[parser_struct_count].member_count = member_count;
    parser_struct_table[parser_struct_count].total_size = 0;  /* Codegen 计算实际大小 */
    parser_struct_table[parser_struct_count].members = NULL;  /* Codegen 从 AST 获取 */
    return parser_struct_count++;
}

/* 查找 typedef 别名 */
static int lookup_typedef_alias(const char *alias)
{
    for (int i = 0; i < typedef_alias_count; i++)
        if (strcmp(typedef_aliases[i].alias_name, alias) == 0)
            return typedef_aliases[i].struct_id;
    return -1;
}

/* 注册 typedef 别名 */
static void register_typedef_alias(const char *alias, int struct_id)
{
    typedef_aliases[typedef_alias_count].alias_name = strdup(alias);
    typedef_aliases[typedef_alias_count].struct_id = struct_id;
    typedef_alias_count++;
}

/* Forward declarations for parse_typedef */
static void parse_error(int line, int col, const char *msg);
static int expect(TokenType t);

/* typedef 解析：typedef struct Name Alias; */
static ASTNode *parse_typedef(void)
{
    cur = cur->next;  /* skip "typedef" */

    /* Expect "struct" */
    if (cur->type != TOK_STRUCT) {
        parse_error(cur->line, cur->col, "expected 'struct' after 'typedef'");
        return NULL;
    }
    cur = cur->next;  /* skip "struct" */

    /* Expect struct name */
    if (cur->type != TOK_ID) {
        parse_error(cur->line, cur->col, "expected struct name");
        return NULL;
    }
    char *struct_name = strdup(cur->text);
    int struct_id = lookup_struct(struct_name);
    if (struct_id < 0) {
        parse_error(cur->line, cur->col, "undefined struct type");
        free(struct_name);
        return NULL;
    }
    cur = cur->next;  /* skip struct name */

    /* Expect alias name */
    if (cur->type != TOK_ID) {
        parse_error(cur->line, cur->col, "expected alias name");
        free(struct_name);
        return NULL;
    }
    char *alias_name = strdup(cur->text);
    cur = cur->next;  /* skip alias name */

    /* Register the alias */
    register_typedef_alias(alias_name, struct_id);

    /* Expect ';' */
    expect(TOK_SEMI);

    /* Return a typedef node (for AST tracking, though no codegen needed) */
    ASTNode *n = ast_new(AST_TYPEDEF_DEF);
    n->struct_name = struct_name;
    n->name = alias_name;
    return n;
}

static ASTNode *parse_term(void);
static ASTNode *parse_addsub(void);
static ASTNode *parse_expr(void);
static ASTNode *parse_stmt(void);
static ASTNode *parse_compound(void);
static ASTNode *parse_if_stmt(void);
static ASTNode *parse_while_stmt(void);
static ASTNode *parse_for_stmt(void);
static ASTNode *parse_member_access(ASTNode *target);
static ASTNode *parse_extern_decl(void);
static Type parse_type(void);  /* NEW: type parsing helper */

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

/* primary = integer-literal | string-literal | identifier | "&" primary | "*" primary | "(" expression ")" */
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
    if (cur->type == TOK_STRING) {
        ASTNode *n = ast_new(AST_STRING_LIT);
        n->str_val = strdup(cur->text);
        n->str_label = -1;  /* assigned later by codegen */
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
        /* 成员访问: p->member 或 n.member */
        if (cur->type == TOK_ARROW || cur->type == TOK_DOT) {
            ASTNode *ref = ast_new(AST_VAR_REF);
            ref->name = name;
            return parse_member_access(ref);
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

/* expression = addsub { ("<" | "<=" | ">" | ">=" | "==" | "!=") addsub } */
static ASTNode *parse_expr(void)
{
    ASTNode *left = parse_addsub();
    if (!left) return NULL;

    while (cur->type == TOK_LT || cur->type == TOK_LE ||
           cur->type == TOK_GT || cur->type == TOK_GE ||
           cur->type == TOK_EQ || cur->type == TOK_NE) {
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
    if (cur->type != TOK_SEMI) {
        n->body = parse_expr();
    } else {
        n->body = NULL;  /* empty return for void functions */
    }
    expect(TOK_SEMI);
    return n;
}

/* parse_type = parse type qualifiers (volatile/const) + base type + pointer level
 * Returns Type with is_const/is_volatile set */
static Type parse_type(void)
{
    Type t = type_make_int();
    int is_const = 0;
    int is_volatile = 0;

    /* Parse type qualifiers (volatile/const can appear multiple times) */
    while (cur->type == TOK_VOLATILE || cur->type == TOK_CONST) {
        if (cur->type == TOK_VOLATILE) {
            is_volatile = 1;
            cur = cur->next;
        } else if (cur->type == TOK_CONST) {
            is_const = 1;
            cur = cur->next;
        }
    }

    /* Parse base type */
    if (cur->type == TOK_INT) {
        t = type_make_int();
        cur = cur->next;
    } else if (cur->type == TOK_CHAR) {
        t = type_make_char();
        cur = cur->next;
    } else if (cur->type == TOK_VOID) {
        t = type_make_void();
        cur = cur->next;
    } else if (cur->type == TOK_STRUCT) {
        cur = cur->next; /* skip "struct" */
        if (cur->type != TOK_ID) {
            parse_error(cur->line, cur->col, "expected struct name");
            return t;
        }
        int struct_id = lookup_struct(cur->text);
        if (struct_id < 0) {
            parse_error(cur->line, cur->col, "undefined struct");
            return t;
        }
        t = type_make_struct_val(struct_id);
        cur = cur->next;
    } else if (cur->type == TOK_ID) {
        /* Check if it's a typedef alias */
        int struct_id = lookup_typedef_alias(cur->text);
        if (struct_id >= 0) {
            t = type_make_struct_val(struct_id);
            cur = cur->next;
        } else {
            parse_error(cur->line, cur->col, "unknown type name");
            return t;
        }
    }

    /* Set type qualifiers */
    t.is_const = is_const;
    t.is_volatile = is_volatile;

    /* Parse pointer level */
    while (cur->type == TOK_STAR) {
        t.ptr_level++;
        cur = cur->next;
    }

    return t;
}

/* var-decl = type-qualifiers ("int" | "char" | "struct Name") ["*"] identifier ["[" number "]"] ["=" expr] ";"
 *           Uses parse_type for type parsing */
static ASTNode *parse_var_decl(void)
{
    /* Use parse_type to handle volatile/const + base type + pointer */
    Type var_type = parse_type();

    if (cur->type != TOK_ID) {
        parse_error(cur->line, cur->col, "expected identifier");
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
        if (var_type.base_type == TYPE_INT)
            var_type = type_make_array(size);
        else if (var_type.base_type == TYPE_CHAR)
            var_type = type_make_char_array(size);
        cur = cur->next; /* skip size */
        if (cur->type != TOK_RBRACKET) {
            parse_error(cur->line, cur->col, "expected ']' after array size");
            return NULL;
        }
        cur = cur->next; /* skip ']' */
    }
    n->var_type = var_type;

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

/* 成员声明: int name 或 struct Name* name
 * current_struct_name: 当前正在定义的 struct 名称（用于支持自引用） */
static ASTNode *parse_member_decl(const char *current_struct_name)
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
        /* 支持自引用：如果找不到，但名字与当前定义的 struct 相同，则先注册 */
        if (struct_id < 0 && current_struct_name && strcmp(struct_name, current_struct_name) == 0) {
            /* 前向声明：先注册一个空 struct，稍后填充成员 */
            struct_id = register_struct_parser(struct_name, 0);
        }
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

    /* 解析成员列表，传递当前 struct 名称以支持自引用 */
    ASTNode *members = NULL, *tail = NULL;
    int member_count = 0;

    while (cur->type != TOK_RBRACE) {
        ASTNode *member = parse_member_decl(name);
        if (!member) break;
        member_count++;
        if (!members) members = tail = member;
        else { tail->next = member; tail = member; }
    }

    expect(TOK_RBRACE);
    expect(TOK_SEMI);

    /* 注册结构体 */
    int struct_id = lookup_struct(name);
    if (struct_id < 0) {
        /* 如果之前没有注册（无自引用），现在注册 */
        struct_id = register_struct_parser(name, member_count);
    } else {
        /* 已注册（自引用情况），更新成员数 */
        parser_struct_table[struct_id].member_count = member_count;
    }

    ASTNode *n = ast_new(AST_STRUCT_DEF);
    n->struct_name = name;
    n->members = members;
    n->struct_id = struct_id;
    return n;
}

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
    n->init = NULL;  /* 初始化 */
    cur = cur->next;

    /* 支持初始化: struct Name* p = expr; */
    if (cur->type == TOK_ASSIGN) {
        cur = cur->next;  /* skip '=' */
        n->init = parse_expr();
    }

    expect(TOK_SEMI);

    return n;
}

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

/* assign-stmt = identifier "[" expr "]" "=" expr ";" OR identifier "=" expr ";" OR "*" primary "=" expr ";" OR member-access "=" expr ";" */
static ASTNode *parse_assign(void)
{
    ASTNode *n = ast_new(AST_ASSIGN);
    n->is_deref_assign = 0;
    n->is_array_assign = 0;
    n->target_expr = NULL;  /* for member assignment: p->member = value or n.member = value */

    /* Member assignment: p->member = value or n.member = value */
    if (cur->type == TOK_ID && cur->next &&
        (cur->next->type == TOK_ARROW || cur->next->type == TOK_DOT)) {
        /* Parse variable reference */
        ASTNode *ref = ast_new(AST_VAR_REF);
        ref->name = strdup(cur->text);
        cur = cur->next;  /* skip identifier, now cur is -> or . */

        /* Parse member access */
        n->target_expr = parse_member_access(ref);

        /* Expect '=' */
        if (cur->type != TOK_ASSIGN) {
            parse_error(cur->line, cur->col, "expected '=' after member access");
            return NULL;
        }
        cur = cur->next;  /* skip '=' */

        /* Parse assignment expression */
        n->expr = parse_expr();
        n->name = NULL;  /* no simple variable name for member assignment */

        if (cur->type != TOK_SEMI) {
            parse_error(cur->line, cur->col, "expected ';' after assignment");
        } else {
            cur = cur->next;
        }
        return n;
    }

    /* Check for dereference assignment: *p = expr */
    if (cur->type == TOK_STAR) {
        n->is_deref_assign = 1;
        cur = cur->next; /* skip '*' */
        n->deref_target = parse_primary();
        n->name = NULL;

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

    /* Check for array assignment: arr[i] = expr */
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
    /* Variable declaration: int/char/volatile/const + type */
    if (cur->type == TOK_INT || cur->type == TOK_CHAR ||
        cur->type == TOK_VOLATILE || cur->type == TOK_CONST)
        return parse_var_decl();
    if (cur->type == TOK_STRUCT)
        return parse_struct_decl(0);  /* is_global=0, 局部变量 */
    /* typedef alias variable declaration: Alias *p; */
    if (cur->type == TOK_ID && lookup_typedef_alias(cur->text) >= 0)
        return parse_var_decl();  /* parse_var_decl uses parse_type which handles typedef */
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
        /* Array assignment: arr[i] = val */
        if (next && next->type == TOK_LBRACKET)
            return parse_assign();
        /* Member assignment: p->member = val or n.member = val */
        if (next && (next->type == TOK_ARROW || next->type == TOK_DOT))
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
    /* Use parse_type for return type (handles volatile/const + int/char/void/struct + pointers) */
    Type ret_type = parse_type();

    ASTNode *n = ast_new(AST_FUNC_DEF);
    n->var_type = ret_type;  /* store return type */
    n->func_name = strdup(cur->text);
    cur = cur->next; /* skip identifier */
    expect(TOK_LPAREN);

    /* Handle void parameter declaration: func(void) */
    if (cur->type == TOK_VOID && cur->next->type == TOK_RPAREN) {
        cur = cur->next; /* skip void */
        n->right = NULL; /* no parameters */
    } else if (cur->type != TOK_RPAREN) {
        /* Parse parameter list: (int name, int name, ...) OR (char *name, ...) OR (struct Name *name) */
        ASTNode *params = NULL, *tail = NULL;
        do {
            if (cur->type == TOK_COMMA)
                cur = cur->next;

            /* Use parse_type for parameter type */
            Type param_type = parse_type();

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
        n->right = params; /* params chain stored in .right */
    }
    expect(TOK_RPAREN);
    expect(TOK_LBRACE);
    n->body = parse_compound();
    expect(TOK_RBRACE);
    return n;
}

/* func-decl = "int" identifier "(" [param-list] ")" ";"  (function prototype) */
static ASTNode *parse_func_decl(void)
{
    /* Use parse_type for return type (handles volatile/const + int/char/void/struct + pointers) */
    Type ret_type = parse_type();

    ASTNode *n = ast_new(AST_FUNC_DECL);
    n->func_name = strdup(cur->text);
    n->var_type = ret_type;  /* store return type */
    cur = cur->next; /* skip identifier */
    expect(TOK_LPAREN);

    /* Handle void parameter declaration: func(void) */
    if (cur->type == TOK_VOID && cur->next->type == TOK_RPAREN) {
        cur = cur->next; /* skip void */
        n->right = NULL; /* no parameters */
    } else if (cur->type != TOK_RPAREN) {
        /* Parse parameter list using parse_type */
        ASTNode *params = NULL, *tail = NULL;
        do {
            if (cur->type == TOK_COMMA)
                cur = cur->next;

            Type param_type = parse_type();

            /* Parameter name (optional in prototypes, but we require it for simplicity) */
            if (cur->type == TOK_ID) {
                ASTNode *p = ast_new(AST_VAR_DECL);
                p->name = strdup(cur->text);
                p->var_type = param_type;
                cur = cur->next;
                if (!params) params = tail = p;
                else { tail->next = p; tail = p; }
            } else {
                /* Anonymous parameter - still track the type */
                ASTNode *p = ast_new(AST_VAR_DECL);
                p->name = strdup("_anon");
                p->var_type = param_type;
                if (!params) params = tail = p;
                else { tail->next = p; tail = p; }
            }
        } while (cur->type == TOK_COMMA);
        n->right = params; /* params chain stored in .right */
    }
    expect(TOK_RPAREN);
    expect(TOK_SEMI);
    return n;
}

/* global-decl = ("int" | "char") ["*"] identifier ["[" num "]"] ["=" (expr | string-lit)] ";" */
static ASTNode *parse_global_decl(void)
{
    /* Use parse_type to handle volatile/const + base type + pointer */
    Type var_type = parse_type();

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

/* extern-decl = "extern" ("int" | "char" | "struct" Name) ["*"] identifier ["[" num "]"] ";"
 * Extern declarations register symbol for codegen reference */
static ASTNode *parse_extern_decl(void)
{
    cur = cur->next; /* skip "extern" */

    /* Parse type specifier */
    Type var_type;
    if (cur->type == TOK_INT) {
        var_type = type_make_int();
        cur = cur->next; /* skip "int" */
    } else if (cur->type == TOK_CHAR) {
        var_type = type_make_char();
        cur = cur->next; /* skip "char" */
    } else if (cur->type == TOK_STRUCT) {
        cur = cur->next; /* skip "struct" */
        if (cur->type != TOK_ID) {
            parse_error(cur->line, cur->col, "expected struct name after 'extern struct'");
            return NULL;
        }
        int struct_id = lookup_struct(cur->text);
        if (struct_id < 0) {
            parse_error(cur->line, cur->col, "undefined struct");
            return NULL;
        }
        var_type = type_make_struct_ptr(struct_id);
        cur = cur->next; /* skip struct name */
        /* struct pointer must have '*' */
        if (cur->type == TOK_STAR) {
            cur = cur->next; /* skip '*' */
        }
    } else {
        parse_error(cur->line, cur->col, "expected type after 'extern'");
        return NULL;
    }

    /* Parse pointer marker */
    if (cur->type == TOK_STAR) {
        if (var_type.base_type == TYPE_INT)
            var_type = type_make_int_ptr();
        else if (var_type.base_type == TYPE_CHAR)
            var_type = type_make_char_ptr();
        cur = cur->next; /* skip '*' */
    }

    /* Parse identifier */
    if (cur->type != TOK_ID) {
        parse_error(cur->line, cur->col, "expected identifier after 'extern'");
        return NULL;
    }

    ASTNode *n = ast_new(AST_EXTERN_DECL);
    n->name = strdup(cur->text);
    n->var_type = var_type;
    cur = cur->next; /* skip identifier */

    /* Skip array size if present */
    if (cur->type == TOK_LBRACKET) {
        cur = cur->next; /* skip '[' */
        if (cur->type == TOK_NUM) {
            var_type.array_size = atoi(cur->text);
            cur = cur->next; /* skip size */
        }
        if (cur->type == TOK_RBRACKET) {
            cur = cur->next; /* skip ']' */
        }
    }

    /* Expect semicolon */
    if (cur->type != TOK_SEMI) {
        parse_error(cur->line, cur->col, "expected ';' after extern declaration");
        return NULL;
    }
    cur = cur->next; /* skip ';' */

    return n;
}

/* program = (struct-def | struct-decl | global-decl | func-def)* */
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
        /* static 声明 */
        else if (cur->type == TOK_STATIC) {
            cur = cur->next;  /* skip "static" */
            /* Now parse the declaration as usual */
            if (cur->type == TOK_INT || cur->type == TOK_CHAR || cur->type == TOK_VOID ||
                cur->type == TOK_VOLATILE || cur->type == TOK_CONST ||
                (cur->type == TOK_ID && lookup_typedef_alias(cur->text) >= 0)) {
                /* Look ahead to distinguish global decl from func def */
                Token *next = cur->next;
                int is_func = 0;
                int is_proto = 0;
                int is_static = 1;  /* mark as static */

                /* Skip type qualifiers (volatile/const) */
                while (next && (next->type == TOK_VOLATILE || next->type == TOK_CONST)) {
                    next = next->next;
                }

                /* Skip base type */
                if (next && (next->type == TOK_INT || next->type == TOK_CHAR || next->type == TOK_VOID)) {
                    next = next->next;
                } else if (next && next->type == TOK_STRUCT) {
                    next = next->next;
                    if (next && next->type == TOK_ID) {
                        next = next->next;
                    }
                } else if (next && next->type == TOK_ID && lookup_typedef_alias(next->text) >= 0) {
                    next = next->next;
                }

                /* Skip pointer marker */
                if (next && next->type == TOK_STAR)
                    next = next->next;

                /* Check if function */
                if (next && next->type == TOK_ID && next->next && next->next->type == TOK_LPAREN) {
                    is_func = 1;
                    Token *scan = next->next->next;
                    while (scan && scan->type != TOK_RPAREN) {
                        scan = scan->next;
                    }
                    if (scan) {
                        scan = scan->next;
                        if (scan && scan->type == TOK_SEMI) {
                            is_proto = 1;
                        }
                    }
                }

                if (is_func) {
                    if (is_proto) {
                        node = parse_func_decl();
                    } else {
                        node = parse_func_def();
                        if (node) node->is_static = is_static;
                    }
                } else {
                    node = parse_global_decl();
                    if (node) node->is_static = is_static;
                }
            }
        }
        /* 函数定义或 int/char/void/volatile/const/typedef-alias 全局声明 */
        else if (cur->type == TOK_INT || cur->type == TOK_CHAR || cur->type == TOK_VOID ||
                 cur->type == TOK_VOLATILE || cur->type == TOK_CONST ||
                 (cur->type == TOK_ID && lookup_typedef_alias(cur->text) >= 0)) {
            /* Look ahead to distinguish global decl from func def/decl */
            Token *start = cur;  /* remember start position */
            Token *next = cur->next;
            int is_func = 0;
            int is_proto = 0;

            /* Skip type qualifiers (volatile/const) */
            while (next && (next->type == TOK_VOLATILE || next->type == TOK_CONST)) {
                next = next->next;
            }

            /* Skip base type (int/char/void/struct/typedef-alias) */
            if (next && (next->type == TOK_INT || next->type == TOK_CHAR || next->type == TOK_VOID)) {
                next = next->next;
            } else if (next && next->type == TOK_STRUCT) {
                /* Skip struct Name */
                next = next->next;  /* skip "struct" */
                if (next && next->type == TOK_ID) {
                    next = next->next;  /* skip struct name */
                }
            } else if (next && next->type == TOK_ID && lookup_typedef_alias(next->text) >= 0) {
                /* typedef alias: skip the alias name */
                next = next->next;
            }

            /* Skip pointer marker if present */
            if (next && next->type == TOK_STAR)
                next = next->next;

            /* If next is identifier followed by '(' → function definition or prototype */
            if (next && next->type == TOK_ID && next->next && next->next->type == TOK_LPAREN) {
                is_func = 1;
                /* Look further ahead to find '{' or ';' after parameters */
                Token *scan = next->next->next; /* skip '(' */
                /* Scan through parameters to find closing ')' */
                while (scan && scan->type != TOK_RPAREN) {
                    scan = scan->next;
                }
                if (scan) {
                    scan = scan->next; /* skip ')' */
                    if (scan && scan->type == TOK_SEMI) {
                        is_proto = 1;  /* function prototype */
                    }
                }
            }

            if (is_func) {
                if (is_proto) {
                    node = parse_func_decl();
                } else {
                    node = parse_func_def();
                }
            } else {
                node = parse_global_decl();
            }
        }
        /* typedef declaration */
        else if (cur->type == TOK_TYPEDEF) {
            node = parse_typedef();
        }
        /* extern declaration */
        else if (cur->type == TOK_EXTERN) {
            node = parse_extern_decl();
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

ASTNode *parse(Token *tokens)
{
    cur = tokens;
    has_errors = 0;
    parser_struct_count = 0;
    typedef_alias_count = 0;
    ASTNode *prog = parse_program();
    if (has_errors) {
        ast_free_all(prog);
        return NULL;
    }
    return prog;
}