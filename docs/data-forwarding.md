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
        MEM_EX["MEM→EX 前递<br/>ex2mem.first<br/>非 Load"]
        WB_EX["WB→EX 前递<br/>mem2wb.first"]
        WB_EX_HIST["WB→EX (历史)<br/>wb_forward_data0/1"]
        WB_ID["WB→ID 前递<br/>wb_forward_data0/1"]
    end

    MEM -->|"产生结果"| MEM_EX
    WB -->|"产生结果"| WB_EX
    WB -->|"产生结果"| WB_EX_HIST
    WB -->|"写寄存器"| RegFile[寄存器堆]
    RegFile -->|"读取"| ID
    WB_EX -->|"同一周期"| EX
    WB_EX_HIST -->|"双缓冲"| EX
    WB_EX_HIST -->|"双缓冲"| ID
```

## 2. 前递优先级

当多个前递源同时有效时，按以下优先级选择：

```mermaid
flowchart LR
    Start[EX 阶段需要 rs1/rs2 值] --> CheckMEM{MEM→EX<br/>有效?<br/>非Load}
    CheckMEM -->|是| UseMEM[使用 mem2wb.first<br/>或 ex2mem.first]
    CheckMEM -->|否| CheckWB{WB→EX<br/>有效?}
    CheckWB -->|是| CheckWB0{wb_forward_valid0<br/>匹配?}
    CheckWB0 -->|是| UseWB0[使用 wb_forward_data0]
    CheckWB0 -->|否| CheckWB1{wb_forward_valid1<br/>匹配?}
    CheckWB1 -->|是| UseWB1[使用 wb_forward_data1]
    CheckWB1 -->|否| UseReg[使用寄存器堆值]

    UseMEM --> Done[ALU 输入]
    UseWB0 --> Done
    UseWB1 --> Done
    UseReg --> Done
```

**优先级规则**：
1. **MEM→EX 最高** - 从 ex2mem.first 读取，非 Load 数据同周期可用
2. **WB→EX 中** - 从 mem2wb.first 读取，Load 数据在 WB 阶段可用
3. **WB→EX (历史) 次低** - wb_forward_data0/1 双缓冲，解决 mkReg 写入延迟
4. **WB→ID 最低** - 分支指令读取寄存器时使用
5. **寄存器堆默认** - 无前递时使用

## 3. 双缓冲机制

WB 前递使用双缓冲解决 mkReg 写入延迟问题：

```mermaid
flowchart TB
    subgraph WB_Cycle_N["周期 N: WB 写入"]
        WbData["wb_data"]
        WbRd["pkt.rd"]
        WbValid["write_reg"]
    end

    subgraph Buffer_Update["双缓冲更新"]
        Buf0["wb_forward_data0"] 
        Buf1["wb_forward_data1"]
        WbData --> Buf0
        Buf0 --> Buf1
    end

    subgraph EX_Cycle_N["周期 N: EX 使用"]
        Use0["同周期读取 mem2wb.first"]
        Use1["前几周期数据用 wb_forward"]
    end
```

**时序**：
- `wb_forward_data0` 保存上一周期 WB 写入
- `wb_forward_data1` 保存两周期前 WB 写入
- 双缓冲确保同一周期内可同时写入和读取

## 4. 前递时序图

### 正常前递场景（ADD → ADD）

```mermaid
sequenceDiagram
    participant I as IF
    participant D as ID
    participant E as EX
    participant M as MEM
    participant W as WB

    Note over I: add x1, x2, x3 (周期1)
    I->>D: IF_ID_Packet (周期2)
    D->>E: ID_EX_Packet (周期3)
    E->>M: EX_MEM_Packet (周期4)
    M->>W: MEM_WB_Packet (周期5)
    W->>W: 写入 x1, 更新双缓冲

    Note over I: add x4, x1, x5 (周期2)
    I->>D: IF_ID_Packet (周期3)
    D->>E: ID_EX_Packet (周期4)
    Note over E: 需要 x1 值
    M->>E: MEM→EX 前递
```

### WB→ID 前递场景（分支）

```mermaid
sequenceDiagram
    participant I as IF
    participant D as ID
    participant E as EX
    participant W as WB

    Note over W: li t0, 1 (周期 N)
    W->>W: 写入 t0
    W->>W: wb_forward_data0 = 1

    Note over D: beq t0, t1, pass (周期 N+2)
    Note over D: ID 读取 t0
    W->>D: wb_forward_data0 前递
    Note over D: t0 值可用
```

## 5. 代码实现要点

```bsv
// EX 阶段前递逻辑 (Core.bsv:183-220)
Word op1 = pkt.rs1_val;  // 默认使用 ID 阶段读取的值

// WB→EX 前递（直接读取 mem2wb.first，同周期可用）
if (mem2wb.notEmpty && mem2wb.first.write_reg && mem2wb.first.rd == pkt.rs1 && pkt.rs1 != 0)
    op1 = mem2wb.first.is_load ? mem2wb.first.mem_data : mem2wb.first.alu_result;
else if (wb_forward_valid0 && wb_forward_rd0 == pkt.rs1 && pkt.rs1 != 0)
    op1 = wb_forward_data0;
else if (wb_forward_valid1 && wb_forward_rd1 == pkt.rs1 && pkt.rs1 != 0)
    op1 = wb_forward_data1;

// MEM→EX 前递（从 ex2mem FIFO 读取上一周期 EX 输出）
if (ex2mem.notEmpty && ex2mem.first.write_reg && !ex2mem.first.is_load && ex2mem.first.rd == pkt.rs1 && pkt.rs1 != 0)
    op1 = ex2mem.first.alu_result;
```

```bsv
// WB 阶段双缓冲更新 (Core.bsv:417-425)
wb_forward_data1 <= wb_forward_data0;
wb_forward_rd1 <= wb_forward_rd0;
wb_forward_valid1 <= wb_forward_valid0;

wb_forward_data0 <= wb_data;
wb_forward_rd0 <= pkt.rd;
wb_forward_valid0 <= pkt.write_reg;
```

**关键点**：
- `x0` 寄存器永远为 0，不参与前递
- Load 指令数据在 MEM 阶段不可用，MEM→EX 前递排除 Load
- Load 数据在 WB 阶段通过 mem2wb.first 或 wb_forward_data0 前递
- 双缓冲确保前递数据在多个周期内可用