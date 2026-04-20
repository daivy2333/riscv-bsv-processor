# 项目调试经验：棘手问题记录

本文档记录项目开发过程中遇到的特别难以调试和解决的问题，供后续参考和学习。

---

## 问题 1：分支预测与前递交互导致死循环

**日期**：2026-04-18

**现象**：loop_test.s 和 pipeline_test.s 超时，但禁用分支预测后测试通过。

**调试时长**：约 4 小时

### 根因分析

这是一个多因素交织的问题，表面看起来是前递时机问题，实际上是分支预测失败处理缺失：

1. **fetchStage 跳过分支指令**
   - 当 BHT/BTB 预测"taken"时，旧实现直接用预测目标作为取指地址
   - 这导致分支指令本身被跳过，流水线直接从预测目标取指
   - 看起来像是"前递读到旧值"，实际是取了错误路径的指令

2. **预测信息丢失**
   - IF_ID_Packet 有 `predicted_taken` 字段
   - 但 ID 阶段没有传递到 ID_EX_Packet
   - executeStage 无法知道分支是否被预测，无法检测预测失败

3. **预测失败处理缺失**
   - 当预测"taken"但实际"not taken"时，没有冲刷流水线
   - 错误路径指令继续执行，导致死循环

### 调试方法

1. **逐步排除法**
   - 先禁用分支预测 → 测试通过 → 排除前递问题
   - 确认问题在预测而非前递

2. **周期级 trace**
   - 添加详细的 cycle-level debug 输出
   - 观察 `predicted_taken` 和 `branch_taken` 的对比
   - 发现预测失败后 PC 没有重定向

3. **关键发现**
   ```
   C26: BRANCH PC=80000014, op1=00000000, taken=0
   但 PC 继续从 80000010 取指（预测目标），而非顺序地址 80000018
   ```

### 解决方案

```bsv
// 1. fetchStage：预测不改变当前取指地址
rule fetchStage (...);
    Addr fetchPC = pcReg;  // 当前周期取原地址
    Bool take_prediction = False;
    Addr prediction_target = 0;

    // 预测只影响下一周期 PC
    if (!branch_flush_done && !no_pc_update) begin
        if (btb_hit && bht_predict) begin
            take_prediction = True;
            prediction_target = target;
        end
    end

    // 当前周期仍取 fetchPC 的指令
    Word instr = imem[fetchPC[11:2]];

    // 下一周期 PC 由预测决定
    if (take_prediction)
        pcReg <= prediction_target;
    else
        pcReg <= pcReg + 4;
endrule

// 2. ID_EX_Packet 添加预测字段
typedef struct {
    ...
    Bool predicted_taken;
    Addr predicted_target;
} ID_EX_Packet ...;

// 3. executeStage 检测预测失败
Bool mispredicted = pkt.is_branch && (pkt.predicted_taken != branch_taken);

if (mispredicted) begin
    pcReg <= pkt.pc + 4;  // 重定向到顺序地址
    branch_flush <= True;
    if2id.clear;
    id2ex.clear;
end
```

### 经验教训

1. **不要跳过当前指令**
   - 分支预测应该"预测下一周期的行为"，而不是"跳过当前周期"
   - 当前周期的分支指令必须正常进入流水线

2. **预测信息必须完整传递**
   - 预测决策点（IF）和判断点（EX）之间隔着多个阶段
   - 必须在 pipeline packet 中携带预测信息

3. **冲刷恢复期间禁用预测**
   - 冲刷后的几个周期内，BHT/BTB 可能基于错误路径的指令地址
   - 应该等到 flush 完成后再恢复预测

---

## 问题 2：BSV 规则调度与前递时机

**日期**：2026-04-18（早期调试）

**现象**：理论上 MEM→EX 前递应该工作，但实际读到旧值。

### BSV 技术限制

| 特性 | 行为 | 对流水线的影响 |
|------|------|----------------|
| `mkReg` 写入 | 规则结束时生效 | 同规则内读取是旧值 |
| `mkFIFO` enq/deq | 规则结束时生效 | 同周期 `first` 是旧值 |
| 规则执行顺序 | 编译器决定 | 无法保证 memoryStage 在 executeStage 之前 |

### 尝试的方案

| 方案 | 结果 |
|------|------|
| `descending_urgency` | 规则调度循环，executeStage 无法执行 |
| `RWire` | Predicate 过于复杂，规则无法执行 |
| 从 WB FIFO 读取 | 与 writebackStage 冲突 |

### 最终方案

使用 FIFO 的 `.first` 方法直接读取，配合正确的优先级：

```bsv
// MEM→EX 前递（最高优先级）
// 注意：ex2mem.first 在同周期 memoryStage 执行后更新
// 但 BSV 允许在同一个规则内读取 first（不会竞争）
if (ex2mem.notEmpty && ex2mem.first.write_reg && !ex2mem.first.is_load ...)
    op1 = ex2mem.first.alu_result;
```

**关键点**：实际前递不是问题的根因，真正的问题是分支预测。

### 经验教训

