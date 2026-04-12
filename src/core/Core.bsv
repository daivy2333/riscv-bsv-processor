// src/core/Core.bsv - 完整版（带分支预测、数据前递和Load-Use停顿）
package Core;

import Types::*;
import ALU::*;
import RegFile::*;
import Decoder::*;
import BHT::*;
import BTB::*;
import FIFO::*;
import Vector::*;

interface Core;
    method Addr pc;
    method Word instruction;
    method Bool running;
    method Action loadProgram(Vector#(1024, Word) prog);
    method Word readReg(Bit#(5) addr);
endinterface

module mkCore#(String firmwareFile)(Core);
    Decoder decoder <- mkDecoder;
    ALU alu <- mkALU;
    RegFile regFile <- mkRegFile;
    BHT bht <- mkBHT;
    BTB btb <- mkBTB;

    // 流水线寄存器
    FIFO#(IF_ID_Packet) if2id <- mkFIFO;
    FIFO#(ID_EX_Packet) id2ex <- mkFIFO;
    FIFO#(EX_MEM_Packet) ex2mem <- mkFIFO;
    FIFO#(MEM_WB_Packet) mem2wb <- mkFIFO;

    // Load-Use停顿控制
    Reg#(Bool) stall <- mkReg(False);
    Reg#(Bool) needBubble <- mkReg(False);

    // PC和状态
    Reg#(Addr) pcReg <- mkReg(32'h80000000);
    Reg#(Word) currentInstr <- mkReg(0);
    Reg#(ProcessorState) state <- mkReg(RUNNING);
    Reg#(Bool) programLoaded <- mkReg(False);

    // 前递数据
    Reg#(Word) ex_forward <- mkReg(0);
    Reg#(Bit#(5)) ex_forward_rd <- mkReg(0);
    Reg#(Bool) ex_forward_valid <- mkReg(False);

    Reg#(Word) mem_forward <- mkReg(0);
    Reg#(Bit#(5)) mem_forward_rd <- mkReg(0);
    Reg#(Bool) mem_forward_valid <- mkReg(False);

    Reg#(Word) wb_forward <- mkReg(0);
    Reg#(Bit#(5)) wb_forward_rd <- mkReg(0);
    Reg#(Bool) wb_forward_valid <- mkReg(False);

    // 内存
    Vector#(1024, Reg#(Word)) imem <- replicateM(mkReg(0));
    Vector#(512, Reg#(Word)) dmem <- replicateM(mkReg(0));

    // ============================================================
    // IF阶段
    // ============================================================

    rule fetchStage (programLoaded && state == RUNNING && !stall);
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

    // ============================================================
    // ID阶段
    // ============================================================

    rule decodeStage (!stall && !needBubble);
        IF_ID_Packet pkt = if2id.first;
        if2id.deq;

        DecodedInstr dec = decoder.decode(pkt.instruction);

        Word rs1 = regFile.read1(dec.rs1);
        Word rs2 = regFile.read2(dec.rs2);

        id2ex.enq(ID_EX_Packet {
            pc: pkt.pc,
            instruction: pkt.instruction,
            rs1_val: rs1, rs2_val: rs2,
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
    endrule

    // 插入bubble到id2ex
    rule insertBubble (needBubble && !stall);
        id2ex.deq;  // 清空当前包
        // 插入NOP
        id2ex.enq(ID_EX_Packet {
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
        });
        needBubble <= False;
    endrule

    // ============================================================
    // EX阶段 + Load-Use检测
    // ============================================================

    rule executeStage (!stall);
        ID_EX_Packet pkt = id2ex.first;
        id2ex.deq;

        // 前递逻辑
        Word op1 = pkt.rs1_val;
        Word op2 = pkt.rs2_val;

        // EX→EX前递
        if (ex_forward_valid && ex_forward_rd == pkt.rs1 && pkt.rs1 != 0)
            op1 = ex_forward;
        if (ex_forward_valid && ex_forward_rd == pkt.rs2 && pkt.rs2 != 0)
            op2 = ex_forward;

        // MEM→EX前递
        if (mem_forward_valid && mem_forward_rd == pkt.rs1 && pkt.rs1 != 0)
            op1 = mem_forward;
        if (mem_forward_valid && mem_forward_rd == pkt.rs2 && pkt.rs2 != 0)
            op2 = mem_forward;

        // WB→EX前递
        if (wb_forward_valid && wb_forward_rd == pkt.rs1 && pkt.rs1 != 0)
            op1 = wb_forward;
        if (wb_forward_valid && wb_forward_rd == pkt.rs2 && pkt.rs2 != 0)
            op2 = wb_forward;

        // ALU输入选择
        Word alu_in1, alu_in2;
        case (pkt.alu_op)
            ALU_PASS: begin alu_in1 = pkt.imm; alu_in2 = 0; end
            ALU_PC:   begin alu_in1 = pkt.pc; alu_in2 = pkt.imm; end
            ALU_ADD:  begin alu_in1 = op1; alu_in2 = pkt.use_imm ? pkt.imm : op2; end
            ALU_SUB:  begin alu_in1 = op1; alu_in2 = op2; end
            default:  begin
                alu_in1 = op1;
                alu_in2 = op2;
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

    // ============================================================
    // MEM阶段 + Load-Use检测
    // ============================================================

    rule memoryStage;
        EX_MEM_Packet pkt = ex2mem.first;
        ex2mem.deq;

        Word mem_data = 0;

        if (pkt.mem_op == MEM_READ) begin
            mem_data = dmem[pkt.alu_result[10:2]];
        end else if (pkt.mem_op == MEM_WRITE) begin
            dmem[pkt.alu_result[10:2]] <= pkt.rs2_val;
        end

        // Load-Use冒险检测：Load结果在MEM阶段可用
        // 如果下一条指令在ID阶段且需要这个Load的结果，需要停顿
        if (pkt.is_load && pkt.rd != 0) begin
            if (id2ex.first.rs1 == pkt.rd || id2ex.first.rs2 == pkt.rd) begin
                stall <= True;
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

        mem_forward <= pkt.alu_result;
        mem_forward_rd <= pkt.rd;
        mem_forward_valid <= pkt.write_reg;
    endrule

    // 清除stall
    rule clearStall (stall);
        stall <= False;
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

        wb_forward <= wb_data;
        wb_forward_rd <= pkt.rd;
        wb_forward_valid <= pkt.write_reg;
    endrule

    // ============================================================
    // 接口
    // ============================================================

    method Addr pc = pcReg;
    method Word instruction = currentInstr;
    method Bool running = (state == RUNNING);

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

endpackage
