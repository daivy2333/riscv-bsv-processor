# 流水线架构重构设计规格

日期：2026-04-18

## 问题背景

### 阻塞问题

loop_test.s 和 pipeline_test.s 超时，根本原因是 BSV 规则调度限制导致同周期 FIFO 数据传递不可行。

### 具体场景

```assembly
loop1:
    addi x10, x10, -1   ; x10 递减
    bne x10, x0, loop1  ; 应在 x10=0 时退出循环
```

**期望行为**：
- 周期 N+1: EX 阶段读取 x10=0，不跳转，退出循环

**实际行为**：
- 周期 N+1: executeStage 先执行，读取 ex2mem.first = 旧值(x10=1)，错误跳转

### 根源

BSV FIFO 特性：
- `fifo.enq` 和 `fifo.deq` 在规则结束时生效
- 同周期内 enq 后立即 `first`，读到的是旧值
- 流水线需要同周期前递，但 BSV 不允许

---

## 设计方案：阶段寄存器与前递网络分离

### 核心原则

**真正解决问题的是"每一级都有自己明确的时序边界"，即 stage reg + valid**。

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

### 四个关键约束

| 约束 | 说明 |
|------|------|
| Load 不能从 ex_mem_reg 前递 | ex_mem_reg 对 load 只有地址/控制信息，真正 load data 要到 MEM 完成后才能进 mem_wb_reg |
| WB→ID 可保留但非必要 | wb_history 用于 ID 阶段早期比较，但功能正确性以 EX 前递后的值为准 |
| flush > stall > normal advance | flush/stall 需要明确优先级，否则分支/异常可能保留错误指令 |
| valid + payload 更易控制 | `Reg#(Bool) valid + Reg#(T) payload` 比 `Reg#(Maybe#(T))` 更容易单独控制 flush、stall、bubble |

---

## 架构设计

### 整体结构

```
mkCore (顶层模块)
├── Pipeline Registers (顶层统一维护)
│   ├── if_id_reg: Reg#(Bool) valid + Reg#(IF_ID_Packet) payload
│   ├── id_ex_reg: Reg#(Bool) valid + Reg#(ID_EX_Packet) payload
│   ├── ex_mem_reg: Reg#(Bool) valid + Reg#(EX_MEM_Packet) payload
│   └── mem_wb_reg: Reg#(Bool) valid + Reg#(MEM_WB_Packet) payload
│
├── WB History (前递历史)
│   ├── wb_history_0: Reg#(Bool) valid + Reg#(Word) data + Reg#(Bit#(5)) rd
│   ├── wb_history_1: Reg#(Bool) valid + Reg#(Word) data + Reg#(Bit#(5)) rd
│
├── Stage Modules (计算逻辑)
│   ├── IFStage: method next_if_id()
│   ├── IDStage: method next_id_ex()
│   ├── EXStage: method next_ex_mem()
│   ├── MEMStage: method next_mem_wb()
│   ├── WBStage: method wb_write()
│
├── ForwardingUnit: method forward_val(rs, rd_needed)
│
└── Components
    ├── ALU, RegFile, Decoder, CSR
    ├── BHT, BTB
```

### Pipeline Register 结构

```bsv
// 替代 FIFOF，使用显式 valid + payload
Reg#(Bool) if_id_valid <- mkReg(False);
Reg#(IF_ID_Packet) if_id_payload <- mkRegU;

// 读写方式
// 读：周期 K 开始时已稳定
if (if_id_valid)
    IF_ID_Packet pkt = if_id_payload;

// 写：周期 K 结束时提交
if_id_valid <= next_valid;
if_id_payload <= next_payload;

// flush：只清除 valid
if_id_valid <= False;

// stall：保持 valid 不变，下游设为 False
if_id_valid <= if_id_valid;  // 保持
id_ex_valid <= False;        // 气泡
```

### 前递网络

