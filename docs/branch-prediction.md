# 分支预测机制图解

本处理器采用动态分支预测技术，包含分支历史表 (BHT) 和分支目标缓冲区 (BTB)。

## 1. 分支预测组件总览

```mermaid
flowchart TB
    subgraph IF_Stage["IF 阶段"]
        PC[当前 PC]
        BHT_Query[BHT 查询<br/>是否预测跳转]
        BTB_Query[BTB 查询<br/>跳转目标地址]

        PC -->|"PC bits 11-2"| BHT_Query
        PC -->|"PC bits 11-2"| BTB_Query

        BHT_Query -->|"taken/not taken"| Decision
        BTB_Query -->|"Valid/Invalid"| Decision

        Decision{预测跳转?}
        Decision -->|"BHT: taken<br/>BTB: valid"| PredictedPC[使用预测目标]
        Decision -->|否| SequentialPC[PC + 4]
    end

    subgraph BHT["分支历史表 (BHT)"]
        BHT_Table["64 条目<br/>每条目 2 位饱和计数器"]
        BHT_Update["EX 阶段更新<br/>实际分支结果"]
    end

    subgraph BTB["分支目标缓冲区 (BTB)"]
        BTB_Table["64 条目<br/>branch_pc + target_addr"]
        BTB_Update["EX 阶段更新<br/>分支目标地址"]
    end

    PredictedPC -->|"预测 PC"| NextIF[下一条指令取指]
    SequentialPC -->|"顺序 PC"| NextIF

    EX_Stage[EX 阶段] -->|"实际结果"| BHT_Update
    EX_Stage -->|"目标地址"| BTB_Update
    BHT_Update -->|"更新状态"| BHT_Table
    BTB_Update -->|"更新条目"| BTB_Table
```

## 2. BHT - 2位饱和计数器

```mermaid
stateDiagram-v2
    [*] --> S00: 初始状态 (强不跳转)

    S00[00: 强不跳转] --> S01: 实际跳转
    S00 --> S00: 实际不跳转

    S01[01: 弱不跳转] --> S10: 实际跳转
    S01 --> S00: 实际不跳转

    S10[10: 弱跳转] --> S11: 实际跳转
    S10 --> S01: 实际不跳转

    S11[11: 强跳转] --> S11: 实际跳转
    S11 --> S10: 实际不跳转

    note right of S00
        预测: not taken
        置信度: 高
    end note

    note right of S01
        预测: not taken
        置信度: 低
    end note

    note right of S10
        预测: taken
        置信度: 低
    end note

    note right of S11
        预测: taken
        置信度: 高
    end note
```

### 预测逻辑

```bsv
// Types.bsv:241-243
function Bool bhtPredict(BHTState state);
    return (state >= 2'b10);  // 10, 11 预测跳转
endfunction
```

| 状态 | 值 | 预测结果 | 置信度 |
|------|-----|----------|--------|
| S00 | 00 | not taken | 高 |
| S01 | 01 | not taken | 低 |
| S10 | 10 | taken | 低 |
| S11 | 11 | taken | 高 |

### 状态更新逻辑

```bsv
// Types.bsv:246-254
function BHTState bhtUpdate(BHTState state, Bool taken);
    case (state)
        2'b00: return taken ? 2'b01 : 2'b00;
        2'b01: return taken ? 2'b10 : 2'b00;
        2'b10: return taken ? 2'b11 : 2'b01;
        2'b11: return taken ? 2'b11 : 2'b10;
        default: return 2'b01;
    endcase
endfunction
```

## 3. BTB - 分支目标缓冲区

