# 嵌入式操作系统支持路线图

日期：2026-04-18（更新）

## 目标

支持 FreeRTOS/uClinux（无 MMU），可运行简单嵌入式操作系统。

## 开发阶段

### 阶段 1-3：已完成

| 阶段 | 内容 | 状态 |
|------|------|------|
| 阶段 1 | 五级流水线、数据前递、分支预测 | ✓ 完成 |
| 阶段 2 | RV32I 全指令、Load-Use 冒险、WB 前递双缓冲 | ✓ 完成 |
| 阶段 3 | 特权级架构、CSR、陷阱处理 | ✓ 完成 |

### 阶段 4：分支预测修复（已完成）

**问题**：loop_test/pipeline_test 超时

**根因**：分支预测失败时，流水线没有正确冲刷错误路径
- BHT/BTB 预测跳转时，fetchStage 直接从预测目标取指，跳过了分支指令本身
- ID_EX_Packet 没有携带预测信息，executeStage 无法检测预测失败
- 预测失败时没有重定向 PC 到顺序地址

**修复方案**：
1. fetchStage：预测只影响下一周期 PC，当前周期仍取原地址指令
2. ID_EX_Packet：添加 `predicted_taken` 和 `predicted_target` 字段
3. executeStage：检测 `mispredicted` 并正确冲刷
4. 冲刷恢复期间禁用预测

**修复结果**：
| 测试 | 修复前 | 修复后 |
|------|--------|--------|
| loop_test.s | TIMEOUT | PASSED (71 cycles) |
| pipeline_test.s | TIMEOUT | PASSED (65 cycles) |

### 阶段 5-7：待开始

| 阶段 | 内容 | 新增文件 |
|------|------|----------|
| 阶段 5 | PLIC 中断控制器 | src/peripheral/PLIC.bsv |
| 阶段 6 | UART 控制台 | src/peripheral/UART.bsv |
| 阶段 7 | 内存扩展（16MB RAM） | - |

## 里程碑

| 里程碑 | 状态 | 目标 |
|--------|------|------|
| M1 | ✓ 完成 | RV32I 全指令支持 |
| M2 | ✓ 完成 | 特权级架构完成 |
| M3 | ✓ 完成 | 分支预测修复完成 |
| M4 | ⏳ 待开始 | PLIC/外设完成 |
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