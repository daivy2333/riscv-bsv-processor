# RISC-V 流水线架构设计

## 核心设计原则

### 1. 阶段寄存器与前递网络分离

**问题根源**：之前的设计将 FIFOF 同时用于：
- 流水线寄存器（阶段间数据传递）
- 前递旁路源（同周期数据读取）
- 规则调度同步点

这导致 BSV 规则调度限制与流水线时序需求冲突。

**解决方案**：
- 阶段寄存器使用 `Reg#(Bool) valid + Reg#(T) payload` 结构
- 每个阶段只写自己的输出寄存器，下一阶段只读上一周期锁存值
- 前递网络只读 pipeline registers 的上周期稳定值

### 2. 流水线时序模型

```
周期 K 开始时：
  if_id_reg / id_ex_reg / ex_mem_reg / mem_wb_reg 都已经是稳定值

周期 K 内：
  IF 读取 pc，计算 next_if_id
  ID 读取 if_id_reg，计算 next_id_ex
  EX 读取 id_ex_reg，并读取 ex_mem_reg / mem_wb_reg / wb_history 做前递，计算 next_ex_mem
  MEM 读取 ex_mem_reg，计算 next_mem_wb
  WB 读取 mem_wb_reg，写 RegFile，并更新 wb_history

周期 K 结束时：
  顶层统一提交：
  if_id_reg  <= next_if_id
  id_ex_reg  <= next_id_ex
  ex_mem_reg <= next_ex_mem
  mem_wb_reg <= next_mem_wb
```

**核心规则**：周期 K 的所有 stage，都只读取周期 K 开始时已经稳定存在的寄存器内容。

### 3. 四个关键约束

| 约束 | 说明 |
|------|------|
| Load 不能从 ex_mem_reg 前递 | ex_mem_reg 对 load 只有地址/控制信息，真正 load data 要到 MEM 完成后才能进 mem_wb_reg |
| WB→ID 可保留但非必要 | wb_history 用于 ID 阶段早期比较，但功能正确性以 EX 前递后的值为准 |
| flush > stall > normal advance | flush/stall 需要明确优先级，否则分支/异常可能保留错误指令 |
| valid + payload 更易控制 | `Reg#(Bool) valid + Reg#(T) payload` 比 `Reg#(Maybe#(T))` 更容易单独控制 flush、stall、bubble |

---

## 五级流水线结构

```
┌──────────────────────────────────────────────────────────────────────┐
│                           mkCore (顶层模块)                           │
│                                                                       │
│  ┌─────────────────────────────────────────────────────────────────┐ │
│  │                 顶层统一维护的 Pipeline Registers                │ │
│  │  ┌───────────┐  ┌───────────┐  ┌───────────┐  ┌───────────┐     │ │
│  │  │ if_id_reg │  │ id_ex_reg │  │ ex_mem_reg│  │ mem_wb_reg│     │ │
│  │  │valid+payload│ │valid+payload│ │valid+payload│ │valid+payload│ │ │
│  │  └───────────┘  └───────────┘  └───────────┘  └───────────┘     │ │
│  └─────────────────────────────────────────────────────────────────┘ │
│       ↓ (写)        ↓ (写)        ↑ (读前递)      ↑ (读前递)         │
│                                                                       │
│  ┌──────────┐  ┌──────────┐  ┌──────────┐  ┌──────────┐  ┌──────────┐ │
│  │  IFStage │  │  IDStage │  │  EXStage │  │ MEMStage │  │  WBStage │ │
│  │  (计算)  │  │  (计算)  │  │  (计算)  │  │  (计算)  │  │  (计算)  │ │
│  └──────────┘  └──────────┘  └──────────┘  └──────────┘  └──────────┘ │
│                                                                       │
│  stage 内部封装成模块 → 通过 method 暴露组合计算结果                   │
│  阶段之间的状态推进 → 由顶层统一维护的 pipeline registers 决定         │
└──────────────────────────────────────────────────────────────────────┘
```

---

## 数据包结构

### IF_ID_Packet

| 字段 | 类型 | 说明 |
|------|------|------|
| pc | Addr | 当前指令 PC |
| instruction | Word | 取到的指令 |
| predicted_pc | Addr | 预测的 PC |
| predicted_taken | Bool | 是否预测分支命中 |
| priv_mode | Bit#(2) | 特权模式 |

### ID_EX_Packet

