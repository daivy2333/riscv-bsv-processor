#define _GNU_SOURCE
#include "lexer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static int has_errors = 0;

const char *tok_name(TokenType t)
{
    switch (t) {
    case TOK_INT:    return "int";
    case TOK_CHAR:   return "char";      /* NEW */
    case TOK_STRING: return "string";    /* NEW */
    case TOK_STRUCT: return "struct";    /* NEW */
    case TOK_ARROW:  return "->";         /* NEW */
    case TOK_DOT:    return ".";          /* NEW */
    case TOK_ID:     return "identifier";
    case TOK_NUM:    return "number";
    case TOK_RETURN: return "return";
    case TOK_LPAREN: return "(";
    case TOK_RPAREN: return ")";
    case TOK_LBRACE: return "{";
    case TOK_RBRACE: return "}";
    case TOK_SEMI:   return ";";
    case TOK_ASSIGN: return "=";
    case TOK_PLUS:   return "+";
    case TOK_MINUS:  return "-";
    case TOK_STAR:   return "*";
    case TOK_SLASH:  return "/";
    case TOK_IF:     return "if";
    case TOK_ELSE:   return "else";
    case TOK_WHILE:  return "while";
    case TOK_FOR:    return "for";
    case TOK_LT:     return "<";
    case TOK_LE:     return "<=";
    case TOK_GT:     return ">";
    case TOK_GE:     return ">=";
    case TOK_EQ:     return "==";
    case TOK_NE:     return "!=";
    case TOK_INC:    return "++";
    case TOK_COMMA:  return ",";
    case TOK_AND:    return "&";
    case TOK_LBRACKET: return "[";
    case TOK_RBRACKET: return "]";
    case TOK_EXTERN: return "extern";    /* NEW */
    case TOK_VOLATILE: return "volatile";
    case TOK_CONST:   return "const";
    case TOK_VOID:    return "void";
    case TOK_TYPEDEF: return "typedef";    /* NEW */
    case TOK_STATIC:  return "static";     /* NEW */
    case TOK_EOF:    return "EOF";
    default:         return "?";
    }
}

void tokens_free(Token *head)
{
    while (head) {
        Token *next = head->next;
        free(head->text);
        free(head);
        head = next;
    }
}

static Token *new_token(TokenType type, const char *text, int len, int line, int col)
{
    Token *t = calloc(1, sizeof(Token));
    if (!t) return NULL;
    t->type = type;
    t->text = len > 0 ? strndup(text, len) : strdup(text ? text : "");
    t->line = line;
    t->col  = col;
    return t;
}

static void lex_error(int line, int col, const char *msg)
{
    fprintf(stderr, "lexer error at %d:%d: %s\n", line, col, msg);
    has_errors = 1;
}

static int is_ident_start(int c) { return isalpha(c) || c == '_'; }
static int is_ident_char(int c)  { return isalnum(c) || c == '_'; }

static Token *lex_keyword_or_id(const char *s, int len, int line, int col)
{
    if (len == 3 && strncmp(s, "int", 3) == 0)
        return new_token(TOK_INT, s, len, line, col);
    if (len == 4 && strncmp(s, "char", 4) == 0)
        return new_token(TOK_CHAR, s, len, line, col);  /* NEW */
    if (len == 6 && strncmp(s, "return", 6) == 0)
        return new_token(TOK_RETURN, s, len, line, col);
    if (len == 2 && strncmp(s, "if", 2) == 0)
        return new_token(TOK_IF, s, len, line, col);
    if (len == 4 && strncmp(s, "else", 4) == 0)
        return new_token(TOK_ELSE, s, len, line, col);
    if (len == 5 && strncmp(s, "while", 5) == 0)
        return new_token(TOK_WHILE, s, len, line, col);
    if (len == 3 && strncmp(s, "for", 3) == 0)
        return new_token(TOK_FOR, s, len, line, col);
    if (len == 6 && strncmp(s, "struct", 6) == 0)
        return new_token(TOK_STRUCT, s, len, line, col);
    if (len == 6 && strncmp(s, "extern", 6) == 0)
        return new_token(TOK_EXTERN, s, len, line, col);
    if (len == 8 && strncmp(s, "volatile", 8) == 0)
        return new_token(TOK_VOLATILE, s, len, line, col);
    if (len == 5 && strncmp(s, "const", 5) == 0)
        return new_token(TOK_CONST, s, len, line, col);
    if (len == 4 && strncmp(s, "void", 4) == 0)
        return new_token(TOK_VOID, s, len, line, col);
    if (len == 7 && strncmp(s, "typedef", 7) == 0)
        return new_token(TOK_TYPEDEF, s, len, line, col);
    if (len == 6 && strncmp(s, "static", 6) == 0)
        return new_token(TOK_STATIC, s, len, line, col);
    return new_token(TOK_ID, s, len, line, col);
}

