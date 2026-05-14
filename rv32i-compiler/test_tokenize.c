#include <stdio.h>
#include "lexer.h"

int main() {
    Token *t = tokenize("build/_pp_tests/phase9/full_test.c");
    while (t && t->type != TOK_EOF) {
        printf("%d:%d tok=%d (%s) text='%s'\n", t->line, t->col, t->type, tok_name(t->type), t->text ? t->text : "");
        t = t->next;
    }
    return 0;
}
