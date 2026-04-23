# RISC-V 处理器架构

## 五级流水线

```
IF → ID → EX → MEM → WB
```

| 阶段 | 功能 | 关键组件 |
|------|------|----------|
| IF | 取指 + 分支预测 | BHT(64条目)/BTB(64条目) |
| ID | 解码 + 冒险检测 + 前递 | Decoder/HazardUnit/WB前递 |
| EX | ALU执行 + MEM前递 + CSR操作 | ALU/CSR/前递网络 |
| MEM | 内存请求发送 | MemChannel接口 |
| WB | 寄存器写回 + 中断处理 | RegFile/CSR中断 |

## 流水线寄存器

使用 FIFOF 深度 2 实现：

```
IF_ID_Packet: pc, instruction, predicted_pc, predicted_taken, priv_mode
ID_EX_Packet: pc, rs1_val, rs2_val, imm, rd, alu_op, branch_cond, mem_op, ...
EX_MEM_Packet: pc, alu_result, rs2_val, rd, mem_op, branch_taken, actual_target, ...
MEM_WB_Packet: pc, mem_data, alu_result, rd, write_reg, is_load, mem_width, ...
```

## 前递网络

### 前递路径

| 路径 | 数据来源 | 适用条件 |
|------|----------|----------|
| MEM→EX | mem_alu_result_cached | 非Load指令，rd匹配 |
| WB→EX (bypass) | wb_bypass_data | 同周期写回数据 |
| WB→EX (cached) | wb_mem_data_cached/wb_alu_result_cached | Load/非Load均可 |
| WB→ID | wb_forward_data0/data1 | 两级历史缓冲 |

### 前递优先级

```
1. MEM→EX (非Load)       ← 最高优先级
2. WB bypass (同周期)
3. WB cached (历史)
4. WB forward buffer
```

**Load 不能从 MEM 前递**：Load 数据在 WB 阶段才可用，需要 stall 处理。

## Load-Use 冒险

ID 阶段检测条件：
```
if ex_is_load_cached && ex_rd_cached != 0:
    if (dec.use_rs1 && dec.rs1 == ex_rd) || (dec.use_rs2 && dec.rs2 == ex_rd):
        stall_load_use = True
        stall_count = 3
        插入 NOP 包
```

处理流程：
| 周期 | Load位置 | 动作 |
|------|----------|------|
| N | EX | 检测冒险，stall=1，插入NOP |
| N+1 | MEM | stall_count=2，插入NOP |
| N+2 | WB | stall_count=1，插入NOP |
| N+3 | - | stall结束，WB→EX前递可用 |

## 分支预测

### 组件

| 组件 | 说明 |
|------|------|
| BHT | 分支历史表，64条目，2位饱和计数器 |
| BTB | 分支目标缓冲区，64条目 |

### 预测流程

1. IF阶段：BHT查询 → 预测taken/not-taken，BTB查询 → 目标地址
2. 预测taken时，PC跳转到预测目标
3. EX阶段：计算实际分支结果，检测misprediction
4. 预测失败时：冲刷流水线，重定向PC

### 预测失败处理

```
if branch_taken && !prediction_correct:
    clear if2id, id2ex
    redirect to actual_target
elif !branch_taken && predicted_taken:
    clear if2id, id2ex
    redirect to pc+4
```

## 控制流重定向协议

统一处理所有控制流变化：

| 状态寄存器 | 说明 |
|------------|------|
| redirect_pending | 重定向请求挂起 |
| redirect_target | 重定向目标地址 |
| redirect_reason | 重定向原因编码 |

### redirect_reason 编码

| 编码 | 原因 | 触发场景 |
|------|------|----------|
| 0 | NONE | 无重定向 |
| 1 | BRANCH | 分支mispredict |
| 2 | JAL | 无条件跳转 |
| 3 | TRAP | 陷阱(ECALL/EBREAK) |
| 4 | MRET | 从陷阱返回 |
| 5 | INTERRUPT | WB阶段中断 |

### 流水线冲刷

```
if need_redirect:
    clear if2id, id2ex
    pcReg <= redirect_target
    redirect_pending <= True
```

## Core-SOC 消息通道

### MemChannel 接口

```bsv
interface MemChannel;
    method Action sendMemReq(MemReq req);
    method Bool hasMemResp();
    method MemResp peekMemResp();
    method Action deqMemResp();
    method CSRs csrModule();
    method Bool clintTimerIRQ();
    ...
endinterface
```

### SOC 实现

| 组件 | 说明 |
|------|------|
| mem_req_fifo | Core→SOC请求FIFO (mkFIFOF) |
| mem_resp_fifo | SOC→Core响应FIFO (mkBypassFIFOF) |

