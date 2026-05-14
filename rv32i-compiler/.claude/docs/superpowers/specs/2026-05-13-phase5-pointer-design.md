# 阶段 5 设计文档：指针基础

> 创建时间：2026-05-13
> 状态：已批准

---

## 目标

为 RV32I 编译器添加指针基础支持，验证目标是 `swap(&a, &b)` 指针传参。

---

## 特性范围

### 支持的特性

| 特性 | 示例 | 说明 |
|------|------|------|
| 指针类型声明 | `int *p;` | 单级指针 |
| 指针初始化 | `int *p = &x;` | 声明时初始化 |
| 函数参数指针 | `void swap(int *a, int *b)` | 指针类型参数 |
| 取地址（局部变量） | `&x` | 仅支持局部变量栈地址 |
| 解引用（右值） | `int tmp = *a;` | 读取指针指向的值 |
| 解引用（左值） | `*a = *b;` | 写入指针指向的地址 |

### 不支持的特性（推迟）

| 特性 | 推迟阶段 | 原因 |
|------|----------|------|
| 多级指针 `int **pp` | 阶段 8 | 结构体指针需要时引入 |
| 指针算术 `p + 1` | 阶段 6 | 数组地址计算时引入 |
| 全局变量取地址 | 阶段 7 | 全局变量引入时扩展 |

---

## Lexer 改动

### 新增 Token

```c
TOK_AND    // 取地址操作符 '&'
```

### TOK_STAR 保持不变

Parser 根据上下文判断 `TOK_STAR` 的语义：
- 类型声明时：`int *p` → 指针类型标记
- 表达式开头：`*p` → 解引用操作
- 表达式中间：`a * b` → 乘法运算

---

## Type 结构体设计

### 新增类型定义（types.h）

```c
typedef struct {
    int base_type;    // 基本类型：0 = int（后续扩展）
    int ptr_level;    // 指针层级：0 = 基本类型, 1 = int*, 2 = int**
} Type;
```

### 阶段 5 使用方式

- `base_type = 0`（仅 int 类型）
- `ptr_level = 0` → `int x`
- `ptr_level = 1` → `int *p`
- `ptr_level > 1` → 阶段 5 报错："multi-level pointer not supported"

### 符号表扩展

```c
static struct {
    char *name;
    int   offset;
    Type  type;      // 新增：类型信息
} syms[MAX_LOCALS];
```

---

## AST 节点设计

### 新增节点类型（ast.h）

```c
typedef enum {
    // ... 现有节点 ...
    AST_ADDR,        // 取地址：.left = 变量节点
    AST_DEREF,       // 解引用：.left = 指针表达式
} ASTNodeType;
```

### 节点语义

| 节点 | 字段 | 语义 |
|------|------|------|
| `AST_ADDR` | `.left = AST_VAR_REF` | 获取变量地址，结果存入 t0 |
| `AST_DEREF` | `.left = 指针表达式` | 访问指针指向的内存，codegen 根据上下文决定 lw/sw |

---

## Parser 改动

### 类型声明解析

```
var-decl = "int" ["*"] identifier ["=" expr] ";"
```

解析逻辑：
1. 遇到 `TOK_INT` 后检查下一个是否为 `TOK_STAR`
2. 若有 `TOK_STAR`，设置 `Type.ptr_level = 1`，跳过 token
3. 继续解析变量名和初始化表达式

### 函数参数解析

```
param = "int" ["*"] identifier
```

同类型声明逻辑，设置参数的 `Type.ptr_level`。

### 表达式解析扩展

在 `parse_primary` 中添加：

```
primary = integer-literal
        | identifier [ "(" args ")" ]   // 函数调用或变量引用
        | "&" primary                   // 取地址（新增）
        | "*" primary                   // 解引用（新增）
        | "(" expression ")"
```

解析逻辑：
1. `TOK_AND` → 生成 `AST_ADDR`，递归解析后续表达式
2. `TOK_STAR` → 生成 `AST_DEREF`，递归解析后续表达式

**说明**：`parse_primary` 是表达式解析的最底层，`TOK_STAR` 在此处必然是解引用。乘法运算在 `parse_term` 层处理（`primary { ("*" | "/") primary }`），不会与解引用冲突。

---

## Codegen 改动

### 取地址 `&x`

```asm
# x 是局部变量，偏移 offset
addi t0, sp, offset    # t0 = &x（栈地址）
```

