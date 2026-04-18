# 流水线调度规则图解

本文档详细说明 BSV 中的流水线调度规则（Rules）及其执行顺序和条件。

## 1. 规则总览

```mermaid
flowchart TB
    subgraph Rules["七大调度规则"]
        R1["fetchStage<br/>IF 阶段"]
        R2["decodeStage<br/>ID 阶段"]
        R3["decrementStall<br/>stall 计数递减"]
        R4["executeStage<br/>EX 阶段"]
        R5["memoryStage<br/>MEM 阶段"]
        R6["writebackStage<br/>WB 阶段"]
        R7["clearBranchFlush<br/>清除分支冲刷"]
        R8["clearBranchFlushDone"]
    end

    subgraph Conditions["执行条件"]
        C1["!stall && !branch_flush"]
        C2["!stall"]
        C3["stall && count > 0"]
        C4["!stall && id2ex.notEmpty"]
        C5["无条件"]
        C6["无条件"]
        C7["branch_flush"]
        C8["branch_flush_done && !branch_flush"]
    end

    R1 --> C1
    R2 --> C2
    R3 --> C3
    R4 --> C4
    R5 --> C5
    R6 --> C6
    R7 --> C7
    R8 --> C8
```

## 2. 规则执行顺序

BSV 编译器使用 `execution_order` 和 `preempts` 注解控制规则执行顺序：

```mermaid
flowchart LR
    subgraph Annotations["BSV 调度注解"]
        ExecOrder["execution_order:<br/>writebackStage, executeStage"]
        Preempts["preempts:<br/>executeStage, fetchStage"]
    end

    subgraph Order["执行顺序"]
        WB["writebackStage (最先)"]
        EX["executeStage"]
        MEM["memoryStage"]
        ID["decodeStage"]
        IF["fetchStage (最后)"]
        Flush["clearBranchFlush"]
    end

    WB --> EX
    EX --> MEM
    MEM --> ID
    ID --> IF
    IF -.-> Flush
```

**关键设计**：
- `execution_order`：writebackStage 先于 executeStage
- `preempts`：executeStage 抢占 fetchStage，防止同时更新 PC
- `clearBranchFlush`：在 fetchStage 之后执行

## 3. FIFO 流动图

```mermaid
flowchart LR
    subgraph FIFOs["流水线 FIFOF"]
        IF_ID["if2id<br/>FIFOF#IF_ID_Packet"]
        ID_EX["id2ex<br/>FIFOF#ID_EX_Packet"]
        EX_MEM["ex2mem<br/>FIFOF#EX_MEM_Packet"]
        MEM_WB["mem2wb<br/>FIFOF#MEM_WB_Packet"]
    end

    subgraph Operations["操作"]
        Enq["enq (入队)"]
        Deq["deq (出队)"]
        First["first (读取)"]
        Clear["clear (清空)"]
    end

    fetchStage -->|"enq"| IF_ID
    decodeStage -->|"first, deq"| IF_ID
    decodeStage -->|"enq"| ID_EX
    executeStage -->|"first, deq/clear"| ID_EX
    executeStage -->|"enq"| EX_MEM
    memoryStage -->|"first, deq"| EX_MEM
    memoryStage -->|"enq"| MEM_WB
    writebackStage -->|"first, deq"| MEM_WB

    decrementStall -->|"enq"| ID_EX
```

## 4. 分支冲刷控制

分支跳转时需要冲刷流水线中的错误指令：

```mermaid
flowchart TB
    subgraph BranchFlush["分支冲刷流程"]
        Detect["executeStage 检测到 branch_taken"]
        SetFlags["设置标志"]
        Clear["清空 FIFO"]
        Update["更新 PC"]
    end

    subgraph Flags["控制标志"]
        BF["branch_flush<br/>阻止 IF 执行一周期"]
        BFD["branch_flush_done<br/>阻止 IF 更新 PC"]
        NPU["no_pc_update<br/>阻止 IF PC+4"]
    end

    Detect --> SetFlags
    SetFlags -->|"branch_flush=True"| Clear
    SetFlags -->|"branch_flush_done=True"| Update
    SetFlags -->|"no_pc_update=True"| Update
    Clear -->|"if2id.clear"| FlushIF
    Clear -->|"id2ex.clear"| FlushID
```

### 分支冲刷时序

```mermaid
sequenceDiagram
    participant IF as fetchStage
    participant ID as decodeStage
    participant EX as executeStage
    participant Flush as clearBranchFlush

    Note over EX: 周期 N: 分支跳转执行
    EX->>EX: branch_taken = True
    EX->>EX: pcReg <= actual_target
    EX->>EX: branch_flush <= True
    EX->>EX: no_pc_update <= True
    EX->>IF: if2id.clear
    EX->>ID: id2ex.clear

    Note over IF: 周期 N: fetchStage 不执行
    Note over Flush: 周期 N: clearBranchFlush 执行
    Flush->>Flush: branch_flush <= False
    Flush->>Flush: branch_flush_done <= True

    Note over IF: 周期 N+1: fetchStage 不更新 PC
    Note over Flush: 周期 N+1: clearBranchFlushDone 执行
    Flush->>Flush: branch_flush_done <= False
```

