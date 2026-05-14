# 阶段 6 设计文档：数组支持

> 创建时间：2026-05-13
> 状态：已批准（自动模式）

---

## 目标

为 RV32I 编译器添加数组支持，验证目标是 `arr_sum(arr, 5)` 数组求和。

---

## 特性范围

### 支持的特性

| 特性 | 示例 | 说明 |
|------|------|------|
| 数组声明 | `int arr[5];` | 局部数组，栈上分配 |
| 下标访问（读取） | `arr[i]` | 读取第 i 个元素 |
| 下标访问（写入） | `arr[i] = val;` | 写入第 i 个元素 |
| 数组名作为指针 | `arr` | 自动转换为 `&arr[0]` |
| 指针算术 | `p + n` | 指针偏移 n 个元素 |
| 数组参数 | `int *arr` | 复用指针参数机制 |

### 不支持的特性（推迟）

| 特性 | 推迟阶段 | 原因 |
|------|----------|------|
| 数组初始化 `{1,2,3}` | 后续阶段 | 需要花括号解析和初始化列表 |
| 多维数组 `arr[i][j]` | 暂不支持 | 自举不需要 |
| 全局数组 | 阶段 7 | 全局变量引入时扩展 |

---

## Lexer 改动

### 新增 Token

```c
TOK_LBRACKET   // '['
TOK_RBRACKET   // ']'
```

---

## Type 结构体扩展

### 扩展 types.h

```c
typedef struct {
    int base_type;    /* 0 = int */
    int ptr_level;    /* 指针层级 */
    int array_size;   /* 数组大小：0 = 非数组, >0 = 数组元素数 */
} Type;
```

### 新增 helper 函数

```c
Type type_make_array(int size);     /* 创建数组类型 */
int  type_is_array(Type t);         /* 检查是否为数组 */
```

---

## AST 节点设计

### 新增节点类型

```c
AST_ARRAY_ACCESS  /* 数组下标访问：.name = 数组名, .left = 下标表达式 */
```

### AST_ASSIGN 扩展

数组赋值 `arr[i] = val` 处理方式：
- Parser 检测到 `identifier "[" expr "]" "=" expr`
- 生成 AST_ASSIGN，设置：
  - `is_array_assign = 1`
  - `array_name = "arr"`
  - `array_index = index_expr`
  - `expr = val_expr`

---

## Parser 改动

### 数组声明解析

```
var-decl = "int" identifier "[" number "]" ";" 
         | "int" ["*"] identifier ["=" expr] ";"  // 原有
```

解析逻辑：
1. 遇到 `TOK_INT` 后检查 identifier
2. 若下一个 token 是 `TOK_LBRACKET`：
   - 解析 `[number]`
   - 设置 `Type.array_size = number`
3. 否则继续原有指针/变量解析

### 数组下标表达式解析

在 `parse_primary` 中添加：

```
primary = identifier ["[" expr "]" ]   // 数组访问或变量引用
        | ...
```

解析逻辑：
1. 解析 identifier
2. 若下一个是 `TOK_LBRACKET`：
   - 解析 `[expr]`
   - 生成 `AST_ARRAY_ACCESS`
3. 否则检查是否函数调用或变量引用

### 数组赋值解析

在 `parse_assign` 中添加数组赋值分支：

```
assign-stmt = identifier "[" expr "]" "=" expr ";"  // 数组赋值
            | identifier "=" expr ";"              // 变量赋值
            | "*" primary "=" expr ";"             // 解引用赋值
```

---

## Codegen 改动

### 数组声明处理

- 符号表记录 `array_size`
- 栈帧计算：`frame_size += 4 * array_size`（每个元素 4 字节）

### 数组下标读取 `arr[i]`

```asm
# arr[i] → 读取第 i 个元素
gen_expr(i)               # 计算 i，结果在 t0
slli t0, t0, 2            # t0 = i * 4（字节偏移）
addi t1, sp, base         # t1 = &arr[0]（数组基址）
add t0, t1, t0            # t0 = &arr[i]
lw t0, 0(t0)              # t0 = arr[i]
```

### 数组下标写入 `arr[i] = val`

```asm
# arr[i] = val
gen_expr(val)             # 计算 val，结果在 t0
sw t0, (sp + spill)       # 暂存 val
gen_expr(i)               # 计算 i，结果在 t0
slli t0, t0, 2            # t0 = i * 4
addi t1, sp, base         # t1 = &arr[0]
add t0, t1, t0            # t0 = &arr[i]
lw t1, (sp + spill)       # t1 = val
sw t1, 0(t0)              # arr[i] = val
```

### 数组名作为指针 `arr`

```asm
# arr（数组名）→ 返回首地址
addi t0, sp, base         # t0 = &arr[0]
```

符号表查找时检查 `array_size > 0`，生成地址而非加载值。

### 指针算术 `p + n`

```asm
# p + n（指针偏移）
gen_expr(p)               # p 的值（地址），结果在 t0
sw t0, (sp + spill)       # 暂存地址
gen_expr(n)               # n 的值，结果在 t0
slli t0, t0, 2            # t0 = n * 4（字节偏移）
lw t1, (sp + spill)       # t1 = p
add t0, t0, t1            # t0 = p + n*4（新地址）
```

---

## 验证测试

### 测试文件：tests/phase6/test_array.c

```c
int arr_sum(int *arr, int n) {
    int sum = 0;
    int i = 0;
    while (i < n) {
        sum = sum + arr[i];
        i = i + 1;
    }
    return sum;
}

int main() {
    int arr[5];
    arr[0] = 1;
    arr[1] = 2;
    arr[2] = 3;
    arr[3] = 4;
    arr[4] = 5;
    return arr_sum(arr, 5);  // 应返回 15
}
```

### 验证标准

- 编译产出 `.hex` 文件
- CPU TestBench 执行
- `tohost` 读出值 = 15

---

## 实现任务清单

| 任务 | 模块 | 说明 |
|------|------|------|
| T1 | lexer.h/c | 添加 `TOK_LBRACKET`、`TOK_RBRACKET` |
| T2 | types.h/c | Type 添加 `array_size` 字段 |
| T3 | ast.h | 添加 `AST_ARRAY_ACCESS` 节点 |
| T4 | ast.h | AST_ASSIGN 添加 `is_array_assign`、`array_index` |
| T5 | parser.c | 数组声明解析 `int arr[n]` |
| T6 | parser.c | 数组下标表达式解析 `arr[i]` |
| T7 | parser.c | 数组赋值解析 `arr[i] = val` |
| T8 | codegen.c | 符号表扩展 `array_size` |
| T9 | codegen.c | 数组栈帧空间计算 |
| T10 | codegen.c | 数组下标读取代码生成 |
| T11 | codegen.c | 数组下标写入代码生成 |
| T12 | codegen.c | 数组名作为指针处理 |
| T13 | codegen.c | 指针算术代码生成 |
| T14 | Makefile | 添加 phase6 测试目标 |
| T15 | tests/phase6/ | 创建 test_array.c |
| T16 | 验证 | 运行测试确认 tohost = 15 |

---

## 后续阶段影响

| 阶段 | 基于此设计的扩展 |
|------|------------------|
| 阶段 7 | Type 添加 `is_global` 标记，支持全局数组 |
| 阶段 8 | 结构体数组支持 |