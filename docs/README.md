# CPU 设计文档索引

## 核心文档

| 文档 | 内容 |
|------|------|
| [cpu-pipeline-architecture.md](cpu-pipeline-architecture.md) | 流水线架构设计、数据包结构、前递网络 |
| [roadmap-embedded-os.md](roadmap-embedded-os.md) | 开发阶段、里程碑、测试状态 |
| [problem-resolution-progress.md](problem-resolution-progress.md) | 问题解决进度、架构修复记录 |

## 参考文档

| 文档 | 内容 |
|------|------|
| [branch-prediction.md](branch-prediction.md) | BHT/BTB 动态分支预测 |
| [load-use-hazard.md](load-use-hazard.md) | Load-Use 冒险检测流程 |
| [memory-layout.md](memory-layout.md) | 内存布局、地址空间 |
| [testing-guide.md](testing-guide.md) | 汇编测试方法、trace 调试 |

## 经验文档

| 文档 | 内容 |
|------|------|
| [debugging-lessons.md](debugging-lessons.md) | 棘手问题记录、调试方法论、控制流协议重构 |

## 快速导航

- **想了解整体架构？** → [cpu-pipeline-architecture.md](cpu-pipeline-architecture.md)
- **想了解开发进度？** → [roadmap-embedded-os.md](roadmap-embedded-os.md)
- **想了解控制流协议？** → [debugging-lessons.md](debugging-lessons.md) 问题 6
- **想添加测试？** → [testing-guide.md](testing-guide.md)
- **想学习调试经验？** → [debugging-lessons.md](debugging-lessons.md)

## 当前项目状态

### 已完成

- ✓ 五级流水线 + 数据前递
- ✓ Load-Use 冒险处理
- ✓ 动态分支预测 (BHT + BTB)
- ✓ 控制流重定向协议（统一处理分支/JAL/trap/MRET/中断）
- ✓ RV32I 全指令集
- ✓ CSR + 特权指令 + 陷阱处理
- ✓ SOC 架构 + 外设框架
- ✓ 10 个基线测试通过
- ✓ 稳定性测试通过 (10⁵+ 周期)
- ✓ FreeRTOS demo 基础运行

### 待完善

- 中断连接修复 (connect_interrupts 规则冲突)
- FreeRTOS 定时器中断支持
- 任务调度验证

---

*更新日期: 2026-04-20*