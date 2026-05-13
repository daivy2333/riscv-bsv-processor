# CLAUDE.md

> RV32I C 编译器 | 上次更新：2026-05-13 | 阶段1+2 完成 ✅

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

## 与父项目关系

本项目是 [riscv-bsv-processor](../CLAUDE.md) 的编译器子项目。编译产出的二进制通过 `hex_to_bsv.py` 工具链加载到 CPU 执行。