# 内存布局与整体架构图解

本文档描述 RISC-V 处理器的内存布局、地址空间分配和整体架构。

## 1. 整体架构图

```mermaid
flowchart TB
    subgraph Processor["RISC-V 处理器核心"]
        subgraph Pipeline["五级流水线"]
            IF[IF<br/>取指]
            ID[ID<br/>解码]
            EX[EX<br/>执行]
            MEM[MEM<br/>内存]
            WB[WB<br/>写回]
            IF --> ID --> EX --> MEM --> WB
        end

        subgraph Components["核心组件"]
            PC[PC 寄存器<br/>32'h80000000]
            RegFile[寄存器堆<br/>x0-x31]
            ALU[ALU<br/>算术逻辑单元]
            Decoder[解码器]
            BHT[BHT<br/>分支历史表]
            BTB[BTB<br/>分支目标缓冲]
            HazardUnit[冒险检测单元]
        end

        PC --> IF
        RegFile --> ID
        Decoder --> ID
        ALU --> EX
        BHT --> IF
        BTB --> IF
        HazardUnit --> ID
    end

    subgraph Memory["内存系统"]
        IMem[指令内存<br/>1024×32bit<br/>4KB]
        DMem[数据内存<br/>512×32bit<br/>2KB]
    end

    IMem -->|"取指"| IF
    MEM -->|"Load/Store"| DMem
    WB -->|"写回"| RegFile

    subgraph External["外部接口"]
        TestBench[测试平台<br/>TestBench]
        Firmware[固件程序<br/>测试程序]
    end

    TestBench -->|"loadProgram"| IMem
    TestBench -->|"验证"| RegFile
```

## 2. 内存地址空间布局

```mermaid
flowchart TB
    subgraph AddressSpace["32位地址空间"]
        Base["基地址<br/>0x80000000"]

        subgraph IMemRange["指令内存区域"]
            IMemStart["0x80000000<br/>IMem entry 0"]
            IMemEnd["0x80000FFF<br/>IMem entry 1023"]
            IMemSize["4KB<br/>1024条指令"]
        end

        IMemStart -->|"地址范围"| IMemEnd
        IMemStart -->|"PC"| IMemSize

        subgraph DMemRange["数据内存区域"]
            DMemStart["实际映射<br/>addr bits 10-2 索引"]
            DMemEnd["最大地址<br/>< 2048"]
            DMemSize["2KB<br/>512字"]
        end

        DMemStart --> DMemEnd
        DMemStart --> DMemSize
    end

    note right of AddressSpace
        哈佛架构：
        - IMem 和 DMem 物理分离
        - 可同时访问
        - 无结构冒险
    end note
```

### 地址映射详解

```mermaid
flowchart LR
    subgraph IMemAccess["指令内存访问"]
        InstrAddr["指令地址<br/>32位 Addr"]
        Index1["索引计算<br/>addr bits 11-2"]
        InstrWord["IMem<br/>32位指令"]
    end

    InstrAddr --> Index1 --> InstrWord

    note right of Index1
        10位索引
        覆盖 4KB 空间
        1024 条指令
    end note

    subgraph DMemAccess["数据内存访问"]
        DataAddr["数据地址<br/>32位 Addr"]
        Index2["索引计算<br/>addr bits 10-2"]
        DataWord["DMem<br/>32位数据"]
    end

    DataAddr --> Index2 --> DataWord

    note right of Index2
        9位索引
        覆盖 2KB 空间
        512 个字
    end note
```

### 地址范围对照

| 内存 | 基地址 | 大小 | 索引位 | 最大索引 |
|------|--------|------|--------|----------|
| IMem | 0x80000000 | 4KB (1024×4) | addr[11:2] (10位) | 1023 |
| DMem | - | 2KB (512×4) | addr[10:2] (9位) | 511 |

**地址限制**：
- IMem: PC 必须 < 0x80001000
- DMem: Load/Store 地址必须 < 2048 (实际 2KB 边界)

## 3. 寄存器堆结构