```bsv
// ForwardingUnit 只读上周期稳定值
function Word forward_val(Bit#(5) rs, Bool is_load_stage);
    // MEM→EX (最高优先级，非 Load)
    if (ex_mem_reg.valid && !ex_mem_reg.payload.is_load && ex_mem_reg.payload.rd == rs)
        return ex_mem_reg.payload.alu_result;

    // WB→EX
    if (mem_wb_reg.valid && mem_wb_reg.payload.rd == rs)
        return mem_wb_reg.payload.is_load ? mem_wb_reg.payload.mem_data : mem_wb_reg.payload.alu_result;

    // WB History
    if (wb_history_0.valid && wb_history_0.rd == rs)
        return wb_history_0.data;
    if (wb_history_1.valid && wb_history_1.rd == rs)
        return wb_history_1.data;

    // 默认：使用 RegFile 值
    return regFile.read(rs);
endfunction
```

### 控制信号优先级

```
flush > stall > normal advance

处理流程：
1. 检查 flush 条件（分支命中、陷阱、MRET）
   → 清除相关阶段的 valid
   → 不推进任何数据

2. 检查 stall 条件（Load-Use 冒险）
   → 保持上游 valid 不变
   → 下游 valid 设为 False

3. 正常推进
   → 各阶段 valid 和 payload 按时序更新
```

---

## 模块接口设计

### IFStage

```bsv
interface IFStage;
    method Action run(Addr pc, Bool flush, Bool stall);
    method IF_ID_Packet next_if_id();
    method Addr next_pc();
endinterface
```

### IDStage

```bsv
interface IDStage;
    method Action run(IF_ID_Packet pkt, Word wb_fwd_rs1, Word wb_fwd_rs2);
    method ID_EX_Packet next_id_ex();
    method Bool detect_load_use_hazard();  // 冒险检测
endinterface
```

### EXStage

```bsv
interface EXStage;
    method Action run(ID_EX_Packet pkt, Word fwd_rs1, Word fwd_rs2);
    method EX_MEM_Packet next_ex_mem();
    method Bool branch_taken();
    method Addr branch_target();
endinterface
```

### MEMStage

```bsv
interface MEMStage;
    method Action run(EX_MEM_Packet pkt);
    method MEM_WB_Packet next_mem_wb();
endinterface
```

### WBStage

```bsv
interface WBStage;
    method Action run(MEM_WB_Packet pkt);
    method Action update_history();
endinterface
```

---

## 实现计划

### 步骤 1：创建 PipelineRegister 模块

```bsv
module mkPipelineRegister#(T default_val)(PipelineRegister#(T));
    Reg#(Bool) valid <- mkReg(False);
    Reg#(T) payload <- mkReg(default_val);

    method Bool isValid = valid;
    method T getPayload = payload;

    method Action set(T val);
        valid <= True;
        payload <= val;
    endmethod

    method Action clear();
        valid <= False;
    endmethod
endmodule
```

### 步骤 2：创建 ForwardingUnit

```bsv
module mkForwardingUnit(ForwardingUnit);
    // 读取 pipeline registers 的 method

    method Word forward_rs1(
        Bit#(5) rs,
        Bool ex_mem_valid, EX_MEM_Packet ex_mem,
        Bool mem_wb_valid, MEM_WB_Packet mem_wb,
        Bool wb0_valid, Word wb0_data, Bit#(5) wb0_rd,
        Bool wb1_valid, Word wb1_data, Bit#(5) wb1_rd,
        Word regfile_val
    );
        // 前递逻辑
    endmethod
endmodule
```

### 步骤 3：重构 Core.bsv

1. 替换 FIFOF 为 PipelineRegister
2. 创建 Stage 模块实例
3. 统一管理 pipeline registers 和控制信号
4. 实现前递网络调用

### 步骤 4：验证

1. 运行 loop_test.s
2. 运行 pipeline_test.s
3. 确保所有现有测试通过

---

## 预期效果

| 测试 | 当前状态 | 重构后预期 |
|------|----------|------------|
| loop_test.s | TIMEOUT | PASSED |
| pipeline_test.s | TIMEOUT | PASSED |
| 其他测试 | PASSED | PASSED |

---

## 保留功能

- 所有 RV32I 指令
- CSR 和特权级架构
- BHT/BTB 分支预测
- CLINT 定时器
- 中断检查框架

---

## 参考

- `docs/cpu-pipeline-architecture.md` - 流水线架构设计
- `docs/roadmap-embedded-os.md` - 开发阶段和里程碑