/* Read entire file into a dynamically allocated string.
   Returns NULL on failure. Caller must free() the result. */
static char *slurp_file(const char *filename)
{
    FILE *f = fopen(filename, "r");
    if (!f) {
        fprintf(stderr, "cannot open %s\n", filename);
        return NULL;
    }
    fseek(f, 0, SEEK_END);
    long sz = ftell(f);
    rewind(f);
    char *buf = malloc(sz + 2);
    if (!buf) { fclose(f); return NULL; }
    size_t n = fread(buf, 1, sz, f);
    buf[n] = '\0';
    buf[n+1] = '\0';
    fclose(f);
    return buf;
}

Token *tokenize(const char *filename)
{
    char *src = slurp_file(filename);
    if (!src) return NULL;
    has_errors = 0;

    Token head_dummy = {0};
    Token *tail = &head_dummy;
    int line = 1, col = 1;
    char *p = src;

    while (*p) {
        int c = *p;

        /* whitespace */
        if (c == ' ' || c == '\t' || c == '\r') { p++; col++; continue; }
        if (c == '\n') { p++; line++; col = 1; continue; }

        /* line comment: // or # */
        if ((c == '/' && p[1] == '/') || c == '#') {
            while (*p && *p != '\n') p++;
            continue;
        }
        if (c == '/' && p[1] == '*') {
            p += 2; col += 2;
            while (*p && !(*p == '*' && p[1] == '/')) {
                if (*p == '\n') { line++; col = 1; }
                else col++;
                p++;
            }
            if (*p) { p += 2; col += 2; }
            continue;
        }

        /* string literals: "..." with escape handling */
        if (c == '"') {
            int start_col = col;
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

        /* numbers */
        if (isdigit(c)) {
            char *start = p; int start_col = col;
            while (isdigit(*p)) { p++; col++; }
            tail->next = new_token(TOK_NUM, start, (int)(p - start), line, start_col);
            tail = tail->next;
            continue;
        }

        /* identifiers / keywords */
        if (is_ident_start(c)) {
            char *start = p; int start_col = col;
            while (is_ident_char(*p)) { p++; col++; }
            tail->next = lex_keyword_or_id(start, (int)(p - start), line, start_col);
            tail = tail->next;
            continue;
        }

        /* single-char tokens */
        TokenType t;
        switch (c) {
        case '(': t = TOK_LPAREN; break;
        case ')': t = TOK_RPAREN; break;
        case '{': t = TOK_LBRACE; break;
        case '}': t = TOK_RBRACE; break;
        case ';': t = TOK_SEMI;   break;
        case '+':
            if (p[1] == '+') { t = TOK_INC; p++; col++; }
            else { t = TOK_PLUS; }
            break;
        case '-':
            if (p[1] == '>') { t = TOK_ARROW; p++; col++; }
            else { t = TOK_MINUS; }
            break;
        case '*': t = TOK_STAR;  break;
        case '/': t = TOK_SLASH; break;
        case '<':
            if (p[1] == '=') { t = TOK_LE; p++; col++; }
            else { t = TOK_LT; }
            break;
        case '>':
            if (p[1] == '=') { t = TOK_GE; p++; col++; }
            else { t = TOK_GT; }
            break;
        case '=':
            if (p[1] == '=') { t = TOK_EQ; p++; col++; }
            else { t = TOK_ASSIGN; }
            break;
        case '!':
            if (p[1] == '=') { t = TOK_NE; p++; col++; }
            else {
                lex_error(line, col, "unexpected character");
                p++; col++;
                continue;
            }
            break;
        case '&': t = TOK_AND; break;
        case '[': t = TOK_LBRACKET; break;
        case ']': t = TOK_RBRACKET; break;
        case ',': t = TOK_COMMA; break;
        case '.': t = TOK_DOT; break;
        default:
            lex_error(line, col, "unexpected character");
            p++; col++;
            continue;
        }
        tail->next = new_token(t, NULL, 0, line, col);
        tail = tail->next;
        p++; col++;
    }

    tail->next = new_token(TOK_EOF, "", 0, line, col);
    free(src);
    return has_errors ? NULL : head_dummy.next;
}