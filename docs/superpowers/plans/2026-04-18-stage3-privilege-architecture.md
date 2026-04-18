# Stage 3: 特权级架构实现计划

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** 实现 RISC-V 特权架构，支持 M/S/U 三级特权模式、CSR 寄存器和异常/中断处理机制。

**Architecture:**
- 添加 CSR 寄存器文件（Machine 模式核心 CSR）
- 实现三级特权模式（M/S/U）切换逻辑
- 在 ID 阶段检测异常（非法指令、ECALL 等）
- 在 EX/MEM 阶段处理中断和陷阱
- 支持 CSR 访问指令（CSRRW、CSRRS、CSRRC 等）

**Tech Stack:** BSV (Bluespec SystemVerilog), Verilator 仿真

---

## 文件结构

```
src/
  core/
    Core.bsv              # 修改：集成 CSR 和陷阱处理
    Decoder.bsv           # 修改：添加 CSR 指令解码
    CSR.bsv               # 新增：CSR 寄存器文件
    PrivilegedTypes.bsv   # 新增：特权级相关类型定义
  soc/
    TestBench.bsv         # 修改：添加特权级测试
    TestProgram.bsv       # 修改：生成带 CSR 测试的程序

tests/
  assembly/
    privilege_m_mode_test.s    # 新增：Machine 模式测试
    csr_basic_test.s          # 新增：CSR 基本读写测试
    exception_test.s           # 新增：异常处理测试
    interrupt_test.s           # 新增：中断处理测试
```

---

## Task 1: 添加特权级类型定义

**Files:**
- Create: `src/core/PrivilegedTypes.bsv`

> ⚠️ **审计修正**: mstatus 字段位置按照 RISC-V spec 修正

- [ ] **Step 1: 创建特权级类型文件**

```bsv
// src/core/PrivilegedTypes.bsv
package PrivilegedTypes;

import Types::*;

// ============================================================
// 特权级别
// ============================================================

typedef enum {
    M_MODE = 2'b11,    // Machine Mode (最高特权)
    S_MODE = 2'b01,    // Supervisor Mode
    U_MODE = 2'b00     // User Mode (最低特权)
} PrivilegeMode deriving (Bits, Eq, FShow);

// ============================================================
// CSR 地址
// ============================================================

typedef enum {
    // Machine Information Registers (只读)
    CSR_MVENDORID = 12'hF11,
    CSR_MARCHID   = 12'hF12,
    CSR_MIMPID    = 12'hF13,
    CSR_MHARTID   = 12'hF14,

    // Machine Trap Setup
    CSR_MSTATUS   = 12'h300,
    CSR_MISA      = 12'h301,
    CSR_MIE       = 12'h304,
    CSR_MTVEC     = 12'h305,

    // Machine Trap Handling
    CSR_MEPC      = 12'h341,
    CSR_MCAUSE    = 12'h342,
    CSR_MTVAL     = 12'h343,

    // Machine Interrupt Pending (新增)
    CSR_MIP       = 12'h344,

    // Machine Counter/Timer - 注意地址分开！
    CSR_MCYCLE    = 12'hB00,
    CSR_MTIME     = 12'hB01,
    CSR_MTIMECMP  = 12'hB02,
    CSR_MINSTRET  = 12'hB03,   // 修正：与 mtimecmp 分开

    // Machine Counter Setup
    CSR_MCOUNTEREN = 12'h306,

    // Supervisor Registers (S-mode 基础)
    CSR_SSTATUS   = 12'h100,
    CSR_SIE       = 12'h104,
    CSR_STVEC     = 12'h105,
    CSR_SEPC      = 12'h141,
    CSR_SCAUSE    = 12'h142,
    CSR_STVAL     = 12'h143,
    CSR_SATP      = 12'h180
} CSRArea deriving (Bits, Eq, FShow);

// ============================================================
// 异常原因编码
// ============================================================

typedef enum {
    EXC_INST_MISALIGNED   = 0,
    EXC_INST_ACCESS_FAULT = 1,
    EXC_ILLEGAL_INST      = 2,
    EXC_BREAKPOINT         = 3,
    EXC_LOAD_MISALIGNED   = 4,
    EXC_LOAD_ACCESS_FAULT = 5,
    EXC_STORE_MISALIGNED  = 6,
    EXC_STORE_ACCESS_FAULT = 7,
    EXC_ECALL_U           = 8,
    EXC_ECALL_S           = 9,
    EXC_ECALL_M           = 11,
    EXC_INST_PAGE_FAULT   = 12,
    EXC_LOAD_PAGE_FAULT   = 13,
    EXC_STORE_PAGE_FAULT  = 15
} ExceptionCode deriving (Bits, Eq, FShow);

// 中断（mcause[31] = 1）
typedef enum {
    INT_SOFTWARE_S        = 1,
    INT_SOFTWARE_M        = 3,
    INT_TIMER_S           = 5,
    INT_TIMER_M           = 7,
    INT_EXTERNAL_S        = 9,
    INT_EXTERNAL_M        = 11
} InterruptCode deriving (Bits, Eq, FShow);

// ============================================================
// 陷阱信息包
// ============================================================

typedef struct {
    Addr         epc;
    ExceptionCode cause;
    Bool         is_interrupt;
    Addr         tval;
    PrivilegeMode mode;
} TrapInfo deriving (Bits, Eq, FShow);

// ============================================================
// CSR 指令类型
// ============================================================

typedef enum {
    CSR_OP_CLR,
    CSR_OP_SET,
    CSR_OP_WRITE,
    CSR_OP_READ
} CSROp deriving (Bits, Eq, FShow);

// ============================================================
// mstatus 域分解（按照 RISC-V spec 修正位置）
// ============================================================

typedef struct {
    Bit#(1) uie;      // [0]  U-mode 中断使能
    Bit#(1) sie;      // [1]  S-mode 中断使能
    Bit#(1) wie;      // [3]  ← 修正！M-mode 中断使能在 bit 3
    Bit#(1) upie;     // [4]  U-mode 上一级中断使能
    Bit#(1) spie;     // [5]  S-mode 上一级中断使能
    Bit#(1) mpie;     // [7]  M-mode 上一级中断使能
    Bit#(2) spp;      // [8]  S-mode 上一级特权模式
    Bit#(2) mpp;      // [11:10] M-mode 上一级特权模式 ← 修正！是 2 位
    Bit#(1) mprv;     // [17]
    Bit#(1) sum;      // [18]
    Bit#(1) mxr;      // [19]
    Bit#(1) tvm;      // [20]
    Bit#(1) tw;       // [21]
    Bit#(1) tsr;      // [22]
    Bit#(4) fs;       // [14:12]
    Bit#(2) xs;       // [16:15]
    Bit#(1) sd;       // [31] 只读，反映 xs|fs 状态
    Bit#(26) reserved;
} MStatus deriving (Bits, Eq, FShow);

endpackage
```

- [ ] **Step 2: 运行编译验证**

Run: `make compile 2>&1 | head -50`
Expected: 新文件无语法错误

- [ ] **Step 3: 提交**

```bash
git add src/core/PrivilegedTypes.bsv
git commit -m "feat(types): add privilege mode and CSR type definitions"
```

---

## Task 2: 创建 CSR 寄存器模块

**Files:**
- Create: `src/core/CSR.bsv`

> ⚠️ **审计修正**:
> - 添加 mip CSR 寄存器
> - 修复 mtimecmp/minstret 地址冲突
> - 添加 MIP/MEI/MSI/MTI 挂起标志

- [ ] **Step 1: 创建 CSR 寄存器模块**

