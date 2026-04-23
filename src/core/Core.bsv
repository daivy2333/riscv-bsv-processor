// src/core/Core.bsv - 彻底重构版（使用 MemChannel 接口）
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
import MemInterface::*;
import FIFO::*;
import FIFOF::*;
import Vector::*;

interface Core;
    method Addr pc;
    method Word instruction;
    method Bool running;
    method Action loadProgram(Vector#(4096, Word) prog);  // 加载程序（16KB）
endinterface

// Core 接收 MemChannel 接口作为参数
module mkCore#(String firmwareFile, MemChannel mem_if)(Core);
    Decoder decoder <- mkDecoder;
    ALU alu <- mkALU;
    RegFile regFile <- mkRegFile;
    BHT bht <- mkBHT;
    BTB btb <- mkBTB;
    HazardUnit hazardUnit <- mkHazardUnit;
    // CSR 由 SOC 提供，Core 使用 mem_if.csrModule()

    // 流水线寄存器（使用 FIFOF 深度2）
    FIFOF#(IF_ID_Packet) if2id <- mkFIFOF;
    FIFOF#(ID_EX_Packet) id2ex <- mkFIFOF;
    FIFOF#(EX_MEM_Packet) ex2mem <- mkFIFOF;
    FIFOF#(MEM_WB_Packet) mem2wb <- mkFIFOF;

    // Load-Use停顿控制
    Reg#(Bool) stall_load_use <- mkReg(False);
    Reg#(Bit#(2)) stall_count <- mkReg(0);

    // EX阶段信息缓存
    Reg#(Bool) ex_is_load_cached <- mkReg(False);
    Reg#(Bit#(5)) ex_rd_cached <- mkReg(0);

    // MEM阶段信息缓存
    Reg#(Bool) mem_write_reg_cached <- mkReg(False);
    Reg#(Bool) mem_is_load_cached <- mkReg(False);
    Reg#(Bit#(5)) mem_rd_cached <- mkReg(0);
    Reg#(Word) mem_alu_result_cached <- mkReg(0);

    // WB阶段信息缓存
    Reg#(Bool) wb_write_reg_cached <- mkReg(False);
    Reg#(Bool) wb_is_load_cached <- mkReg(False);
    Reg#(Bit#(5)) wb_rd_cached <- mkReg(0);
    Reg#(Word) wb_alu_result_cached <- mkReg(0);
    Reg#(Word) wb_mem_data_cached <- mkReg(0);

    // 控制流重定向协议
    Reg#(Bool) redirect_pending <- mkReg(False);
    Reg#(Addr) redirect_target <- mkReg(0);
    Reg#(Bit#(4)) redirect_reason <- mkReg(0);

    // PC和状态
    Reg#(Addr) pcReg <- mkReg(32'h80000000);
    Reg#(Word) currentInstr <- mkReg(0);
    Reg#(ProcessorState) state <- mkReg(RUNNING);
    Reg#(Bool) programLoaded <- mkReg(False);

    // 前递数据
    Reg#(Word) wb_forward_data0 <- mkReg(0);
    Reg#(Bit#(5)) wb_forward_rd0 <- mkReg(0);
    Reg#(Bool) wb_forward_valid0 <- mkReg(False);

    Reg#(Word) wb_forward_data1 <- mkReg(0);
    Reg#(Bit#(5)) wb_forward_rd1 <- mkReg(0);
    Reg#(Bool) wb_forward_valid1 <- mkReg(False);

    Wire#(Word) wb_bypass_data <- mkDWire(0);
    Wire#(Bit#(5)) wb_bypass_rd <- mkDWire(0);
    Wire#(Bool) wb_bypass_valid <- mkDWire(False);

    // 内存
    Vector#(4096, Reg#(Word)) imem <- replicateM(mkReg(0));

    // Load 响应等待状态
    Reg#(Bool) waiting_for_load_resp <- mkReg(False);

    // 陷阱控制
    Reg#(Bool) in_trap <- mkReg(False);
    Reg#(Bool) wfi_waiting <- mkReg(False);

    // ============================================================
    // 中断驱动规则（每周期执行，优先级最高）
    // ============================================================
    rule drive_interrupts;
        mem_if.timerIRQWire(mem_if.clintTimerIRQ());
        mem_if.softwareIRQWire(mem_if.clintSoftwareIRQ());
        mem_if.externalIRQWire(mem_if.plicExternalIRQ());

        // 调试：显示定时器中断状态（已禁用）
        // if (mem_if.clintTimerIRQ()) begin
        //     $display("[IRQ] Timer IRQ active!");
        // end
    endrule

    // ============================================================
    // IF阶段
    // ============================================================

    (* execution_order = "consumeRedirect, fetchStage" *)
    // IF 规则：当流水线被清空时（mem2wb 空），允许取指即使有 Load 等待状态
    // 这是为了处理 WB 中断处理后流水线清空的情况
    rule fetchStage (programLoaded && state == RUNNING && !stall_load_use && !redirect_pending && (!waiting_for_load_resp || !mem2wb.notEmpty));
        Addr fetchPC = pcReg;

        // 调试：显示取指地址和状态（已禁用）
        // $display("[IF] Fetch from %x, redirect_pending=%d, waiting_for_load_resp=%d", fetchPC, redirect_pending, waiting_for_load_resp);

        Bool take_prediction = False;
        Addr prediction_target = 0;

        Bit#(12) idx = fetchPC[13:2];
        Word instr = imem[idx];

        Maybe#(Addr) btb_hit = btb.lookup(fetchPC);
        Bool bht_predict = bht.predict(fetchPC);

        Bit#(7) opcode = instr[6:0];
        Bool is_jal = (opcode == 7'b1101111);
        Bool is_jalr = (opcode == 7'b1100111);

        if (btb_hit matches tagged Valid .target) begin
            if (is_jal || is_jalr) begin
                take_prediction = True;
                prediction_target = target;
            end else if (bht_predict) begin
                take_prediction = True;
                prediction_target = target;
            end
        end

        Addr next_pc = take_prediction ? prediction_target : fetchPC + 4;

        if2id.enq(IF_ID_Packet {
            pc: fetchPC,
            instruction: instr,
            predicted_pc: prediction_target,
            predicted_taken: take_prediction,
            priv_mode: pack(mem_if.csrModule().currentMode())
        });

        currentInstr <= instr;
        if (take_prediction)
            pcReg <= prediction_target;
        else
            pcReg <= pcReg + 4;
    endrule

    rule consumeRedirect (redirect_pending);
        redirect_pending <= False;
    endrule

    // ============================================================
    // ID阶段
    // ============================================================

    rule decodeStage (!stall_load_use && !waiting_for_load_resp && if2id.notEmpty);
        IF_ID_Packet pkt = if2id.first;
        DecodedInstr dec = decoder.decode(pkt.instruction);

        Bool load_use_hazard = False;

        if (ex_is_load_cached && ex_rd_cached != 0) begin
            Bit#(5) ex_rd = ex_rd_cached;
            if (dec.use_rs1 && dec.rs1 == ex_rd)
                load_use_hazard = True;
            if (dec.use_rs2 && dec.rs2 == ex_rd)
                load_use_hazard = True;
        end

        if (load_use_hazard) begin
            stall_load_use <= True;
            stall_count <= 3;
            id2ex.enq(nopPacket());
            ex_is_load_cached <= False;
            ex_rd_cached <= 0;
        end else begin
            if2id.deq;

            Word rs1_val = regFile.read1(dec.rs1);
            Word rs2_val = regFile.read2(dec.rs2);

            // WB→ID 前递
            if (wb_forward_valid0 && wb_forward_rd0 == dec.rs1 && dec.rs1 != 0)
                rs1_val = wb_forward_data0;
            else if (wb_forward_valid1 && wb_forward_rd1 == dec.rs1 && dec.rs1 != 0)
                rs1_val = wb_forward_data1;
            if (wb_forward_valid0 && wb_forward_rd0 == dec.rs2 && dec.rs2 != 0)
                rs2_val = wb_forward_data0;
            else if (wb_forward_valid1 && wb_forward_rd1 == dec.rs2 && dec.rs2 != 0)
                rs2_val = wb_forward_data1;

            Bit#(7) opcode = getOpcode(pkt.instruction);
            Bit#(3) funct3 = getFunct3(pkt.instruction);
            Bit#(7) funct7 = getFunct7(pkt.instruction);

            Bool is_ecall = (opcode == 7'b1110011) && (funct3 == 3'b000) && (funct7 == 7'b0000000);
            Bool is_ebreak = (opcode == 7'b1110011) && (funct3 == 3'b000) && (funct7 == 7'b0000001);

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
                case (pkt.priv_mode)
                    2'b11: trap_cause = 5'd11;
                    2'b01: trap_cause = 5'd9;
                    2'b00: trap_cause = 5'd8;
                    default: trap_cause = 5'd11;
                endcase
            end

            if (is_ebreak) begin
                has_trap = True;
                trap_epc = pkt.pc;
                trap_cause = 5'd3;
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
                trap_mode: trap_mode,
                predicted_taken: pkt.predicted_taken,
                predicted_target: pkt.predicted_pc
            });
            ex_is_load_cached <= (dec.mem_op == MEM_READ);
            ex_rd_cached <= dec.rd;
        end
    endrule

    rule decrementStall (stall_load_use && stall_count > 0);
        Bit#(2) new_count = stall_count - 1;
        stall_count <= new_count;
        if (new_count == 0) begin
            stall_load_use <= False;
        end
        id2ex.enq(nopPacket());
        ex_is_load_cached <= False;
        ex_rd_cached <= 0;
    endrule

    // ============================================================
    // EX阶段
    // ============================================================

    (* execution_order = "writebackStage_nonLoad, writebackStage_Load, executeStage" *)
    (* preempts = "executeStage, fetchStage" *)
    rule executeStage (id2ex.notEmpty && ex2mem.notFull && !waiting_for_load_resp);
        ID_EX_Packet pkt = id2ex.first;

        Word op1 = pkt.rs1_val;
        Word op2 = pkt.rs2_val;

        // MEM→EX 前递
        if (mem_write_reg_cached && !mem_is_load_cached && mem_rd_cached == pkt.rs1 && pkt.rs1 != 0)
            op1 = mem_alu_result_cached;
        else if (wb_bypass_valid && wb_bypass_rd == pkt.rs1 && pkt.rs1 != 0)
            op1 = wb_bypass_data;
        else if (wb_write_reg_cached && wb_rd_cached == pkt.rs1 && pkt.rs1 != 0)
            op1 = wb_is_load_cached ? wb_mem_data_cached : wb_alu_result_cached;
        else if (wb_forward_valid0 && wb_forward_rd0 == pkt.rs1 && pkt.rs1 != 0)
            op1 = wb_forward_data0;
        else if (wb_forward_valid1 && wb_forward_rd1 == pkt.rs1 && pkt.rs1 != 0)
            op1 = wb_forward_data1;

        if (mem_write_reg_cached && !mem_is_load_cached && mem_rd_cached == pkt.rs2 && pkt.rs2 != 0)
            op2 = mem_alu_result_cached;
        else if (wb_bypass_valid && wb_bypass_rd == pkt.rs2 && pkt.rs2 != 0)
            op2 = wb_bypass_data;
        else if (wb_write_reg_cached && wb_rd_cached == pkt.rs2 && pkt.rs2 != 0)
            op2 = wb_is_load_cached ? wb_mem_data_cached : wb_alu_result_cached;
        else if (wb_forward_valid0 && wb_forward_rd0 == pkt.rs2 && pkt.rs2 != 0)
            op2 = wb_forward_data0;
        else if (wb_forward_valid1 && wb_forward_rd1 == pkt.rs2 && pkt.rs2 != 0)
            op2 = wb_forward_data1;

        Word alu_in1, alu_in2;
        case (pkt.alu_op)
            ALU_PASS: begin alu_in1 = pkt.imm; alu_in2 = 0; end
            ALU_PC:   begin alu_in1 = pkt.pc; alu_in2 = pkt.imm; end
            ALU_ADD:  begin alu_in1 = op1; alu_in2 = pkt.use_imm ? pkt.imm : op2; end
            ALU_SUB:  begin alu_in1 = op1; alu_in2 = op2; end
            default:  begin
                alu_in1 = op1;
                alu_in2 = pkt.use_imm ? pkt.imm : op2;
            end
        endcase

        Word alu_result = alu.execute(pkt.alu_op, alu_in1, alu_in2);

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

        Bool btb_update_valid = (pkt.is_jump) || (pkt.is_branch && branch_taken);
        btb.update(pkt.pc, actual_target, btb_update_valid);
        if (pkt.is_branch)
            bht.update(pkt.pc, branch_taken);
        else if (pkt.is_jump)
            bht.update(pkt.pc, True);

        Bool is_mret = (getOpcode(pkt.instruction) == 7'b1110011) && (getFunct3(pkt.instruction) == 3'b000) && (getFunct7(pkt.instruction) == 7'b0011000);
        Bool is_load = (pkt.mem_op == MEM_READ);

        if (pkt.has_trap) begin
            /* 标准RISC-V：CPU更新CSR并跳转
             * trap_entry 负责：保存CSR到帧，恢复寄存器
             */
            $display("[TRAP] cause=%d, pc=%x", pkt.trap_cause, pkt.trap_epc);
            mem_if.csrModule().writeCSR(12'h341, pack(pkt.trap_epc));
            mem_if.csrModule().writeCSR(12'h342, zeroExtend(pack(pkt.trap_cause)) | (pkt.trap_is_interrupt ? 32'h80000000 : 0));
            mem_if.csrModule().writeCSR(12'h343, pack(pkt.trap_tval));

            MStatus ms = unpackMStatus(mem_if.csrModule().readCSR(12'h300));
            MStatus new_ms = ms;
            new_ms.mpie = ms.mie;
            new_ms.mpp = pack(pkt.trap_mode);
            new_ms.mie = 0;
            mem_if.csrModule().writeCSR(12'h300, packMStatus(new_ms));
            mem_if.csrModule().setMode(M_MODE);

            Addr trap_base = mem_if.csrModule().readCSR(12'h305) & ~32'h3;
            redirect_pending <= True;
            redirect_target <= trap_base;
            redirect_reason <= 3;
            pcReg <= trap_base;
            if2id.clear;
            id2ex.clear;
        end else begin
            DecodedInstr dec = decoder.decode(pkt.instruction);
            if (dec.is_csr) begin
                Word old_csr = mem_if.csrModule().readCSR(dec.csr_addr);
                Word csr_result = old_csr;
                Word new_csr = case (dec.csr_op)
                    CSR_OP_WRITE: dec.is_csr_imm ? { 27'b0, dec.csr_zimm } : op1;
                    CSR_OP_SET:   old_csr | (dec.is_csr_imm ? { 27'b0, dec.csr_zimm } : op1);
                    CSR_OP_CLR:   old_csr & ~(dec.is_csr_imm ? { 27'b0, dec.csr_zimm } : op1);
                    CSR_OP_READ:  old_csr;
                    default:      old_csr;
                endcase;
                // 调试：打印 CSR 指令执行（已禁用）
                // $display("[EX_CSR] pc=%x, csr_addr=%x, csr_op=%d, is_imm=%d, zimm=%x, op1=%x, old=%x, new=%x",
                //     pkt.pc, dec.csr_addr, dec.csr_op, dec.is_csr_imm, dec.csr_zimm, op1, old_csr, new_csr);
                if (dec.csr_op != CSR_OP_READ) begin
                    mem_if.csrModule().writeCSR(dec.csr_addr, new_csr);
                end
                alu_result = csr_result;
            end

            if (is_mret) begin
                MStatus ms = unpackMStatus(mem_if.csrModule().readCSR(12'h300));
                MStatus new_ms = ms;
                new_ms.mie = ms.mpie;
                new_ms.mpie = 1;
                mem_if.csrModule().writeCSR(12'h300, packMStatus(new_ms));

                PrivilegeMode prev = unpack(ms.mpp);
                mem_if.csrModule().setMode(prev);

                Addr mepc = mem_if.csrModule().readCSR(12'h341);
                redirect_pending <= True;
                redirect_target <= mepc;
                redirect_reason <= 4;
                pcReg <= mepc;
                if2id.clear;
                id2ex.clear;
            end else begin
                Bool mispredicted = pkt.is_branch && (pkt.predicted_taken != branch_taken);

                // 先处理 deq（除非需要 clear）
                Bool need_clear = False;

                if (branch_taken) begin
                    // 分支 taken：只有预测失败时才重定向
                    Bool prediction_correct = pkt.predicted_taken && (pkt.predicted_target == actual_target);
                    if (!prediction_correct) begin
                        need_clear = True;
                        Bit#(4) reason = pkt.is_jump ? 2 : 1;
                        redirect_pending <= True;
                        redirect_target <= actual_target;
                        redirect_reason <= reason;
                        pcReg <= actual_target;
                    end
                    // 预测正确时，不重定向（PC 已由预测设置）
                end else if (mispredicted) begin
                    need_clear = True;
                    redirect_pending <= True;
                    redirect_target <= pkt.pc + 4;
                    redirect_reason <= 1;
                    pcReg <= pkt.pc + 4;
                end

                // 清除或正常消费
                if (need_clear) begin
                    if2id.clear;
                    id2ex.clear;
                end else begin
                    id2ex.deq;
                end

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
                    predicted_taken: pkt.predicted_taken,
                    predicted_target: pkt.predicted_target,
                    write_reg: pkt.write_reg,
                    is_load: is_load,
                    mem_width: pkt.mem_width,
                    mem_unsigned: pkt.mem_unsigned
                });
            end
        end
    endrule

    // ============================================================
    // MEM阶段（通过 MemChannel 发送请求）
    // ============================================================

    (* execution_order = "writebackStage_nonLoad, writebackStage_Load, memoryStage" *)
    rule memoryStage (ex2mem.notEmpty && !waiting_for_load_resp);
        EX_MEM_Packet pkt = ex2mem.first;
        ex2mem.deq;

        mem_write_reg_cached <= pkt.write_reg;
        mem_is_load_cached <= pkt.is_load;
        mem_rd_cached <= pkt.rd;
        mem_alu_result_cached <= pkt.alu_result;

        if (pkt.mem_op != MEM_NONE && !checkAlignment(pkt.alu_result, pkt.mem_width)) begin
            // Misaligned access - silently handle
        end

        // 通过 MemChannel 发送请求
        MemReq req = nopMemReq();
        if (pkt.mem_op != MEM_NONE) begin
            req = MemReq {
                valid: True,
                addr: pkt.alu_result,
                wdata: pkt.rs2_val,
                op: pkt.mem_op,
                width: pkt.mem_width,
                is_unsigned: pkt.mem_unsigned
            };

            // 直接调用 MemChannel 方法发送请求
            mem_if.sendMemReq(req);
        end

        if (pkt.is_load) begin
            waiting_for_load_resp <= True;
        end

        mem2wb.enq(MEM_WB_Packet {
            pc: pkt.pc,
            mem_data: 0,
            alu_result: pkt.alu_result,
            rd: pkt.rd,
            write_reg: pkt.write_reg,
            is_load: pkt.is_load,
            mem_width: pkt.mem_width,
            mem_unsigned: pkt.mem_unsigned
        });
    endrule

    // ============================================================
    // WB阶段（通过 MemChannel 接收响应）
    // ============================================================

    // 非Load包可以直接commit，Load包需要等待响应
    rule writebackStage_nonLoad (mem2wb.notEmpty && !mem2wb.first.is_load);
        MEM_WB_Packet pkt = mem2wb.first;
        mem2wb.deq;

        Word wb_data = pkt.alu_result;

        wb_write_reg_cached <= pkt.write_reg;
        wb_is_load_cached <= pkt.is_load;
        wb_rd_cached <= pkt.rd;
        wb_alu_result_cached <= pkt.alu_result;
        wb_mem_data_cached <= wb_data;

        if (pkt.write_reg && pkt.rd != 0) begin
            regFile.write(pkt.rd, wb_data);
        end

        wb_forward_data1 <= wb_forward_data0;
        wb_forward_rd1 <= wb_forward_rd0;
        wb_forward_valid1 <= wb_forward_valid0;

        wb_forward_data0 <= wb_data;
        wb_forward_rd0 <= pkt.rd;
        wb_forward_valid0 <= pkt.write_reg && pkt.rd != 0;

        wb_bypass_data <= wb_data;
        wb_bypass_rd <= pkt.rd;
        wb_bypass_valid <= pkt.write_reg && pkt.rd != 0;

        mem_if.csrModule().incrementMinstret;

        // 中断处理 - 详细调试（已禁用大部分）
        Bool has_irq = mem_if.csrModule().hasPendingInterrupt();
        if (has_irq) begin
            // $display("[WB_IRQ] hasPendingInterrupt=True, checking MIE...");
        end
        if (has_irq) begin
            MStatus ms = unpackMStatus(mem_if.csrModule().readCSR(12'h300));
            // $display("[WB_IRQ] mstatus=%x (MIE=%d, MPIE=%d)", packMStatus(ms), ms.mie, ms.mpie);
            if (ms.mie == 1'b1) begin
                Maybe#(Bit#(5)) cause_opt = mem_if.csrModule().getPendingInterruptCause();
                if (cause_opt matches tagged Valid .cause) begin
                    Addr return_addr = pkt.pc + 4;
                    $display("[WB_IRQ] Timer IRQ: pc=%x, return_addr=%x", pkt.pc, return_addr);
                    mem_if.csrModule().writeCSR(12'h341, pack(return_addr));
                    mem_if.csrModule().writeCSR(12'h342, {1'b1, 26'b0, cause});
                    mem_if.csrModule().writeCSR(12'h343, 0);

                    MStatus new_ms = ms;
                    new_ms.mpie = ms.mie;
                    new_ms.mpp = 2'b11;
                    new_ms.mie = 1'b0;
                    mem_if.csrModule().writeCSR(12'h300, packMStatus(new_ms));

                    Addr trap_vec = mem_if.csrModule().readCSR(12'h305) & ~32'h3;
                    // $display("[WB_IRQ] mtvec=%x, trap_vec=%x", mem_if.csrModule().readCSR(12'h305), trap_vec);

                    if2id.clear;
                    id2ex.clear;
                    ex2mem.clear;

                    redirect_pending <= True;
                    redirect_target <= trap_vec;
                    redirect_reason <= 5;
                    pcReg <= trap_vec;
                end
            end
        end
    endrule

    // Load包等待响应
    rule writebackStage_Load (mem2wb.notEmpty && mem2wb.first.is_load && mem_if.hasMemResp());
        MEM_WB_Packet pkt = mem2wb.first;
        mem2wb.deq;

        MemResp resp = mem_if.peekMemResp();
        Word raw_data = resp.rdata;  // SOC 返回的原始 word

        // 字节/半字提取（根据 width 和地址偏移）
        Word wb_data = raw_data;
        if (pkt.mem_width == MEM_BYTE) begin
            // LB/LBU: 根据 addr[1:0] 提取字节
            Bit#(2) byte_off = pkt.alu_result[1:0];
            Bit#(5) shift = {3'b0, byte_off} * 8;
            Bit#(8) byte_val = (raw_data >> shift)[7:0];
            wb_data = pkt.mem_unsigned ? {24'b0, byte_val} : signExtend(byte_val);
        end else if (pkt.mem_width == MEM_HALF) begin
            // LH/LHU: 根据 addr[1] 提取半字
            Bit#(1) half_off = pkt.alu_result[1];
            Bit#(5) shift = {4'b0, half_off} * 16;
            Bit#(16) half_val = (raw_data >> shift)[15:0];
            wb_data = pkt.mem_unsigned ? {16'b0, half_val} : signExtend(half_val);
        end

        waiting_for_load_resp <= False;
        mem_if.deqMemResp();
        ex_is_load_cached <= False;
        ex_rd_cached <= 0;

        wb_write_reg_cached <= pkt.write_reg;
        wb_is_load_cached <= pkt.is_load;
        wb_rd_cached <= pkt.rd;
        wb_alu_result_cached <= pkt.alu_result;
        wb_mem_data_cached <= wb_data;

        if (pkt.write_reg && pkt.rd != 0) begin
            regFile.write(pkt.rd, wb_data);
        end

        wb_forward_data1 <= wb_forward_data0;
        wb_forward_rd1 <= wb_forward_rd0;
        wb_forward_valid1 <= wb_forward_valid0;

        wb_forward_data0 <= wb_data;
        wb_forward_rd0 <= pkt.rd;
        wb_forward_valid0 <= pkt.write_reg && pkt.rd != 0;

        wb_bypass_data <= wb_data;
        wb_bypass_rd <= pkt.rd;
        wb_bypass_valid <= pkt.write_reg && pkt.rd != 0;

        mem_if.csrModule().incrementMinstret;

        // 中断处理 - 详细调试（已禁用大部分）
        Bool has_irq = mem_if.csrModule().hasPendingInterrupt();
        if (has_irq) begin
            // $display("[WB_IRQ] hasPendingInterrupt=True, checking MIE...");
        end
        if (has_irq) begin
            MStatus ms = unpackMStatus(mem_if.csrModule().readCSR(12'h300));
            // $display("[WB_IRQ] mstatus=%x (MIE=%d, MPIE=%d)", packMStatus(ms), ms.mie, ms.mpie);
            if (ms.mie == 1'b1) begin
                Maybe#(Bit#(5)) cause_opt = mem_if.csrModule().getPendingInterruptCause();
                if (cause_opt matches tagged Valid .cause) begin
                    Addr return_addr = pkt.pc + 4;
                    $display("[WB_IRQ] Timer IRQ: pc=%x, return_addr=%x", pkt.pc, return_addr);
                    mem_if.csrModule().writeCSR(12'h341, pack(return_addr));
                    mem_if.csrModule().writeCSR(12'h342, {1'b1, 26'b0, cause});
                    mem_if.csrModule().writeCSR(12'h343, 0);

                    MStatus new_ms = ms;
                    new_ms.mpie = ms.mie;
                    new_ms.mpp = 2'b11;
                    new_ms.mie = 1'b0;
                    mem_if.csrModule().writeCSR(12'h300, packMStatus(new_ms));

                    Addr trap_vec = mem_if.csrModule().readCSR(12'h305) & ~32'h3;
                    // $display("[WB_IRQ] mtvec=%x, trap_vec=%x", mem_if.csrModule().readCSR(12'h305), trap_vec);

                    if2id.clear;
                    id2ex.clear;
                    ex2mem.clear;

                    redirect_pending <= True;
                    redirect_target <= trap_vec;
                    redirect_reason <= 5;
                    pcReg <= trap_vec;
                end
            end
        end
    endrule

    // ============================================================
    // 接口
    // ============================================================

    method Addr pc = pcReg;
    method Word instruction = currentInstr;
    method Bool running = (state == RUNNING);

    method Action loadProgram(Vector#(4096, Word) prog);
        for (Integer i = 0; i < 4096; i = i + 1)
            imem[i] <= prog[i];
        if2id.clear;
        id2ex.clear;
        ex2mem.clear;
        mem2wb.clear;
        programLoaded <= True;
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

function Bool checkAlignment(Addr addr, MemWidth width);
    case (width)
        MEM_BYTE:  return True;
        MEM_HALF:  return addr[0] == 0;
        MEM_WORD:  return addr[1:0] == 0;
        default:   return True;
    endcase
endfunction

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
        trap_mode: 0,
        predicted_taken: False,
        predicted_target: 0
    };
endfunction

endpackage