### 解引用读取 `*p`

```asm
# t0 已存指针值
lw t0, 0(t0)           # t0 = *p
```

### 解引用写入 `*p = val`

在 `AST_ASSIGN` 处理中检查左侧是否为 `AST_DEREF`：

```asm
# 左侧是 *p，右侧值在 t0
# 需要先计算指针地址
gen_expr(assign->left->left)  # 计算 p，结果在 t1
sw t0, 0(t1)                  # *p = val
```

### 函数调用传指针

指针参数与其他参数处理相同，调用前将指针值存入 `a0-a7`。

---

## 验证测试

### 测试文件：tests/phase5/swap.c

```c
void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int main() {
    int x = 1;
    int y = 2;
    swap(&x, &y);
    return x;  // 应返回 2
}
```

### 验证标准

- 编译产出 `.hex` 文件
- CPU TestBench 执行
- `tohost` 读出值 = 2（x 与 y 交换成功）

### 预期执行流程

```
main() 入口
  x = 1 (sp+16)
  y = 2 (sp+20)
  swap(&x, &y)
    a0 = sp+16 (&x)
    a1 = sp+20 (&y)
    swap() 入口
      tmp = lw 0(a0) = 1
      sw lw 0(a1), 0(a0)  → x = 2
      sw tmp, 0(a1)       → y = 1
    swap() 返回
  return x (lw sp+16 = 2)
main() 返回 a0 = 2
tohost = 2 ✅
```

---

## 实现任务清单

| 任务 | 模块 | 说明 |
|------|------|------|
| T1 | lexer.h/c | 添加 `TOK_AND` token |
| T2 | types.h/c | 创建 Type 结构体定义 |
| T3 | ast.h/c | 添加 `AST_ADDR`、`AST_DEREF` 节点类型 |
| T4 | parser.c | 类型声明解析支持 `int *p` |
| T5 | parser.c | 函数参数解析支持指针类型 |
| T6 | parser.c | 表达式解析支持 `&` 和 `*` |
| T7 | codegen.c | 符号表扩展 Type 字段 |
| T8 | codegen.c | 取地址代码生成 `addi t0, sp, offset` |
| T9 | codegen.c | 解引用读取代码生成 `lw t0, 0(t0)` |
| T10 | codegen.c | 解引用写入代码生成（赋值左侧处理） |
| T11 | Makefile | 添加 phase5 测试目标 |
| T12 | tests/phase5/ | 创建 swap.c 测试文件 |
| T13 | 验证 | 运行测试确认 tohost = 2 |

---

## 依赖关系

```
T1 (lexer) ──────────────────────────────────────┐
                                                  │
T2 (types) ──────────────────────────────────────┼── T4/T5 (parser type)
                                                  │
T3 (ast) ────────────────────────────────────────┼── T6 (parser expr)
                                                  │
T4-T6 (parser) ──────────────────────────────────┼── T7-T10 (codegen)
                                                  │
T7-T10 (codegen) ────────────────────────────────┼── T11-T13 (test)
                                                  │
T11 (makefile) ──────────────────────────────────┘
T12 (test file)
T13 (verify)
```

---

## 风险与边界

### 潜在问题

1. **TOK_STAR 的语义判断**
   - 问题：`*p`（解引用）vs `a * b`（乘法）
   - 解决：解析器层级分离，`parse_primary` 处理解引用，`parse_term` 处理乘法，自然无冲突

2. **解引用左值与右值的区分**
   - 问题：`*p = val`（写入）vs `x = *p`（读取）
   - 解决：codegen 在 `AST_ASSIGN` 处理中检测左侧是否为 `AST_DEREF`，生成 `sw` 而非 `lw`

3. **多级指针误用**
   - 问题：用户写 `int **pp`
   - 解决：Parser 检测 `ptr_level > 1` 时报错："multi-level pointer not supported in phase 5"

### 不处理的情况

- 指针空值 NULL（阶段 7 全局常量）
- 指针类型转换（自举不需要）
- 指针比较 `p1 == p2`（阶段 6 指针算术）

---

## 后续阶段影响

| 阶段 | 基于此设计的扩展 |
|------|------------------|
| 阶段 6 | Type 结构体添加 `array_size` 字段 |
| 阶段 7 | Type 结构体添加 `is_global` 标记，codegen 支持全局变量地址 |
| 阶段 8 | `ptr_level` 支持多级，Type 添加 `struct_tag` 字段 |