```bsv
// src/core/CSR.bsv
package CSR;

import Types::*;
import PrivilegedTypes::*;

// ============================================================
// CSR 寄存器文件接口
// ============================================================

interface CSRs;
    method Word readCSR(Bit#(12) addr);
    method Action writeCSR(Bit#(12) addr, Word data);
    method Word atomicOp(Bit#(12) addr, Word rs1_val, CSROp op);
    method Word atomicOpImm(Bit#(12) addr, Bit#(5) zimm, CSROp op);  // 新增：立即数版本

    method PrivilegeMode currentMode();
    method Action setMode(PrivilegeMode mode);

    method Addr getTrapVector(TrapInfo trap);

    // 中断状态
    method Bool hasPendingInterrupt();
    method Action setMEIP(Bool v);
    method Action setMSIP(Bool v);
    method Action setMTIP(Bool v);

    // 时钟/计数器（64 位）
    method Action incrementCycle;
endinterface

module mkCSRs(CSRs);
    // ========== Machine Information Registers (只读) ==========
    Reg#(Word) mvendorid <- mkReg(0);
    Reg#(Word) marchid <- mkReg(0);
    Reg#(Word) mimpid <- mkReg(0);
    Reg#(Word) mhartid <- mkReg(0);

    // ========== Machine Trap Setup ==========
    Reg#(Word) mstatus <- mkReg(0);
    Reg#(Word) misa <- mkReg(32'h40001100);
    Reg#(Word) mie <- mkReg(0);
    Reg#(Word) mtvec <- mkReg(32'h80000000);

    // ========== Machine Trap Handling ==========
    Reg#(Word) mepc <- mkReg(0);
    Reg#(Word) mcause <- mkReg(0);
    Reg#(Word) mtval <- mkReg(0);

    // ========== Machine Interrupt Pending (新增) ==========
    Reg#(Word) mip <- mkReg(0);

    // ========== Machine Counter/Timer (64 位) ==========
    Reg#(Bit#(64)) mcycle <- mkReg(0);
    Reg#(Bit#(64)) minstret <- mkReg(0);
    Reg#(Bit#(64)) mtime <- mkReg(0);
    Reg#(Bit#(64)) mtimecmp <- mkReg(64'hFFFF_FFFF_FFFF_FFFF);

    Reg#(Word) mcounteren <- mkReg(0);

    // ========== 当前特权模式 ==========
    Reg#(PrivilegeMode) priv_mode <- mkReg(M_MODE);

    // ========== 辅助函数 ==========

    function MStatus unpackMStatus(Word w);
        return MStatus {
            uie:      w[0],
            sie:      w[1],
            wie:      w[3],      // 修正：MIE 在 bit 3
            upie:     w[4],
            spie:     w[5],
            mpie:     w[7],
            spp:      w[8],
            mpp:      w[11:10],  // 修正：2 位
            mprv:     w[17],
            sum:      w[18],
            mxr:      w[19],
            tvm:      w[20],
            tw:       w[21],
            tsr:      w[22],
            fs:       w[14:12],
            xs:       w[16:15],
            sd:       w[31],
            reserved: 0
        };
    endfunction

    function Word packMStatus(MStatus s);
        Bit#(1) sd = s.xs[0] | s.xs[1] | |s.fs;  // 计算 sd
        return {sd, 26'b0, s.tsr, s.tw, s.tvm, s.mxr, s.sum, s.mprv,
                2'b0, s.mpp, 1'b0, s.spp, 1'b0, s.mpie, 1'b0, s.spie, 1'b0, s.upie, 1'b0, s.wie, 1'b0, s.sie, 1'b0, s.uie};
    endfunction

    function Bool isReadOnlyCSR(Bit#(12) addr);
        return (addr[11:8] == 4'hF);  // 0xFxx 只读
    endfunction

    // ========== 方法实现 ==========

    method Word readCSR(Bit#(12) addr);
        case (addr)
            12'hF11: return mvendorid;
            12'hF12: return marchid;
            12'hF13: return mimpid;
            12'hF14: return mhartid;
            12'h300: return mstatus;
            12'h301: return misa;
            12'h304: return mie;
            12'h305: return mtvec;
            12'h341: return mepc;
            12'h342: return mcause;
            12'h343: return mtval;
            12'h344: return mip;        // 新增
            12'hB00: return mcycle[31:0];
            12'hB01: return mtime[31:0];
            12'hB02: return mtimecmp[31:0];
            12'hB03: return minstret[31:0];  // 修正：分开
            12'hB80: return mcycle[63:32];
            12'hB81: return mtime[63:32];
            12'hB82: return mtimecmp[63:32];
            12'hB83: return minstret[63:32];
            12'h306: return mcounteren;
            default: return 0;
        endcase
    endmethod

    method Action writeCSR(Bit#(12) addr, Word data);
        if (!isReadOnlyCSR(addr)) begin
            case (addr)
                12'h300: mstatus <= data;
                12'h304: mie <= data;
                12'h305: mtvec <= data;
                12'h341: mepc <= data;
                12'h342: mcause <= data;
                12'h343: mtval <= data;
                12'h344: mip <= data;
                12'hB00: mcycle[31:0] <= data;
                12'hB01: mtime[31:0] <= data;
                12'hB02: mtimecmp[31:0] <= data;
                12'hB03: minstret[31:0] <= data;
                12'hB80: mcycle[63:32] <= data;
                12'hB81: mtime[63:32] <= data;
                12'hB82: mtimecmp[63:32] <= data;
                12'hB83: minstret[63:32] <= data;
                12'h306: mcounteren <= data;
            endcase
        end
    endmethod

    method Word atomicOp(Bit#(12) addr, Word rs1_val, CSROp op);
        Word csr_val = readCSR(addr);
        Word result = csr_val;

        case (op)
            CSR_OP_WRITE: result = rs1_val;
            CSR_OP_SET:   result = csr_val | rs1_val;
            CSR_OP_CLR:   result = csr_val & ~rs1_val;
            CSR_OP_READ:  result = csr_val;
        endcase

        if (op != CSR_OP_READ)
            writeCSR(addr, result);

        return csr_val;
    endmethod

    // 新增：立即数版本 (CSRRWI, CSRRSI, CSRRCI)
    method Word atomicOpImm(Bit#(12) addr, Bit#(5) zimm, CSROp op);
        return atomicOp(addr, zeroExtend(zimm), op);
    endmethod

    method PrivilegeMode currentMode();
        return priv_mode;
    endmethod

    method Action setMode(PrivilegeMode mode);
        priv_mode <= mode;
    endmethod

    method Addr getTrapVector(TrapInfo trap);
        Word base = mtvec & ~3;
        Bit#(2) mode = mtvec[1:0];

        if (mode == 2'b00) begin
            return base;
        end else begin
            if (trap.is_interrupt) begin
                Bit#(5) cause = pack(trap.cause)[4:0];
                return base + zeroExtend(cause) * 4;
            end else begin
                return base;
            end
        end
    endmethod

    method Bool hasPendingInterrupt();
        MStatus ms = unpackMStatus(mstatus);
        Word mie_val = mie;
        Word mip_val = mip;
        return ((mie_val & mip_val) != 0) && (ms.wie == 1);  // MIE 全局使能
    endmethod

    method Action setMEIP(Bool v);
        Bit#(1) meip_bit = v ? 1'b1 : 1'b0;
        mip <= {mip[31:12], 1'b0, mip[10:9], meip_bit, mip[7:0]};  // MEIP 在 bit 11
    endmethod

    method Action setMSIP(Bool v);
        Bit#(1) msip_bit = v ? 1'b1 : 1'b0;
        mip <= {mip[31:12], 1'b0, mip[10:8], msip_bit, mip[6:0]};  // MSIP 在 bit 3
    endmethod

    method Action setMTIP(Bool v);
        Bit#(1) mtip_bit = v ? 1'b1 : 1'b0;
        mip <= {mip[31:12], 1'b0, mip[10:9], 1'b0, mip[7:4], mtip_bit, mip[2:0]};  // MTIP 在 bit 7
    endmethod

    method Action incrementCycle;
        mcycle <= mcycle + 1;
        minstret <= minstret + 1;
    endmethod
endmodule

endpackage
```