```mermaid
flowchart TB
    subgraph BTB_Entry["BTB 条目结构"]
        BranchPC["branch_pc<br/>分支指令地址<br/>(用于匹配)"]
        TargetAddr["target_addr<br/>分支目标地址"]
        Valid["valid<br/>条目有效性"]
    end

    subgraph Lookup["查询流程"]
        QueryPC[查询 PC]
        CheckValid{valid == True?}
        CheckMatch{branch_pc == PC?}

        QueryPC --> CheckValid
        CheckValid -->|是| CheckMatch
        CheckValid -->|否| NoHit[未命中]
        CheckMatch -->|是| Hit[命中<br/>返回 target_addr]
        CheckMatch -->|否| NoHit
    end

    subgraph Update["更新流程"]
        ExPC[EX 阶段 PC]
        ExTarget[实际目标地址]
        ExTaken{分支实际跳转?}

        ExPC -->|"索引"| BTB_Array[BTB 数组]
        ExTarget -->|"写入"| BTB_Array
        ExTaken -->|"设置 valid"| BTB_Array

        ExTaken -->|是| SetValid[valid = True]
        ExTaken -->|否| SetInvalid[valid = False]
    end

    BTB_Entry --> BTB_Array
```

### BTB 条目结构

```bsv
// Types.bsv:160-164
typedef struct {
    Addr    branch_pc;      // 分支指令地址（用于匹配）
    Addr    target_addr;    // 分支目标地址
    Bool    valid;          // 条目是否有效
} BTBEntry deriving (Bits, Eq, FShow);
```

## 4. 预测流程时序图

```mermaid
sequenceDiagram
    participant IF as IF 阶段
    participant BHT as BHT
    participant BTB as BTB
    participant EX as EX 阂段
    participant Pipeline as 流水线

    Note over IF: 取指 beq x1, x2, target
    IF->>BHT: predict(PC)
    BHT->>IF: taken (状态 10)
    IF->>BTB: lookup(PC)
    BTB->>IF: Valid target_addr
    IF->>IF: 使用预测 PC 取指

    Note over IF: 预测跳转，取指 target 地址
    IF->>Pipeline: 发送预测信息

    Note over EX: 实际分支判断
    EX->>EX: 比较 x1, x2
    EX->>EX: 实际结果: taken

    EX->>BHT: update(PC, taken)
    Note over BHT: 状态 10 → 11

    EX->>BTB: update(PC, target)
    Note over BTB: 更新目标地址

    Note over EX: 预测正确，无惩罚
```

## 5. 预测失败处理

```mermaid
sequenceDiagram
    participant IF as IF 阶段
    participant BHT as BHT
    participant BTB as BTB
    participant EX as EX 阂段
    participant Pipeline as 流水线

    Note over IF: 取指 beq x1, x2, target
    IF->>BHT: predict(PC)
    BHT->>IF: taken (状态 11)
    IF->>BTB: lookup(PC)
    BTB->>IF: Valid target_addr
    IF->>Pipeline: 预测跳转，后续指令进入流水线

    Note over EX: 实际分支判断
    EX->>EX: 比较 x1, x2
    EX->>EX: 实际结果: NOT taken!

    EX->>BHT: update(PC, not_taken)
    Note over BHT: 状态 11 → 10

    EX->>BTB: update(PC, target)
    Note over BTB: valid 保持 True

    Note over Pipeline: 预测失败！
    Note over Pipeline: 清空流水线中错误指令
    Note over EX: 恢复正确 PC

    Note over IF: 从正确地址重新取指
```

### 预测失败惩罚

| 场景 | 惩罚周期数 | 说明 |
|------|------------|------|
| 预测跳转，实际不跳转 | 2-3 周期 | 清空已取的错误指令 |
| 预测不跳转，实际跳转 | 2-3 周期 | 从目标地址重新取指 |
| BTB 未命中 | 1 周期 | 无法预测目标，等待 EX 计算 |

## 6. 索引方式

```mermaid
flowchart LR
    subgraph PC_Address["PC 地址结构"]
        PC_Bits["PC (32位)"]
        PC_Index["PC bits 11-2<br/>10位索引"]
        PC_Tag["PC bits 31-12<br/>20位标签<br/>(未使用)"]
    end

    PC_Bits --> PC_Index
    PC_Bits --> PC_Tag

    PC_Index -->|"直接映射"| BHT_Entries["BHT 64 条目"]
    PC_Index -->|"直接映射"| BTB_Entries["BTB 64 条目"]

    note right of BHT_Entries
        简单直接映射
        可能存在冲突
        适用于小规模设计
    end note
```

