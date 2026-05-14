#define _GNU_SOURCE
#include "linker.h"
#include "asm.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *read_file(const char *filename)
{
    if (!filename) return strdup("");
    FILE *f = fopen(filename, "r");
    if (!f) return strdup("");
    fseek(f, 0, SEEK_END);
    long sz = ftell(f);
    rewind(f);
    char *buf = malloc(sz + 2);
    if (!buf) { fclose(f); return NULL; }
    size_t n = fread(buf, 1, sz, f);
    buf[n] = '\0';
    fclose(f);
    return buf;
}

int linker_link(const char *user_asm_file, const char *crt0_asm_file,
                const char *lib_asm_file, const char *out_hex)
{
    // Read all files
    char *crt0_text = read_file(crt0_asm_file);
    char *lib_text  = read_file(lib_asm_file);
    char *user_text = read_file(user_asm_file);

    if (!crt0_text || !user_text) {
        free(crt0_text); free(lib_text); free(user_text);
        fprintf(stderr, "linker: cannot read input files\n");
        return 1;
    }

    // Concatenate: crt0 + lib + user (with newlines between)
    size_t total_len = strlen(crt0_text) + strlen(lib_text) + strlen(user_text) + 8;
    char *combined = malloc(total_len);
    if (!combined) {
        free(crt0_text); free(lib_text); free(user_text);
        return 1;
    }
    combined[0] = '\0';
    strcat(combined, crt0_text);
    strcat(combined, "\n");
    strcat(combined, lib_text);
    strcat(combined, "\n");
    strcat(combined, user_text);

    free(crt0_text);
    free(lib_text);
    free(user_text);

    // Assemble everything together (two-pass resolves all labels)
    uint32_t *words = NULL;
    size_t count = 0;
    if (asm_assemble(combined, &words, &count) != 0) {
        free(combined);
        fprintf(stderr, "linker: assembly failed\n");
        return 1;
    }
    free(combined);

    // Write hex output
    FILE *h = fopen(out_hex, "w");
    if (!h) {
        asm_free_words(words);
        fprintf(stderr, "linker: cannot write %s\n", out_hex);
        return 1;
    }

    size_t i;
    for (i = 0; i < count; i++) {
        uint32_t addr = 0x80000000 + (uint32_t)(i * 4);
        fprintf(h, "@%08X\n%02X %02X %02X %02X\n",
                addr,
                words[i] & 0xFF,
                (words[i] >> 8) & 0xFF,
                (words[i] >> 16) & 0xFF,
                (words[i] >> 24) & 0xFF);
    }

    fclose(h);
    asm_free_words(words);

    printf("Linked: %zu words → %s\n", count, out_hex);
    return 0;
}

int linker_link_multi(const char *asm_files[], int num_files,
                      const char *crt0_asm_file,
                      const char *lib_asm_file, const char *out_hex)
{
    /* Read crt0 and lib */
    char *crt0_text = read_file(crt0_asm_file);
    char *lib_text  = read_file(lib_asm_file);

    if (!crt0_text) {
        free(crt0_text); free(lib_text);
        fprintf(stderr, "linker: cannot read crt0\n");
        return 1;
    }

    /* Calculate total length for all asm files */
    size_t total_len = strlen(crt0_text) + strlen(lib_text) + 8;
    for (int i = 0; i < num_files; i++) {
        char *asm_text = read_file(asm_files[i]);
        if (!asm_text) {
            free(crt0_text); free(lib_text);
            fprintf(stderr, "linker: cannot read %s\n", asm_files[i]);
            return 1;
        }
        total_len += strlen(asm_text) + 2;
        free(asm_text);
    }

    /* Allocate combined buffer */
    char *combined = malloc(total_len);
    if (!combined) {
        free(crt0_text); free(lib_text);
        return 1;
    }
    combined[0] = '\0';

    /* Concatenate: crt0 + lib + all user asm files */
    strcat(combined, crt0_text);
    strcat(combined, "\n");
    strcat(combined, lib_text);
    strcat(combined, "\n");

    for (int i = 0; i < num_files; i++) {
        char *asm_text = read_file(asm_files[i]);
        strcat(combined, asm_text);
        strcat(combined, "\n");
        free(asm_text);
    }

    free(crt0_text);
    free(lib_text);

    /* Assemble everything together (two-pass resolves all labels) */
    uint32_t *words = NULL;
    size_t count = 0;
    if (asm_assemble(combined, &words, &count) != 0) {
        free(combined);
        fprintf(stderr, "linker: assembly failed\n");
        return 1;
    }
    free(combined);

    /* Write hex output */
    FILE *h = fopen(out_hex, "w");
    if (!h) {
        asm_free_words(words);
        fprintf(stderr, "linker: cannot write %s\n", out_hex);
        return 1;
    }

    size_t i;
    for (i = 0; i < count; i++) {
        uint32_t addr = 0x80000000 + (uint32_t)(i * 4);
        fprintf(h, "@%08X\n%02X %02X %02X %02X\n",
                addr,
                words[i] & 0xFF,
                (words[i] >> 8) & 0xFF,
                (words[i] >> 16) & 0xFF,
                (words[i] >> 24) & 0xFF);
    }

    fclose(h);
    asm_free_words(words);

    printf("Linked: %zu words → %s\n", count, out_hex);
    return 0;
}
