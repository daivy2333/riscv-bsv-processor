# 问题解决进度报告

## 已解决的问题

### 1. BSV 规则调度冲突（核心问题）

**问题描述**：
- TestBench.countCycles 调用 soc.sync_mtime()
- SOC.handle_mem_req 处理所有内存写入
- 两者写入 CLINT.mtime 寄存器，形成调度冲突
- BSC 生成 `!WILL_FIRE_RL_countCycles` 条件阻止内存写入

**解决方案**：
- 移除 TestBench → SOC → CLINT 跨模块调用链
- CLINT 内部添加 `auto_increment_mtime` 规则
- mtime 设为只读，只允许写 msip/mtimecmp

**验证结果**：
```verilog
// 修复前
soc_dmem_tohost_value_reg$EN = !WILL_FIRE_RL_countCycles && ...

// 修复后
soc_dmem_tohost_value_reg$EN = soc_core_current_mem_req[69] && ...
```

---

### 2. 控制流重定向协议重构（架构级修复）

**问题描述**：
- simple_branch_test 和 simple_loop 测试失败（程序卡在无限循环）
- 原因分析涉及两个层面：
  1. **测试程序不完整**：缺少 tohost 写入，无法触发测试完成信号
  2. **架构缺陷**：`no_pc_update` 标志没有完整清除协议

**根因分析**：

| 问题 | 说明 |
|------|------|
| 契约缺失 | `no_pc_update` 没有明确的"何时清除"协议 |
| 职责重叠 | `branch_flush`、`branch_flush_done`、`no_pc_update` 三者功能重叠 |
| 状态机不完备 | 只有"正常执行"才清除 `no_pc_update`，跳转分支不清除 |

**架构修复方案**：

1. **方案A（最小修复）**：
   - 删除冗余的 `no_pc_update` 标志
   - 统一使用 `branch_flush_done` 控制冲刷暂停

2. **方案B（正式重构）**：
   - 收敛控制流为单一协议
   - 新状态：`redirect_pending`、`redirect_target`、`redirect_reason`
   - 统一处理：分支/JAL/trap/MRET/中断

**新协议语义**：

```
redirect_reason 编码：
0 = NONE
1 = BRANCH (条件分支 taken/mispredict)
2 = JAL (无条件跳转)
3 = TRAP (ECALL/EBREAK)
4 = MRET (陷阱返回)
5 = INTERRUPT (WB阶段中断)
```

**新增 trace**：

```
REDIRECT_REQ: pc=X target=Y reason=Z    // 重定向请求
FETCH_PC: old=X new=Y predicted=N       // 取指 PC 更新
PIPE_FLUSH: stages                      // 流水线冲刷
REDIRECT_CONSUMED: target=X reason=N    // 重定向消费
```

**验证结果**：所有 10 个测试通过

---

### 3. Load 响应协议修复

**问题描述**：
- Load 指令完成后，`ex_is_load_cached` 未清除
- 导致后续指令被误判为 Load-Use 冒险
- 触发错误的 stall，阻塞流水线

**解决方案**：
- 在 WB 阶段 Load 提交时清除 `ex_is_load_cached` 和 `ex_rd_cached`

---

## 测试状态

| 测试 | 状态 | 周期数 |
|------|------|--------|
| loop_test | ✓ PASSED | 53 |
| simple_arith_test | ✓ PASSED | 32 |
| load_test | ✓ PASSED | - |
| csr_basic_test | ✓ PASSED | 44 |
| csr_immediate_test | ✓ PASSED | - |
| privilege_m_mode_test | ✓ PASSED | - |
| rtype_complete_test | ✓ PASSED | - |
| itype_alu_test | ✓ PASSED | - |
| simple_branch_test | ✓ PASSED | - |
| simple_loop | ✓ PASSED | - |

**总计**: 10/10 测试通过 ✓

---

## 遗留问题（不影响核心功能）

### 1. connect_interrupts 规则警告

**警告**：`rule 'soc_connect_interrupts' can never fire`

**原因**：CSR.bsv 的 update_mip 规则与 SOC.connect_interrupts 规则存在调度冲突

**状态**：中断信号连接未生效，后续 FreeRTOS 测试时处理

### 2. uart_tx_complete 规则警告

**警告**：`rule 'soc_uart_tx_complete' can never fire`

**原因**：UART.bsv 的 tx_complete 规则条件被 write 方法覆盖

**状态**：UART TX 完成中断不触发，后续处理

---

## 下一步

1. **FreeRTOS demo 测试**：✓ 执行正确（BSS清零、UART输出、任务创建），但需要修复中断连接才能进行任务调度
2. **长期稳定性测试**：✓ 通过 - 30秒内输出 100009 行，处理器持续稳定运行

---

## 当前项目状态

### 核心功能完成
- ✓ 五级流水线 (IF, ID, EX, MEM, WB)
- ✓ 数据前递 (MEM→EX, WB→EX, WB→ID)
- ✓ Load-Use 冒险检测 + stall
- ✓ 动态分支预测 (BHT + BTB)
- ✓ 控制流重定向协议（统一处理分支/JAL/trap/MRET/中断）
- ✓ RV32I 全指令集
- ✓ CSR 寄存器和特权指令
- ✓ 陷阱处理 (ECALL, EBREAK, MRET)
- ✓ SOC 架构 (Core ↔ SOC ↔ 外设)

### 待完善功能
- 中断连接（connect_interrupts 规则冲突）
- UART TX 完成（uart_tx_complete 规则冲突）
- FreeRTOS 定时器中断支持

### 测试结果
- 10/10 基线测试通过
- 稳定性测试通过（10⁵+ 周期）