# Phase 10: 自举准备 - 设计文档

> 创建日期：2026-05-15
> 目标：添加 volatile/const/void/typedef/static 特性，实现编译器自举验证

---

## 设计概览

**阶段 10 目标**：添加 volatile/const/void/typedef/static 特性，实现编译器自举验证。

**实现顺序**：volatile + const → void → typedef → static（复杂度递增）

**验证策略**：每个特性独立测试 → 最后整体自举验证

**代码改动范围**：Lexer + Parser + types.c/h + codegen.c

**预估工作量**：约 200 行代码改动 + 50 行测试代码

---

## 实现顺序

| 序号 | 特性 | 复杂度 | 预估时间 | 改动文件 |
|------|------|--------|----------|----------|
| 1 | volatile + const | ⭐ | 1 小时 | lexer.c + types.h + parser.c |
| 2 | void | ⭐⭐ | 1.5 小时 | lexer.c + parser.c + codegen.c |
| 3 | typedef | ⭐⭐ | 2 小时 | lexer.c + parser.c |
| 4 | static | ⭐⭐⭐ | 2.5 小时 | lexer.c + parser.c + ast.h + codegen.c |
| 5 | 自举验证 | ⭐⭐⭐⭐ | 1 小时 | 测试流程 |

---

## 第一部分：volatile + const 设计

### 设计决策

- volatile：类型标记，不阻止优化（编译器无优化阶段）
- const：类型标记，不生成 .rodata 段（编译器无只读段管理）
- volatile + const 可组合使用：`volatile const int x`

### Lexer 改动

**新增 Token 类型**：
```c
TOK_VOLATILE
TOK_CONST
```

**关键字识别**（lexer.c:lex_keyword_or_id）：
```c
if (len == 8 && strncmp(s, "volatile", 8) == 0)
    return new_token(TOK_VOLATILE, s, len, line, col);
if (len == 5 && strncmp(s, "const", 5) == 0)
    return new_token(TOK_CONST, s, len, line, col);
```

**改动文件**：`lexer.c` + `lexer.h`（约 10 行）

---

### Parser 改动

**类型修饰位**（types.h:TypeInfo）：
```c
typedef struct {
    int base_type;       // TYPE_INT, TYPE_CHAR, TYPE_STRUCT
    int ptr_level;       // 指针层级
    int array_size;      // 数组大小
    int struct_id;       // 结构体 ID
    int is_const;        // NEW: const 标记位
    int is_volatile;     // NEW: volatile 标记位
} TypeInfo;
```

**类型解析流程**（parser.c:parse_type）：
```
遇到 TOK_VOLATILE → 设置 is_volatile=1 → 继续解析类型
遇到 TOK_CONST → 设置 is_const=1 → 继续解析类型
volatile/const 可组合使用（volatile const int x）
```

**改动文件**：`types.h` + `parser.c`（约 22 行）

---

### Codegen 改动

**volatile + const 不生成特殊代码**：
- volatile 变量：普通 lw/sw 指令（无寄存器缓存优化）
- const 变量：普通 lw/sw 指令（无 .rodata 段）
- 类型修饰位透明传递，不影响汇编输出

**改动文件**：无改动

---

### 测试案例

**volatile 测试**：
```c
volatile int x;
x = 42;
return x;  // 预期：42
```

**const 测试**：
```c
const int a = 10;
int b;
b = a + 5;
return b;  // 预期：15
```

**组合测试**：
```c
volatile const int x = 5;
return x;  // 预期：5
```

---

## 第二部分：void 设计

### 设计决策

- void 返回类型：`void func()` 函数不返回值，自动添加 ret
- void 参数：`void func(void)` 显式声明无参数
- void 指针：不支持（自举源码未使用）

### Lexer 改动

**新增 Token 类型**：
```c
TOK_VOID
```

**关键字识别**：
```c
if (len == 4 && strncmp(s, "void", 4) == 0)
    return new_token(TOK_VOID, s, len, line, col);
```

**改动文件**：`lexer.c` + `lexer.h`（约 5 行）

---

### Parser 改动