- [ ] **Step 2: 运行编译验证**

Run: `make compile 2>&1 | head -50`
Expected: CSR 模块编译通过

- [ ] **Step 3: 提交**

```bash
git add src/core/CSR.bsv
git commit -m "feat(core): add CSR register file with mip and 64-bit counters"
```

---

## Task 3: 修改 Decoder 支持 CSR 指令

**Files:**
- Modify: `src/core/Decoder.bsv`

> ⚠️ **审计修正**: CSRRWI 应使用 zimm[4:0]，funct3 010/101 是立即数版本

- [ ] **Step 1: 添加 CSR 指令解码**

在 `DecodedInstr` 结构体中添加：

```bsv
typedef struct {
    // ... 现有字段 ...
    Bool        is_csr;         // 是否 CSR 指令
    Bool        is_csr_imm;     // 是否是立即数版本 (CSRRWI等)
    Bit#(12)    csr_addr;       // CSR 地址
    CSROp       csr_op;         // CSR 操作类型
    Bit#(5)     csr_zimm;      // 立即数版本的 zimm
} DecodedInstr deriving (Bits, Eq, FShow);
```

在 `mkDecoder` 的 `case (opcode)` 中添加：

```bsv
// CSR 指令 (SYSTEM) - opcode = 7'b1110011
7'b1110011: begin
    Bit#(3) f3 = funct3;
    Bit#(5) rs1_addr = getRs1(instruction);

    // 默认值
    Bool use_rs1 = (f3 != 3'b101);  // 立即数版本不使用 rs1
    Bool write_reg = True;
    Bool is_csr_imm = False;
    CSROp csr_op = CSR_OP_READ;
    Bit#(5) csr_zimm = 0;

    case (f3)
        3'b001: csr_op = CSR_OP_WRITE;              // CSRRW
        3'b010: begin                                // CSRRWI ← 修正！
            csr_op = CSR_OP_WRITE;
            is_csr_imm = True;
            use_rs1 = False;
        end
        3'b011: begin                                // CSRRS
            csr_op = (rs1_addr == 0) ? CSR_OP_READ : CSR_OP_SET;
        end
        3'b101: begin                                // CSRRSI ← 修正！
            csr_op = (instr[19:15] == 0) ? CSR_OP_READ : CSR_OP_SET;
            is_csr_imm = True;
            use_rs1 = False;
        end
        3'b110: begin                                // CSRRC
            csr_op = (rs1_addr == 0) ? CSR_OP_READ : CSR_OP_CLR;
        end
        3'b111: begin                                // CSRRCI ← 修正！
            csr_op = (instr[19:15] == 0) ? CSR_OP_READ : CSR_OP_CLR;
            is_csr_imm = True;
            use_rs1 = False;
        end
        default: begin
            // ECALL/EBREAK/MRET/SFENCE.VMA 等在 Core 处理
        end
    endcase

    if (is_csr_imm)
        csr_zimm = instr[19:15];  // zimm = rs1 字段

    return DecodedInstr {
        // ... 现有字段 ...
        is_csr: True,
        is_csr_imm: is_csr_imm,
        csr_addr: instr[31:20],
        csr_op: csr_op,
        csr_zimm: csr_zimm
    };
end
```

- [ ] **Step 2: 运行编译验证**

Run: `make compile 2>&1 | head -80`
Expected: Decoder 修改编译通过

- [ ] **Step 3: 提交**

```bash
git add src/core/Decoder.bsv
git commit -m "feat(decoder): add complete CSR instruction decoding with immediates"
```

---

## Task 4: 修改 Core 集成 CSR 和陷阱处理

**Files:**
- Modify: `src/core/Core.bsv`

> ⚠️ **审计修正**:
> - 修正 mstatus 字段位置
> - MRET 返回 mepc（不需要 +4）
> - 添加 WFI 指令处理
> - 异常期间禁用中断
> - 流水线冲刷时正确处理 cycle 计数

- [ ] **Step 1-4: 基础修改（导入、实例化、类型扩展、IF 阶段）**

```bsv
// 1. 导入
import CSR::*;
import PrivilegedTypes::*;

// 2. CSR 实例
CSRs csrs <- mkCSRs;

// 3. 添加陷阱相关 Reg
Reg#(Bool) in_trap <- mkReg(False);
Reg#(Bool) wfi_waiting <- mkReg(False);  // WFI 等待状态
Reg#(Bool) meip <- mkReg(False);
Reg#(Bool) msip <- mkReg(False);
Reg#(Bool) mtip <- mkReg(False);

// 4. IF_ID_Packet 添加 priv_mode
typedef struct {
    Addr    pc;
    Word    instruction;
    Addr    predicted_pc;
    Bool    predicted_taken;
    PrivilegeMode priv_mode;
} IF_ID_Packet deriving (Bits, Eq, FShow);

// 5. ID_EX_Packet 添加 has_trap
typedef struct {
    // ... 现有字段 ...
    Bool        has_trap;
    TrapInfo    trap_info;
} ID_EX_Packet deriving (Bits, Eq, FShow);
```

- [ ] **Step 5: IF 阶段传递特权模式**

```bsv
if2id.enq(IF_ID_Packet {
    // ...
    priv_mode: csrs.currentMode()
});
```

- [ ] **Step 6: ID 阶段异常检测（修正 ECALL/EBREAK 区分）**

```bsv
// ECALL 检测 (funct3=000, funct7=0000000)
Bool is_ecall = (opcode == 7'b1110011) &&
                (funct3 == 3'b000) &&
                (funct7 == 7'b0000000);

// EBREAK 检测 (funct3=000, funct7=0000001) ← 修正！
Bool is_ebreak = (opcode == 7'b1110011) &&
                 (funct3 == 3'b000) &&
                 (funct7 == 7'b0000001);

// WFI 检测
Bool is_wfi = (opcode == 7'b1110011) &&
              (funct3 == 3'b000) &&
              (funct7 == 7'b0000101);  // WFI
```

- [ ] **Step 7: EX 阶段处理（CSR + 陷阱 + MRET + WFI）**

```bsv
rule executeStage (!stall_load_use && id2ex.notEmpty && ex2mem.notFull);
    ID_EX_Packet pkt = id2ex.first;
    DecodedInstr dec = decoder.decode(pkt.instruction);

    // 前递逻辑（保持不变）...

    // ========== CSR 指令处理 ==========
    if (dec.is_csr) begin
        Word csr_result;
        if (dec.is_csr_imm) begin
            csr_result = csrs.atomicOpImm(dec.csr_addr, dec.csr_zimm, dec.csr_op);
        end else begin
            csr_result = csrs.atomicOp(dec.csr_addr, op1, dec.csr_op);
        end
        alu_result = csr_result;
        write_reg_output = True;  // CSR 读需要写回 rd
    end

    // ========== 陷阱处理 ==========
    if (pkt.has_trap) begin
        // 保存状态到 CSR
        csrs.writeCSR(12'h341, pack(pkt.pc));  // mepc = 发生异常的 PC
        csrs.writeCSR(12'h342, cause_bits);
        csrs.writeCSR(12'h343, pkt.trap_info.tval);

        // 更新 mstatus：保存当前 MIE -> MPIE，保存当前模式 -> MPP，设置 MIE=0
        MStatus ms = unpackMStatus(csrs.readCSR(12'h300));
        MStatus new_ms = ms;
        new_ms.mpie = ms.wie;  // 保存当前中断使能
        new_ms.mpp = pack(pkt.trap_info.mode);
        new_ms.wie = 0;        // 陷阱期间关闭中断 ← 关键！
        csrs.writeCSR(12'h300, packMStatus(new_ms));

        csrs.setMode(M_MODE);  // 固定跳转到 M-mode

        // 跳转到 trap 向量
        pcReg <= csrs.getTrapVector(pkt.trap_info);
        branch_flush <= True;
        no_pc_update <= True;
        if2id.clear;
        id2ex.clear;
    end

    // ========== MRET 处理 ==========
    if (is_mret) begin
        MStatus ms = unpackMStatus(csrs.readCSR(12'h300));
        MStatus new_ms = ms;
        new_ms.wie = ms.mpie;   // 恢复中断使能
        new_ms.mpie = 1;         // 设置 MPIE
        csrs.writeCSR(12'h300, packMStatus(new_ms));

        PrivilegeMode prev = unpack(ms.mpp);
        csrs.setMode(prev);

        // MRET 直接返回 mepc，不需要 +4（RISC-V spec）
        pcReg <= csrs.readCSR(12'h341);
        no_pc_update <= True;
        branch_flush <= True;
        if2id.clear;
        id2ex.clear;
    end

    // ========== WFI 处理 ==========
    if (is_wfi) begin
        // 检查是否有挂起的中断
        if (csrs.hasPendingInterrupt()) begin
            // 有挂起中断，不等待
        end else begin
            // 进入等待状态，暂停 IF/ID
            wfi_waiting <= True;
            no_pc_update <= True;
        end
    end
endrule

// WFI 唤醒规则
rule wakeFromWFI (wfi_waiting && csrs.hasPendingInterrupt());
    wfi_waiting <= False;
    no_pc_update <= False;
endrule
```