```mermaid
flowchart TB
    subgraph RegFile32["32个通用寄存器"]
        X0["x0 (零寄存器)<br/>永远为 0"]
        X1["x1 (ra)<br/>返回地址"]
        X2["x2 (sp)<br/>栈指针"]
        X3["x3 (gp)<br/>全局指针"]
        X4["x4 (tp)<br/>线程指针"]
        X5_X7["x5-x7 (t0-t2)<br/>临时寄存器"]
        X8_X9["x8-x9 (s0-s1)<br/>保存寄存器"]
        X10_X17["x10-x17 (a0-a7)<br/>参数/返回值"]
        X18_X27["x18-x27 (s2-s11)<br/>保存寄存器"]
        X28_X31["x28-x31 (t3-t6)<br/>临时寄存器"]
    end

    subgraph AccessPorts["访问端口"]
        Read1["read1(rs1)<br/>读取端口1"]
        Read2["read2(rs2)<br/>读取端口2"]
        Write["write(rd, value)<br/>写入端口"]
    end

    Read1 --> RegFile32
    Read2 --> RegFile32
    Write --> RegFile32

    note right of X0
        RISC-V 约定：
        x0 硬连线为 0
        写入 x0 无效果
        不参与前递/冒险检测
    end note

    note left of AccessPorts
        BSV 实现：
        - 双读取端口
        - 单写入端口
        - 同周期读写
    end note
```

### 寄存器 ABI 命名

| 寄存器 | ABI 名称 | 用途 | 说明 |
|--------|----------|------|------|
| x0 | zero | 常数 0 | 硬连线 |
| x1 | ra | 返回地址 | JAL/JALR 使用 |
| x2 | sp | 栈指针 | 保存 |
| x3 | gp | 全局指针 | 保存 |
| x4 | tp | 纩程指针 | 保存 |
| x5-x7 | t0-t2 | 临时 | 调用者保存 |
| x8-x9 | s0-s1 | 保存 | 被调用者保存 |
| x10-x17 | a0-a7 | 参数/返回 | 调用者保存 |
| x18-x27 | s2-s11 | 保存 | 被调用者保存 |
| x28-x31 | t3-t6 | 临时 | 调用者保存 |

## 4. 模块依赖关系

```mermaid
flowchart TB
    subgraph Packages["BSV 包依赖"]
        Types["Types.bsv<br/>基础类型定义"]

        ALU["ALU.bsv"]
        RegFile["RegFile.bsv"]
        Decoder["Decoder.bsv"]

        BHT["BHT.bsv"]
        BTB["BTB.bsv"]
        HazardUnit["HazardUnit.bsv"]

        Core["Core.bsv<br/>流水线核心"]
        TestBench["TestBench.bsv<br/>测试平台"]
    end

    Types --> ALU
    Types --> RegFile
    Types --> Decoder
    Types --> BHT
    Types --> BTB
    Types --> HazardUnit
    Types --> Core

    ALU --> Core
    RegFile --> Core
    Decoder --> Core
    BHT --> Core
    BTB --> Core
    HazardUnit --> Core

    Core --> TestBench

    note right of Types
        Types 包定义：
        - Word, Addr 类型
        - 流水线数据包结构
        - 枚举类型
        - 辅助函数
    end note
```

## 5. 数据流总览

```mermaid
flowchart LR
    subgraph Input["输入"]
        Program[测试程序<br/>Vector#1024 Word]
    end

    subgraph Processing["处理"]
        Load["loadProgram()<br/>加载到 IMem"]
        Pipeline["流水线执行<br/>IF→ID→EX→MEM→WB"]
    end

    subgraph Output["输出"]
        RegResult["寄存器结果<br/>readReg()"]
        MemResult["内存状态<br/>DMem 内容"]
        PCState["PC 状态<br/>当前执行位置"]
    end

    Program --> Load
    Load --> Pipeline
    Pipeline --> RegResult
    Pipeline --> MemResult
    Pipeline --> PCState
```

## 6. 测试平台交互

```mermaid
sequenceDiagram
    participant TB as TestBench
    participant Core as Core
    participant IMem as IMem
    participant RegFile as RegFile

    TB->>Core: loadProgram(prog)
    Core->>IMem: 加载指令到 imem (0..1023)

    Note over TB: 启动仿真

    loop 每个时钟周期
        Core->>Core: 流水线执行
        TB->>Core: readReg(addr)
        Core->>RegFile: 读取寄存器值
        RegFile->>TB: 返回值
    end

    Note over TB: 验证结果
    TB->>TB: 检查 x3 == 10
    TB->>TB: 检查 x4 == 20

    Note over TB: 仿真结束
```

## 7. 程序加载流程

