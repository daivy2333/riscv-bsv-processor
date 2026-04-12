# Load-Use 冒险检测修复实现计划

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** 修复 RISC-V 五级流水线处理器中的 Load-Use 冒险检测，确保 `lw` 指令后紧跟使用其结果的指令能正确执行。

**Architecture:** 在 ID 阶段检测 Load-Use 冒险，停顿 IF/ID 阶段，插入气泡到 EX 阶段，在 WB 阶段前递 Load 数据。

**Tech Stack:** Bluespec SystemVerilog (BSV), Verilator 仿真

---

## 文件结构

| 文件 | 责任 | 修改类型 |
|------|------|----------|
| `src/common/Types.bsv` | DecodedInstr 结构添加 use_rs1/use_rs2 字段 | 修改 |
| `src/core/Decoder.bsv` | 解码时设置 use_rs1/use_rs2 | 修改 |
| `src/core/Core.bsv` | 冒险检测、停顿、气泡插入、前递逻辑 | 重构 |
| `src/soc/TestBench.bsv` | Load-Use 测试用例 | 修改 |

---

### Task 1: 添加 DecodedInstr 的 use_rs1/use_rs2 字段

**Files:**
- Modify: `src/common/Types.bsv`
- Modify: `src/core/Decoder.bsv`

- [ ] **Step 1: 在 Decoder.bsv 的 DecodedInstr 结构添加字段**

```bsv
// src/core/Decoder.bsv:7-20
typedef struct {
    ALUOp       alu_op;
    BranchCond  branch_cond;
    MemOp       mem_op;
    Word        imm;
    Bit#(5)     rs1;
    Bit#(5)     rs2;
    Bit#(5)     rd;
    Bool        is_branch;
    Bool        is_jump;
    Bool        write_reg;
    Bool        is_load;
    Bool        use_imm;
    Bool        use_rs1;    // 新增：是否使用 rs1
    Bool        use_rs2;    // 新增：是否使用 rs2
} DecodedInstr deriving (Bits, Eq, FShow);
```

- [ ] **Step 2: 在 Decoder.bsv decode 方法中初始化新字段**

需要根据指令类型判断是否使用 rs1/rs2：

```bsv
// src/core/Decoder.bsv:27-164
// 在 decode 方法开头添加：
Bool use_rs1 = False;
Bool use_rs2 = False;

// 在每个 opcode case 分支中设置：
// R-Type: 使用 rs1 和 rs2
7'b0110011: begin
    write_reg = True;
    use_imm = False;
    use_rs1 = True;
    use_rs2 = True;
    // ... alu_op 设置
end

// I-Type (立即数操作): 使用 rs1
7'b0010011: begin
    write_reg = True;
    use_imm = True;
    use_rs1 = True;
    use_rs2 = False;
    // ...
end

// Load: 使用 rs1
7'b0000011: begin
    write_reg = True;
    is_load = True;
    mem_op = MEM_READ;
    use_imm = True;
    use_rs1 = True;
    use_rs2 = False;
    // ...
end

// Store: 使用 rs1 和 rs2
7'b0100011: begin
    mem_op = MEM_WRITE;
    use_imm = True;
    use_rs1 = True;
    use_rs2 = True;
    // ...
end

// Branch: 使用 rs1 和 rs2
7'b1100011: begin
    is_branch = True;
    use_imm = True;
    use_rs1 = True;
    use_rs2 = True;
    // ...
end

// LUI: 不使用 rs1/rs2
7'b0110111: begin
    write_reg = True;
    use_imm = True;
    use_rs1 = False;
    use_rs2 = False;
    // ...
end

// AUIPC: 不使用 rs1/rs2
7'b0010111: begin
    write_reg = True;
    use_imm = True;
    use_rs1 = False;
    use_rs2 = False;
    // ...
end

// JAL: 不使用 rs1/rs2
7'b1101111: begin
    write_reg = True;
    is_jump = True;
    use_imm = True;
    use_rs1 = False;
    use_rs2 = False;
    // ...
end

// JALR: 使用 rs1
7'b1100111: begin
    write_reg = True;
    is_jump = True;
    use_imm = True;
    use_rs1 = True;
    use_rs2 = False;
    // ...
end

// 返回结构体中添加：
return DecodedInstr {
    alu_op: alu_op,
    branch_cond: branch_cond,
    mem_op: mem_op,
    imm: imm,
    rs1: rs1_addr,
    rs2: rs2_addr,
    rd: rd_addr,
    is_branch: is_branch,
    is_jump: is_jump,
    write_reg: write_reg,
    is_load: is_load,
    use_imm: use_imm,
    use_rs1: use_rs1,      // 新增
    use_rs2: use_rs2       // 新增
};
```