- [ ] **Step 8: WB 阶段（修正 cycle 计数）**

```bsv
rule writebackStage;
    MEM_WB_Packet pkt = mem2wb.first;
    mem2wb.deq;

    // 写回寄存器
    if (pkt.write_reg && pkt.rd != 0) begin
        regFile.write(pkt.rd, pkt.is_load ? pkt.mem_data : pkt.alu_result);
    end

    // 只有非陷阱指令才计数（陷阱指令的 PC 已经保存到 mepc）
    // 如果当前指令被冲刷，不计数
    if (!branch_flush && !in_trap) begin
        csrs.incrementCycle;
    end
endrule
```

- [ ] **Step 9: 运行编译验证**

Run: `make compile 2>&1`
Expected: Core.bsv 编译通过

- [ ] **Step 10: 提交**

```bash
git add src/core/Core.bsv
git commit -m "feat(core): integrate CSR, trap handling, MRET, and WFI"
```

---

## Task 5: 创建特权级测试汇编文件

**Files:**
- Create: `tests/assembly/privilege_m_mode_test.s`
- Create: `tests/assembly/csr_basic_test.s`
- Create: `tests/assembly/exception_test.s`
- Create: `tests/assembly/csr_immediate_test.s`  # 新增：立即数版本测试

- [ ] **Step 1: Machine 模式基本测试**（保持不变）

- [ ] **Step 2: CSR 立即数版本测试（新增）**

```asm
# tests/assembly/csr_immediate_test.s
# 测试 CSRRWI, CSRRSI, CSRRCI

.globl _start
_start:
    # 测试 CSRRWI (write immediate)
    csrrwi a0, mstatus, 0x10  # 将 0x10 写入 mstatus，a0 = 旧值
    # 期望: mstatus |= 0x10, a0 = 0

    csrrwi a1, mstatus, 0     # 只读取，a1 = 当前值
    # 期望: a1 = 0x10

    # 测试 CSRRSI (set immediate)
    csrrsi a2, mstatus, 0x08  # 设置 bit，a2 = 旧值
    # 期望: mstatus |= 0x08, a2 = 0x10

    # 测试 CSRRCI (clear immediate)
    csrrci a3, mstatus, 0x18  # 清除 bit，a3 = 旧值
    # 期望: mstatus &= ~0x18, a3 = 0x18

    # 验证结果
    csrr a4, mstatus
    # 期望: a4 = 0

    # 写入 tohost
    li t0, 0x80001000
    li t4, 4
    sw t4, 0(t0)

_inf_loop:
    j _inf_loop
```

- [ ] **Step 3: 编译测试**

Run: `make firmware/csr_immediate_test.hex`
Expected: 编译成功

- [ ] **Step 4: 提交**

```bash
git add tests/assembly/csr_immediate_test.s
git commit -m "test: add CSR immediate instruction test"
```

---

## Task 6: 集成测试运行

**Files:**
- Modify: `src/soc/TestBench.bsv`

- [ ] **Step 1: 逐个运行测试并验证**

```bash
# 1. privilege_m_mode_test
# 2. csr_basic_test
# 3. exception_test
# 4. csr_immediate_test
```

- [ ] **Step 2: 提交**

---

## Task 7: 更新文档

**Files:**
- Create: `docs/privilege-architecture.md`

- [ ] **Step 1: 创建文档（包含修正后的 CSR 地址表）**

---

## 审计后新增任务

## Task 8: 添加中断控制器接口（为阶段4 PLIC 预留）

**Files:**
- Modify: `src/core/CSR.bsv`

- [ ] **Step 1: 添加中断检测方法**

```bsv
// 在 hasPendingInterrupt 中检查 MEI, MSI, MTI
method Bool hasPendingInterrupt();
    MStatus ms = unpackMStatus(mstatus);
    Word mie_val = mie;
    Word mip_val = mip;

    Bool meip_pending = mip_val[11] && mie_val[11];  // 外部中断
    Bool msip_pending = mip_val[3] && mie_val[3];   // 软件中断
    Bool mtip_pending = mip_val[7] && mie_val[7];   // 定时器中断

    return (meip_pending || msip_pending || mtip_pending) && (ms.wie == 1);
endmethod
```

---

## 验证检查清单

- [ ] mstatus 字段位置正确（MIE 在 bit 3，MPP 是 2 位）
- [ ] mip CSR 存在且正确更新
- [ ] CSR 立即数指令使用 zimm
- [ ] mtimecmp 和 minstret 地址不冲突（0xB02 vs 0xB03）
- [ ] MRET 返回 mepc（不是 mepc+4）
- [ ] WFI 指令有实现
- [ ] 异常期间 MIE=0（防止嵌套）
- [ ] CSRRWI 等立即数版本测试通过

