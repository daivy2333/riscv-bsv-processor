#include "lexer.h"
#include "parser.h"
#include "codegen.h"
#include "linker.h"
#include "ast.h"
#include "preprocess.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILES 16

/* Compile a single source file to assembly */
static int compile_file(const char *src_file, const char *asm_file)
{
    /* Preprocess */
    char *pp_content = pp_process(src_file);
    if (!pp_content) {
        fprintf(stderr, "preprocess failed for %s\n", src_file);
        return 1;
    }

    /* Write preprocessed content to temp file for lexer */
    char tmp_pp_file[256];
    snprintf(tmp_pp_file, sizeof(tmp_pp_file), "build/_pp_%s", src_file);
    /* Create directory if needed */
    char *last_slash = strrchr(tmp_pp_file, '/');
    if (last_slash) {
        *last_slash = '\0';
        char mkdir_cmd[512];
        snprintf(mkdir_cmd, sizeof(mkdir_cmd), "mkdir -p %s 2>/dev/null || true", tmp_pp_file);
        system(mkdir_cmd);
        *last_slash = '/';
    }

    FILE *f = fopen(tmp_pp_file, "w");
    if (!f) {
        fprintf(stderr, "cannot write temp file %s\n", tmp_pp_file);
        free(pp_content);
        return 1;
    }
    fprintf(f, "%s", pp_content);
    fclose(f);
    free(pp_content);

    /* Lex */
    Token *tokens = tokenize(tmp_pp_file);
    if (!tokens) {
        fprintf(stderr, "lex failed for %s\n", src_file);
        return 1;
    }

    /* Parse */
    ASTNode *prog = parse(tokens);
    tokens_free(tokens);
    if (!prog) {
        fprintf(stderr, "parse failed for %s\n", src_file);
        return 1;
    }

    /* Codegen */
    if (codegen_gen(prog, asm_file) != 0) {
        ast_free_all(prog);
        fprintf(stderr, "codegen failed for %s\n", src_file);
        return 1;
    }
    ast_free_all(prog);

    return 0;
}

int main(int argc, char **argv)
{
    const char *crt0    = "runtime/crt0.s";
    const char *libfile = "runtime/lib.S";

    /* Single file mode (legacy): microcc src.c out.hex [crt0] [tmpasm] [lib] */
    if (argc >= 3 && strstr(argv[1], ".c") != NULL) {
        const char *infile  = argv[1];
        const char *outfile = argv[2];
        if (argc >= 4) crt0    = argv[3];
        if (argc >= 6) libfile = argv[5];

        const char *tmpasm  = (argc >= 5) ? argv[4] : "build/_user.s";

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

    /* Multi-file mode: microcc out.hex src1.c src2.c ... */
    if (argc < 3) {
        fprintf(stderr, "Usage: %s out.hex src1.c [src2.c ...]\n", argv[0]);
        fprintf(stderr, "   or: %s src.c out.hex [crt0.s] [tmp.s] [lib.S]\n", argv[0]);
        return 1;
    }

    const char *outfile = argv[1];
    const char *src_files[MAX_FILES];
    int num_files = 0;

    for (int i = 2; i < argc && num_files < MAX_FILES; i++) {
        src_files[num_files++] = argv[i];
    }

    if (num_files == 0) {
        fprintf(stderr, "no source files specified\n");
        return 1;
    }

    /* Ensure build directory exists */
    system("mkdir -p build");

    /* Compile each source file to assembly */
    const char *asm_files[MAX_FILES];
    char asm_file_paths[MAX_FILES][256];

    for (int i = 0; i < num_files; i++) {
        /* Generate assembly file path: build/_fileN.s */
        snprintf(asm_file_paths[i], sizeof(asm_file_paths[i]),
                 "build/_file%d.s", i);
        asm_files[i] = asm_file_paths[i];

        if (compile_file(src_files[i], asm_files[i]) != 0) {
            fprintf(stderr, "compilation failed for %s\n", src_files[i]);
            return 1;
        }
    }

    /* Multi-file link */
    if (linker_link_multi(asm_files, num_files, crt0, libfile, outfile) != 0) {
        fprintf(stderr, "link failed\n");
        return 1;
    }

    printf("OK: %s (%d files)\n", outfile, num_files);
    return 0;
}