**设计说明**：
- 使用 PC 的低 10 位作为索引（64 条目 × 4 字节/条目 = 256 字节对齐）
- 未使用标签比较，可能导致别名冲突
- 对于嵌入式处理器规模，简单方案足够

## 7. 分支类型处理

```mermaid
flowchart TB
    subgraph BranchTypes["分支指令类型"]
        Conditional["条件分支<br/>BEQ, BNE, BLT..."]
        JumpLink["跳转链接<br/>JAL"]
        JumpReg["寄存器跳转<br/>JALR"]
    end

    Conditional -->|"BHT + BTB"| Predict
    JumpLink -->|"BTB (总是跳转)"| Predict
    JumpReg -->|"目标需计算<br/>BTB 可缓存"| Predict

    subgraph Predict["预测处理"]
        BHT_Check{BHT 预测跳转?}
        BTB_Check{BTB 命中?}
        UsePredict[使用预测目标]
        UseSequential[顺序取指]

        BHT_Check -->|是| BTB_Check
        BHT_Check -->|否| UseSequential
        BTB_Check -->|是| UsePredict
        BTB_Check -->|否| UseSequential
    end

    subgraph EX_Update["EX 阶段更新"]
        ActualTaken[实际跳转结果]
        ActualTarget[实际目标地址]

        Conditional -->|"更新 BHT"| BHT_Update
        Conditional -->|"更新 BTB"| BTB_Update_Cond
        JumpLink -->|"更新 BTB"| BTB_Update_JAL
        JumpReg -->|"更新 BTB"| BTB_Update_JALR

        ActualTaken --> BHT_Update
        ActualTarget --> BTB_Update_Cond
        ActualTarget --> BTB_Update_JAL
        ActualTarget --> BTB_Update_JALR
    end
```

## 8. 预测准确率优化

```mermaid
flowchart TB
    subgraph Factors["影响准确率因素"]
        HistoryBits["历史位数<br/>当前: 2位"]
        Entries["条目数<br/>当前: 64"]
        Associativity["关联性<br/>当前: 直接映射"]
    end

    subgraph Improvements["优化方向"]
        MoreBits["增加历史位数<br/>→ 更精细预测"]
        MoreEntries["增加条目数<br/>→ 减少冲突"]
        SetAssoc["组关联<br/>→ 减少别名"]
        GlobalHistory["全局历史<br/>→ 相关性预测"]
    end

    Factors --> Improvements

    note right of Improvements
        当前设计适合嵌入式处理器
        准确率约 85-90%
        进一步优化会增加硬件复杂度
    end note
```

## 9. 代码实现

### IF 阶段预测查询

```bsv
// Core.bsv:75-103
rule fetchStage (programLoaded && state == RUNNING && !stall_load_use && !branch_flush);
    Addr fetchPC = pcReg;
    Bool take_prediction = False;
    Addr prediction_target = 0;

    Maybe#(Addr) btb_hit = btb.lookup(fetchPC);
    Bool bht_predict = bht.predict(fetchPC);

    if (btb_hit matches tagged Valid .target &&& bht_predict) begin
        take_prediction = True;
        prediction_target = target;
        fetchPC = target;
    end
    // ...
endrule
```

### EX 阶段更新

```bsv
// Core.bsv:251-268
// 更新BHT和BTB
Bool btb_update_valid = (pkt.is_jump) || (pkt.is_branch && branch_taken);
btb.update(pkt.pc, actual_target, btb_update_valid);
if (pkt.is_branch)
    bht.update(pkt.pc, branch_taken);

// 分支/跳转执行
if (branch_taken) begin
    pcReg <= actual_target;
    branch_flush <= True;
    no_pc_update <= True;
    if2id.clear;
    id2ex.clear;
end
```

**更新策略**：
- JAL/JALR：总是跳转，更新 BTB
- 条件分支：仅在实际跳转时更新 BTB
- BHT 仅对条件分支更新（JAL 不需要历史预测）

**分支冲刷**：
- 分支跳转时设置 `branch_flush` 和 `no_pc_update` 标志
- 阻止 IF 阶段在跳转后继续取指