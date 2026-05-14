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
#define MAX_MACROS 64
#define MAX_MACRO_NAME_LEN 128
#define MAX_MACRO_VALUE_LEN 256
#define MAX_COND_DEPTH 16

/* 宏定义结构 */
typedef struct {
    char name[MAX_MACRO_NAME_LEN];
    char value[MAX_MACRO_VALUE_LEN];
} Macro;

/* 条件编译栈结构 */
typedef struct {
    int orig_cond_was_true;  /* 原始 #ifdef/#ifndef 条件值 */
    int cond_was_true;       /* 当前条件值（#elif 可能修改） */
    int in_else;             /* 是否在 #else 分支 */
    int else_seen;           /* 是否已遇到 #else（防止重复 #else） */
    int elif_seen;           /* 是否已遇到 #elif */
} CondStack;

/* 宏定义表 */
static Macro macro_table[MAX_MACROS];
static int macro_count = 0;

/* 条件编译栈 */
static CondStack cond_stack[MAX_COND_DEPTH];
static int cond_depth = 0;

/* 已包含文件列表 */
static char *included_files[MAX_INCLUDED_FILES];
static int included_count = 0;

/* 添加宏定义 */
static void add_macro(const char *name, const char *value) {
    if (macro_count >= MAX_MACROS) {
        fprintf(stderr, "preprocessor: too many macros (max %d)\n", MAX_MACROS);
        return;
    }

    /* 检查是否已定义，如果是则覆盖 */
    for (int i = 0; i < macro_count; i++) {
        if (strcmp(macro_table[i].name, name) == 0) {
            strncpy(macro_table[i].value, value, MAX_MACRO_VALUE_LEN - 1);
            macro_table[i].value[MAX_MACRO_VALUE_LEN - 1] = '\0';
            return;
        }
    }

    /* 添加新宏 */
    strncpy(macro_table[macro_count].name, name, MAX_MACRO_NAME_LEN - 1);
    macro_table[macro_count].name[MAX_MACRO_NAME_LEN - 1] = '\0';
    strncpy(macro_table[macro_count].value, value, MAX_MACRO_VALUE_LEN - 1);
    macro_table[macro_count].value[MAX_MACRO_VALUE_LEN - 1] = '\0';
    macro_count++;
}

/* 查找宏定义 */
static Macro *find_macro(const char *name) {
    for (int i = 0; i < macro_count; i++) {
        if (strcmp(macro_table[i].name, name) == 0) {
            return &macro_table[i];
        }
    }
    return NULL;
}

/* 清空宏表 */
static void clear_macros(void) {
    macro_count = 0;
}

/* 清空条件编译栈 */
static void clear_cond_stack(void) {
    cond_depth = 0;
}

/* 检查当前代码是否应该输出 */
static int is_active(void) {
    for (int i = 0; i < cond_depth; i++) {
        if (cond_stack[i].in_else) {
            /* 在 else/elif 分支中，原始条件为假且当前条件也为假时激活 */
            /* 对于 #else: orig_cond_was_true = false 时激活 */
            /* 对于 #elif: cond_was_true = true 时跳过（简化实现） */
            if (cond_stack[i].orig_cond_was_true || cond_stack[i].cond_was_true) return 0;
        } else {
            /* 在 if 分支中，当前条件为真时激活 */
            if (!cond_stack[i].cond_was_true) return 0;
        }
    }
    return 1;
}

/* 处理 #ifdef 指令 */
static void handle_ifdef(const char *name) {
    if (cond_depth >= MAX_COND_DEPTH) {
        fprintf(stderr, "preprocessor: conditional nesting too deep (max %d)\n", MAX_COND_DEPTH);
        return;
    }

    int defined = (find_macro(name) != NULL);
    cond_stack[cond_depth].orig_cond_was_true = defined;
    cond_stack[cond_depth].cond_was_true = defined;
    cond_stack[cond_depth].in_else = 0;
    cond_stack[cond_depth].else_seen = 0;
    cond_stack[cond_depth].elif_seen = 0;
    cond_depth++;
}

/* 处理 #ifndef 指令 */
static void handle_ifndef(const char *name) {
    if (cond_depth >= MAX_COND_DEPTH) {
        fprintf(stderr, "preprocessor: conditional nesting too deep (max %d)\n", MAX_COND_DEPTH);
        return;
    }

    int defined = (find_macro(name) != NULL);
    cond_stack[cond_depth].orig_cond_was_true = !defined;  /* #ifndef 条件为真是"未定义" */
    cond_stack[cond_depth].cond_was_true = !defined;
    cond_stack[cond_depth].in_else = 0;
    cond_stack[cond_depth].else_seen = 0;
    cond_stack[cond_depth].elif_seen = 0;
    cond_depth++;
}