1. **不要过早归因**
   - 看到"读到旧值"容易想到"前递时机问题"
   - 但可能实际是取指地址错误，根本没执行到那条指令

2. **最小化假设**
   - 先排除最简单的可能（禁用预测）
   - 再考虑复杂的架构重构

---

## 问题 3：WB 前递双缓冲写入时机

**日期**：阶段 2

**现象**：WB 前递的第一个周期数据不可用。

### 根因

`wb_forward_data0 <= wb_data` 在 writebackStage 结束时生效，同周期的 executeStage 读取的是旧值。

### 解决方案

双缓冲机制：

```bsv
// WB 前递历史（保存最近两个周期）
Reg#(Word) wb_forward_data0 <- mkReg(0);
Reg#(Word) wb_forward_data1 <- mkReg(0);

// 每周期更新
wb_forward_data1 <= wb_forward_data0;  // 两周期前
wb_forward_data0 <= wb_data;           // 上一周期
```

前递优先级：

```
MEM→EX（最高） → WB→EX（中） → WB History（低） → RegFile
```

---

## 问题 4：wb_forward_valid0 写入 x0 寄存器

**日期**：阶段 4

**现象**：前递错误地匹配到 x0 寄存器（硬连线为 0）。

### 根因

```bsv
// 错误代码
wb_forward_valid0 <= pkt.write_reg;  // 不检查 rd != 0
```

x0 寄存器虽然 `write_reg=True`，但实际不应写入，不应参与前递。

### 解决方案

```bsv
// 正确代码
wb_forward_valid0 <= pkt.write_reg && pkt.rd != 0;
```

---

## 问题 5：BSV 规则调度死锁（TestBench 与 SOC 冲突）

**日期**：2026-04-19

**现象**：仿真超时，`done` 信号始终为 0，`tohost_value=1` 已写入但 TestBench 检测不到。

**调试时长**：约 2 小时

### 根因分析

BSV 规则调度冲突导致死锁：

1. **stepSimulation 规则阻止 handle_mem_req**
   - TestBench 的 `stepSimulation` 规则读取 `soc.tohostValue()`
   - SOC 的 `handle_mem_req` 规则写入 `soc_dmem_tohost_value_reg`
   - BSC 生成 `!WILL_FIRE_RL_stepSimulation` 作为 handle_mem_req 的条件
   - 导致内存操作被阻止，tohost 永远无法写入

2. **checkDone 规则 never fire**
   - `checkDone` 读取 `soc.testDone()`（调用 `tohost_written_reg`）
   - `countCycles` 也读取 `dumpDone` 并写入 `cycleCount`
   - 规则间读写冲突，BSC 优化掉 checkDone 的 enable 信号
   - Verilog 生成 `programDone$EN = 1'b0 && ...`

### 调试方法

1. **Verilator 信号追踪**
   - 检查 `WILL_FIRE_RL_stepSimulation` 和 `tohost_written_reg`
   - 发现 stepSimulation 周期执行，但 tohost_written_reg 始终为 0
   - 内存写入被阻止

2. **Verilog 代码分析**
   ```verilog
   // handle_mem_req 条件中有 !WILL_FIRE_RL_stepSimulation
   assign MUX_soc_dmem_tohost_value$write_1__SEL_1 =
          !WILL_FIRE_RL_stepSimulation && soc_core_current_mem_req[69] ...
   
   // checkDone enable 被优化为 0
   assign programDone$EN = 1'b0 && (soc_dmem_tohost_written || ...)
   ```

### 解决方案

使用 `descending_urgency` 属性调整规则优先级：

```bsv
(* descending_urgency = "checkCompletion, countCycles" *)
rule countCycles (programLoaded && !dumpDone);
    cycleCount <= cycleCount + 1;
    if (cycleCount >= 100000) begin
        $display("WARNING: Timeout at cycle %0d", cycleCount);
        dumpDone <= True;
    end
endrule

(* descending_urgency = "checkCompletion, countCycles" *)
rule checkCompletion (programLoaded && !dumpDone && soc.tohostValue() != 0);
    $display("\n====================================");
    if (soc.tohostValue() == 1) begin
        $display("  Test Results: PASSED");
    end else begin
        $display("  Test Results: FAILED (tohost=0x%x)", soc.tohostValue());
    end
    $display("====================================");
    $display("Cycles: %0d", cycleCount);
    dumpDone <= True;
endrule
```

同时简化 DMem，只使用寄存器而非 Wire：

```bsv
// 移除 Wire，避免读写冲突
Reg#(Bool) tohost_written_reg <- mkReg(False);
Reg#(Word) tohost_value_reg <- mkReg(0);
```

### 经验教训

1. **Wire 信号会引发规则冲突**
   - Wire 在同周期可读写，BSC 无法确定执行顺序
   - 对跨模块的状态信号，应使用 Reg

2. **descending_urgency 是关键**
   - BSV 默认按规则定义顺序调度，可能导致死锁
   - 使用属性显式指定优先级

