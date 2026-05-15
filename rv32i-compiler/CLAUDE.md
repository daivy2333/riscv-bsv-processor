# CLAUDE.md

> RV32I C 编译器 | 上次更新：2026-05-15 | Phase 1-10 全部完成 ✅

## 项目简介

构建一个能编译自身的 C 编译器，目标平台为 RISC-V RV32I 五级流水线处理器。最终实现：**编译器编译自身 → 编译器编译 mini-os → 二进制跑在自造 CPU 上**。

## 技术栈

- **语言**: C (Micro-C 子集，用于自举)
- **目标平台**: RV32I + Zicsr (32-bit, 小端, 无浮点)
- **构建工具**: Make + GCC (宿主开发阶段)
- **测试框架**: CPU TestBench + tohost 机制
- **内存基址**: 0x80000000
- **tohost 地址**: 0x80001000

## 文档体系

本项目使用 `.claude/docs/` 目录下的单一职责文档管理开发知识与约束。

| 文档 | 用途 | 何时读取 |
|------|------|----------|
| [rules.md](.claude/docs/rules.md) | 编码规范与行为约束 | 编码前、修改代码前 |
| [architecture.md](.claude/docs/architecture.md) | 架构决策记录 | 设计新功能、重构时 |
| [snapshot.md](.claude/docs/snapshot.md) | 项目当前状态快照 | 恢复上下文、开始新任务时 |
| [tasks.md](.claude/docs/tasks.md) | 当前任务与待办 | 需要知道"接下来做什么"时 |
| [learned.md](.claude/docs/learned.md) | 学习记忆与探索发现 | 需要回忆 API 路径、技巧、踩坑经验时 |
| [references.md](.claude/docs/references.md) | 外部参考资料 | 需要查阅技术细节时 |
| [optimization.md](.claude/docs/optimization.md) | 优化方向与技术债 | 优化迭代或重构前 |

## 快速开始

- **开始编码前**: 阅读 `rules.md`
- **接手任务时**: 阅读 `tasks.md` + `snapshot.md`
- **回忆项目知识**: 阅读 `learned.md`
- **做技术决策后**: 更新 `architecture.md`
- **发现可优化点**: 记录到 `optimization.md`
- **探索发现新知识**: 记录到 `learned.md`

## 关键约束

- **目标平台**: RV32I + Zicsr，无 M 扩展（乘除法软件实现）
- **调用约定**: RISC-V ABI (a0-a7 传参, ra 返回, sp 栈, s0 帧指针)
- **对齐**: 4 字节对齐
- **自举要求**: 编译器源码必须用 Micro-C 子集编写，能被自己编译

## 已完成阶段

| 阶段 | 功能 | 状态 |
|------|------|------|
| Phase 1-2 | Lexer + Parser + 基本表达式 | ✅ |
| Phase 3 | 控制流 + 函数调用 | ✅ |
| Phase 4 | 数组 + 指针 + 字符串 | ✅ |
| Phase 5 | 全局变量 + extern 变量 | ✅ |
| Phase 6 | 结构体 + 成员访问 (p->x, n.x) | ✅ |
| Phase 7 | 汇编器 + 链接器 + 单文件编译 | ✅ |
| Phase 8 | 预处理器 (#define, #ifdef) | ✅ |
| Phase 9 | extern 函数原型 | ✅ |
| **Phase 10** | **volatile/const/void/typedef/static** | ✅ |

## 支持的 C 特性

### 类型
- `int`, `char`, `void`
- `struct` (定义、声明、成员访问)
- 数组 (`int arr[10]`)
- 指针 (`int *p`, `char *s`)
- `typedef` 结构体别名

### 类型限定符
- `volatile` (标记，无 codegen 影响)
- `const` (标记，无 codegen 影响)

### 存储类
- `extern` (变量声明、函数原型)
- `static` (全局变量内部链接 `.Lstatic_` 标签)
- `typedef` (仅结构体别名)

### 控制流
- `if/else`, `while`, `for`
- `return` (含空 return 用于 void 函数)

### 表达式
- 算术: `+`, `-`, `*`, `/` (乘除法软件实现)
- 比较: `<`, `<=`, `>`, `>=`, `==`, `!=`
- 逻辑: `&&` (AND)
- 赋值: `=`, `++` (自增)
- 位运算: `&` (取地址)

### 函数
- 函数定义、调用、参数传递
- void 函数、void(void) 参数
- 递归调用
- extern 函数原型

### 其他
- 字符串字面量 `"hello"`
- 全局变量初始化
- 结构体全局变量
- 成员指针访问 `p->x`、值访问 `n.x`

## 不支持特性

- `#include <file>` 标准库头文件 (预处理器限制)
- 浮点数 (`float`, `double`)
- 多级指针 (`int **pp`)
- `switch/case`
- 复合初始化器 `{1, 2, 3}`
- `union`, `enum`
- 位域、变长数组

## 测试验证

所有 Phase 10 测试通过:

| 测试 | 功能 | 结果 |
|------|------|------|
| volatile_test.c | volatile 变量 | tohost=42 ✅ |
| const_test.c | const 变量 | tohost=15 ✅ |
| void_test.c | void 函数 | tohost=42 ✅ |
| void_param_test.c | void(void) 参数 | tohost=15 ✅ |
| void_no_return.c | 空 return | tohost=5 ✅ |
| typedef_test.c | typedef 别名 | tohost=30 ✅ |
| static_test.c | static 全局变量 | tohost=7 ✅ |
| integration_test.c | 综合测试 | tohost=31 ✅ |

## 自举状态

编译器已具备自举所需的全部特性 (volatile/const/void/typedef/static)。

**限制**: 预处理器不支持 `#include <stdio.h>` 等标准库头文件。

**下一步**: 增强预处理器支持系统头文件，实现完整自举。

## 与父项目关系

本项目是 [riscv-bsv-processor](../CLAUDE.md) 的编译器子项目。编译产出的二进制通过 `hex_to_bsv.py` 工具链加载到 CPU 执行。