## 5. Load-Use 停顿时序

```mermaid
sequenceDiagram
    participant IF as fetchStage
    participant ID as decodeStage
    participant EX as executeStage
    participant Stall as decrementStall
    participant MEM as memoryStage
    participant WB as writebackStage

    Note over ID: 周期 N: 检测到 Load-Use
    ID->>ID: stall_load_use = True
    ID->>ID: stall_count = 2
    ID->>EX: 插入 NOP

    Note over IF: fetchStage 不执行
    Note over Stall: 周期 N: stall_count = 2

    Note over Stall: 周期 N+1: stall_count = 1
    Stall->>Stall: stall_count--
    Stall->>EX: 插入 NOP

    Note over Stall: 周期 N+2: stall_count = 0
    Stall->>Stall: stall_count--
    Stall->>Stall: stall_load_use = False

    Note over WB: Load 数据写回
    WB->>EX: WB→EX 前递可用
```

## 6. 规则调度矩阵

| 规则 | 执行条件 | 操作的 FIFOF | 关键功能 |
|------|----------|--------------|----------|
| writebackStage | 无条件 | mem2wb (deq) | 释放 WB，更新双缓冲 |
| memoryStage | 无条件 | ex2mem (deq), mem2wb (enq) | 内存访问 |
| executeStage | !stall && id2ex.notEmpty | id2ex (deq/clear), ex2mem (enq) | 执行分支/ALU，前递 |
| decodeStage | !stall | if2id (deq), id2ex (enq) | 解码，冒险检测 |
| decrementStall | stall && count > 0 | id2ex (enq) | stall 递减，插入 NOP |
| clearBranchFlush | branch_flush | - | 清除 branch_flush |
| fetchStage | !stall && !branch_flush | if2id (enq) | 取指，预测 |

## 7. preempts 机制

```mermaid
flowchart TB
    subgraph Conflict["潜在冲突"]
        Execute["executeStage<br/>更新 PC"]
        Fetch["fetchStage<br/>更新 PC+4"]
        Shared["共享资源: pcReg"]
    end

    Execute -.-> Shared
    Fetch -.-> Shared

    subgraph Resolution["preempts 解决"]
        Preempt["preempts = executeStage, fetchStage"]
        Result["executeStage 抢占<br/>fetchStage 不执行"]
    end

    Preempt --> Result
```

**关键点**：
- `executeStage` 抢占 `fetchStage`
- 当 `executeStage` 执行时，`fetchStage` 不会同时执行
- 防止 PC 被两个规则同时更新

## 8. 代码实现对照

### fetchStage

```bsv
(* preempts = "executeStage, fetchStage" *)
rule fetchStage (programLoaded && state == RUNNING && !stall_load_use && !branch_flush);
    Addr fetchPC = pcReg;
    // ... BTB/BHT 预测 ...

    if2id.enq(IF_ID_Packet { ... });

    // 只在 branch_flush_done 和 no_pc_update 为 False 时更新 PC
    if (!branch_flush_done && !no_pc_update) begin
        if (take_prediction)
            pcReg <= prediction_target;
        else
            pcReg <= pcReg + 4;
    end
endrule
```

### executeStage

```bsv
(* execution_order = "writebackStage, executeStage" *)
(* preempts = "executeStage, fetchStage" *)
rule executeStage (!stall_load_use && id2ex.notEmpty && ex2mem.notFull);
    // ... 前递逻辑 ...

    if (branch_taken) begin
        pcReg <= actual_target;
        branch_flush <= True;
        no_pc_update <= True;
        if2id.clear;
        id2ex.clear;
    end else begin
        id2ex.deq;
        no_pc_update <= False;
    end
endrule
```

### decrementStall

```bsv
rule decrementStall (stall_load_use && stall_count > 0);
    Bit#(2) new_count = stall_count - 1;
    stall_count <= new_count;
    if (new_count == 0) begin
        stall_load_use <= False;
    end
    id2ex.enq(nopPacket());
endrule
```

## 9. 设计要点总结

```mermaid
mindmap
  root((流水线调度))
    规则设计
      preempts 注解
        executeStage 抢占 fetchStage
      execution_order 注解
        writebackStage 先于 executeStage
      条件互斥
        branch_flush 控制 IF
        no_pc_update 控制 PC+4
    FIFO 流动
      FIFOF 深度2
      支持 stall 时 enq
      clear vs deq
    冒险处理
      Load-Use 停顿
        stall_count 递减
        2周期延迟
      分支冲刷
        branch_flush 标志
        no_pc_update 标志
    BSV 保证
      原子性
      确定性
      无死锁
```