**void 返回类型解析**（parser.c:parse_func_def）：
```c
if (cur->type == TOK_VOID) {
    func_type.base_type = TYPE_VOID;
    cur = cur->next;
}
```

**void 参数处理**：
```c
if (cur->type == TOK_VOID && cur->next->type == TOK_RPAREN) {
    cur = cur->next;  // 跳过 void，无参数
}
```

**改动文件**：`parser.c`（约 15 行）

---

### Codegen 改动

**void 函数返回处理**：
```c
if (func_type.base_type == TYPE_VOID) {
    emit("    ret\n");  // 无返回值，直接 ret
}
```

**空 return 语句**：
```c
// void func() { return; } → 视为跳转到函数末尾
// void func() { } → 自动添加 ret
```

**改动文件**：`codegen.c`（约 10 行）

---

### 测试案例

**void 返回类型测试**：
```c
void test_void() { }
int main() {
    test_void();
    return 42;  // 预期：42
}
```

**void 参数测试**：
```c
int get_value(void) { return 10; }
int main() { return get_value(); }  // 预期：10
```

**空 return 测试**：
```c
void early_return(void) { if (1) return; }
int main() { early_return(); return 5; }  // 预期：5
```

---

## 第三部分：typedef 设计

### 设计决策

- 仅支持结构体别名：`typedef struct { ... } Name;`
- 不支持基本类型别名、指针别名、函数指针别名（自举源码未使用）

### Lexer 改动

**新增 Token 类型**：
```c
TOK_TYPEDEF
```

**关键字识别**：
```c
if (len == 7 && strncmp(s, "typedef", 7) == 0)
    return new_token(TOK_TYPEDEF, s, len, line, col);
```

**改动文件**：`lexer.c` + `lexer.h`（约 5 行）

---

### Parser 改动

**typedef 结构体别名解析**（parser.c:parse_global_decl）：
```c
if (cur->type == TOK_TYPEDEF && cur->next->type == TOK_STRUCT) {
    cur = cur->next;  // 跳过 typedef
    ASTNode *struct_def = parse_struct_def(cur);
    char *alias_name = extract_typedef_name(cur);
    register_type_alias(alias_name, struct_def->struct_id);
    return AST_NOOP;  // typedef 不生成 AST
}
```

**类型别名表**：
```c
#define MAX_TYPE_ALIASES 32
typedef struct {
    char name[64];
    int struct_id;
} TypeAlias;
static TypeAlias type_aliases[MAX_TYPE_ALIASES];
static int num_type_aliases = 0;
```

**类型别名查找**（parser.c:parse_type）：
```c
int alias_id = lookup_type_alias(token_text);
if (alias_id >= 0) {
    type.base_type = TYPE_STRUCT;
    type.struct_id = type_aliases[alias_id].struct_id;
}
```

**改动文件**：`parser.c`（约 50 行）

---

### Codegen 改动

**typedef 不生成代码**：typedef 在 Parser 返回 AST_NOOP，Codegen 跳过。

**改动文件**：无改动

---

### 测试案例

**typedef 结构体别名测试**：
```c
typedef struct { int value; } Node;
int main() {
    Node n;
    n.value = 42;
    return n.value;  // 预期：42
}
```

**typedef 指针测试**：
```c
typedef struct { int x; } Point;
int main() {
    Point p;
    Point *ptr;
    ptr = &p;
    ptr->x = 10;
    return ptr->x;  // 预期：10
}
```

---

## 第四部分：static 设计

### 设计决策

- 静态全局变量：`.Lstatic_<name>` 本地标签（GNU 汇编器约定）
- 静态函数：`.Lstatic_<func>` 本地标签
- 静态局部变量：不支持（自举源码未使用）

### Lexer 改动

**新增 Token 类型**：
```c
TOK_STATIC
```

**关键字识别**：
```c
if (len == 6 && strncmp(s, "static", 6) == 0)
    return new_token(TOK_STATIC, s, len, line, col);
```

**改动文件**：`lexer.c` + `lexer.h`（约 5 行）

---

### Parser 改动