/* 处理 #else 指令 */
static int handle_else(const char *filename) {
    if (cond_depth == 0) {
        fprintf(stderr, "preprocessor: #else without matching #ifdef/#ifndef in '%s'\n", filename);
        return 0;
    }

    if (cond_stack[cond_depth - 1].else_seen) {
        fprintf(stderr, "preprocessor: duplicate #else in '%s'\n", filename);
        return 0;
    }

    cond_stack[cond_depth - 1].in_else = 1;
    cond_stack[cond_depth - 1].else_seen = 1;
    /* 恢复 cond_was_true 为原始值，让 #else 分支根据原条件判断 */
    cond_stack[cond_depth - 1].cond_was_true = cond_stack[cond_depth - 1].orig_cond_was_true;

    return 1;
}

/* 处理 #elif 指令 (简化实现: 不支持表达式求值，总是跳过) */
static int handle_elif(const char *filename) {
    if (cond_depth == 0) {
        fprintf(stderr, "preprocessor: #elif without matching #ifdef/#ifndef in '%s'\n", filename);
        return 0;
    }

    if (cond_stack[cond_depth - 1].else_seen) {
        fprintf(stderr, "preprocessor: #elif after #else in '%s'\n", filename);
        return 0;
    }

    /* 标记已遇到 #elif */
    cond_stack[cond_depth - 1].elif_seen = 1;

    /* 简化实现: #elif 分支总是跳过（不支持表达式求值） */
    /* 设置 in_else = true 和 cond_was_true = true 使 is_active() 跳过 */
    cond_stack[cond_depth - 1].in_else = 1;
    cond_stack[cond_depth - 1].cond_was_true = 1;

    return 1;
}

/* 处理 #endif 指令 */
static int handle_endif(const char *filename) {
    if (cond_depth == 0) {
        fprintf(stderr, "preprocessor: #endif without matching #ifdef/#ifndef in '%s'\n", filename);
        return 0;
    }

    cond_depth--;
    return 1;
}

/* 检查字符是否为标识符字符 */
static int is_identifier_char(char c) {
    return isalnum(c) || c == '_';
}