```mermaid
flowchart TB
    subgraph TestProgram["测试程序结构"]
        HexCode["机器码<br/>32位十六进制"]
        ASM["汇编指令<br/>RISC-V"]
        Example["示例:<br/>32'h00a00093 = li x1, 10"]
    end

    subgraph Vector["BSV 向量"]
        ProgVec["Vector#1024 Word<br/>prog = replicate(0)"]
        Init["prog(0) = li x1, 10<br/>prog(1) = li x2, 20<br/>..."]
    end

    subgraph Loading["加载过程"]
        Method["loadProgram(prog)"]
        Loop["for i = 0..1023<br/>imem(i) <= prog(i)"]
        Flag["programLoaded <= True"]
    end

    subgraph Execution["执行"]
        Fetch["IF 阶段取指<br/>imem indexed by<br/>PC bits 11-2"]
        Run["流水线执行<br/>直至仿真结束"]
    end

    TestProgram --> Vector
    Vector --> Loading
    Loading --> Execution
```

### 测试程序示例

```bsv
// TestBench.bsv
function Vector#(1024, Word) testProgram();
    Vector#(1024, Word) prog = replicate(0);
    prog[0] = 32'h00a00093;    // li x1, 10
    prog[1] = 32'h01400113;    // li x2, 20
    prog[2] = 32'h02010113;    // li x2, 4  (地址偏移)
    prog[3] = 32'h00112023;    // sw x1, 0(x2)
    prog[4] = 32'h00112183;    // lw x3, 0(x2)
    prog[5] = 32'h003081b3;    // add x3, x1, x3
    // ...
    return prog;
endfunction
```

## 8. 处理器状态

```mermaid
stateDiagram-v2
    [*] --> RUNNING: programLoaded = True

    RUNNING --> RUNNING: 正常执行
    RUNNING --> HALTED: ecall/ebreak
    RUNNING --> TRAPPED: 异常发生

    HALTED --> [*]: 仿真结束
    TRAPPED --> RUNNING: 异常处理
    TRAPPED --> HALTED: 严重错误

    note right of RUNNING
        PC 持续递增
        流水线流动
        指令执行
    end note

    note right of HALTED
        PC 停止
        流水线冻结
        仿真终止
    end note

    note right of TRAPPED
        进入异常处理
        CSR 更新
        可恢复执行
    end note
```

## 9. 扩展路线图

```mermaid
timeline
    title RISC-V 处理器扩展路线

    section 阶段1 (当前)
        五级流水线 : 基本指令集
        数据前递 : 分支预测
        Load-Use 冒险处理

    section 阶段2 (近期)
        LB/LH/LBU/LHU : SB/SH
        内存扩展 64KB : RISC-V 官方测试

    section 阶段3-4 (中期)
        特权级 M/S/U : CSR 寄存器
        异常/中断 : Timer 中断

    section 阶段5-8 (长期)
        CLINT 定时器 : PLIC 中断控制器
        UART 控制台 : 内存扩展 16MB
        FreeRTOS/uClinux : 首次启动 OS
```

## 10. 目录结构

```
riscv-bsv-processor/
├── src/
│   ├── common/
│   │   └── Types.bsv          # 类型定义
│   ├── core/
│   │   ├── Core.bsv           # 流水线核心
│   │   ├── ALU.bsv            # ALU
│   │   ├── RegFile.bsv        # 寄存器堆
│   │   ├── Decoder.bsv        # 解码器
│   │   └── HazardUnit.bsv     # 冒险检测
│   ├── branch/
│   │   ├── BHT.bsv            # 分支历史表
│   │   └── BTB.bsv            # 分支目标缓冲
│   └── soc/
│       └── TestBench.bsv      # 测试平台
├── build/
│   └── mkTestBench.v          # 生成的 Verilog
├── tests/
│   └── c/
│       └── test_bench.cpp     # Verilator C++ 测试
├── obj_dir/
│   └── VmkTestBench           # Verilator 仿真二进制
├── docs/
│   ├── cpu-pipeline-architecture.md  # 流水线架构图解
│   ├── data-forwarding.md             # 数据前递图解
│   ├── load-use-hazard.md             # Load-Use 冒险图解
│   ├── branch-prediction.md           # 分支预测图解
│   ├── pipeline-scheduling.md         # 流水线调度图解
│   └── memory-layout.md               # 本文档
│   ├── roadmap-embedded-os.md         # OS 支持路线图
│   └── superpowers/
│       └── specs/
│           └── 2026-04-12-load-use-hazard-fix-design.md
├── tools/
│   └── elf_to_bsv.py          # ELF 转换工具 (开发中)
├── Makefile
└── CLAUDE.md                  # 项目说明
```