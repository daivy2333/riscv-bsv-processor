# RISC-V 五级流水线架构图解

本文档使用 Mermaid 图表展示 RISC-V 处理器的设计架构和数据流。

## 1. 五级流水线整体架构

```mermaid
flowchart TB
    subgraph IF["IF - 指令获取阶段"]
        PC[PC 寄存器<br/>0x80000000]
        IMem[指令内存<br/>IMem 1024×32bit]
        BHT[分支历史表<br/>BHT 64条目]
        BTB[分支目标缓冲<br/>BTB 64条目]
        PC --> IMem
        PC --> BHT
        PC --> BTB
        BHT --> BTB
        BTB -->|预测跳转| PC
    end

    subgraph ID["ID - 指令解码阶段"]
        Decoder[解码器<br/>Decoder]
        RegFile[寄存器堆<br/>x0-x31]
        HazardUnit[冒险检测单元<br/>HazardUnit]
        Decoder --> RegFile
        Decoder --> HazardUnit
    end

    subgraph EX["EX - 执行阶段"]
        ALU[算术逻辑单元<br/>ALU]
        ForwardUnit[前递逻辑]
        BranchComp[分支比较器]
        ALU --> ForwardUnit
        ForwardUnit --> BranchComp
    end

    subgraph MEM["MEM - 内存访问阶段"]
        DMem[数据内存<br/>DMem 512×32bit<br/>2KB]
    end

    subgraph WB["WB - 写回阶段"]
        WriteBack[写回寄存器堆]
    end

    IF -->|"IF_ID_Packet<br/>pc, instr, pred"| ID
    ID -->|"ID_EX_Packet<br/>rs1_val, rs2_val, imm<br/>alu_op, mem_op, rd"| EX
    EX -->|"EX_MEM_Packet<br/>alu_result, mem_op<br/>is_load, branch_taken"| MEM
    MEM -->|"MEM_WB_Packet<br/>mem_data, alu_result<br/>rd, write_reg"| WB
    WB -->|"写寄存器"| RegFile

    ForwardUnit -->|"WB→EX 前递"| EX
    ForwardUnit -->|"MEM→EX 前递"| EX

    HazardUnit -->|"Load-Use 停顿"| ID
    HazardUnit -->|"气泡插入"| EX
```

## 2. 流水线寄存器数据包结构

```mermaid
classDiagram
    class IF_ID_Packet {
        +Addr pc
        +Word instruction
        +Addr predicted_pc
        +Bool predicted_taken
    }

    class ID_EX_Packet {
        +Addr pc
        +Word instruction
        +Word rs1_val
        +Word rs2_val
        +Word imm
        +Bit5 rs1
        +Bit5 rs2
        +Bit5 rd
        +ALUOp alu_op
        +BranchCond branch_cond
        +MemOp mem_op
        +Bool is_branch
        +Bool is_jump
        +Bool write_reg
        +Bool use_imm
    }

    class EX_MEM_Packet {
        +Addr pc
        +Word alu_result
        +Word rs2_val
        +Bit5 rd
        +MemOp mem_op
        +Bool is_branch
        +Bool branch_taken
        +Bool predicted_taken
        +Bool write_reg
        +Bool is_load
    }

    class MEM_WB_Packet {
        +Addr pc
        +Word mem_data
        +Word alu_result
        +Bit5 rd
        +Bool write_reg
        +Bool is_load
    }

    IF_ID_Packet --> ID_EX_Packet : ID阶段转换
    ID_EX_Packet --> EX_MEM_Packet : EX阶段转换
    EX_MEM_Packet --> MEM_WB_Packet : MEM阶段转换
```

## 3. 指令类型与解码结果

```mermaid
flowchart LR
    subgraph Input["指令输入"]
        Instr["32位指令"]
    end

    subgraph Decoder["解码器处理"]
        Opcode["Opcode 提取<br/>bits 6-0"]
        Funct3["Funct3 提取<br/>bits 14-12"]
        Funct7["Funct7 提取<br/>bits 31-25"]
        Rs1["Rs1 提取<br/>bits 19-15"]
        Rs2["Rs2 提取<br/>bits 24-20"]
        Rd["Rd 提取<br/>bits 11-7"]
        Imm["立即数提取<br/>I/S/B/U/J型"]
    end

    subgraph Output["DecodedInstr 输出"]
        ALUOp["ALUOp<br/>ADD/SUB/SLL..."]
        BranchCond["BranchCond<br/>EQ/NE/LT/GE..."]
        MemOp["MemOp<br/>NONE/READ/WRITE"]
        UseRs1["use_rs1<br/>是否使用rs1"]
        UseRs2["use_rs2<br/>是否使用rs2"]
        WriteReg["write_reg<br/>是否写寄存器"]
    end

    Instr --> Opcode
    Instr --> Funct3
    Instr --> Funct7
    Instr --> Rs1
    Instr --> Rs2
    Instr --> Rd
    Instr --> Imm

    Opcode --> ALUOp
    Funct3 --> ALUOp
    Funct7 --> ALUOp
    Funct3 --> BranchCond
    Opcode --> MemOp
    Opcode --> UseRs1
    Opcode --> UseRs2
    Opcode --> WriteReg
```

### 指令类型对照表

| Opcode | 类型 | use_rs1 | use_rs2 | 说明 |
|--------|------|---------|---------|------|
| 0110011 | R-Type | ✓ | ✓ | ADD, SUB, AND, OR... |
| 0010011 | I-Type | ✓ | ✗ | ADDI, ANDI, SLLI... |
| 0000011 | Load | ✓ | ✗ | LB, LH, LW, LBU, LHU |
| 0100011 | Store | ✓ | ✓ | SB, SH, SW |
| 1100011 | Branch | ✓ | ✓ | BEQ, BNE, BLT, BGE... |
| 0110111 | LUI | ✗ | ✗ | LUI (加载高位立即数) |
| 0010111 | AUIPC | ✗ | ✗ | AUIPC |
| 1101111 | JAL | ✗ | ✗ | JAL (跳转并链接) |
| 1100111 | JALR | ✓ | ✗ | JALR (寄存器跳转) |