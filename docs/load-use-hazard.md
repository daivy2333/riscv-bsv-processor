# Load-Use 冒险检测图解

Load-Use 冒险是指 Load 指令后紧跟使用其结果的指令，由于 Load 数据在 MEM 阶段才从内存读取，无法通过正常前递解决，需要流水线停顿。

## 1. 冒险检测位置

```mermaid
flowchart TB
    subgraph Pipeline["五级流水线"]
        IF[IF 阶段]
        ID[ID 阶段<br/>⚠️ 冒险检测点]
        EX[EX 阶段]
        MEM[MEM 阶段<br/>Load 数据读取]
        WB[WB 阶段<br/>Load 数据可用]
        IF --> ID --> EX --> MEM --> WB
    end

    subgraph HazardDetection["冒险检测逻辑"]
        CheckLoad{EX/MEM 阶段<br/>有 Load 指令?}
        CheckRs1{ID 阶段<br/>使用 Load 的 rd?}
        CheckRs2{ID 阶段<br/>使用 Load 的 rd?}

        EX -->|"ex2mem.first"| CheckLoad
        MEM -->|"ex2mem.first"| CheckLoad
        ID -->|"if2id.first"| CheckRs1
        ID -->|"if2id.first"| CheckRs2

        CheckLoad -->|是| CheckRs1
        CheckRs1 -->|是| Hazard[检测到冒险]
        CheckRs1 -->|否| CheckRs2
        CheckRs2 -->|是| Hazard
        CheckRs2 -->|否| NoHazard[无冒险]
    end

    Hazard --> Stall[停顿 ID 阶段]
    Hazard --> Bubble[插入气泡到 EX]
    NoHazard --> Normal[正常执行]
```

## 2. 冒险检测详细逻辑

```mermaid
flowchart TB
    Start["ID 阶段开始"] --> GetPkt["获取 if2id.first"]
    GetPkt --> Decode["解码得到 DecodedInstr"]
    Decode --> CheckEX{"检查 id2ex<br/>是否有 Load?"}

    CheckEX -->|"mem_op == MEM_READ<br/>& rd != 0"| CheckEXRs1
    CheckEX -->|否| CheckMEM

    CheckEXRs1{"use_rs1 &&<br/>rs1 == ex_rd?"}
    CheckEXRs1 -->|是| SetHazard1["load_use_hazard = True"]
    CheckEXRs1 -->|否| CheckEXRs2{"use_rs2 &&<br/>rs2 == ex_rd?"}
    CheckEXRs2 -->|是| SetHazard1
    CheckEXRs2 -->|否| CheckMEM

    CheckMEM{"检查 ex2mem<br/>是否有 Load?"}
    CheckMEM -->|"is_load && rd != 0"| CheckMEMRs1
    CheckMEM -->|否| NoHazard["无冒险"]

    CheckMEMRs1{"use_rs1 &&<br/>rs1 == mem_rd?"}
    CheckMEMRs1 -->|是| SetHazard2["load_use_hazard = True"]
    CheckMEMRs1 -->|否| CheckMEMRs2{"use_rs2 &&<br/>rs2 == mem_rd?"}
    CheckMEMRs2 -->|是| SetHazard2
    CheckMEMRs2 -->|否| NoHazard

    SetHazard1 --> Stall
    SetHazard2 --> Stall

    Stall["设置 stall_load_use = True<br/>设置 bubble_pending = True<br/>不 deq if2id"]
    NoHazard --> Normal["正常执行<br/>deq if2id<br/>enq id2ex"]
```

## 3. 停顿与气泡插入时序

```mermaid
gantt
    title Load-Use 冒险处理时序
    dateFormat X
    axisFormat 周期%s

    section lw x1, 0(x2)
    IF          :1, 1
    ID          :2, 2
    EX          :3, 3
    MEM         :4, 4
    WB          :5, 5

    section add x3, x1, x4
    IF          :2, 2
    ID (检测冒险) :3, 3
    ID (停顿)    :crit, 4, 4
    EX (气泡)   :crit, 5, 5
    EX          :6, 6

    section sub x5, x1, x6
    IF (暂停)   :crit, 3, 3
    IF (暂停)   :crit, 4, 4
    IF          :5, 5
    ID          :6, 6
```

**关键时间点**：
- 周期 3：`add` 在 ID 阶段检测到冒险，停顿
- 周期 4：ID 阶段继续停顿，等待 Load 数据
- 周期 5：Load 在 WB 写回数据，WB→EX 前递可用
- 周期 6：`add` 进入 EX 阶段，使用前递数据

## 4. 控制信号状态转换

```mermaid
stateDiagram-v2
    [*] --> Normal: 初始状态

    Normal --> DetectingHazard: ID 阶段开始
    DetectingHazard --> Normal: 无冒险
    DetectingHazard --> Stalling: 检测到 Load-Use

    Stalling --> InsertingBubble: 下个周期
    InsertingBubble --> Normal: 气泡插入完成

    note right of Normal
        stall_load_use = False
        bubble_pending = False
        IF/ID 正常运行
    end note

    note right of Stalling
        stall_load_use = True
        bubble_pending = True
        IF/ID 阶段暂停
        if2id 保留数据
    end note

    note right of InsertingBubble
        stall_load_use = False
        bubble_pending = True
        EX 阶段接收 NOP
        ID 阶段恢复
    end note
```