| 字段 | 类型 | 说明 |
|------|------|------|
| pc | Addr | 当前指令 PC |
| instruction | Word | 指令 |
| rs1_val / rs2_val | Word | 源寄存器值 |
| imm | Word | 立即数（已扩展） |
| rs1 / rs2 / rd | Bit#(5) | 寄存器编号 |
| alu_op | ALUOp | ALU 操作码 |
| branch_cond | BranchCond | 分支条件 |
| mem_op | MemOp | 内存操作类型 |
| is_branch / is_jump | Bool | 分支/跳转标志 |
| write_reg | Bool | 是否写寄存器 |
| use_imm | Bool | 是否使用立即数 |
| mem_width | MemWidth | 内存访问宽度 |
| mem_unsigned | Bool | 是否无符号扩展 |
| has_trap | Bool | 是否有陷阱 |
| trap_* | - | 陷阱相关信息 |

### EX_MEM_Packet

| 字段 | 类型 | 说明 |
|------|------|------|
| pc | Addr | 当前指令 PC |
| alu_result | Word | ALU 结果 / 分支目标 |
| rs2_val | Word | Store 数据 |
| rd | Bit#(5) | 目标寄存器 |
| mem_op | MemOp | 内存操作 |
| is_branch / is_jump | Bool | 分支/跳转标志 |
| branch_taken | Bool | 分支是否命中 |
| actual_target | Addr | 实际分支目标 |
| write_reg | Bool | 是否写寄存器 |
| is_load | Bool | 是否是 Load |
| mem_width / mem_unsigned | - | 内存访问参数 |

### MEM_WB_Packet

| 字段 | 类型 | 说明 |
|------|------|------|
| pc | Addr | 当前指令 PC |
| mem_data | Word | Load 数据 |
| alu_result | Word | ALU 结果 |
| rd | Bit#(5) | 目标寄存器 |
| write_reg | Bool | 是否写寄存器 |
| is_load | Bool | 是否是 Load |

---

## 前递网络

### 前递源与时序

| 前递路径 | 数据来源 | 时序边界 | 适用场景 |
|----------|----------|----------|----------|
| MEM→EX | ex_mem_reg | 周期 K 开始时已稳定 | ALU→ALU（非 Load） |
| WB→EX | mem_wb_reg | 周期 K 开始时已稳定 | Load→ALU，更早期 ALU→ALU |
| WB→ID | wb_history | 周期 K 开始时已稳定 | ID 阶段早期比较（可选） |

### 前递优先级

```
EX 阶段需要操作数值：
  1. 检查 ex_mem_reg.valid && !is_load && rd 匹配 → 使用 ex_mem_reg.payload
  2. 检查 mem_wb_reg.valid && rd 匹配 → 使用 mem_wb_reg.payload
  3. 检查 wb_history[N] && rd 匹配 → 使用 wb_history[N]
  4. 使用 ID 阶段从 RegFile 读取的值
```

### Load 特殊处理

**Load 不能从 ex_mem_reg 前递**：
- ex_mem_reg 在周期 K 时只包含 Load 地址和控制信息
- Load 数据在周期 K 的 MEM 阶段才从内存读取
- 在周期 K+1 开始时，Load 数据才稳定存在于 mem_wb_reg

**Load-Use 冒险处理**：
```
周期 N: Load 进入 EX
周期 N: ID 检测冒险 → stall=1, valid=False → 插入气泡
周期 N+1: stall 递减
周期 N+2: stall 清除
周期 N+3: Load 数据在 mem_wb_reg → WB→EX 前递可用
```

---

## 控制信号优先级

```
flush > stall > normal advance

处理顺序：
1. 检查 flush 条件（分支命中、陷阱、MRET）
   → 清除相关阶段的 valid 标志
   → 不推进任何数据

2. 检查 stall 条件（Load-Use 冒险）
   → 保持上游阶段 valid 不变
   → 下游阶段 valid 设为 False（气泡）

3. 正常推进
   → 各阶段 valid 和 payload 按时序更新
```

---

## 模块划分

| 模块 | 职责 | 接口 |
|------|------|------|
| IFStage | 取指、分支预测 | method next_if_id() |
| IDStage | 解码、冒险检测 | method next_id_ex() |
| EXStage | ALU/CSR、前递选择 | method next_ex_mem() |
| MEMStage | 内存访问、CLINT | method next_mem_wb() |
| WBStage | 写回、更新 wb_history | method wb_write() |
| ForwardingUnit | 前递数据选择 | method forward_val() |