```bsv
// src/core/PrivilegedTypes.bsv
package PrivilegedTypes;

import Types::*;

// ============================================================
// 特权级别
// ============================================================

typedef enum {
    M_MODE = 2'b11,    // Machine Mode (最高特权)
    S_MODE = 2'b01,    // Supervisor Mode
    U_MODE = 2'b00     // User Mode (最低特权)
} PrivilegeMode deriving (Bits, Eq, FShow);

// ============================================================
// CSR 地址（只列出我们实现的核心 CSR）
// ============================================================

// Machine Information Registers (只读)
typedef enum {
    CSR_MVENDORID = 12'hF11,  // Vendor ID
    CSR_MARCHID   = 12'hF12,  // Architecture ID
    CSR_MIMPID    = 12'hF13,  // Implementation ID
    CSR_MHARTID   = 12'hF14,  // Hardware Thread ID

    // Machine Trap Setup
    CSR_MSTATUS   = 12'h300,  // Machine Status
    CSR_MISA      = 12'h301,  // Machine ISA
    CSR_MIE       = 12'h304,  // Machine Interrupt Enable
    CSR_MTVEC     = 12'h305,  // Machine Trap Vector

    // Machine Trap Handling
    CSR_MEPC      = 12'h341,  // Machine Exception PC
    CSR_MCAUSE    = 12'h342,  // Machine Cause
    CSR_MTVAL     = 12'h343,  // Machine Trap Value

    // Machine Counter/Timer
    CSR_MCYCLE    = 12'hB00,  // Machine Cycle Counter (lower 32)
    CSR_MTIME     = 12'hB01,  // Machine Time (lower 32) - CLINT
    CSR_MTIMECMP  = 12'hB02,  // Machine Time Compare
    CSR_MINSTRET  = 12'hB02,  // Machine Instructions Retired

    // Machine Counter Setup
    CSR_MCOUNTEREN = 12'h306, // Machine Counter Enable

    // Supervisor Registers (S-mode 基础)
    CSR_SSTATUS   = 12'h100,  // Supervisor Status
    CSR_SIE       = 12'h104,  // Supervisor Interrupt Enable
    CSR_STVEC     = 12'h105,  // Supervisor Trap Vector
    CSR_SEPC      = 12'h141,  // Supervisor Exception PC
    CSR_SCAUSE    = 12'h142,  // Supervisor Cause
    CSR_STVAL     = 12'h143,  // Supervisor Trap Value
    CSR_SATP      = 12'h180   // Supervisor Address Translation
} CSRArea deriving (Bits, Eq, FShow);

typeclass IsCSRArea a;
    instance IsCSRArea #(CSRArea);
endtypeclass

function Bit#(12) csrIndex(CSRArea x) = pack(x);

// ============================================================
// 异常原因编码
// ============================================================

// 同步异常（mcause[31] = 0）
typedef enum {
    EXC_INST_MISALIGNED   = 0,   // 指令地址对齐错误
    EXC_INST_ACCESS_FAULT = 1,   // 指令访问错误
    EXC_ILLEGAL_INST      = 2,   // 非法指令
    EXC_BREAKPOINT         = 3,   // 断点
    EXC_LOAD_MISALIGNED   = 4,   // Load 地址对齐错误
    EXC_LOAD_ACCESS_FAULT = 5,   // Load 访问错误
    EXC_STORE_MISALIGNED  = 6,   // Store 地址对齐错误
    EXC_STORE_ACCESS_FAULT = 7,  // Store 访问错误
    EXC_ECALL_U           = 8,   // ECALL from U-mode
    EXC_ECALL_S           = 9,   // ECALL from S-mode
    EXC_ECALL_M           = 11,  // ECALL from M-mode
    EXC_INST_PAGE_FAULT   = 12,  // 指令页错误
    EXC_LOAD_PAGE_FAULT   = 13,   // Load 页错误
    EXC_STORE_PAGE_FAULT  = 15   // Store 页错误
} ExceptionCode deriving (Bits, Eq, FShow);

// 中断（mcause[31] = 1）
typedef enum {
    INT_SOFTWARE_S        = 1,   // S-mode 软件中断
    INT_SOFTWARE_M        = 3,   // M-mode 软件中断
    INT_TIMER_S           = 5,   // S-mode 定时器中断
    INT_TIMER_M           = 7,   // M-mode 定时器中断
    INT_EXTERNAL_S        = 9,   // S-mode 外部中断
    INT_EXTERNAL_M        = 11   // M-mode 外部中断
} InterruptCode deriving (Bits, Eq, FShow);

// ============================================================
// 陷阱信息包
// ============================================================

typedef struct {
    Addr         epc;            // 异常发生时 PC
    ExceptionCode cause;        // 异常原因（同步异常）
    Bool         is_interrupt;  // 是否是中断
    Addr         tval;          // 附加信息（访问地址/指令等）
    PrivilegeMode mode;         // 发生时的特权模式
} TrapInfo deriving (Bits, Eq, FShow);

// ============================================================
// CSR 指令类型
// ============================================================

typedef enum {
    CSR_OP_CLR,    // CSRRS + rs1 = x0 (read and clear)
    CSR_OP_SET,    // CSRRC + rs1 = x0 (read and set)
    CSR_OP_WRITE,  // CSRRW + rs1 != x0 (write)
    CSR_OP_READ    // CSRRW + rs1 = x0 (read only)
} CSROp deriving (Bits, Eq, FShow);

// ============================================================
// mstatus 域分解
// ============================================================

typedef struct {
    Bit#(1) uie;      // U-mode 中断使能
    Bit#(1) sie;      // S-mode 中断使能
    Bit#(1) wie;      // M-mode 中断使能
    Bit#(1) upie;     // U-mode 上一级中断使能
    Bit#(1) spie;     // S-mode 上一级中断使能
    Bit#(1) mpie;     // M-mode 上一级中断使能
    Bit#(2) spp;      // S-mode 上一级特权模式
    Bit#(1) mpp;      // M-mode 上一级特权模式
    Bit#(1) mprv;     // M-mode 寄存器翻译使能
    Bit#(1) sum;      // 允许 S-mode 访问 U-mode 页
    Bit#(1) mxr;      // M-mode 执行读取设置
    Bit#(1) tvm;      // 陷阱 SRET/S-mode 访问
    Bit#(1) tw;       // 陷阱 WFI
    Bit#(1) tsr;      // 陷阱 SRET 访问 SSTATUS
    Bit#(4) fs;       // 浮点状态
    Bit#(2) xs;       // 用户自定义状态
    Bit#(1) sd;       // Dirty 状态
    Bit#(26) reserved;
} MStatus deriving (Bits, Eq, FShow);

endpackage
```

- [ ] **Step 2: 运行编译验证**

Run: `make compile 2>&1 | head -50`
Expected: 新文件无语法错误

- [ ] **Step 3: 提交**

```bash
git add src/core/PrivilegedTypes.bsv
git commit -m "feat(types): add privilege mode and CSR type definitions"
```

---

## Task 2: 创建 CSR 寄存器模块

**Files:**
- Create: `src/core/CSR.bsv`

- [ ] **Step 1: 创建 CSR 寄存器模块**

