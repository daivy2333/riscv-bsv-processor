#define _GNU_SOURCE
#include "preprocess.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <libgen.h>

#define MAX_INCLUDE_DEPTH 32
#define MAX_INCLUDED_FILES 32
#define MAX_LINE_LEN 1024
#define MAX_FILE_SIZE 65536

/* 已包含文件列表 */
static char *included_files[MAX_INCLUDED_FILES];
static int included_count = 0;

/* 检查文件是否已包含 */
static int is_already_included(const char *filepath) {
    for (int i = 0; i < included_count; i++) {
        if (strcmp(included_files[i], filepath) == 0) {
            return 1;
        }
    }
    return 0;
}

/* 添加到已包含列表 */
static void add_included_file(const char *filepath) {
    if (included_count < MAX_INCLUDED_FILES) {
        included_files[included_count++] = strdup(filepath);
    }
}

/* 清空已包含列表 */
static void clear_included_files(void) {
    for (int i = 0; i < included_count; i++) {
        free(included_files[i]);
    }
    included_count = 0;
}

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

    if (sz > MAX_FILE_SIZE) {
        fprintf(stderr, "preprocessor: file too large '%s'\n", filename);
        fclose(f);
        return NULL;
    }

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

/* 递归处理单个文件 */
static char *process_file(const char *filename, int depth) {
    if (depth > MAX_INCLUDE_DEPTH) {
        fprintf(stderr, "preprocessor: include depth exceeded (> %d)\n", MAX_INCLUDE_DEPTH);
        return NULL;
    }

    if (is_already_included(filename)) {
        return strdup("");  /* 循环包含检测 - 返回空内容 */
    }

    char *content = read_file_content(filename);
    if (!content) return NULL;

    add_included_file(filename);

    char *output = malloc(MAX_FILE_SIZE * 4);
    if (!output) {
        free(content);
        return NULL;
    }
    output[0] = '\0';

    char *line = content;
    char *next_line;
    while (line && *line) {
        next_line = strchr(line, '\n');
        char linebuf[MAX_LINE_LEN];
        if (next_line) {
            size_t linelen = next_line - line;
            if (linelen >= MAX_LINE_LEN) linelen = MAX_LINE_LEN - 1;
            memcpy(linebuf, line, linelen);
            linebuf[linelen] = '\0';
            line = next_line + 1;
        } else {
            strncpy(linebuf, line, MAX_LINE_LEN - 1);
            linebuf[MAX_LINE_LEN - 1] = '\0';
            line = NULL;
        }

        /* 处理 #include 指令 */
        if (strncmp(linebuf, "#include", 8) == 0) {
            char *p = linebuf + 8;
            while (*p && isspace(*p)) p++;

            if (*p == '"') {
                p++;
                char *end = strchr(p, '"');
                if (!end) {
                    fprintf(stderr, "preprocessor: malformed #include in '%s'\n", filename);
                    free(content);
                    free(output);
                    return NULL;
                }

                char include_name[256];
                size_t namelen = end - p;
                if (namelen >= 256) namelen = 255;
                memcpy(include_name, p, namelen);
                include_name[namelen] = '\0';

                char fullpath[512];
                char *tmp = strdup(filename);
                char *dir = dirname(tmp);
                snprintf(fullpath, sizeof(fullpath), "%s/%s", dir, include_name);
                free(tmp);

                char *included_content = process_file(fullpath, depth + 1);
                if (!included_content) {
                    fprintf(stderr, "preprocessor: cannot process included file '%s'\n", fullpath);
                    free(content);
                    free(output);
                    return NULL;
                }

                strcat(output, included_content);
                free(included_content);
            } else {
                fprintf(stderr, "preprocessor: #include <file> not supported\n");
                free(content);
                free(output);
                return NULL;
            }
        } else {
            strcat(output, linebuf);
            strcat(output, "\n");
        }
    }

    free(content);
    return output;
}

/* 预处理入口 */
char *pp_process(const char *filename) {
    clear_included_files();
    return process_file(filename, 0);
}