**static 存储类别标记**：
```c
int is_static = 0;
if (cur->type == TOK_STATIC) {
    is_static = 1;
    cur = cur->next;
}
node->is_static = is_static;
```

**AST 节点扩展**：
```c
// AST_GLOBAL_DECL + AST_FUNC_DEF 添加 is_static 字段
```

**改动文件**：`parser.c` + `ast.h`（约 30 行）

---

### Codegen 改动

**静态全局变量命名**：
```c
if (globals[i].is_static) {
    emit(".Lstatic_%s:\n", globals[i].name);
} else {
    emit(".global_%s:\n", globals[i].name);
}
```

**静态函数命名**：
```c
if (func->is_static) {
    emit(".Lstatic_%s:\n", func->name);
} else {
    emit("%s:\n", func->name);
}
```

**静态符号访问**：
```c
if (global_is_static(name)) {
    emit("    la t0, .Lstatic_%s\n", name);
}
```

**改动文件**：`codegen.c`（约 40 行）

---

### 汇编器改动

**本地标签解析**：`.Lstatic_name` 标签视为普通标签处理（现有机制已支持）。

**改动文件**：无改动

---

### 测试案例

**静态全局变量测试**：
```c
static int g_hidden = 100;
int main() { return g_hidden; }  // 预期：100
```

**静态函数测试**：
```c
static int helper() { return 30; }
int main() { return helper(); }  // 预期：30
```

**多文件静态符号测试**：
```c
// file1.c
static int g_local = 50;
int get_local() { return g_local; }

// file2.c
extern int get_local();
int main() { return get_local(); }  // 预期：50
```

---

## 第五部分：整体自举验证设计

### 自举验证流程

**步骤 1：编译器编译自身**
```bash
./build/microcc src/main.c src/lexer.c ... → microcc_self.hex
```

**步骤 2：对比测试**
```bash
gcc -o microcc_gcc src/*.c
./microcc_gcc tests/test.c → test_gcc.hex
# 自编译版编译 test.c → test_self.hex
diff test_gcc.hex test_self.hex
```

**步骤 3：功能验证**
```bash
CPU TestBench 运行 test_self.hex → tohost = 42
```

---

### 自举失败诊断

| 失败症状 | 诊断方向 |
|----------|----------|
| 编译自身失败 | 检查特性实现不完整 |
| hex 不一致 | 检查类型系统差异 |
| 自编译程序运行失败 | 检查代码生成差异 |

---

## 文件改动清单

| 文件 | 改动内容 | 改动量 |
|------|----------|--------|
| `lexer.c` | 新增 TOK_VOLATILE/CONST/VOID/TYPEDEF/STATIC | 30 行 |
| `lexer.h` | TokenType enum 扩展 | 5 行 |
| `types.h` | TypeInfo 添加 is_const/is_volatile | 2 行 |
| `parser.c` | parse_type + parse_func_def + typedef 别名表 | 100 行 |
| `parser.h` | 类型别名函数声明 | 10 行 |
| `ast.h` | AST 节点添加 is_static | 5 行 |
| `codegen.c` | void 返回 + static 符号命名 | 50 行 |
| `tests/phase10/` | 新增测试目录 | 新增 |

**总改动量**：约 200 行新增代码

---

## 不支持的特性

| 特性 | 原因 |
|------|------|
| enum | 自举源码未使用，标记为"不支持" |
| volatile 指针 | 编译器无优化阶段，类型标记足够 |
| const 变量 .rodata | 编译器无只读段管理 |
| void 指针 | 自举源码未使用，需复杂类型转换 |
| typedef 基本类型别名 | 自举源码未使用 |
| typedef 函数指针 | 自举源码未使用 |
| static 局部变量 | 自举源码未使用 |

---

## 验证标准

**阶段性验证**：
- volatile + const 测试 → tohost 验证
- void 测试 → tohost 验证
- typedef 测试 → tohost 验证
- static 测试 → tohost 验证

**最终验证**：
- 编译器编译自身成功 → microcc_self.hex 生成
- 自编译版编译 test.c → tohost = 42

---

## 实现计划

详见实现计划文档（PLAN.md）。