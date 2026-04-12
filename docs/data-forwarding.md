# 数据前递机制图解

数据前递（Data Forwarding）是解决数据冒险的关键技术，允许后续指令在数据写入寄存器堆之前就获取到结果。

## 1. 前递路径总览

```mermaid
flowchart TB
    subgraph Pipeline["五级流水线"]
        IF[IF<br/>取指]
        ID[ID<br/>解码]
        EX[EX<br/>执行]
        MEM[MEM<br/>内存]
        WB[WB<br/>写回]
        IF --> ID --> EX --> MEM --> WB
    end

    subgraph Forwarding["前递路径"]
        EX_EX["EX→EX 前递<br/>alu_result"]
        MEM_EX["MEM→EX 前递<br/>alu_result<br/>⚠️ Load不前递"]
        WB_EX["WB→EX 前递<br/>mem_data/alu_result"]
    end

    EX -->|"产生结果"| EX_EX
    MEM -->|"产生结果"| MEM_EX
    WB -->|"产生结果"| WB_EX

    EX_EX -->|"同一周期"| EX
    MEM_EX -->|"下一周期"| EX
    WB_EX -->|"两周期后"| EX

    WB -->|"写寄存器"| RegFile[寄存器堆]
    RegFile -->|"读取"| ID
```

## 2. 前递优先级

当多个前递源同时有效时，按以下优先级选择：

```mermaid
flowchart LR
    Start[EX 阶段需要 rs1/rs2 值] --> CheckEX{EX→EX<br/>有效?}
    CheckEX -->|是| UseEX[使用 ex_forward<br/>最新结果]
    CheckEX -->|否| CheckMEM{MEM→EX<br/>有效?<br/>非Load}
    CheckMEM -->|是| UseMEM[使用 mem_forward]
    CheckMEM -->|否| CheckWB{WB→EX<br/>有效?}
    CheckWB -->|是| UseWB[使用 wb_forward]
    CheckWB -->|否| UseReg[使用寄存器堆值]

    UseEX --> Done[ALU 输入]
    UseMEM --> Done
    UseWB --> Done
    UseReg --> Done
```

**优先级规则**：
1. **EX→EX 最高** - 刚产生的结果，最新
2. **MEM→EX 次高** - 但 Load 指令不在此前递（数据尚未从内存读取）
3. **WB→EX 第三** - Load 数据在此阶段可用
4. **寄存器堆最低** - 默认来源

## 3. 前递时序图

### 正常前递场景（ADD → ADD）

```mermaid
sequenceDiagram
    participant I as IF
    participant D as ID
    participant E as EX
    participant M as MEM
    participant W as WB
    participant R as RegFile

    Note over I: add x1, x2, x3 (周期1)
    I->>D: IF_ID_Packet (周期2)
    D->>E: ID_EX_Packet (周期3)
    E->>M: EX_MEM_Packet (周期4)
    M->>W: MEM_WB_Packet (周期5)
    W->>R: 写入 x1

    Note over I: add x4, x1, x5 (周期2)
    I->>D: IF_ID_Packet (周期3)
    D->>E: ID_EX_Packet (周期4)
    Note over E: 需要 x1 值
    E->>E: EX→EX 前递 alu_result
    Note over E: 使用最新 x1 值
```

### Load-Use 场景（LW → ADD）

```mermaid
sequenceDiagram
    participant I as IF
    participant D as ID
    participant E as EX
    participant M as MEM
    participant W as WB
    participant R as RegFile

    Note over I: lw x1, 0(x2) (周期1)
    I->>D: IF_ID_Packet (周期2)
    D->>E: ID_EX_Packet (周期3)
    E->>M: EX_MEM_Packet (周期4)
    Note over M: 从 dmem 读取数据
    M->>W: MEM_WB_Packet (周期5)
    W->>R: 写入 x1

    Note over I: add x3, x1, x4 (周期2)
    I->>D: IF_ID_Packet (周期3)
    Note over D: 检测到 Load-Use 冒险!
    Note over D: 停顿 ID 阶段

    Note over I: IF 阶段暂停 (周期3)
    Note over E: 插入气泡 NOP (周期4)

    Note over D: 解除停顿 (周期5)
    D->>E: ID_EX_Packet (周期5)
    Note over E: 需要 x1 值
    W->>E: WB→EX 前递 mem_data
    Note over E: 使用 Load 结果
```

## 4. 前递数据流详细图

```mermaid
flowchart TB
    subgraph EX_Stage["EX 阶段"]
        subgraph OperandSelection["操作数选择"]
            Op1_rs1["rs1_val<br/>(来自 RegFile)"]
            Op1_ex["ex_forward<br/>(EX→EX)"]
            Op1_mem["mem_forward<br/>(MEM→EX, 非Load)"]
            Op1_wb["wb_forward<br/>(WB→EX)"]
            Op1_mux{MUX 选择 op1}
            Op1_rs1 --> Op1_mux
            Op1_ex --> Op1_mux
            Op1_mem --> Op1_mux
            Op1_wb --> Op1_mux
        end

        subgraph ForwardValidation["前递有效性判断"]
            ExValid["ex_forward_valid<br/>& ex_forward_rd == rs1"]
            MemValid["mem_forward_valid<br/>& mem_forward_rd == rs1<br/>& !is_load"]
            WbValid["wb_forward_valid<br/>& wb_forward_rd == rs1"]
        end

        ExValid --> Op1_mux
        MemValid --> Op1_mux
        WbValid --> Op1_mux

        Op1_mux --> ALU["ALU 输入 op1"]
    end

    subgraph MEM_Stage["MEM 阶段"]
        MemResult["alu_result"]
        MemLoad["is_load 标志"]
        MemResult -->|"非Load时前递"| Op1_mem
        MemLoad -->|"Load不前递"| Op1_mem
    end

    subgraph WB_Stage["WB 阶段"]
        WbData["wb_data<br/>Load: mem_data<br/>其他: alu_result"]
        WbData --> Op1_wb
    end
```

## 5. 前递控制信号

| 信号 | 来源 | 有效条件 | 数据内容 |
|------|------|----------|----------|
| `ex_forward` | EX 阶段 | `write_reg && rd != 0` | `alu_result` |
| `mem_forward` | MEM 阶段 | `write_reg && !is_load` | `alu_result` |
| `wb_forward` | WB 阶段 | `write_reg` | `mem_data` (Load) 或 `alu_result` |
| `ex_forward_rd` | EX 阶段 | - | 目标寄存器号 |
| `mem_forward_rd` | MEM 阶段 | - | 目标寄存器号 |
| `wb_forward_rd` | WB 阶段 | - | 目标寄存器号 |

## 6. 代码实现要点

```bsv
// EX 阶段前递逻辑 (Core.bsv:179-195)
Word op1 = pkt.rs1_val;  // 默认使用寄存器堆值

// EX→EX 前递 (最高优先级)
if (ex_forward_valid && ex_forward_rd == pkt.rs1 && pkt.rs1 != 0)
    op1 = ex_forward;

// MEM→EX 前递 (次高优先级，Load 不前递)
if (mem_forward_valid && mem_forward_rd == pkt.rs1 && pkt.rs1 != 0 && !ex2mem.first.is_load)
    op1 = mem_forward;

// WB→EX 前递 (最低优先级)
if (wb_forward_valid && wb_forward_rd == pkt.rs1 && pkt.rs1 != 0)
    op1 = wb_forward;
```

**关键点**：
- `x0` 寄存器永远为 0，不参与前递
- Load 指令在 MEM 阶段数据尚未可用，不在 MEM→EX 前递
- Load 数据在 WB 阶段通过 WB→EX 前递传递