---

## 指令集覆盖

### RV32I 指令

| 类型 | 指令 | 状态 |
|------|------|------|
| R-Type | ADD, SUB, SLL, SRL, SRA, SLT, SLTU, AND, OR, XOR | ✓ 已验证 |
| I-Type ALU | ADDI, SLTI, SLTIU, ANDI, ORI, XORI, SLLI, SRLI, SRAI | ✓ 已验证 |
| Load | LB, LH, LW, LBU, LHU | ✓ 已实现 |
| Store | SB, SH, SW | ✓ 已实现 |
| Branch | BEQ, BNE, BLT, BGE, BLTU, BGEU | ✓ 已验证 |
| U-Type | LUI, AUIPC | ✓ 已实现 |
| J-Type | JAL, JALR | ✓ 已验证 |

### Zicsr 扩展

| 指令 | 说明 | 状态 |
|------|------|------|
| CSRRW/CSRRWI | 读后写 | ✓ 已实现 |
| CSRRS/CSRRSI | 读后置位 | ✓ 已实现 |
| CSRRC/CSRRCI | 读后清除 | ✓ 已实现 |
| ECALL/EBREAK | 陷阱 | ✓ 已实现 |
| MRET | 陷阱返回 | ✓ 已实现 |

---

## CSR 寄存器

| 地址 | 名称 | 说明 |
|------|------|------|
| 0xF11-0xF14 | mvendorid/marchid/mimpid/mhartid | ID 寄存器 |
| 0x300 | mstatus | 机器状态 |
| 0x301 | misa | ISA 配置 |
| 0x304/0x344 | mie/mip | 中断使能/挂起 |
| 0x305 | mtvec | 陷阱向量 |
| 0x341-0x343 | mepc/mcause/mtval | 陷阱信息 |
| 0xB00-0xB03 | mcycle/mtime/mtimecmp/minstret | 计数器 |

---

## 内存布局

| 区域 | 范围 | 大小 |
|------|------|------|
| Boot ROM | 0x00000000 - 0x00000FFF | 4KB |
| CLINT | 0x02000000 - 0x0200FFFF | 64KB |
| PLIC | 0x0C000000 - 0x0C0FFFFF | 64KB |
| UART | 0x10000000 - 0x10000FFF | 4KB |
| RAM | 0x80000000 - 0x80FFFFFF | 16MB |

---

## 测试状态

| 测试 | 状态 | 说明 |
|------|------|------|
| simple_arith_test.s | ✓ PASSED | 基本算术 |
| load_test.s | ✓ PASSED | Load-Use 冒险 |
| csr_basic_test.s | ✓ PASSED | CSR 读写 |
| privilege_m_mode_test.s | ✓ PASSED | M-mode 操作 |
| csr_immediate_test.s | ✓ PASSED | CSR 立即数 |
| loop_test.s | ✓ PASSED | 循环分支（71 cycles） |
| pipeline_test.s | ✓ PASSED | 完整流水线（65 cycles） |

---

## 分支预测机制

### 预测流程

```
IF 阶段：
  1. 查询 BHT/BTB 获取预测
  2. 当前周期取原地址指令（不跳过）
  3. 预测只影响下一周期 PC

ID 阶段：
  1. 传递 predicted_taken/predicted_target 到 ID_EX_Packet

EX 阶段：
  1. 执行分支判断，得到实际 taken/not taken
  2. 检测 misprediction = (predicted_taken != branch_taken)
  3. 如果 misprediction：
     - 冲刷 if2id、id2ex
     - 重定向 PC 到正确地址
     - 设置 branch_flush 标志

冲刷恢复期间：
  - 禁用预测（!branch_flush_done && !no_pc_update）
  - 避免二次错误
```

### 关键修复点

| 问题 | 原因 | 修复 |
|------|------|------|
| 分支指令被跳过 | fetchStage 直接用预测目标取指 | 预测只影响下一周期 PC |
| 无法检测预测失败 | ID_EX_Packet 无预测信息 | 添加 predicted_taken/target 字段 |
| 预测失败后死循环 | 未重定向到顺序地址 | 添加 misprediction 处理分支 |
| 冲刷后二次错误 | 预测在冲刷恢复期间仍运行 | 禁用预测直到 flush_done 清除 |