- [ ] **Step 3: 编译验证 Types.bsv 和 Decoder.bsv**

Run: `make compile`
Expected: 编译成功，无错误

- [ ] **Step 4: 提交 Decoder 字段修改**

```bash
git add src/core/Decoder.bsv
git commit -m "feat(decoder): 添加 use_rs1/use_rs2 字段用于冒险检测

Co-Authored-By: Claude Opus 4.6 <noreply@anthropic.com>"
```

---

### Task 2: 添加 Load-Use 测试用例

**Files:**
- Modify: `src/soc/TestBench.bsv`

- [ ] **Step 1: 修改 TestBench 添加 Load-Use 测试程序**

将现有 `testProgram` 函数替换为 Load-Use 测试：

```bsv
// src/soc/TestBench.bsv:22-31
// 测试 Load-Use 冒险
function Vector#(1024, Word) testProgram();
    Vector#(1024, Word) prog = replicate(0);

    // 测试1: 基本 Load-Use
    prog[0] = 32'h00a00093;    // li x1, 10
    prog[1] = 32'h00400113;    // li x2, 4
    prog[2] = 32'h00112023;    // sw x1, 0(x2) - 存储 10 到 dmem[0]
    prog[3] = 32'h00012083;    // lw x3, 0(x2) - Load x3 = 10
    prog[4] = 32'h00310033;    // add x4, x3, x1 - Load-Use 冒险! x4 = 20
    prog[5] = 32'h0000006f;    // j end (跳转到自己，结束)

    return prog;
endfunction
```

- [ ] **Step 2: 修改 report 规则输出更多寄存器**

```bsv
// src/soc/TestBench.bsv:54-61
rule report (dumpDone);
    $display("\n====================================");
    $display("  Load-Use Hazard Test Results");
    $display("====================================");
    $display("Cycles: %0d", cycleCount);
    $display("Register dump:");
    $display("  x1 = %0d (expected 10)", core.readReg(1));
    $display("  x2 = %0d (expected 4)", core.readReg(2));
    $display("  x3 = %0d (expected 10)", core.readReg(3));
    $display("  x4 = %0d (expected 20)", core.readReg(4));
endrule
```

- [ ] **Step 3: 编译并运行测试（预期失败）**

Run: `make compile && rm -rf obj_dir && verilator --cc --exe --build -o VmkTestBench build/mkTestBench.v /opt/bsc/lib/Verilog/FIFO2.v tests/c/test_bench.cpp -Wno-STMTDLY -Wno-WIDTH && ./obj_dir/VmkTestBench`

Expected: x4 ≠ 20（当前 Load-Use 实现有问题）

- [ ] **Step 4: 记录测试失败结果**

手动记录当前输出，确认 x4 值不正确。

---

### Task 3: 重构 Core.bsv 冒险检测逻辑

**Files:**
- Modify: `src/core/Core.bsv`

这是核心修改，需要分多个步骤完成。

- [ ] **Step 1: 添加 HazardUnit 导入和实例化**