/* 宏展开：替换行中的宏名称（完整标识符匹配） */
static void expand_macros(char *line) {
    char result[MAX_LINE_LEN * 2];
    result[0] = '\0';

    int i = 0;
    int result_pos = 0;

    while (line[i]) {
        /* 跳过空白 */
        if (!is_identifier_char(line[i])) {
            result[result_pos++] = line[i++];
            continue;
        }

        /* 提取标识符 */
        int ident_start = i;
        while (is_identifier_char(line[i])) {
            i++;
        }

        char identifier[MAX_MACRO_NAME_LEN];
        int ident_len = i - ident_start;
        if (ident_len >= MAX_MACRO_NAME_LEN) {
            ident_len = MAX_MACRO_NAME_LEN - 1;
        }
        strncpy(identifier, line + ident_start, ident_len);
        identifier[ident_len] = '\0';

        /* 查找是否为宏 */
        Macro *macro = find_macro(identifier);
        if (macro) {
            /* 替换为宏值 */
            int value_len = strlen(macro->value);
            if (result_pos + value_len >= MAX_LINE_LEN * 2 - 1) {
                /* 防止溢出 */
                break;
            }
            strcpy(result + result_pos, macro->value);
            result_pos += value_len;
        } else {
            /* 保留原标识符 */
            if (result_pos + ident_len >= MAX_LINE_LEN * 2 - 1) {
                break;
            }
            strncpy(result + result_pos, identifier, ident_len);
            result_pos += ident_len;
        }
    }

    result[result_pos] = '\0';
    strcpy(line, result);
}

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

        /* 跳过行首空白，用于识别指令 */
        char *stripped = linebuf;
        while (*stripped && isspace(*stripped)) stripped++;

        /* 处理 #ifdef 指令（总是处理，不受 is_active() 影响） */
        if (strncmp(stripped, "#ifdef", 6) == 0 && (stripped[6] == ' ' || stripped[6] == '\t' || stripped[6] == '\0')) {
            char *p = stripped + 6;
            while (*p && isspace(*p)) p++;

            /* 提取宏名 */
            char name[MAX_MACRO_NAME_LEN];
            int name_len = 0;
            while (*p && is_identifier_char(*p) && name_len < MAX_MACRO_NAME_LEN - 1) {
                name[name_len++] = *p++;
            }
            name[name_len] = '\0';

            if (name_len == 0) {
                fprintf(stderr, "preprocessor: empty macro name in #ifdef in '%s'\n", filename);
                free(content);
                free(output);
                return NULL;
            }

            handle_ifdef(name);
            continue;
        }

        /* 处理 #ifndef 指令（总是处理，不受 is_active() 影响） */
        if (strncmp(stripped, "#ifndef", 7) == 0 && (stripped[7] == ' ' || stripped[7] == '\t' || stripped[7] == '\0')) {
            char *p = stripped + 7;
            while (*p && isspace(*p)) p++;

            /* 提取宏名 */
            char name[MAX_MACRO_NAME_LEN];
            int name_len = 0;
            while (*p && is_identifier_char(*p) && name_len < MAX_MACRO_NAME_LEN - 1) {
                name[name_len++] = *p++;
            }
            name[name_len] = '\0';

            if (name_len == 0) {
                fprintf(stderr, "preprocessor: empty macro name in #ifndef in '%s'\n", filename);
                free(content);
                free(output);
                return NULL;
            }

            handle_ifndef(name);
            continue;
        }

        /* 处理 #else 指令（总是处理，不受 is_active() 影响） */
        if (strncmp(stripped, "#else", 5) == 0 && (stripped[5] == ' ' || stripped[5] == '\t' || stripped[5] == '\0' || stripped[5] == '\n')) {
            if (!handle_else(filename)) {
                free(content);
                free(output);
                return NULL;
            }
            continue;
        }

        /* 处理 #elif 指令（总是处理，不受 is_active() 影响） */
        if (strncmp(stripped, "#elif", 5) == 0 && (stripped[5] == ' ' || stripped[5] == '\t')) {
            if (!handle_elif(filename)) {
                free(content);
                free(output);
                return NULL;
            }
            continue;
        }

        /* 处理 #endif 指令（总是处理，不受 is_active() 影响） */
        if (strncmp(stripped, "#endif", 6) == 0 && (stripped[6] == ' ' || stripped[6] == '\t' || stripped[6] == '\0' || stripped[6] == '\n')) {
            if (!handle_endif(filename)) {
                free(content);
                free(output);
                return NULL;
            }
            continue;
        }

        /* 非条件编译指令：检查是否在活动块中 */
        if (!is_active()) {
            continue;  /* 跳过非活动块中的所有内容 */
        }

        /* 处理 #define 指令 */
        if (strncmp(stripped, "#define", 7) == 0) {
            char *p = stripped + 7;
            while (*p && isspace(*p)) p++;

            /* 提取宏名 */
            char name[MAX_MACRO_NAME_LEN];
            int name_len = 0;
            while (*p && is_identifier_char(*p) && name_len < MAX_MACRO_NAME_LEN - 1) {
                name[name_len++] = *p++;
            }
            name[name_len] = '\0';

            if (name_len == 0) {
                fprintf(stderr, "preprocessor: empty macro name in '%s'\n", filename);
                continue;
            }

            /* 跳过空格 */
            while (*p && isspace(*p)) p++;

            /* 提取宏值（剩余内容） */
            char value[MAX_MACRO_VALUE_LEN];
            if (*p) {
                strncpy(value, p, MAX_MACRO_VALUE_LEN - 1);
                value[MAX_MACRO_VALUE_LEN - 1] = '\0';
                /* 去除尾部空白 */
                int val_len = strlen(value);
                while (val_len > 0 && isspace(value[val_len - 1])) {
                    value[--val_len] = '\0';
                }
            } else {
                value[0] = '\0';
            }

            add_macro(name, value);
            continue;  /* #define 行不输出 */
        }

        /* 处理 #include 指令 */
        if (strncmp(stripped, "#include", 8) == 0) {
            char *p = stripped + 8;
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
            /* 非指令行：进行宏展开后输出 */
            expand_macros(linebuf);
            strcat(output, linebuf);
            strcat(output, "\n");
        }
    }

    /* 检查未匹配的条件编译指令 */
    if (cond_depth > 0) {
        fprintf(stderr, "preprocessor: unmatched #ifdef/#ifndef in '%s'\n", filename);
        free(content);
        free(output);
        return NULL;
    }

    free(content);
    return output;
}

/* 预处理入口 */
char *pp_process(const char *filename) {
    clear_included_files();
    clear_macros();
    clear_cond_stack();
    return process_file(filename, 0);
}