```bsv
// src/core/CSR.bsv
package CSR;

import Types::*;
import PrivilegedTypes::*;

// ============================================================
// CSR 寄存器文件接口
// ============================================================

interface CSRs;
    // 读取 CSR
    method Word readCSR(Bit#(12) addr);

    // 写入 CSR
    method Action writeCSR(Bit#(12) addr, Word data);

    // 原子 CSR 操作（用于 CSRRW/CSRRS/CSRRC）
    method Word atomicOp(Bit#(12) addr, Word rs1_val, CSROp op);

    // 获取当前特权模式
    method PrivilegeMode currentMode();

    // 设置特权模式（陷阱返回时）
    method Action setMode(PrivilegeMode mode);

    // 获取 trap 向量基址
    method Addr getTrapVector(TrapInfo trap);

    // 时钟/计数器
    method Action incrementCycle;
endinterface

module mkCSRs(CSRs);
    // ========== Machine Information Registers (只读) ==========
    Reg#(Word) mvendorid <- mkReg(0);           // 0 表示非标准
    Reg#(Word) marchid <- mkReg(0);             // 架构 ID
    Reg#(Word) mimpid <- mkReg(0);              // 实现 ID
    Reg#(Word) mhartid <- mkReg(0);             // Hart ID = 0

    // ========== Machine Trap Setup ==========
    Reg#(Word) mstatus <- mkReg(0);
    Reg#(Word) misa <- mkReg(32'h40001100);    // MISA = RV32I + M-mode
    Reg#(Word) mie <- mkReg(0);                // 中断使能
    Reg#(Word) mtvec <- mkReg(32'h80000000);   // trap 向量基址

    // ========== Machine Trap Handling ==========
    Reg#(Word) mepc <- mkReg(0);                // 异常 PC
    Reg#(Word) mcause <- mkReg(0);              // 异常原因
    Reg#(Word) mtval <- mkReg(0);               // 异常附加信息

    // ========== Machine Counter/Timer ==========
    Reg#(Word) mcycle <- mkReg(0);              // 周期计数器
    Reg#(Word) minstret <- mkReg(0);            // 指令 retired 计数
    Reg#(Word) mtime <- mkReg(0);               // 时间（来自 CLINT）
    Reg#(Word) mtimecmp <- mkReg({28'hFFFF_FFFF, 4'h0}); // 时间比较

    Reg#(Word) mcounteren <- mkReg(0);         // 计数器使能

    // ========== 当前特权模式 ==========
    Reg#(PrivilegeMode) priv_mode <- mkReg(M_MODE);

    // ========== 辅助函数 ==========

    function MStatus unpackMStatus(Word w);
        return MStatus {
            uie:      w[0],
            sie:      w[1],
            wie:      w[3],
            upie:     w[4],
            spie:     w[5],
            mpie:     w[7],
            spp:      w[8],
            mpp:      w[11:10],
            mprv:     w[17],
            sum:      w[18],
            mxr:      w[19],
            tvm:      w[20],
            tw:       w[21],
            tsr:      w[22],
            fs:       w[14:12],
            xs:       w[16:15],
            sd:       w[31],
            reserved: 0
        };
    endfunction

    function Word packMStatus(MStatus s);
        return {s.sd, 26'b0, s.tsr, s.tw, s.tvm, s.mxr, s.sum, s.mprv,
                2'b0, s.mpp, 1'b0, s.spp, 1'b0, s.mpie, 1'b0, s.spie, 1'b0, s.upie, 1'b0, s.wie, 1'b0, s.sie, 1'b0, s.uie};
    endfunction

    function Bool isReadOnlyCSR(Bit#(12) addr);
        return (addr == 12'hF11) || (addr == 12'hF12) ||
               (addr == 12'hF13) || (addr == 12'hF14);
    endfunction

    // ========== 方法实现 ==========

    method Word readCSR(Bit#(12) addr);
        case (addr)
            12'hF11: return mvendorid;
            12'hF12: return marchid;
            12'hF13: return mimpid;
            12'hF14: return mhartid;
            12'h300: return mstatus;
            12'h301: return misa;
            12'h304: return mie;
            12'h305: return mtvec;
            12'h341: return mepc;
            12'h342: return mcause;
            12'h343: return mtval;
            12'hB00: return mcycle[31:0];
            12'hB01: return mtime[31:0];
            12'hB02: return mtimecmp[31:0];
            12'hB80: return mcycle[63:32];
            12'hB81: return mtime[63:32];
            12'hB82: return mtimecmp[63:32];
            12'hB02: return minstret[31:0];
            12'hB82: return minstret[63:32];
            12'h306: return mcounteren;
            default: return 0;
        endcase
    endmethod

    method Action writeCSR(Bit#(12) addr, Word data);
        if (!isReadOnlyCSR(addr)) begin
            case (addr)
                12'h300: mstatus <= data;
                12'h304: mie <= data;
                12'h305: mtvec <= data;
                12'h341: mepc <= data;
                12'h342: mcause <= data;
                12'h343: mtval <= data;
                12'hB00: mcycle[31:0] <= data;
                12'hB01: mtime[31:0] <= data;
                12'hB02: mtimecmp[31:0] <= data;
                12'hB80: mcycle[63:32] <= data;
                12'hB81: mtime[31:0] <= data;
                12'hB82: mtimecmp[63:32] <= data;
                12'hB02: minstret[31:0] <= data;
                12'hB82: minstret[63:32] <= data;
                12'h306: mcounteren <= data;
            endcase
        end
    endmethod

    method Word atomicOp(Bit#(12) addr, Word rs1_val, CSROp op);
        Word csr_val = readCSR(addr);
        Word result = csr_val;

        case (op)
            CSR_OP_WRITE: result = rs1_val;                    // CSRRW
            CSR_OP_SET:   result = csr_val | rs1_val;         // CSRRS
            CSR_OP_CLR:   result = csr_val & ~rs1_val;         // CSRRC
            CSR_OP_READ:  result = csr_val;                    // CSRRW with rs1=x0
        endcase

        if (op != CSR_OP_READ)
            writeCSR(addr, result);

        return csr_val;  // 总是返回原值给 rd
    endmethod

    method PrivilegeMode currentMode();
        return priv_mode;
    endmethod

    method Action setMode(PrivilegeMode mode);
        priv_mode <= mode;
    endmethod

    method Addr getTrapVector(TrapInfo trap);
        Word base = mtvec & ~3;  // 向量基址（清零模式位）
        Bit#(2) mode = mtvec[1:0];

        if (mode == 2'b00) begin
            // Direct mode: 所有陷阱跳转到同一地址
            return base;
        end else begin
            // Vectored mode: 中断跳转到 base + 4*cause
            if (trap.is_interrupt) begin
                Bit#(5) cause = pack(trap.cause)[4:0];
                return base + zeroExtend(cause) * 4;
            end else begin
                return base;
            end
        end
    endmethod

    method Action incrementCycle;
        mcycle <= mcycle + 1;
        minstret <= minstret + 1;
    endmethod
endmodule

endpackage
```

- [ ] **Step 2: 运行编译验证**

Run: `make compile 2>&1 | head -50`
Expected: CSR 模块编译通过

- [ ] **Step 3: 提交**

```bash
git add src/core/CSR.bsv
git commit -m "feat(core): add CSR register file module"
```

---

## Task 3: 修改 Decoder 支持 CSR 指令

**Files:**
- Modify: `src/core/Decoder.bsv`

- [ ] **Step 1: 添加 CSR 指令解码**

找到 `InstrType` 枚举定义，添加：

```bsv
typedef enum {
    // ... 现有类型 ...
    CSR_TYPE    // CSR 访问指令 (CSRRW, CSRRS, CSRRC, etc.)
} InstrType deriving (Bits, Eq, FShow);
```

在 `DecodedInstr` 结构体中添加：

```bsv
typedef struct {
    // ... 现有字段 ...
    Bool        is_csr;         // 新增：是否 CSR 指令
    Bit#(12)    csr_addr;       // 新增：CSR 地址
    CSROp       csr_op;          // 新增：CSR 操作类型
} DecodedInstr deriving (Bits, Eq, FShow);
```

在 `mkDecoder` 的 `case (opcode)` 中添加新的 opcode 处理：

```bsv
// CSR 指令 (SYSTEM)
7'b1110011: begin
    Bool use_rs1 = True;
    Bool write_reg = True;
    CSROp csr_op = CSR_OP_READ;

    case (funct3)
        3'b001: begin
            csr_op = CSR_OP_WRITE;  // CSRRW
            use_rs1 = True;
        end
        3'b010: begin
            csr_op = CSR_OP_WRITE;  // CSRRWI (immediate version - treat same for now)
            use_rs1 = True;
        end
        3'b011: begin  // CSRRS - set bits
            csr_op = (rs1_addr == 0) ? CSR_OP_READ : CSR_OP_SET;
        end
        3'b101: begin
            csr_op = CSR_OP_WRITE;  // CSRRWI
            use_rs1 = True;
        end
        3'b110: begin  // CSRRC - clear bits
            csr_op = (rs1_addr == 0) ? CSR_OP_READ : CSR_OP_CLR;
        end
        3'b111: begin  // CSRRCI
            csr_op = (rs1_addr == 0) ? CSR_OP_READ : CSR_OP_CLR;
        end
        default: begin
            // ECALL/EBREAK/MRET 等
            // 这些在 ID 阶段处理
        end
    endcase

    return DecodedInstr {
        // ... 现有字段 ...
        is_csr: True,
        csr_addr: {instr[31:20]},  // CSR[11:0]
        csr_op: csr_op
    };
end
```

- [ ] **Step 2: 添加 CSR 指令相关的立即数解码**

在 U-type 立即数提取后添加：

```bsv
// CSR 立即数字段（zimm[4:0] 用于 CSRRWI 等）
function Bit#(5) getCSRIimm(Word instr);
    return instr[19:15];  // rs1 字段作为立即数
endfunction
```

- [ ] **Step 3: 运行编译验证**

Run: `make compile 2>&1 | head -80`
Expected: Decoder 修改编译通过，无语法错误

- [ ] **Step 4: 提交**

```bash
git add src/core/Decoder.bsv
git commit -m "feat(decoder): add CSR instruction decoding"
```

---

