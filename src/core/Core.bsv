// src/core/Core.bsv - 完整版（带分支预测、数据前递和Load-Use停顿）
package Core;

import Types::*;
import ALU::*;
import RegFile::*;
import Decoder::*;
import BHT::*;
import BTB::*;
import HazardUnit::*;
import CSR::*;
import PrivilegedTypes::*;
import FIFO::*;
import FIFOF::*;
import Vector::*;

interface Core;
    method Addr pc;
    method Word instruction;
    method Bool running;
    method Bool testDone;         // tohost 写入检测
    method Word tohostValue;      // tohost 写入值
    method Action loadProgram(Vector#(1024, Word) prog);
    method Word readReg(Bit#(5) addr);
endinterface

module mkCore#(String firmwareFile)(Core);
    Decoder decoder <- mkDecoder;
    ALU alu <- mkALU;
    RegFile regFile <- mkRegFile;
    BHT bht <- mkBHT;
    BTB btb <- mkBTB;
    HazardUnit hazardUnit <- mkHazardUnit;
    CSRs csrs <- mkCSR;

    // 流水线寄存器（使用 FIFOF 深度2）
    FIFOF#(IF_ID_Packet) if2id <- mkFIFOF;
    FIFOF#(ID_EX_Packet) id2ex <- mkFIFOF;
    FIFOF#(EX_MEM_Packet) ex2mem <- mkFIFOF;
    FIFOF#(MEM_WB_Packet) mem2wb <- mkFIFOF;

    // Load-Use停顿控制
    Reg#(Bool) stall_load_use <- mkReg(False);    // Load-Use 停顿标志
    Reg#(Bit#(2)) stall_count <- mkReg(0);        // 停顿剩余周期数

    // 分支冲刷控制
    Reg#(Bool) branch_flush <- mkReg(False);      // 分支冲刷标志
    Reg#(Bool) branch_flush_done <- mkReg(False); // 分支冲刷完成标志（阻止 IF 更新 PC）
    Reg#(Bool) no_pc_update <- mkReg(False);      // 阻止 IF 更新 PC（用于 JAL 循环）

    // PC和状态
    Reg#(Addr) pcReg <- mkReg(32'h80000000);
    Reg#(Word) currentInstr <- mkReg(0);
    Reg#(ProcessorState) state <- mkReg(RUNNING);
    Reg#(Bool) programLoaded <- mkReg(False);

    // 前递数据（WB 前递使用双缓冲，保存最近两个 WB 写入）
    Reg#(Word) wb_forward_data0 <- mkReg(0);  // 上一周期 WB 写入
    Reg#(Bit#(5)) wb_forward_rd0 <- mkReg(0);
    Reg#(Bool) wb_forward_valid0 <- mkReg(False);

    Reg#(Word) wb_forward_data1 <- mkReg(0);  // 两周期前 WB 写入
    Reg#(Bit#(5)) wb_forward_rd1 <- mkReg(0);
    Reg#(Bool) wb_forward_valid1 <- mkReg(False);

    // 内存（保持原配置避免编译问题）
    Vector#(1024, Reg#(Word)) imem <- replicateM(mkReg(0));   // 4KB, 2^10 entries
    Vector#(512, Reg#(Word)) dmem <- replicateM(mkReg(0));    // 2KB, 2^9 entries

    // tohost 检测（riscv-tests 完成信号）
    Reg#(Bool) test_done <- mkReg(False);
    Reg#(Word) tohost_value <- mkReg(0);
    Addr tohost_addr = 32'h80001000;  // riscv-tests 标准地址

    // 陷阱控制
    Reg#(Bool) in_trap <- mkReg(False);
    Reg#(Bool) wfi_waiting <- mkReg(False);

    // ============================================================
    // IF阶段
    // ============================================================

    rule fetchStage (programLoaded && state == RUNNING && !stall_load_use && !branch_flush);
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

        Bit#(10) idx = fetchPC[11:2];  // 10 位索引
        Word instr = imem[idx];

        if2id.enq(IF_ID_Packet {
            pc: fetchPC,
            instruction: instr,
            predicted_pc: prediction_target,
            predicted_taken: take_prediction,
            priv_mode: pack(csrs.currentMode())
        });

        currentInstr <= instr;
        // 如果预测跳转，PC 更新为预测目标；否则顺序执行
        // 但如果刚完成分支冲刷或 no_pc_update，不更新 PC
        if (!branch_flush_done && !no_pc_update) begin
            if (take_prediction)
                pcReg <= prediction_target;
            else
                pcReg <= pcReg + 4;
        end
    endrule

    // 分支冲刷清除（branch_flush 持续一周期后自动清除）
    rule clearBranchFlush (branch_flush);
        branch_flush <= False;
        branch_flush_done <= True;  // 设置完成标志，阻止 IF 更新 PC 一周期
    endrule

    // 分支冲刷完成标志清除
    rule clearBranchFlushDone (branch_flush_done && !branch_flush);
        branch_flush_done <= False;
    endrule

    // ============================================================
    // ID阶段
    // ============================================================

    rule decodeStage (!stall_load_use);
        IF_ID_Packet pkt = if2id.first;
        DecodedInstr dec = decoder.decode(pkt.instruction);

        // 检测 Load-Use 冒险（只检查 EX 阶段的 Load）
        Bool load_use_hazard = False;

        if (id2ex.notEmpty && id2ex.first.mem_op == MEM_READ && id2ex.first.rd != 0) begin
            Bit#(5) ex_rd = id2ex.first.rd;
            if (dec.use_rs1 && dec.rs1 == ex_rd)
                load_use_hazard = True;
            if (dec.use_rs2 && dec.rs2 == ex_rd)
                load_use_hazard = True;
        end

        if (load_use_hazard) begin
            // 停顿 ID 阶段，不发送包到 EX
            stall_load_use <= True;
            stall_count <= 2;  // Load 需要 2 周期从 EX→MEM→WB
            // 立即插入气泡到 id2ex（当前周期）
            id2ex.enq(nopPacket());
            // 注意：不 deq if2id，保留指令供下个周期使用
        end else begin
            // 正常解码并发送到 EX
            if2id.deq;

            Word rs1_val = regFile.read1(dec.rs1);
            Word rs2_val = regFile.read2(dec.rs2);

            // WB→ID 前递（WB 刚写入的数据同周期可用）
            if (wb_forward_valid0 && wb_forward_rd0 == dec.rs1 && dec.rs1 != 0)
                rs1_val = wb_forward_data0;
            else if (wb_forward_valid1 && wb_forward_rd1 == dec.rs1 && dec.rs1 != 0)
                rs1_val = wb_forward_data1;
            if (wb_forward_valid0 && wb_forward_rd0 == dec.rs2 && dec.rs2 != 0)
                rs2_val = wb_forward_data0;
            else if (wb_forward_valid1 && wb_forward_rd1 == dec.rs2 && dec.rs2 != 0)
                rs2_val = wb_forward_data1;

            // 检测 ECALL/EBREAK (opcode = 7'b1110011, funct3 = 3'b000)
            Bit#(7) opcode = getOpcode(pkt.instruction);
            Bit#(3) funct3 = getFunct3(pkt.instruction);
            Bit#(7) funct7 = getFunct7(pkt.instruction);

            Bool is_ecall = (opcode == 7'b1110011) && (funct3 == 3'b000) && (funct7 == 7'b0000000);
            Bool is_ebreak = (opcode == 7'b1110011) && (funct3 == 3'b000) && (funct7 == 7'b0000001);

            // 陷阱信息
            Bool has_trap = False;
            Addr trap_epc = 0;
            Bit#(5) trap_cause = 0;
            Bool trap_is_interrupt = False;
            Addr trap_tval = 0;
            Bit#(2) trap_mode = 0;

            if (is_ecall) begin
                has_trap = True;
                trap_epc = pkt.pc;
                trap_is_interrupt = False;
                trap_tval = 0;
                trap_mode = pkt.priv_mode;
                // 根据当前模式选择异常码
                case (pkt.priv_mode)
                    2'b11: trap_cause = 5'd11;  // EXC_ECALL_M
                    2'b01: trap_cause = 5'd9;   // EXC_ECALL_S
                    2'b00: trap_cause = 5'd8;   // EXC_ECALL_U
                    default: trap_cause = 5'd11;
                endcase
            end

            if (is_ebreak) begin
                has_trap = True;
                trap_epc = pkt.pc;
                trap_cause = 5'd3;  // EXC_BREAKPOINT
                trap_is_interrupt = False;
                trap_tval = 0;
                trap_mode = pkt.priv_mode;
            end

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
                use_imm: dec.use_imm,
                mem_width: dec.mem_width,
                mem_unsigned: dec.mem_unsigned,
                has_trap: has_trap,
                trap_epc: trap_epc,
                trap_cause: trap_cause,
                trap_is_interrupt: trap_is_interrupt,
                trap_tval: trap_tval,
                trap_mode: trap_mode
            });
        end
    endrule

    // Stall 计数递减规则
    rule decrementStall (stall_load_use && stall_count > 0);
        Bit#(2) new_count = stall_count - 1;
        stall_count <= new_count;
        if (new_count == 0) begin
            stall_load_use <= False;  // 计数结束，清除 stall
        end
        // 在 stall 周期插入气泡到 id2ex
        id2ex.enq(nopPacket());
    endrule

    // ============================================================
    // EX阶段
    // ============================================================

    (* execution_order = "writebackStage, executeStage" *)
    (* preempts = "executeStage, fetchStage" *)
    rule executeStage (!stall_load_use && id2ex.notEmpty && ex2mem.notFull);
        ID_EX_Packet pkt = id2ex.first;

        // 前递逻辑
        Word op1 = pkt.rs1_val;
        Word op2 = pkt.rs2_val;

        // WB→EX 前递（直接读取 mem2wb.first，同周期可用）
        if (mem2wb.notEmpty && mem2wb.first.write_reg && mem2wb.first.rd == pkt.rs1 && pkt.rs1 != 0)
            op1 = mem2wb.first.is_load ? mem2wb.first.mem_data : mem2wb.first.alu_result;
        else if (wb_forward_valid0 && wb_forward_rd0 == pkt.rs1 && pkt.rs1 != 0)
            op1 = wb_forward_data0;
        else if (wb_forward_valid1 && wb_forward_rd1 == pkt.rs1 && pkt.rs1 != 0)
            op1 = wb_forward_data1;
        if (mem2wb.notEmpty && mem2wb.first.write_reg && mem2wb.first.rd == pkt.rs2 && pkt.rs2 != 0)
            op2 = mem2wb.first.is_load ? mem2wb.first.mem_data : mem2wb.first.alu_result;
        else if (wb_forward_valid0 && wb_forward_rd0 == pkt.rs2 && pkt.rs2 != 0)
            op2 = wb_forward_data0;
        else if (wb_forward_valid1 && wb_forward_rd1 == pkt.rs2 && pkt.rs2 != 0)
            op2 = wb_forward_data1;

        // MEM→EX 前递（从 ex2mem FIFO 读取上一周期 EX 输出）
        if (ex2mem.notEmpty && ex2mem.first.write_reg && !ex2mem.first.is_load && ex2mem.first.rd == pkt.rs1 && pkt.rs1 != 0)
            op1 = ex2mem.first.alu_result;
        if (ex2mem.notEmpty && ex2mem.first.write_reg && !ex2mem.first.is_load && ex2mem.first.rd == pkt.rs2 && pkt.rs2 != 0)
            op2 = ex2mem.first.alu_result;

        // ALU输入选择
        Word alu_in1, alu_in2;
        case (pkt.alu_op)
            ALU_PASS: begin alu_in1 = pkt.imm; alu_in2 = 0; end
            ALU_PC:   begin alu_in1 = pkt.pc; alu_in2 = pkt.imm; end
            ALU_ADD:  begin alu_in1 = op1; alu_in2 = pkt.use_imm ? pkt.imm : op2; end
            ALU_SUB:  begin alu_in1 = op1; alu_in2 = op2; end
            default:  begin
                alu_in1 = op1;
                alu_in2 = pkt.use_imm ? pkt.imm : op2;  // I-Type 也需要使用立即数
            end
        endcase

        Word alu_result = alu.execute(pkt.alu_op, alu_in1, alu_in2);

        // 分支判断
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

        // 更新BHT和BTB
        Bool btb_update_valid = (pkt.is_jump) || (pkt.is_branch && branch_taken);
        btb.update(pkt.pc, actual_target, btb_update_valid);
        if (pkt.is_branch)
            bht.update(pkt.pc, branch_taken);

        // ========== 主控制流：陷阱 -> CSR -> MRET -> 正常分支 ==========
        Bool is_mret = (getOpcode(pkt.instruction) == 7'b1110011) && (getFunct3(pkt.instruction) == 3'b000) && (getFunct7(pkt.instruction) == 7'b0011000);
        Bool is_load = (pkt.mem_op == MEM_READ);

        // 陷阱处理 (最高优先级)
        if (pkt.has_trap) begin
            csrs.writeCSR(12'h341, pack(pkt.trap_epc));  // mepc
            csrs.writeCSR(12'h342, zeroExtend(pkt.trap_cause));  // mcause
            csrs.writeCSR(12'h343, pack(pkt.trap_tval));  // mtval

            MStatus ms = unpackMStatus(csrs.readCSR(12'h300));
            MStatus new_ms = ms;
            new_ms.mpie = ms.mie;
            new_ms.mpp = pkt.trap_mode;
            new_ms.mie = 0;
            csrs.writeCSR(12'h300, packMStatus(new_ms));

            csrs.setMode(M_MODE);

            Addr trap_base = csrs.readCSR(12'h305) & ~32'h3;
            pcReg <= trap_base;
            branch_flush <= True;
            no_pc_update <= True;
            if2id.clear;
            id2ex.clear;
        end else begin
            // 非陷阱路径：处理 CSR 指令或正常分支
            DecodedInstr dec = decoder.decode(pkt.instruction);
            if (dec.is_csr) begin
                // CSR 读-修改-写 (软件原子性)
                Word old_csr = csrs.readCSR(dec.csr_addr);
                Word csr_result = old_csr;
                Word new_csr = case (dec.csr_op)
                    CSR_OP_WRITE: dec.is_csr_imm ? { 27'b0, dec.csr_zimm } : op1;
                    CSR_OP_SET:   old_csr | (dec.is_csr_imm ? { 27'b0, dec.csr_zimm } : op1);
                    CSR_OP_CLR:   old_csr & ~(dec.is_csr_imm ? { 27'b0, dec.csr_zimm } : op1);
                    CSR_OP_READ:  old_csr;
                    default:      old_csr;
                endcase;
                if (dec.csr_op != CSR_OP_READ) begin
                    csrs.writeCSR(dec.csr_addr, new_csr);
                end
                alu_result = csr_result;
            end

            // MRET 处理
            if (is_mret) begin
                MStatus ms = unpackMStatus(csrs.readCSR(12'h300));
                MStatus new_ms = ms;
                new_ms.mie = ms.mpie;
                new_ms.mpie = 1;
                csrs.writeCSR(12'h300, packMStatus(new_ms));

                PrivilegeMode prev = unpack(ms.mpp);
                csrs.setMode(prev);

                pcReg <= csrs.readCSR(12'h341);
                no_pc_update <= True;
                branch_flush <= True;
                if2id.clear;
                id2ex.clear;
            end else begin
                // 正常分支/跳转执行
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

                // enq 到 ex2mem
                ex2mem.enq(EX_MEM_Packet {
                    pc: pkt.pc,
                    alu_result: alu_result,
                    rs2_val: op2,
                    rd: pkt.rd,
                    mem_op: pkt.mem_op,
                    is_branch: pkt.is_branch,
                    is_jump: pkt.is_jump,
                    branch_taken: branch_taken,
                    actual_target: actual_target,
                    predicted_taken: False,
                    write_reg: pkt.write_reg,
                    is_load: is_load,
                    mem_width: pkt.mem_width,
                    mem_unsigned: pkt.mem_unsigned
                });
            end
        end
    endrule

    // ============================================================
    // MEM阶段
    // ============================================================

    rule memoryStage;
        EX_MEM_Packet pkt = ex2mem.first;
        ex2mem.deq;

        Word mem_data = 0;

        // 对齐检查（阶段1仅打印警告）
        if (pkt.mem_op != MEM_NONE && !checkAlignment(pkt.alu_result, pkt.mem_width)) begin
            $display("WARNING: Misaligned access at PC=%h, addr=%h, width=%s",
                     pkt.pc, pkt.alu_result, pkt.mem_width);
        end

        // 内存读取
        if (pkt.mem_op == MEM_READ) begin
            Bit#(9) word_idx = pkt.alu_result[10:2];  // 9 位索引
            Word word_val = dmem[word_idx];

            case (pkt.mem_width)
                MEM_WORD: mem_data = word_val;

                MEM_HALF: begin
                    Bit#(1) half_offset = pkt.alu_result[1];
                    Bit#(16) half_val = half_offset == 0
                        ? word_val[15:0]
                        : word_val[31:16];
                    mem_data = pkt.mem_unsigned
                        ? zeroExtend(half_val)
                        : signExtend(half_val);
                end

                MEM_BYTE: begin
                    Bit#(2) byte_offset = pkt.alu_result[1:0];
                    Bit#(8) byte_val = case (byte_offset)
                        0: word_val[7:0];
                        1: word_val[15:8];
                        2: word_val[23:16];
                        3: word_val[31:24];
                    endcase;
                    mem_data = pkt.mem_unsigned
                        ? zeroExtend(byte_val)
                        : signExtend(byte_val);
                end
            endcase
        end

        // 内存写入
        if (pkt.mem_op == MEM_WRITE) begin
            Bit#(9) word_idx = pkt.alu_result[10:2];  // 9 位索引
            Word old_word = dmem[word_idx];
            Word new_word = old_word;

            case (pkt.mem_width)
                MEM_WORD: new_word = pkt.rs2_val;

                MEM_HALF: begin
                    Bit#(16) half_val = pkt.rs2_val[15:0];
                    Bit#(1) half_offset = pkt.alu_result[1];
                    new_word = half_offset == 0
                        ? {old_word[31:16], half_val}
                        : {half_val, old_word[15:0]};
                end

                MEM_BYTE: begin
                    Bit#(8) byte_val = pkt.rs2_val[7:0];
                    Bit#(2) byte_offset = pkt.alu_result[1:0];
                    case (byte_offset)
                        0: new_word = {old_word[31:8], byte_val};
                        1: new_word = {old_word[31:16], byte_val, old_word[7:0]};
                        2: new_word = {old_word[31:24], byte_val, old_word[15:0]};
                        3: new_word = {byte_val, old_word[23:0]};
                    endcase
                end
            endcase

            dmem[word_idx] <= new_word;

            // tohost 写入检测
            if (pkt.alu_result == tohost_addr) begin
                test_done <= True;
                tohost_value <= pkt.rs2_val;
            end
        end

        mem2wb.enq(MEM_WB_Packet {
            pc: pkt.pc,
            mem_data: mem_data,
            alu_result: pkt.alu_result,
            rd: pkt.rd,
            write_reg: pkt.write_reg,
            is_load: pkt.is_load
        });
    endrule

    // ============================================================
    // WB阶段
    // ============================================================

    rule writebackStage;
        MEM_WB_Packet pkt = mem2wb.first;
        mem2wb.deq;

        Word wb_data = pkt.is_load ? pkt.mem_data : pkt.alu_result;

        if (pkt.write_reg && pkt.rd != 0) begin
            regFile.write(pkt.rd, wb_data);
        end

        // WB 前递设置（Load 数据在此阶段可用）
        // 双缓冲更新：wb_forward_data1 ← wb_forward_data0 ← wb_data
        wb_forward_data1 <= wb_forward_data0;
        wb_forward_rd1 <= wb_forward_rd0;
        wb_forward_valid1 <= wb_forward_valid0;

        wb_forward_data0 <= wb_data;
        wb_forward_rd0 <= pkt.rd;
        wb_forward_valid0 <= pkt.write_reg;

        // CSR 指令在 EX 阶段已处理，这里只更新计数器
        csrs.incrementMinstret;
    endrule

    // ============================================================
    // 接口
    // ============================================================

    method Addr pc = pcReg;
    method Word instruction = currentInstr;
    method Bool running = (state == RUNNING);
    method Bool testDone = test_done;
    method Word tohostValue = tohost_value;

    method Action loadProgram(Vector#(1024, Word) prog);
        for (Integer i = 0; i < 1024; i = i + 1)
            imem[i] <= prog[i];
        programLoaded <= True;
    endmethod

    method Word readReg(Bit#(5) addr);
        return regFile.readReg(addr);
    endmethod
endmodule

function Bool signedLT(Word a, Word b);
    Int#(32) sa = unpack(a);
    Int#(32) sb = unpack(b);
    return (sa < sb);
endfunction

function Bool signedGE(Word a, Word b);
    Int#(32) sa = unpack(a);
    Int#(32) sb = unpack(b);
    return (sa >= sb);
endfunction

// 地址对齐检查函数
function Bool checkAlignment(Addr addr, MemWidth width);
    case (width)
        MEM_BYTE:  return True;           // 字节访问：任意对齐
        MEM_HALF:  return addr[0] == 0;   // 半字访问：addr[0] 必须为 0
        MEM_WORD:  return addr[1:0] == 0; // 字访问：addr[1:0] 必须为 0
        default:   return True;
    endcase
endfunction

// NOP 包辅助函数
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
        use_imm: False,
        mem_width: MEM_WORD,
        mem_unsigned: False,
        has_trap: False,
        trap_epc: 0,
        trap_cause: 0,
        trap_is_interrupt: False,
        trap_tval: 0,
        trap_mode: 0
    };
endfunction

endpackage