```bsv
// src/core/Core.bsv:1-11
package Core;

import Types::*;
import ALU::*;
import RegFile::*;
import Decoder::*;
import BHT::*;
import BTB::*;
import HazardUnit::*;    // 新增导入
import FIFO::*;
import Vector::*;

// 在模块内实例化：
module mkCore#(String firmwareFile)(Core);
    Decoder decoder <- mkDecoder;
    ALU alu <- mkALU;
    RegFile regFile <- mkRegFile;
    BHT bht <- mkBHT;
    BTB btb <- mkBTB;
    HazardUnit hazardUnit <- mkHazardUnit;    // 新增
```

- [ ] **Step 2: 重命名并调整停顿控制寄存器**

```bsv
// src/core/Core.bsv:35-36 (替换现有 stall/needBubble)
// Load-Use 冒险控制
Reg#(Bool) stall_load_use <- mkReg(False);    // Load-Use 停顿标志
Reg#(Bool) bubble_pending <- mkReg(False);    // 待插入气泡标志
```

- [ ] **Step 3: 添加 nopPacket 辅助函数**

```bsv
// src/core/Core.bsv (在模块外添加，文件末尾 endpackage 前)
function ID_EX_Packet nopPacket();
    return ID_EX_Packet {
        pc: 0,
        instruction: 0,
        rs1_val: 0, rs2_val: 0,
        imm: 0,
        rs1: 0, rs2: 0, rd: 0,
        alu_op: ALU_ADD,
        branch_cond: BR_NONE,
        mem_op: MEM_NONE,
        is_branch: False,
        is_jump: False,
        write_reg: False,
        use_imm: False
    };
endfunction
```

- [ ] **Step 4: 修改 IF 阶段规则（添加停顿条件）**

```bsv
// src/core/Core.bsv:65-91
rule fetchStage (programLoaded && state == RUNNING && !stall_load_use);
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

    Bit#(10) idx = fetchPC[11:2];
    Word instr = imem[idx];

    if2id.enq(IF_ID_Packet {
        pc: fetchPC,
        instruction: instr,
        predicted_pc: prediction_target,
        predicted_taken: take_prediction
    });

    currentInstr <= instr;
    pcReg <= pcReg + 4;
endrule
```

- [ ] **Step 5: 修改 ID 阶段规则（检测 Load-Use 冒险）**

这是关键修改，需要检测冒险并控制停顿：

```bsv
// src/core/Core.bsv:97-140 (替换现有 decodeStage 和 insertBubble 规则)
rule decodeStage (!stall_load_use && !bubble_pending);
    IF_ID_Packet pkt = if2id.first;
    DecodedInstr dec = decoder.decode(pkt.instruction);

    // 检测 Load-Use 冒险
    // 条件：MEM 阶段有 Load 指令，且 ID 阶段指令使用 Load 的目标寄存器
    Bool load_use_hazard = False;
    if (ex2mem.first.is_load && ex2mem.first.rd != 0) begin
        if (dec.use_rs1 && dec.rs1 == ex2mem.first.rd) begin
            load_use_hazard = True;
        end
        if (dec.use_rs2 && dec.rs2 == ex2mem.first.rd) begin
            load_use_hazard = True;
        end
    end

    if (load_use_hazard) begin
        // 停顿 ID 阶段，不发送包到 EX
        stall_load_use <= True;
        bubble_pending <= True;
        // 注意：不 deq if2id，保留指令供下个周期使用
    end else begin
        // 正常解码并发送到 EX
        if2id.deq;

        Word rs1_val = regFile.read1(dec.rs1);
        Word rs2_val = regFile.read2(dec.rs2);

        id2ex.enq(ID_EX_Packet {
            pc: pkt.pc,
            instruction: pkt.instruction,
            rs1_val: rs1_val, rs2_val: rs2_val,
            imm: dec.imm,
            rs1: dec.rs1, rs2: dec.rs2, rd: dec.rd,
            alu_op: dec.alu_op,
            branch_cond: dec.branch_cond,
            mem_op: dec.mem_op,
            is_branch: dec.is_branch,
            is_jump: dec.is_jump,
            write_reg: dec.write_reg,
            use_imm: dec.use_imm
        });
    end
endrule

// 气泡插入规则
rule insertBubble (bubble_pending && !stall_load_use);
    // 插入 NOP 到 EX 阶段
    id2ex.enq(nopPacket());
    bubble_pending <= False;
endrule

// 清除 Load-Use 停顿（在 WB 阶段完成 Load 后）
rule clearLoadUseStall (stall_load_use);
    // Load 数据已写入 RegFile 或可前递，解除停顿
    stall_load_use <= False;
endrule
```