## Task 4: 修改 Core 集成 CSR 和陷阱处理

**Files:**
- Modify: `src/core/Core.bsv`

- [ ] **Step 1: 导入新模块**

在 `package Core` 的 import 部分添加：

```bsv
import CSR::*;
import PrivilegedTypes::*;
```

- [ ] **Step 2: 添加 CSR 实例**

在 `module mkCore` 中添加：

```bsv
CSRs csrs <- mkCSRs;
```

- [ ] **Step 3: 添加陷阱控制寄存器**

在现有 Reg 定义区域添加：

```bsv
// 陷阱控制
Reg#(Bool) in_trap <- mkReg(False);           // 当前是否在陷阱处理中
Reg#(TrapInfo) current_trap <- mkReg(?);       // 当前陷阱信息
Reg#(Bool) meip <- mkReg(False);               // Machine 外部中断挂起
Reg#(Bool) msip <- mkReg(False);               // Machine 软件中断挂起
Reg#(Bool) mtip <- mkReg(False);               // Machine 定时器中断挂起
```

- [ ] **Step 4: 修改 IF_ID_Packet 添加特权模式字段**

```bsv
typedef struct {
    Addr    pc;
    Word    instruction;
    Addr    predicted_pc;
    Bool    predicted_taken;
    PrivilegeMode priv_mode;    // 新增：当前特权模式
} IF_ID_Packet deriving (Bits, Eq, FShow);
```

- [ ] **Step 5: 修改 ID_EX_Packet 添加陷阱信息**

```bsv
typedef struct {
    // ... 现有字段 ...
    Bool        has_trap;       // 新增：是否发生陷阱
    TrapInfo    trap_info;      // 新增：陷阱信息
} ID_EX_Packet deriving (Bits, Eq, FShow);
```

- [ ] **Step 6: 修改 IF 阶段传递特权模式**

在 `fetchStage` 规则中修改：

```bsv
if2id.enq(IF_ID_Packet {
    pc: fetchPC,
    instruction: instr,
    predicted_pc: prediction_target,
    predicted_taken: take_prediction,
    priv_mode: csrs.currentMode()  // 新增
});
```

- [ ] **Step 7: 修改 ID 阶段处理 ECALL/EBREAK**

在 `decodeStage` 规则中添加异常检测：

```bsv
// 检测 ECALL/EBREAK
Bool is_ecall = (getOpcode(pkt.instruction) == 7'b1110011) &&
                (getFunct3(pkt.instruction) == 3'b000) &&
                (getRs1(pkt.instruction) == 0) &&
                (getRd(pkt.instruction) == 0) &&
                (getFunct7(pkt.instruction) == 7'b0000000);  // ECALL

Bool is_ebreak = (getOpcode(pkt.instruction) == 7'b1110011) &&
                 (getFunct3(pkt.instruction) == 3'b000) &&
                 (getRs1(pkt.instruction) == 0) &&
                 (getRd(pkt.instruction) == 0) &&
                 (getFunct7(pkt.instruction) == 7'b0000001);  // EBREAK

// ECALL 异常：根据当前模式设置异常原因
if (is_ecall) begin
    ExceptionCode exc = case (pkt.priv_mode)
        M_MODE: EXC_ECALL_M;
        S_MODE: EXC_ECALL_S;
        U_MODE: EXC_ECALL_U;
    endcase;
    // 创建陷阱信息并发送到 EX
end
```

- [ ] **Step 8: 修改 EX 阶段处理 CSR 指令和陷阱**

在 `executeStage` 规则中添加 CSR 处理：

```bsv
// CSR 指令处理
if (dec.is_csr) begin
    Word csr_result = csrs.atomicOp(dec.csr_addr, dec.use_imm ? zeroExtend(getCSRIimm(pkt.instruction)) : op1, dec.csr_op);
    // 设置 ALU 结果为 CSR 值
    alu_result = csr_result;
    // rd 值将在 WB 阶段写回
end

// 陷阱处理：如果 has_trap，转到 trap 向量
if (pkt.has_trap) begin
    // 保存当前 PC 到 mepc
    csrs.writeCSR(12'h341, pkt.pc);

    // 设置 mcause
    Word cause_bits = zeroExtend(pack(pkt.trap_info.cause));
    if (pkt.trap_info.is_interrupt)
        cause_bits = cause_bits | (1 << 31);
    csrs.writeCSR(12'h342, cause_bits);

    // 设置 mtval
    csrs.writeCSR(12'h343, pkt.trap_info.tval);

    // 更新 mstatus.MPIE 和 MPP
    MStatus s = unpackMStatus(csrs.readCSR(12'h300));
    MStatus new_s = s;
    new_s.mpie = s.wie;  // 保存当前 WIE 到 MPIE
    new_s.mpp = pack(pkt.trap_info.mode);  // 保存当前模式
    new_s.wie = 0;  // 关闭全局中断
    csrs.writeCSR(12'h300, packMStatus(new_s));

    // 设置新模式为 M_MODE
    csrs.setMode(M_MODE);

    // 跳转到 trap 向量
    Addr trap_vec = csrs.getTrapVector(pkt.trap_info);
    pcReg <= trap_vec;
    in_trap <= True;

    // 冲刷流水线
    branch_flush <= True;
    no_pc_update <= True;
    if2id.clear;
    id2ex.clear;
end
```

- [ ] **Step 9: 添加 MRET 指令处理**

在 EX 阶段添加：

```bsv
// MRET 指令检测
Bool is_mret = (getOpcode(pkt.instruction) == 7'b1110011) &&
               (getFunct3(pkt.instruction) == 3'b000) &&
               (getRs1(pkt.instruction) == 0) &&
               (getRd(pkt.instruction) == 0) &&
               (getFunct7(pkt.instruction) == 7'b0011000);  // MRET

if (is_mret) begin
    // 恢复 mstatus
    MStatus s = unpackMStatus(csrs.readCSR(12'h300));
    MStatus new_s = s;
    new_s.wie = s.mpie;  // 恢复中断使能
    new_s.mpie = 1;      // 设置 MPIE
    csrs.writeCSR(12'h300, packMStatus(new_s));

    // 恢复特权模式
    PrivilegeMode prev_mode = unpack(s.mpp);
    csrs.setMode(prev_mode);

    // 返回到 mepc
    pcReg <= csrs.readCSR(12'h341);
    no_pc_update <= True;

    // 冲刷流水线
    branch_flush <= True;
    if2id.clear;
    id2ex.clear;
end
```

- [ ] **Step 10: 修改 WB 阶段处理 CSR 指令写回**

```bsv
rule writebackStage;
    // ... 现有逻辑 ...

    // CSR 指令在 EX 阶段已处理，这里只更新计数器
    csrs.incrementCycle;
endrule
```

- [ ] **Step 11: 运行编译验证**

Run: `make compile 2>&1`
Expected: Core.bsv 集成 CSR 和陷阱处理编译通过

- [ ] **Step 12: 提交**

```bash
git add src/core/Core.bsv
git commit -m "feat(core): integrate CSR and trap handling into pipeline"
```

---

## Task 5: 创建特权级测试汇编文件

**Files:**
- Create: `tests/assembly/privilege_m_mode_test.s`
- Create: `tests/assembly/csr_basic_test.s`
- Create: `tests/assembly/exception_test.s`

- [ ] **Step 1: 创建 Machine 模式基本测试**

