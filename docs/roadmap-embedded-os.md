# 嵌入式操作系统支持路线图

日期：2026-04-19（更新）

## 目标

支持 FreeRTOS/uClinux（无 MMU），可运行简单嵌入式操作系统。

## 开发阶段

### 阶段 1-4：已完成

| 阶段 | 内容 | 状态 |
|------|------|------|
| 阶段 1 | 五级流水线、数据前递、分支预测 | ✓ 完成 |
| 阶段 2 | RV32I 全指令、Load-Use 冒险、WB 前递双缓冲 | ✓ 完成 |
| 阶段 3 | 特权级架构、CSR、陷阱处理 | ✓ 完成 |
| 阶段 4 | 分支预测失败修复、测试通过 | ✓ 完成 |

### 阶段 5：中断框架（已完成）

**内容**：
- CLINT 定时器（mtime, mtimecmp 内存映射）
- PLIC 中断控制器（8 IRQ sources）
- UART 控制台框架
- 中断信号连接（Core ↔ SOC ↔ 外设）
- 内存请求/响应接口（MemReq/MemResp）

**新增文件**：
- src/peripheral/CLINT.bsv
- src/peripheral/PLIC.bsv
- src/peripheral/UART.bsv
- src/soc/SOC.bsv（重构）

**关键修复**：
- BSV 规则调度冲突：使用 `descending_urgency` 属性解决 TestBench 规则死锁
- DMem Wire 信号改为寄存器，避免读写冲突

**修复结果**：
- 仿真正常完成，32 cycles
- Test Results: PASSED

### 阶段 6：FreeRTOS 支持（待开始）

| 任务 | 内容 |
|------|------|
| 内存扩展 | 16MB RAM，支持操作系统加载 |
| 中断向量 | mtvec 配置，中断跳转实现 |
| 栈初始化 | MSP 设置，启动代码 |
| FreeRTOS | 首次启动测试 |

## 里程碑

| 里程碑 | 状态 | 目标 |
|--------|------|------|
| M1 | ✓ 完成 | RV32I 全指令支持 |
| M2 | ✓ 完成 | 特权级架构完成 |
| M3 | ✓ 完成 | 分支预测修复完成 |
| M4 | ✓ 完成 | 中断框架完成 |
| M5 | ⏳ 待开始 | 首次启动 FreeRTOS |

## 测试状态

| 测试 | 状态 | 说明 |
|------|------|------|
| simple_arith_test.s | ✓ PASSED | 基本算术 + li 指令 |
| load_test.s | ✓ PASSED | Load-Use 冒险 |
| csr_basic_test.s | ✓ PASSED | CSR 读写 |
| privilege_m_mode_test.s | ✓ PASSED | M-mode CSR 操作 |
| csr_immediate_test.s | ✓ PASSED | CSR 立即数指令 |
| loop_test.s | ✓ PASSED | 循环分支（71 cycles） |
| pipeline_test.s | ✓ PASSED | 完整流水线（65 cycles） |
| rtype_complete_test.s | ✓ PASSED | R-Type 全指令 |
| itype_alu_test.s | ✓ PASSED | I-Type ALU |
| simple_branch_test.s | ✓ PASSED | 分支预测 |
| simple_loop.s | ✓ PASSED | 循环计数 |

**总计**: 11 个测试，全部通过