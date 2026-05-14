#ifndef LEXER_H
#define LEXER_H

typedef enum {
    TOK_INT, TOK_ID, TOK_NUM, TOK_RETURN,
    TOK_LPAREN, TOK_RPAREN, TOK_LBRACE, TOK_RBRACE, TOK_SEMI,
    TOK_ASSIGN, TOK_PLUS, TOK_MINUS, TOK_STAR, TOK_SLASH,
    TOK_IF, TOK_ELSE, TOK_WHILE, TOK_FOR,
    TOK_LT, TOK_LE, TOK_GT, TOK_GE,  /* comparison operators */
    TOK_EQ, TOK_NE,                   /* equality operators */
    TOK_INC,
    TOK_COMMA,
    TOK_AND,
    TOK_CHAR,       /* NEW: char keyword */
    TOK_STRING,     /* NEW: string literal */
    TOK_LBRACKET,
    TOK_RBRACKET,
    TOK_STRUCT,     /* "struct" 关键字 */
    TOK_ARROW,       /* "->" 操作符 */
    TOK_DOT,         /* "." 成员访问操作符 */
    TOK_EOF
} TokenType;

typedef struct Token {
    TokenType type;
    char *text;
    int line, col;
    struct Token *next;
} Token;

const char *tok_name(TokenType t);
Token *tokenize(const char *filename);
void tokens_free(Token *head);

#endif