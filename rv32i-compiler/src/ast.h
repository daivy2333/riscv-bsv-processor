#ifndef AST_H
#define AST_H

#include "types.h"

/* AST node types */
typedef enum {
    AST_GLOBAL_DECL,   /* NEW: global variable declaration */
    AST_FUNC_DEF,
    AST_FUNC_DECL,     /* NEW: function prototype declaration */
    AST_RETURN,
    AST_INT_LIT,
    AST_STRING_LIT,    /* NEW: string literal expression */
    AST_BIN_OP,
    AST_VAR_DECL,
    AST_VAR_REF,
    AST_ASSIGN,
    AST_IF,           /* .left=cond expr, .body=then-body stmt, .right=else-body stmt (NULL if no else) */
    AST_WHILE,        /* .left=cond expr, .body=loop body stmt */
    AST_NOOP,         /* empty statement placeholder */
    AST_FUNC_CALL,    /* .name=func name, .left=args chain via .next */
    AST_ADDR,         /* address-of operator (&x) */
    AST_DEREF,        /* dereference operator (*p) */
    AST_ARRAY_ACCESS, /* array subscript arr[i] */
    AST_STRUCT_DEF,   /* struct definition statement */
    AST_MEMBER_ACCESS /* member access expression p->member or n.member */
} ASTNodeType;

/* Generic AST node */
typedef struct ASTNode {
    ASTNodeType type;
    /* type-specific data */
    char *func_name;       /* for FUNC_DEF */
    struct ASTNode *body;  /* for FUNC_DEF: statement list */
    int int_val;           /* for INT_LIT */
    int op;                /* for BIN_OP: TokenType (PLUS/MINUS/STAR/SLASH) */
    struct ASTNode *left;  /* for BIN_OP: left operand */
    struct ASTNode *right; /* for BIN_OP: right operand / FUNC_DEF: params */
    char *name;            /* for VAR_DECL, VAR_REF, ASSIGN, GLOBAL_DECL: variable name */
    Type  var_type;        /* for VAR_DECL, GLOBAL_DECL: variable type (int, int*, etc.) */
    int   is_deref_assign; /* for ASSIGN: 1 if assigning to *p */
    int   is_array_assign;   /* for ASSIGN: 1 if assigning to arr[i] */
    char  *array_name;       /* for ASSIGN/ARRAY_ACCESS: array variable name */
    struct ASTNode *array_index; /* for ASSIGN/ARRAY_ACCESS: subscript expression */
    struct ASTNode *deref_target; /* for ASSIGN: pointer expr for *p = */
    struct ASTNode *init;  /* for VAR_DECL, GLOBAL_DECL: optional initializer (NULL if none) */
    struct ASTNode *expr;  /* for ASSIGN: right-hand side expression */
    /* NEW: global declaration fields */
    int   is_global;       /* for GLOBAL_DECL: marker (1) */
    /* NEW: string literal fields */
    char *str_val;         /* for STRING_LIT: string content / GLOBAL_DECL: string initializer */
    int   str_label;       /* for STRING_LIT: assigned label index */
    /* for AST_STRUCT_DEF */
    char *struct_name;     /* struct name */
    struct ASTNode *members; /* member chain (each member is AST_VAR_DECL) */
    int struct_id;         /* registered struct ID */
    /* for AST_MEMBER_ACCESS */
    struct ASTNode *target_expr; /* target expression (p or n) */
    char *member_name;     /* member name */
    int is_arrow;          /* 1=p->member, 0=n.member */
    struct ASTNode *next;  /* linked-list chain for statements */
} ASTNode;

/* Allocate a new AST node, zero-initialised */
ASTNode *ast_new(ASTNodeType type);

/* Free a linked list of AST nodes */
void ast_free_all(ASTNode *head);

#endif /* AST_H */