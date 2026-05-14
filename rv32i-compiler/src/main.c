#include "lexer.h"
#include "parser.h"
#include "codegen.h"
#include "linker.h"
#include "ast.h"
#include "preprocess.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    const char *infile  = "tests/test.c";
    const char *outfile = "build/test.hex";
    const char *crt0    = "runtime/crt0.s";
    const char *tmpasm  = "build/_user.s";
    const char *libfile = "runtime/lib.S";

    if (argc >= 2) infile  = argv[1];
    if (argc >= 3) outfile = argv[2];
    if (argc >= 4) crt0    = argv[3];
    if (argc >= 5) tmpasm  = argv[4];
    if (argc >= 6) libfile = argv[5];

    /* 0. Preprocess */
    char *pp_content = pp_process(infile);
    if (!pp_content) {
        fprintf(stderr, "preprocess failed\n");
        return 1;
    }

    /* Write preprocessed content to temp file for lexer */
    const char *tmp_pp_file = "build/_preprocessed.c";
    FILE *f = fopen(tmp_pp_file, "w");
    if (!f) {
        fprintf(stderr, "cannot write temp file\n");
        free(pp_content);
        return 1;
    }
    fprintf(f, "%s", pp_content);
    fclose(f);
    free(pp_content);

    /* 1. Lex */
    Token *tokens = tokenize(tmp_pp_file);
    if (!tokens) { fprintf(stderr, "lex failed\n"); return 1; }

    /* 2. Parse */
    ASTNode *prog = parse(tokens);
    tokens_free(tokens);
    if (!prog) { fprintf(stderr, "parse failed\n"); return 1; }

    /* 3. Codegen → assembly text */
    if (codegen_gen(prog, tmpasm) != 0) {
        ast_free_all(prog);
        fprintf(stderr, "codegen failed\n");
        return 1;
    }
    ast_free_all(prog);

    /* 4. Link (concatenate + assemble + emit hex) */
    if (linker_link(tmpasm, crt0, libfile, outfile) != 0) {
        fprintf(stderr, "link failed\n");
        return 1;
    }

    printf("OK: %s\n", outfile);
    return 0;
}