3. **检查 Verilog 输出**
   - 当规则"never fire"时，检查生成的 enable 信号
   - `1'b0 &&` 表示规则条件被优化掉

---

## 问题 6：控制流重定向协议缺失导致死循环

**日期**：2026-04-20

**现象**：simple_branch_test 和 simple_loop 测试失败，程序卡在 `jal zero, end` 无限循环处。

**调试时长**：约 2 小时

### 根因分析

这是**测试程序不完整**和**架构缺陷**的组合问题：

#### 1. 测试程序缺少 tohost 写入

测试程序在 `end:` 标签处使用 `jal zero, end` 无限循环，但没有写入 tohost (0x80001000)。

**表现**：程序逻辑正确执行（x7=1），但测试框架无法检测完成。

#### 2. 控制流协议架构缺陷

原有实现使用三个重叠的状态标志：
- `branch_flush` - 分支冲刷标志
- `branch_flush_done` - 冲刷完成标志
- `no_pc_update` - 阻止 PC 更新

**问题**：`no_pc_update` 没有完整的清除协议：

```bsv
if (branch_taken) begin
    // JAL 总是进入这个分支
    no_pc_update <= True;  // 设置 True
    // ... 但永远不清除！
end else begin
    // 只有"正常执行"才清除
    no_pc_update <= False;
end
```

**结果**：JAL 指令（无条件跳转）永远设置 `no_pc_update=True`，导致 fetchStage 永久暂停。

### 调试方法

#### 1. Trace 分析

```
WB_COMMIT: pc=80000018 rd= 0 data=8000001c write=1
C25: PC=80000018 wait=0 stall=0 b_flush=0 b_done=1 x7=1
C26: PC=80000018 wait=0 stall=0 b_flush=0 b_done=0 x7=1
... PC 永久停在 0x80000018
```

观察：PC 停止更新，但 x7=1 说明程序逻辑正确执行。

#### 2. 架构审查

分析控制流重定向的职责边界：

| 标志 | 原职责 | 问题 |
|------|--------|------|
| `branch_flush` | 冲刷流水线 | 无清除机制 |
| `branch_flush_done` | 冲刷后暂停 | 与 `no_pc_update` 重叠 |
| `no_pc_update` | 阻止 PC 更新 | 无清除协议 |

### 解决方案

#### 方案 A：最小修复

删除冗余的 `no_pc_update`，统一使用 `branch_flush_done`。

#### 方案 B：架构重构

收敛为单一控制流重定向协议：

```bsv
// 统一状态
Reg#(Bool) redirect_pending <- mkReg(False);
Reg#(Addr) redirect_target <- mkReg(0);
Reg#(Bit#(4)) redirect_reason <- mkReg(0);

// redirect_reason 编码
// 0 = NONE, 1 = BRANCH, 2 = JAL, 3 = TRAP, 4 = MRET, 5 = INTERRUPT
```

**协议流程**：

```
EX/WB 检测重定向需求
    ↓ 设置 redirect_pending + target + reason
    ↓ 清空流水段
fetchStage 看到 redirect_pending
    ↓ 等待（条件: !redirect_pending）
consumeRedirect 规则
    ↓ 清除 redirect_pending
    ↓ 下一周期正常取指
```

**统一处理**：
- 条件分支 (taken/mispredict)
- JAL/JALR 无条件跳转
- Trap (ECALL/EBREAK)
- MRET 返回
- WB 阶段中断

### 经验教训

1. **测试程序必须完整**
   - 无限循环必须配合 tohost 写入
   - 否则测试框架无法检测完成

2. **状态机必须有完整协议**
   - 每个状态标志都要有"何时设置"和"何时清除"
   - 职责重叠会导致维护困难

3. **统一协议优于分散标志**
   - 多个重叠标志是架构坏味道
   - 应收敛为单一控制流协议

4. **区分 architectural_commit vs instr_write**
   - Trace 中 `write_reg=1` 但 `rd=0` 只是语义不够精确
   - 实际写入条件是 `write_reg && rd != 0`

---

## 总结：调试方法论

### 1. 周期级 trace 是最强大的工具

```bsv
$display("REDIRECT_REQ: pc=%h target=%h reason=%d", pc, target, reason);
$display("FETCH_PC: old=%h new=%h predicted=%d", old, new, predicted);
$display("PIPE_FLUSH: stages");
$display("REDIRECT_CONSUMED: target=%h reason=%d", target, reason);
```

### 2. 架构审查优于补丁式修复

- 先判断是"实现 bug"还是"协议/架构 bug"
- 优先从职责边界不清角度分析
- 给出最小正确架构，再讨论优化

### 3. 检查"跳过"假设

- 每个控制流改变都要有完整协议
- "何时阻塞"、"何时恢复"必须明确

### 4. 测试程序完整性

- 必须包含 tohost 写入
- 无限循环必须配合结束标记

### 5. BSV 规则调度

- Wire 信号会引发跨规则冲突，优先使用 Reg
- 使用 `descending_urgency` 属性解决死锁
- 检查 Verilog 输出中的 enable 信号

---

*更新日期: 2026-04-20*