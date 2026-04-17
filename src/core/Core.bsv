// src/core/Core.bsv - 完整版（带分支预测、数据前递和Load-Use停顿）
package Core;

import Types::*;
import ALU::*;
import RegFile::*;
import Decoder::*;
import BHT::*;
import BTB::*;
import HazardUnit::*;
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

    // 流水线寄存器（使用 FIFOF 深度2）
    FIFOF#(IF_ID_Packet) if2id <- mkFIFOF;
    FIFOF#(ID_EX_Packet) id2ex <- mkFIFOF;
    FIFOF#(EX_MEM_Packet) ex2mem <- mkFIFOF;
    FIFOF#(MEM_WB_Packet) mem2wb <- mkFIFOF;

    // Load-Use停顿控制
    Reg#(Bool) stall_load_use <- mkReg(False);    // Load-Use 停顿标志
    Reg#(Bit#(2)) stall_count <- mkReg(0);        // 停顿剩余周期数

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

    // 内存（保持原配置避免编译问题）
    Vector#(1024, Reg#(Word)) imem <- replicateM(mkReg(0));   // 4KB, 2^10 entries
    Vector#(512, Reg#(Word)) dmem <- replicateM(mkReg(0));    // 2KB, 2^9 entries

    // tohost 检测（riscv-tests 完成信号）
    Reg#(Bool) test_done <- mkReg(False);
    Reg#(Word) tohost_value <- mkReg(0);
    Addr tohost_addr = 32'h80001000;  // riscv-tests 标准地址

    // ============================================================
    // IF阶段
    // ============================================================

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

        Bit#(10) idx = fetchPC[11:2];  // 10 位索引
        Word instr = imem[idx];

        if2id.enq(IF_ID_Packet {
            pc: fetchPC,
            instruction: instr,
            predicted_pc: prediction_target,
            predicted_taken: take_prediction
        });

        currentInstr <= instr;
        // 如果预测跳转，PC 更新为预测目标；否则顺序执行
        if (take_prediction)
            pcReg <= prediction_target;
        else
            pcReg <= pcReg + 4;
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
                mem_unsigned: dec.mem_unsigned
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

    rule executeStage;
        ID_EX_Packet pkt = id2ex.first;

        // 前递逻辑
        Word op1 = pkt.rs1_val;
        Word op2 = pkt.rs2_val;

        // EX→EX前递
        if (ex_forward_valid && ex_forward_rd == pkt.rs1 && pkt.rs1 != 0)
            op1 = ex_forward;
        if (ex_forward_valid && ex_forward_rd == pkt.rs2 && pkt.rs2 != 0)
            op2 = ex_forward;

        // MEM→EX 前递（注意：MEM 阶段的 Load 数据还未可用，不前递 Load 的 mem_data）
        if (mem_forward_valid && mem_forward_rd == pkt.rs1 && pkt.rs1 != 0 && !ex2mem.first.is_load)
            op1 = mem_forward;
        if (mem_forward_valid && mem_forward_rd == pkt.rs2 && pkt.rs2 != 0 && !ex2mem.first.is_load)
            op2 = mem_forward;

        // WB→EX前递
        // 注意：wb_forward 在 WB 阶段结束时更新，下一周期可用
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

        // 跳转/分支实际执行：更新 PC 并冲刷流水线
        if (branch_taken) begin
            pcReg <= actual_target;
            // 冲刷 IF 和 ID 阶段（清空 FIFO）
            if2id.clear;
            id2ex.clear;
        end else begin
            // 正常执行：取出指令
            id2ex.deq;
        end

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
            is_load: is_load,
            mem_width: pkt.mem_width,
            mem_unsigned: pkt.mem_unsigned
        });

        // 前递设置
        ex_forward <= alu_result;
        ex_forward_rd <= pkt.rd;
        ex_forward_valid <= pkt.write_reg;
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

        // MEM 前递设置（Load 不在 MEM 前递，数据需要等 WB 阶段）
        mem_forward <= pkt.alu_result;
        mem_forward_rd <= pkt.rd;
        mem_forward_valid <= pkt.write_reg && !pkt.is_load;
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
        mem_unsigned: False
    };
endfunction

endpackage