```asm
# tests/assembly/privilege_m_mode_test.s
# 测试 Machine 模式基本执行和 mstatus CSR

.globl _start
_start:
    # 读取 mhartid (应该为 0)
    csrr a0, mhartid
    # 期望: a0 = 0

    # 读取 misa (应该显示 RV32I)
    csrr a1, misa
    # 期望: a1[26] = 1 (I extension present)

    # 读取 mstatus
    csrr a2, mstatus
    # 期望: a2 = 0 (初始状态)

    # 写入 mstatus 测试
    li a3, 0x1888  # Mstatus: MIE=1, MPIE=1, MPP=11(M-mode)
    csrw mstatus, a3

    # 再次读取验证
    csrr a4, mstatus
    # 期望: a4[3] = 1 (MIE), a4[7] = 1 (MPIE), a4[11:10] = 11 (MPP)

    # 写入 mcause 测试 (非法指令异常)
    li a5, 0x2     # Exception code 2 = Illegal Instruction
    csrw mcause, a5

    # 写入 mepc 测试
    lui a6, 0x80000  # 0x80000000
    addi a6, a6, 0x40
    csrw mepc, a6

    # 写入 mtval 测试
    li a7, 0xDEADBEEF
    csrw mtval, a7

    # 测试 csrrw (read and write)
    li t0, 0x12345678
    csrrw t1, mstatus, t0
    # t1 = 旧值, mstatus = 0x12345678

    # 测试 csrrs (read and set)
    li t0, 0x00000100  # 设置 MIE 位
    csrrs t2, mstatus, t0
    # t2 = 旧值, mstatus |= 0x100

    # 测试 csrrc (read and clear)
    li t0, 0x00000100  # 清除 MIE 位
    csrrc t3, mstatus, t0
    # t3 = 旧值, mstatus &= ~0x100

    # 写入 tohost 表示测试完成
    li t0, 0x80001000
    li t4, 1  # PASS
    sw t4, 0(t0)

_inf_loop:
    j _inf_loop
```

- [ ] **Step 2: 创建 CSR 基本读写测试**

```asm
# tests/assembly/csr_basic_test.s
# 测试 CSR 基本读写操作

.globl _start
_start:
    # 测试 mcycle 计数器递增
    csrr a0, mcycle
    csrr a1, mcycle
    csrr a2, mcycle
    # 期望: a0 <= a1 <= a2 (递增)

    # 测试 mtvec
    lui a0, 0x80000  # 0x80000000
    addi a0, a0, 0x00
    csrw mtvec, a0
    csrr a1, mtvec
    # 期望: a1 = 0x80000000

    # 测试 mtvec 向量模式 (mode=1)
    lui a0, 0x80000
    addi a0, a0, 0x03  # mode=1, base=0x80000000
    csrw mtvec, a0
    csrr a1, mtvec
    # 期望: a1 = 0x80000003

    # 写入 tohost 表示测试完成
    li t0, 0x80001000
    li t4, 2  # PASS
    sw t4, 0(t0)

_inf_loop:
    j _inf_loop
```

- [ ] **Step 3: 创建异常处理测试**

```asm
# tests/assembly/exception_test.s
# 测试异常处理机制

.globl _start
_start:
    # 测试 ECALL 从 U-mode (在我们的实现中等价于 M-mode)
    ecall
    # 期望: mepc 指向 ecall 下一条指令
    #       mcause = 11 (ECALL from M-mode)
    #       pc 跳转到 mtvec

    # 跳过 ecall (如果没跳转的话)
    nop
    nop
    nop

    # 测试 EBREAK (断点异常)
    ebreak

    # 跳过 ebreak (如果没跳转的话)
    nop
    nop
    nop

    # 读取 mepc 检查
    csrr a0, mepc
    csrr a1, mcause

    # 写入 tohost 表示测试完成
    li t0, 0x80001000
    li t4, 3  # PASS
    sw t4, 0(t0)

_inf_loop:
    j _inf_loop
```

- [ ] **Step 4: 编译测试**

Run: `make firmware/privilege_m_mode_test.hex`
Expected: 汇编编译成功，生成 hex 文件

- [ ] **Step 5: 提交**

```bash
git add tests/assembly/privilege_m_mode_test.s tests/assembly/csr_basic_test.s tests/assembly/exception_test.s
git commit -m "test: add privilege mode and CSR assembly tests"
```

---

## Task 6: 集成测试运行

**Files:**
- Modify: `src/soc/TestBench.bsv`

- [ ] **Step 1: 修改 TestBench 支持新测试**

在 `TestBench.bsv` 中添加新的测试用例：

```bsv
// 选择要运行的测试
String test_to_run = "privilege_m_mode_test";
// String test_to_run = "csr_basic_test";
// String test_to_run = "exception_test";
```

- [ ] **Step 2: 运行特权级测试**

Run: `make test`
Expected: 测试完成，tohost 写入预期值

- [ ] **Step 3: 如有问题，调试并修复**

根据仿真输出定位并修复问题

- [ ] **Step 4: 提交**

```bash
git add src/soc/TestBench.bsv
git commit -m "test: add privilege architecture integration tests"
```

---

## Task 7: 更新文档

**Files:**
- Create: `docs/privilege-architecture.md`

- [ ] **Step 1: 创建特权架构文档**

```markdown
# RISC-V 特权架构文档

## 特权级别

| 模式 | 编码 | 说明 |
|------|------|------|
| M-mode | 11 | 最高特权，必需的 |
| S-mode | 01 | 监督模式，用于操作系统 |
| U-mode | 00 | 用户模式，用于应用程序 |

## 已实现 CSR

### Machine Information Registers (只读)
- mvendorid (0xF11): 供应商 ID
- marchid (0xF12): 架构 ID
- mimpid (0xF13): 实现 ID
- mhartid (0xF14): 硬件线程 ID

### Machine Trap Setup
- mstatus (0x300): 机器状态
- misa (0x301): 机器 ISA
- mie (0x304): 机器中断使能
- mtvec (0x305): 机器陷阱向量

### Machine Trap Handling
- mepc (0x341): 机器异常 PC
- mcause (0x342): 机器异常原因
- mtval (0x343): 机器陷阱值

### Machine Counter/Timer
- mcycle (0xB00): 周期计数器
- mtime (0xB01): 时间计数器
- mtimecmp (0xB02): 时间比较
- minstret (0xB02): 指令 retired 计数

## 异常编码

| 编码 | 名称 | 说明 |
|------|------|------|
| 0 | EXC_INST_MISALIGNED | 指令地址对齐错误 |
| 2 | EXC_ILLEGAL_INST | 非法指令 |
| 4 | EXC_LOAD_MISALIGNED | Load 地址对齐错误 |
| 8 | EXC_ECALL_U | U-mode ECALL |
| 11 | EXC_ECALL_M | M-mode ECALL |

## 中断编码 (mcause[31] = 1)

| 编码 | 名称 | 说明 |
|------|------|------|
| 3 | INT_SOFTWARE_M | M-mode 软件中断 |
| 7 | INT_TIMER_M | M-mode 定时器中断 |
| 11 | INT_EXTERNAL_M | M-mode 外部中断 |

## 陷阱处理流程

1. 异常/中断发生
2. 保存当前 PC 到 mepc
3. 保存异常原因到 mcause
4. 保存附加信息到 mtval
5. 更新 mstatus (MPIE, MPP)
6. 设置新特权模式为 M-mode
7. 跳转到 mtvec 指定地址
8. 执行陷阱处理程序
9. MRET 返回时恢复 mstatus 和特权模式
```

- [ ] **Step 2: 提交**

```bash
git add docs/privilege-architecture.md
git commit -m "docs: add privilege architecture documentation"
```

---

## 验证检查清单

- [ ] 特权类型定义编译通过
- [ ] CSR 模块编译通过
- [ ] Decoder 支持 CSR 指令解码
- [ ] Core 集成 CSR 和陷阱处理
- [ ] Machine 模式基本测试通过
- [ ] CSR 基本读写测试通过
- [ ] 异常处理测试通过
- [ ] 文档更新完成

---

## 后续任务（阶段 4）

- 实现 S-mode 和 U-mode 切换
- 添加 CLINT (Core Local Interruptor)
- 添加 PLIC (Platform Level Interrupt Controller)
- 实现虚拟内存 (Sv32)
- 支持 FreeRTOS/uClinux 启动
