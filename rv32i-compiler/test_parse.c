#include <stdio.h>
#include "lexer.h"
#include "parser.h"
#include "ast.h"

int main() {
    Token *t = tokenize("build/_pp_tests/phase9/full_test.c");
    if (!t) { printf("tokenize failed\n"); return 1; }
    ASTNode *prog = parse(t);
    if (!prog) { printf("parse failed\n"); return 1; }
    printf("parse succeeded!\n");
    while (prog) {
        printf("node type=%d\n", prog->type);
        prog = prog->next;
    }
    return 0;
}