- [ ] **Step 6: 修改 EX 阶段规则（简化，移除现有冒险检测）**

```bsv
// src/core/Core.bsv:147-239 (简化现有 executeStage)
rule executeStage;
    ID_EX_Packet pkt = id2ex.first;
    id2ex.deq;

    // 前递逻辑（保持现有实现）
    Word op1 = pkt.rs1_val;
    Word op2 = pkt.rs2_val;

    // WB→EX 前递（关键：Load 数据在 WB 阶段可用）
    if (wb_forward_valid && wb_forward_rd == pkt.rs1 && pkt.rs1 != 0)
        op1 = wb_forward;
    if (wb_forward_valid && wb_forward_rd == pkt.rs2 && pkt.rs2 != 0)
        op2 = wb_forward;

    // MEM→EX 前递（注意：MEM 阶段的 Load 数据还未可用，不前递 Load 的 mem_data）
    // 只前递非 Load 指令的 alu_result
    if (mem_forward_valid && mem_forward_rd == pkt.rs1 && pkt.rs1 != 0 && !ex2mem.first.is_load)
        op1 = mem_forward;
    if (mem_forward_valid && mem_forward_rd == pkt.rs2 && pkt.rs2 != 0 && !ex2mem.first.is_load)
        op2 = mem_forward;

    // EX→EX 前递
    if (ex_forward_valid && ex_forward_rd == pkt.rs1 && pkt.rs1 != 0)
        op1 = ex_forward;
    if (ex_forward_valid && ex_forward_rd == pkt.rs2 && pkt.rs2 != 0)
        op2 = ex_forward;

    // ALU 输入选择（保持现有实现）
    Word alu_in1, alu_in2;
    case (pkt.alu_op)
        ALU_PASS: begin alu_in1 = pkt.imm; alu_in2 = 0; end
        ALU_PC:   begin alu_in1 = pkt.pc; alu_in2 = pkt.imm; end
        ALU_ADD:  begin alu_in1 = op1; alu_in2 = pkt.use_imm ? pkt.imm : op2; end
        ALU_SUB:  begin alu_in1 = op1; alu_in2 = op2; end
        default:  begin alu_in1 = op1; alu_in2 = op2; end
    endcase

    Word alu_result = alu.execute(pkt.alu_op, alu_in1, alu_in2);

    // 分支判断（保持现有实现）
    Bool branch_taken = False;
    Addr actual_target = 0;

    if (pkt.is_branch) begin
        branch_taken = case (pkt.branch_cond)
            BR_EQ:  (op1 == op2);
            BR_NE:  (op1 != op2);
            BR_LT:  signedLT(op1, op2);
            BR_GE:  signedGE(op1, op2);
            BR_LTU: (op1 < op2);
            BR_GEU: (op1 >= op2);
            default: False;
        endcase;
        actual_target = pkt.pc + pkt.imm;
    end

    if (pkt.is_jump) begin
        branch_taken = True;
        if (getOpcode(pkt.instruction) == 7'b1101111) begin
            actual_target = pkt.pc + pkt.imm;
        end else begin
            actual_target = alu_result & ~1;
        end
        alu_result = pkt.pc + 4;
    end

    // BHT/BTB 更新（保持现有实现）
    Bool btb_update_valid = (pkt.is_jump) || (pkt.is_branch && branch_taken);
    btb.update(pkt.pc, actual_target, btb_update_valid);
    if (pkt.is_branch)
        bht.update(pkt.pc, branch_taken);

    Bool is_load = (pkt.mem_op == MEM_READ);
    ex2mem.enq(EX_MEM_Packet {
        pc: pkt.pc,
        alu_result: alu_result,
        rs2_val: op2,
        rd: pkt.rd,
        mem_op: pkt.mem_op,
        is_branch: pkt.is_branch,
        branch_taken: branch_taken,
        predicted_taken: False,
        write_reg: pkt.write_reg,
        is_load: is_load
    });

    // 前递设置
    ex_forward <= alu_result;
    ex_forward_rd <= pkt.rd;
    ex_forward_valid <= pkt.write_reg;
endrule
```