## 5. 气泡包内容

```mermaid
classDiagram
    class NOP_Packet {
        +Addr pc = 0
        +Word instruction = 0
        +Word rs1_val = 0
        +Word rs2_val = 0
        +Word imm = 0
        +Bit5 rs1 = 0
        +Bit5 rs2 = 0
        +Bit5 rd = 0
        +ALUOp alu_op = ALU_ADD
        +BranchCond branch_cond = BR_NONE
        +MemOp mem_op = MEM_NONE
        +Bool is_branch = False
        +Bool is_jump = False
        +Bool write_reg = False
        +Bool use_imm = False
    }

    note for NOP_Packet "气泡包不产生任何副作用：<br/>- 不写寄存器<br/>- 不访问内存<br/>- 不执行分支"
```

## 6. 检测条件详解

### use_rs1 / use_rs2 字段含义

```mermaid
flowchart LR
    subgraph Instructions["指令类型"]
        R["R-Type<br/>ADD, SUB...<br/>use_rs1 ✓ use_rs2 ✓"]
        I["I-Type<br/>ADDI, ANDI...<br/>use_rs1 ✓ use_rs2 ✗"]
        L["Load<br/>LW, LH...<br/>use_rs1 ✓ use_rs2 ✗"]
        S["Store<br/>SW, SH...<br/>use_rs1 ✓ use_rs2 ✓"]
        B["Branch<br/>BEQ, BNE...<br/>use_rs1 ✓ use_rs2 ✓"]
        U["U-Type<br/>LUI, AUIPC<br/>use_rs1 ✗ use_rs2 ✗"]
        J["Jump<br/>JAL, JALR<br/>JALR: use_rs1 ✓"]
    end
```

### 冒险检测示例

```asm
# 场景1: Load 后紧跟使用 rs1
lw x1, 0(x2)       # Load 到 x1
add x3, x1, x4     # 使用 x1 作为 rs1 → Load-Use 冒险!
                    # use_rs1=True, rs1=1, ex_rd=1 → 匹配

# 场景2: Load 后紧跟使用 rs2
lw x1, 0(x2)
add x3, x4, x1     # 使用 x1 作为 rs2 → Load-Use 冒险!
                    # use_rs2=True, rs2=1, ex_rd=1 → 匹配

# 场景3: Load 后紧跟不依赖的指令
lw x1, 0(x2)
add x3, x4, x5     # 不使用 x1 → 无冒险
                    # rs1=4, rs2=5, ex_rd=1 → 不匹配

# 场景4: Load x0 (特殊情况)
lw x0, 0(x2)       # Load 到 x0 (永远为0)
add x3, x0, x4     # 使用 x0 → 无冒险 (x0 不参与检测)
                    # ex_rd=0 → 不检测
```

## 7. 实现代码对照

```bsv
// Core.bsv 冒险检测逻辑 (行 104-123)
Bool load_use_hazard = False;

// 检查 EX 阶段 (id2ex) - Load 指令刚从 EX 进入 MEM
if (id2ex.notEmpty && id2ex.first.mem_op == MEM_READ && id2ex.first.rd != 0) begin
    if (dec.use_rs1 && dec.rs1 == id2ex.first.rd)
        load_use_hazard = True;
    if (dec.use_rs2 && dec.rs2 == id2ex.first.rd)
        load_use_hazard = True;
end

// 检查 MEM 阶段 (ex2mem) - Load 指令在 MEM 执行内存读取
if (ex2mem.notEmpty && ex2mem.first.is_load && ex2mem.first.rd != 0 && !load_use_hazard) begin
    if (dec.use_rs1 && dec.rs1 == ex2mem.first.rd)
        load_use_hazard = True;
    if (dec.use_rs2 && dec.rs2 == ex2mem.first.rd)
        load_use_hazard = True;
end

// 冒险处理 (行 125-151)
if (load_use_hazard) begin
    stall_load_use <= True;     // 停顿 ID 阶段
    bubble_pending <= True;     // 标记需要插入气泡
    // 不 deq if2id，保留指令供下个周期使用
end else begin
    // 正常解码并发送到 EX
    if2id.deq;
    id2ex.enq(packet);
end
```

## 8. 为什么需要停顿？

```mermaid
flowchart TB
    Question[为什么 Load-Use 不能用前递解决?]

    Answer1[Load 数据在 MEM 阶段<br/>才从 dmem 读取]
    Answer2[EX 阶段需要操作数<br/>但数据尚未可用]
    Answer3[无法从未来获取数据<br/>必须等待]

    Question --> Answer1
    Answer1 --> Answer2
    Answer2 --> Answer3

    Answer3 --> Solution[解决方案：<br/>停顿 1 周期 + 插入 1 气泡<br/>使数据在 WB 阶段可用时<br/>再进入 EX 阶段]
```

**与其他冒险的区别**：
- **RAW (非 Load)**：可通过前递解决，无需停顿
- **Load-Use RAW**：数据在 MEM 阶段才产生，必须停顿
- **结构冒险**：硬件资源冲突，需要停顿
- **控制冒险**：分支预测失败，需要清空流水线