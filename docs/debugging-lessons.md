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

## 总结：调试方法论

### 1. 周期级 trace 是最强大的工具

```bsv
$display("Cycle %0d: PC=%h, op1=%h, op2=%h, taken=%b, predicted=%b",
         cycleCount, pkt.pc, op1, op2, branch_taken, pkt.predicted_taken);
```

每个关键信号都要打印，不要省略。

### 2. 逐步排除法

- 禁用可疑功能 → 测试是否通过 → 确认问题范围
- 不要一次性改变多个变量

### 3. 检查"跳过"假设

- 流水线中每个指令都必须进入所有阶段
- 不要假设某个阶段可以跳过

### 4. 预测信息完整性

- 决策点和执行点之间要传递完整信息
- pipeline packet 结构要仔细设计

---

*更新日期: 2026-04-18*