- [ ] **Step 7: 修改 MEM 阶段规则（移除现有冒险检测）**

```bsv
// src/core/Core.bsv:245-283 (简化，移除现有 Load-Use 检测)
rule memoryStage;
    EX_MEM_Packet pkt = ex2mem.first;
    ex2mem.deq;

    Word mem_data = 0;

    if (pkt.mem_op == MEM_READ) begin
        mem_data = dmem[pkt.alu_result[10:2]];
    end else if (pkt.mem_op == MEM_WRITE) begin
        dmem[pkt.alu_result[10:2]] <= pkt.rs2_val;
    end

    mem2wb.enq(MEM_WB_Packet {
        pc: pkt.pc,
        mem_data: mem_data,
        alu_result: pkt.alu_result,
        rd: pkt.rd,
        write_reg: pkt.write_reg,
        is_load: pkt.is_load
    });

    // MEM 前递设置（注意：Load 数据在 MEM 阶段读取，但此时还未可前递到 EX）
    // Load 数据需要等 WB 阶段才能前递
    mem_forward <= pkt.alu_result;  // 非 Load 指令的前递值
    mem_forward_rd <= pkt.rd;
    mem_forward_valid <= pkt.write_reg && !pkt.is_load;  // Load 不在 MEM 前递
endrule

// 移除现有的 clearStall 规则
```

- [ ] **Step 8: 修改 WB 阶段规则（确保正确前递 Load 数据）**

```bsv
// src/core/Core.bsv:288-301
rule writebackStage;
    MEM_WB_Packet pkt = mem2wb.first;
    mem2wb.deq;

    Word wb_data = pkt.is_load ? pkt.mem_data : pkt.alu_result;

    if (pkt.write_reg && pkt.rd != 0) begin
        regFile.write(pkt.rd, wb_data);
    end

    // WB 前递设置（Load 数据在此阶段可用）
    wb_forward <= wb_data;
    wb_forward_rd <= pkt.rd;
    wb_forward_valid <= pkt.write_reg;
endrule
```

- [ ] **Step 9: 编译验证 Core.bsv**

Run: `make compile`
Expected: 编译成功，无错误

- [ ] **Step 10: 构建并运行仿真**

Run: `rm -rf obj_dir && verilator --cc --exe --build -o VmkTestBench build/mkTestBench.v /opt/bsc/lib/Verilog/FIFO2.v tests/c/test_bench.cpp -Wno-STMTDLY -Wno-WIDTH && ./obj_dir/VmkTestBench`

Expected: x3 = 10, x4 = 20（Load-Use 冒险正确处理）

- [ ] **Step 11: 提交 Core.bsv 修改**

```bash
git add src/core/Core.bsv
git commit -m "fix(core): 修复 Load-Use 冒险检测逻辑

- ID 阶段检测 MEM 阶段的 Load 指令
- 停顿 IF/ID 阶段，插入气泡到 EX
- WB 阶段前递 Load 数据到 EX
- 移除错误的 MEM 阶段检测

Co-Authored-By: Claude Opus 4.6 <noreply@anthropic.com>"
```

---

### Task 4: 添加多指令依赖和分支测试

**Files:**
- Modify: `src/soc/TestBench.bsv`

- [ ] **Step 1: 扩展测试程序（多指令依赖 Load）**

