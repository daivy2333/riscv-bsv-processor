#define _GNU_SOURCE
#include "preprocess.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 读取文件内容 */
static char *read_file_content(const char *filename) {
    FILE *f = fopen(filename, "r");
    if (!f) {
        fprintf(stderr, "preprocessor: cannot open '%s'\n", filename);
        return NULL;
    }

    fseek(f, 0, SEEK_END);
    long sz = ftell(f);
    rewind(f);

    char *buf = malloc(sz + 2);
    if (!buf) {
        fclose(f);
        return NULL;
    }

    size_t n = fread(buf, 1, sz, f);
    buf[n] = '\0';
    fclose(f);

    return buf;
}

/* 预处理入口：目前只是读取文件返回 */
char *pp_process(const char *filename) {
    char *content = read_file_content(filename);
    if (!content) {
        return NULL;
    }
    /* 暂时直接返回原文，后续添加预处理逻辑 */
    return content;
}