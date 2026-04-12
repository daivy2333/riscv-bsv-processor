# CPU 设计图解文档索引

本目录包含 RISC-V 处理器设计的详细图解文档，使用 Mermaid 图表语法。

## 文档列表

| 文档 | 内容 | 关键图解 |
|------|------|----------|
| [cpu-pipeline-architecture.md](cpu-pipeline-architecture.md) | 五级流水线整体架构 | 流水线结构、数据包结构、解码流程 |
| [data-forwarding.md](data-forwarding.md) | 数据前递机制 | 前递路径、优先级、时序图 |
| [load-use-hazard.md](load-use-hazard.md) | Load-Use 冒险检测 | 检测逻辑、停顿时序、控制状态 |
| [branch-prediction.md](branch-prediction.md) | 分支预测机制 | BHT/BTB 结构、预测流程、失败处理 |
| [pipeline-scheduling.md](pipeline-scheduling.md) | 流水线调度规则 | 规则执行顺序、FIFO 流动、冲突解决 |
| [memory-layout.md](memory-layout.md) | 内存布局与整体架构 | 地址空间、寄存器堆、模块依赖 |

## 快速导航

### 想了解整体架构？
→ [cpu-pipeline-architecture.md](cpu-pipeline-architecture.md) 五级流水线结构
→ [memory-layout.md](memory-layout.md) 模块依赖和内存布局

### 想了解数据冒险处理？
→ [data-forwarding.md](data-forwarding.md) 前递机制解决 RAW 冒险
→ [load-use-hazard.md](load-use-hazard.md) Load-Use 特殊处理

### 想了解分支预测？
→ [branch-prediction.md](branch-prediction.md) BHT/BTB 动态预测

### 想了解 BSV 规则调度？
→ [pipeline-scheduling.md](pipeline-scheduling.md) 规则执行顺序和条件

## 图表类型汇总

### 流程图 (flowchart)
- 流水线数据流
- 前递逻辑
- 冒险检测流程

### 时序图 (sequenceDiagram)
- 前递时序
- Load-Use 停顿时序
- 分支预测流程

### 状态图 (stateDiagram)
- BHT 2位计数器状态
- 处理器状态转换
- 停顿控制状态

### 类图 (classDiagram)
- 流水线数据包结构
- BTB 条目结构

### 甘特图 (gantt)
- Load-Use 时序展开

### 思维导图 (mindmap)
- 调度设计要点

## 查看方式

这些 Markdown 文件可以在支持 Mermaid 的环境中直接渲染：

1. **GitHub/GitLab** - 自动渲染 Mermaid 图表
2. **VS Code** - 安装 Mermaid 插件预览
3. **Typora/Obsidian** - 原生支持 Mermaid
4. **在线工具** - [Mermaid Live Editor](https://mermaid.live/)

## 相关设计文档

- [Load-Use 冒险修复设计](superpowers/specs/2026-04-12-load-use-hazard-fix-design.md) - 详细设计规范
- [嵌入式 OS 路线图](roadmap-embedded-os.md) - 未来扩展计划

---

*创建日期: 2026-04-12*