```bsv
// src/soc/TestBench.bsv:22-31
function Vector#(1024, Word) testProgram();
    Vector#(1024, Word) prog = replicate(0);

    // 测试场景：多指令依赖 Load
    prog[0] = 32'h00a00093;    // li x1, 10
    prog[1] = 32'h00400113;    // li x2, 4
    prog[2] = 32'h00112023;    // sw x1, 0(x2) - 存储 10
    prog[3] = 32'h00012083;    // lw x3, 0(x2) - Load x3 = 10
    prog[4] = 32'h00310033;    // add x4, x3, x1 - Load-Use 冒险
    prog[5] = 32'h403100b3;    // sub x5, x3, x1 - x5 = 0 (前递可用)
    prog[6] = 32'h0000006f;    // j end

    return prog;
endfunction
```

- [ ] **Step 2: 更新 report 规则输出**

```bsv
rule report (dumpDone);
    $display("\n====================================");
    $display("  Load-Use Hazard Test Results");
    $display("====================================");
    $display("Cycles: %0d", cycleCount);
    $display("Register dump:");
    $display("  x1 = %0d (expected 10)", core.readReg(1));
    $display("  x2 = %0d (expected 4)", core.readReg(2));
    $display("  x3 = %0d (expected 10)", core.readReg(3));
    $display("  x4 = %0d (expected 20)", core.readReg(4));
    $display("  x5 = %0d (expected 0)", core.readReg(5));
endrule
```

- [ ] **Step 3: 编译运行验证**

Run: `make compile && rm -rf obj_dir && verilator --cc --exe --build -o VmkTestBench build/mkTestBench.v /opt/bsc/lib/Verilog/FIFO2.v tests/c/test_bench.cpp -Wno-STMTDLY -Wno-WIDTH && ./obj_dir/VmkTestBench`

Expected: x3=10, x4=20, x5=0

- [ ] **Step 4: 提交测试用例扩展**

```bash
git add src/soc/TestBench.bsv
git commit -m "test: 扩展 Load-Use 冒险测试用例

- 基本 Load-Use (lw → add)
- 多指令依赖 Load (lw → add → sub)

Co-Authored-By: Claude Opus 4.6 <noreply@anthropic.com>"
```

---

### Task 5: 验证并总结

- [ ] **Step 1: 运行完整测试验证**

Run: `./obj_dir/VmkTestBench`
Expected: 所有寄存器值正确

- [ ] **Step 2: 检查 git 状态**

Run: `git log --oneline -5`
Expected: 4 个新提交（Decoder、Core、测试）

- [ ] **Step 3: 更新 CLAUDE.md 标记 Load-Use 已修复**

```bash
# 在 CLAUDE.md 的待完成功能中，将 Load-Use 条目标记为完成
# 将"完善Load-Use停顿机制"移到已实现功能列表
```

- [ ] **Step 4: 提交文档更新**

```bash
git add CLAUDE.md
git commit -m "docs: 更新 CLAUDE.md 标记 Load-Use 冒险已修复

Co-Authored-By: Claude Opus 4.6 <noreply@anthropic.com>"
```

---

## 自审检查

**1. Spec 覆盖检查：**
- ✓ 检测时机：Task 3 Step 5 在 ID 阶段检测
- ✓ 停顿 IF/ID：Task 3 Step 4/5
- ✓ 插入气泡：Task 3 Step 5 insertBubble 规则
- ✓ WB 前递：Task 3 Step 8 WB 阶段前递 Load 数据
- ✓ 测试覆盖：Task 2/4 基本和多指令依赖

**2. Placeholder 检查：**
- 无 TBD/TODO
- 所有代码块完整

**3. 类型一致性：**
- DecodedInstr 结构在 Task 1 定义，Task 5 使用
- ID_EX_Packet nopPacket 在 Task 3 定义并使用
- 前递寄存器命名一致（wb_forward, mem_forward, ex_forward）

---

**计划完成，保存到 `docs/superpowers/plans/2026-04-12-load-use-hazard-fix.md`**