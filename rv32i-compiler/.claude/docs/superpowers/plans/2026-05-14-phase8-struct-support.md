# 阶段 8：结构体支持实现计划 - 索引

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task.

**Goal:** 为 RV32I C 编译器添加完整结构体支持，验证链表求和测试。

**Architecture:** 全局结构体表 + Parser 注册 + Codegen 查询生成成员偏移。

**Tech Stack:** C (Micro-C), RV32I + Zicsr, CPU TestBench + tohost

---

## 计划分片

本计划因篇幅较大，分三部分写入：

| Part | Tasks | 内容 |
|------|-------|------|
| [Part 1](2026-05-14-phase8-struct-support-part1.md) | 1-6 | types.h/c, lexer.h/c, ast.h, parser.c 基础 |
| [Part 2](2026-05-14-phase8-struct-support-part2.md) | 7-9 | parser.c 解析函数, codegen.c struct_table |
| [Part 3](2026-05-14-phase8-struct-support-part3.md) | 10-14 | codegen 成员访问, 全局 struct, 测试 |

---

## 任务总览

| Task | 文件 | 内容 |
|------|------|------|
| 1 | types.h | TYPE_STRUCT, StructInfo, MemberInfo |
| 2 | types.c | struct 类型辅助函数 |
| 3 | lexer.h | TOK_STRUCT, TOK_ARROW, TOK_DOT |
| 4 | lexer.c | 识别 struct 关键字和 -> 操作符 |
| 5 | ast.h | AST_STRUCT_DEF, AST_MEMBER_ACCESS |
| 6 | parser.c | struct 表, parse_member_decl |
| 7 | parser.c | parse_struct_def, parse_struct_decl |
| 8 | parser.c | parse_member_access, parse_program |
| 9 | codegen.c | struct_table, register_structs |
| 10 | codegen.c | AST_MEMBER_ACCESS, 全局 struct 变量 |
| 11 | parser.c | 成员赋值解析 |
| 12 | tests/phase8 | 测试 1: 成员访问 |
| 13 | tests/phase8 | 测试 2: 链表求和 |
| 14 | Makefile | phase8 测试目标 |

---

## 验证目标

**链表求和测试 (test2_linked_list.c)**:
```c
struct Node { int value; struct Node* next; };
// 创建 3 节点链表: 10 → 20 → 30
// sum_list(&g_n1) 返回 60
```

---

## Execution Handoff

**执行选项:**

1. **Subagent-Driven (推荐)** - 按任务分批执行，每批完成后 review
2. **Inline Execution** - 在当前 session 执行，checkpoint 控制

选择哪种方式？