# 阶段 9 设计文档：多文件编译与预处理器

> 创建日期：2026-05-14

## 一、需求概述

### 核心目标

实现多文件编译和预处理器支持，使编译器能够：
1. 编译多个 `.c` 源文件，链接成一个可执行文件
2. 支持 `#include`、`#define`、`#ifdef/#ifndef/#endif`、`#else/#elif` 预处理指令
3. 支持头文件声明和 `extern` 关键字

### 设计方案

**方案 A：预处理器优先 + 简化链接**

流程：预处理(#include展开) → 多文件编译 → 汇编拼接 → hex

---

## 二、架构设计

### 编译流程（新）

```
输入：多个 .c 文件 + 头文件
    ↓ Preprocessor（新增）
预处理后的文本（#include展开、宏替换、条件编译过滤）
    ↓ Lexer
Token 流
    ↓ Parser
AST
    ↓ Codegen
汇编文本（多个 .s 文件）
    ↓ Linker（升级）
拼接所有 .s → asm_assemble → hex
    ↓ 输出
单一 hex 文件
```

### 新增模块

| 模块 | 文件 | 职责 |
|------|------|------|
| Preprocessor | `src/preprocessor.c/h` | 预处理指令解析、文件展开、宏替换 |

### 修改模块

| 模块 | 改动 |
|------|------|
| `main.c` | 支持多文件输入，调用预处理器 |
| `lexer.c` | 新增 `extern` 关键字 |
| `parser.c` | 支持 `extern` 声明语句 |
| `codegen.c` | 处理 extern 引用（生成引用而非定义） |
| `linker.c` | 支持多汇编文件拼接 |

---

## 三、预处理器设计

### 支持的指令

| 指令 | 功能 | 示例 |
|------|------|------|
| `#include "file"` | 文件包含 | `#include "header.h"` |
| `#define NAME VAL` | 常量宏 | `#define MAX 100` |
| `#ifdef NAME` | 条件编译 | `#ifdef DEBUG` |
| `#ifndef NAME` | 条件编译（否定） | `#ifndef RELEASE` |
| `#else` | 条件分支 | `#else` |
| `#elif` | 多条件分支 | `#elif TEST` |
| `#endif` | 条件结束 | `#endif` |

### 不支持的指令（延后）

- `#include <file>`（系统头文件）
- `#define MACRO(args)`（带参数宏）
- `#undef`
- `#pragma`

### 预处理流程

```
读取源文件
    ↓
逐行扫描
    ├─ 非指令行 → 检查宏替换 → 输出
    ├─ #include → 递归处理子文件 → 输出
    ├─ #define → 记录宏表
    ├─ #ifdef/#ifndef → 条件栈操作
    ├─ #else/#elif → 条件栈切换
    ├─ #endif → 条件栈弹出
    ↓
输出预处理后的文本
```

### 数据结构

```c
/* 宏定义表 */
typedef struct Macro {
    char *name;      /* 宏名称 */
    char *value;     /* 宏值（字符串形式） */
} Macro;

Macro *macro_table[MAX_MACROS];
int macro_count;

/* 条件编译栈 */
typedef struct CondStack {
    int active;      /* 当前块是否激活 */
    int else_seen;   /* 是否已遇到 #else */
} CondStack;

CondStack cond_stack[MAX_COND_DEPTH];
int cond_depth;
```

### 文件包含处理

- `#include "file"` → 从当前目录查找文件
- 递归处理，防止循环包含（记录已包含文件列表）
- 最大包含深度限制（防止无限递归）

---

## 四、多文件编译设计

### main.c 新流程

```c
int main(int argc, char **argv) {
    /* 1. 收集所有源文件 */
    char **src_files = collect_sources(argc, argv);
    
    /* 2. 每个文件预处理 + 编译 */
    for (each src_file) {
        char *preprocessed = preprocess(src_file);
        Token *tokens = tokenize_text(preprocessed);
        ASTNode *ast = parse(tokens);
        char *asm_file = codegen_to_asm(ast);
        /* 保存到临时文件 build/_fileN.s */
    }
    
    /* 3. 链接所有汇编文件 */
    linker_link_multi(asm_files[], crt0, lib, out_hex);
}
```

### extern 关键字处理

**Lexer**：新增 `TOKEN_EXTERN` 关键字

**Parser**：解析 `extern int g_val;` 或 `extern int foo();`
- 不生成定义，只记录符号引用
- 符号表标记为 `external`

**Codegen**：extern 声明不生成汇编代码（只引用）
- 函数调用：直接 `call symbol`（汇编器解析）
- 全局变量：生成 `la` 加载符号地址

---

## 五、链接器升级

### 当前链接器

```c
linker_link(user_asm, crt0_asm, lib_asm, out_hex);
// 拼接 crt0 + lib + user → asm_assemble → hex
```

### 新链接器

```c
linker_link_multi(asm_files[], crt0, lib, out_hex);
// 拼接 crt0 + lib + user_asm[0] + user_asm[1] + ... → hex
```

**改动**：
- 参数从单文件变为文件数组
- 拼接逻辑循环处理多个文件
- 其他逻辑不变（仍使用 asm_assemble）

---

## 六、测试设计

### 阶段 9 测试用例

| 测试 | 验证内容 | 预期 |
|------|----------|------|
| include_test | `#include "header.h"` 头文件引入 | tohost=42 |
| define_test | `#define MAX 100` 常量宏替换 | tohost=100 |
| ifdef_test | `#ifdef DEBUG` 条件编译 | tohost=1 |
| ifndef_test | `#ifndef RELEASE` 条件编译否定 | tohost=2 |
| else_test | `#ifdef...#else...#endif` 条件分支 | tohost=3 |
| extern_test | `extern int g_val;` 外部引用 | tohost=100 |
| multi_file_test | 两个 .c 文件编译链接 | tohost=15 |
| full_test | 多文件 + 头文件 + 宏 + extern | tohost=55 |

### 测试文件布局

```
tests/phase9/
├── include_test.c        #include 测试
├── header.h              测试头文件
├── define_test.c         #define 测试
├── ifdef_test.c          #ifdef 测试
├── ifndef_test.c         #ifndef 测试
├── else_test.c           #else 测试
├── extern_test.c         extern 测试
├── main.c                多文件测试主文件
├── helper.c              多文件测试辅助文件
└── helper.h              多文件测试头文件
```

---

## 七、实现步骤

### Step 1：预处理器框架

- 创建 `src/preprocessor.c/h`
- 实现预处理入口函数 `preprocess_file()`
- 实现逐行扫描框架

### Step 2：#include 支持

- 实现文件包含逻辑
- 已包含文件列表防循环
- 测试：include_test

### Step 3：#define 支持

- 实现宏定义表
- 实现宏替换（简单常量替换）
- 测试：define_test

### Step 4：条件编译支持

- 实现条件栈
- `#ifdef/#ifndef/#endif`
- 测试：ifdef_test, ifndef_test

### Step 5：#else/#elif 支持

- 扩展条件栈处理
- 测试：else_test

### Step 6：extern 关键字

- Lexer 新增 TOKEN_EXTERN
- Parser 解析 extern 声明
- Codegen 不生成定义
- 测试：extern_test

### Step 7：多文件编译

- main.c 支持多文件输入
- linker 升级为多文件拼接
- 测试：multi_file_test

### Step 8：完整验证

- 综合测试：full_test
- Makefile 添加 phase9 测试目标
- 回归测试：确保阶段 1-8 测试仍通过

---

## 八、场景草图（BDD）

### Happy Path

| 场景 | Given | When | Then |
|------|-------|------|------|
| 单文件包含 | 源文件含 `#include "header.h"` | 预处理 | header.h 内容展开到源文件 |
| 常量宏替换 | `#define MAX 100` + `return MAX;` | 预处理 + 编译 | tohost = 100 |
| 条件编译激活 | `#ifdef DEBUG` + DEBUG 已定义 | 预处理 | 条件块内容保留 |
| 条件编译跳过 | `#ifdef DEBUG` + DEBUG 未定义 | 预处理 | 条件块内容移除 |
| extern 引用 | `extern int g_val; return g_val;` | 编译 | 正确引用其他文件定义的 g_val |
| 多文件链接 | main.c + helper.c | 编译 + 链接 | 两文件函数/变量正确引用 |

### Sad Path（默认假设）

| 场景 | Given | When | Then |
|------|-------|------|------|
| 文件不存在 | `#include "missing.h"` | 预处理 | stderr: "cannot open missing.h" + exit 1 |
| 循环包含 | a.h 包含 b.h，b.h 包含 a.h | 预处理 | stderr: "recursive include: a.h" + exit 1 |
| 宏重定义 | `#define A 1` + `#define A 2` | 预处理 | stderr: "macro redefined: A" + exit 1 |
| 条件栈溢出 | `#ifdef` 嵌套超过 16 层 | 预处理 | stderr: "too deep condition nesting" + exit 1 |
| #endif 缺失 | `#ifdef DEBUG` 无对应 `#endif` | 预处理结束 | stderr: "unmatched #ifdef" + exit 1 |
| 条件栈不匹配 | `#else` 无对应 `#ifdef` | 预处理 | stderr: "#else without #ifdef" + exit 1 |

### Edge Case（默认假设）

| 场景 | Given | When | Then |
|------|-------|------|------|
| 空文件 | `#include "empty.h"` | 预处理 | 正常处理，输出空内容 |
| 空宏值 | `#define EMPTY` | 预处理 | 正常处理，替换为空字符串 |
| 宏边界替换 | `MAX_VALUE` + `#define MAX 100` | 预处理 | 不替换（MAX 是完整标识符） |
| 最大包含深度 | 嵌套包含超过 32 层 | 预处理 | stderr: "include depth exceeded" + exit 1 |

### 默认边界值

- 最大宏数量：64
- 最大条件嵌套深度：16
- 最大文件包含深度：32

---

## 十、风险与限制

### 已知限制

- 不支持 `#include <file>`（系统头文件路径查找）
- 不支持带参数宏 `#define MAX(a,b)`
- 不支持 `#undef`、`#pragma`
- 预处理器不处理注释（由 lexer 处理）

### 风险点

1. **循环包含**：需要记录已包含文件防止无限递归
2. **宏替换边界**：避免替换宏名称的一部分（如 `MAX_VALUE` 不替换 `MAX`）
3. **条件编译嵌套**：栈深度管理，避免溢出

---

## 十一、下一步

- 通过 Gate 1 检查后，调用 `writing-plans` skill 生成详细实现计划