**关键设计原则**：
1. 分离规则：Load和非Load包由独立规则处理
2. Load-only响应：只为Load请求发送响应
3. BypassFIFOF：响应FIFO支持同周期读写

## 定时器中断架构

### 中断信号链

```
CLINT.mtime (每周期递增)
    → mtime >= mtimecmp
    → timerIRQ Wire
    → CSR mip (组合逻辑读取)
    → WB阶段检测
```

### WB中断处理

```
if csrModule().hasPendingInterrupt() && mstatus.MIE:
    cause = getPendingInterruptCause()
    mepc = pc + 4
    mcause = 0x80000000 | cause
    mstatus.MIE = 0, MPIE = 1, MPP = 3
    redirect to mtvec
    clear all pipeline stages
```

## 内存布局

| 区域 | 范围 | 大小 |
|------|------|------|
| Boot ROM | 0x00000000-0x00000FFF | 4KB |
| CLINT | 0x02000000-0x0200FFFF | 64KB |
| PLIC | 0x0C000000-0x0C0FFFFF | 64KB |
| UART | 0x10000000-0x10000FFF | 4KB |
| RAM | 0x80000000-0x80FFFFFF | 16MB |
| tohost | 0x80001000 | 1 word |

## CSR 寄存器

| 地址 | 名称 | 说明 |
|------|------|------|
| 0x300 | mstatus | 机器状态（MIE/MPIE/MPP） |
| 0x301 | misa | 机器ISA |
| 0x304 | mie | 中断使能 |
| 0x305 | mtvec | 陷阱向量 |
| 0x341 | mepc | 异常PC |
| 0x342 | mcause | 异常原因 |
| 0x343 | mtval | 陷阱值 |
| 0x344 | mip | 中断挂起（Wire直连） |
| 0xB00 | mcycle | 周期计数 |
| 0xB03 | minstret | 指令计数 |

## 指令集

### RV32I

| 类型 | 指令 | 状态 |
|------|------|------|
| R-Type | ADD/SUB/SLL/SRL/SRA/SLT/SLTU/AND/OR/XOR | ✓ |
| I-Type ALU | ADDI/SLTI/SLTIU/ANDI/ORI/XORI/SLLI/SRLI/SRAI | ✓ |
| Load | LB/LH/LW/LBU/LHU | ✓ |
| Store | SB/SH/SW | ✓ |
| Branch | BEQ/BNE/BLT/BGE/BLTU/BGEU | ✓ |
| U-Type | LUI/AUIPC | ✓ |
| J-Type | JAL/JALR | ✓ |

### Zicsr

| 指令 | 状态 |
|------|------|
| CSRRW/CSRRS/CSRRC | ✓ |
| CSRRWI/CSRRSI/CSRRCI | ✓ |
| ECALL/EBREAK | ✓ |
| MRET | ✓ |

## 目录结构

```
src/
├── common/
│   ├── Types.bsv          # 类型定义
│   └── MemInterface.bsv   # MemChannel接口
├── core/
│   ├── Core.bsv           # 流水线核心
│   ├── ALU.bsv            # ALU
│   ├── RegFile.bsv        # 寄存器堆
│   ├── Decoder.bsv        # 解码器
│   ├── CSR.bsv            # CSR
│   ├── HazardUnit.bsv     # 冒险检测
│   └── PrivilegedTypes.bsv # 特权类型
├── branch/
│   ├── BHT.bsv            # 分支历史表
│   └── BTB.bsv            # 分支目标缓冲
├── memory/
│   └── DMem.bsv           # 数据内存
├── peripheral/
│   ├── CLINT.bsv          # 定时器
│   ├── PLIC.bsv           # 中断控制器
│   └── UART.bsv           # UART
└── soc/
    ├── SOC.bsv            # SOC集成
    ├── TestBench.bsv      # 汇编测试平台
    └── MiniOSBench.bsv    # Mini-OS测试平台

mini-os/
├── include/
│   ├── types.h            # 类型定义
│   ├── task.h             # 任务API
│   ├── uart.h             # UART驱动
│   ├── timer.h            # 定时器API
│   └── os.h               # OS初始化
├── src/
│   ├── os.c               # OS核心
│   ├── task.c             # Round-Robin调度
│   ├── uart.c             # UART驱动
│   ├── timer.c            # 定时器配置
│   ├── trap.S             # Trap处理
│   ├── startup.S          # 启动代码
│   └── libc.c             # 基本库函数
├── tests/
│   └── round_robin_demo.c # 多任务演示
├── mini-os.ld             # 链接脚本
└── Makefile               # 编译配置
```