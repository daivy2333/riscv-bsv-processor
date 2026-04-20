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
    // 新增：内存请求接口（请求/响应式）
    method MemReq memReq();
    method Action memReqAck();  // SOC 确认请求已处理
    method Action memResp(MemResp resp);
    // 新增：CSR 模块接口（用于 SOC 连接中断信号）
    method CSRs csrModule();
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

    // EX阶段信息缓存（用于ID阶段冒险检测，避免空FIFO访问）
    Reg#(Bool) ex_is_load_cached <- mkReg(False);
    Reg#(Bit#(5)) ex_rd_cached <- mkReg(0);

    // MEM阶段信息缓存（用于EX阶段前递，避免空FIFO访问）
    Reg#(Bool) mem_write_reg_cached <- mkReg(False);
    Reg#(Bool) mem_is_load_cached <- mkReg(False);
    Reg#(Bit#(5)) mem_rd_cached <- mkReg(0);
    Reg#(Word) mem_alu_result_cached <- mkReg(0);

    // WB阶段信息缓存（用于EX阶段前递，避免空FIFO访问）
    Reg#(Bool) wb_write_reg_cached <- mkReg(False);
    Reg#(Bool) wb_is_load_cached <- mkReg(False);
    Reg#(Bit#(5)) wb_rd_cached <- mkReg(0);
    Reg#(Word) wb_alu_result_cached <- mkReg(0);
    Reg#(Word) wb_mem_data_cached <- mkReg(0);

    // 控制流重定向协议（统一处理分支/JAL/trap/MRET/中断）
    Reg#(Bool) redirect_pending <- mkReg(False);   // 重定向请求挂起
    Reg#(Addr) redirect_target <- mkReg(0);        // 重定向目标地址
    Reg#(Bit#(4)) redirect_reason <- mkReg(0);     // 重定向原因（用于 trace）
    // redirect_reason: 0=NONE, 1=BRANCH, 2=JAL, 3=TRAP, 4=MRET, 5=INTERRUPT

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

    // 当前周期 WB->EX bypass（同周期直通，解决 WB 与 EX 同周期相遇时的前递）
    Wire#(Word) wb_bypass_data <- mkDWire(0);
    Wire#(Bit#(5)) wb_bypass_rd <- mkDWire(0);
    Wire#(Bool) wb_bypass_valid <- mkDWire(False);

    // 内存（保持原配置避免编译问题）
    Vector#(1024, Reg#(Word)) imem <- replicateM(mkReg(0));   // 4KB, 2^10 entries
    // dmem 移至外部模块 DMem.bsv

    // 内存请求/响应寄存器
    Reg#(MemReq) current_mem_req <- mkReg(nopMemReq());
    Reg#(MemResp) pending_mem_resp <- mkReg(MemResp {valid: False, rdata: 0});
    Reg#(Bool) mem_resp_pending <- mkReg(False);

    // Load 阻塞状态：等待 SOC 响应期间冻结流水线
    Reg#(Bool) waiting_for_load_resp <- mkReg(False);

    // tohost 检测（移至外部模块 DMem.bsv）
    Reg#(Bool) test_done <- mkReg(False);
    Reg#(Word) tohost_value <- mkReg(0);

    // 陷阱控制
    Reg#(Bool) in_trap <- mkReg(False);
    Reg#(Bool) wfi_waiting <- mkReg(False);

    // ============================================================
    // IF阶段
    // ============================================================

    // execution_order: consumeRedirect 先执行，然后 fetchStage
    (* execution_order = "consumeRedirect, fetchStage" *)
    rule fetchStage (programLoaded && state == RUNNING && !stall_load_use && !redirect_pending && !waiting_for_load_resp);
        Addr fetchPC = pcReg;
        Bool take_prediction = False;
        Addr prediction_target = 0;

        Bit#(10) idx = fetchPC[11:2];  // 10 位索引
        Word instr = imem[idx];

        // 分支预测
        Maybe#(Addr) btb_hit = btb.lookup(fetchPC);
        Bool bht_predict = bht.predict(fetchPC);

        // 检查指令类型
        Bit#(7) opcode = instr[6:0];
        Bool is_jal = (opcode == 7'b1101111);  // JAL
        Bool is_jalr = (opcode == 7'b1100111); // JALR

        if (btb_hit matches tagged Valid .target) begin
            // BTB 有记录
            if (is_jal || is_jalr) begin
                // JAL/JALR: 无条件跳转，只要 BTB 有记录就预测跳转
                take_prediction = True;
                prediction_target = target;
            end else if (bht_predict) begin
                // 条件分支: 需要 BHT 也预测跳转
                take_prediction = True;
                prediction_target = target;
            end
        end

        // Trace: FETCH_PC
        Addr next_pc = take_prediction ? prediction_target : fetchPC + 4;
        $display("FETCH_PC: old=%h new=%h predicted=%d", fetchPC, next_pc, take_prediction);

        if2id.enq(IF_ID_Packet {
            pc: fetchPC,
            instruction: instr,
            predicted_pc: prediction_target,
            predicted_taken: take_prediction,
            priv_mode: pack(csrs.currentMode())
        });

        currentInstr <= instr;
        // PC 更新：如果预测跳转，下一周期从预测目标取指；否则顺序执行
        if (take_prediction)
            pcReg <= prediction_target;
        else
            pcReg <= pcReg + 4;
    endrule

    // 控制流重定向消费（fetchStage 消费 redirect 后清除）
    rule consumeRedirect (redirect_pending);
        // Fetch 已经使用了 redirect_target，清除挂起状态
        redirect_pending <= False;
        // Trace: 重定向已消费
        $display("REDIRECT_CONSUMED: target=%h reason=%d", redirect_target, redirect_reason);
    endrule

    // ============================================================
    // ID阶段
    // ============================================================

    rule decodeStage (!stall_load_use && !waiting_for_load_resp && if2id.notEmpty);
        IF_ID_Packet pkt = if2id.first;
        DecodedInstr dec = decoder.decode(pkt.instruction);

        // 检测 Load-Use 冒险（使用缓存的 EX 阶段信息，避免空 FIFO 访问）
        Bool load_use_hazard = False;

        if (ex_is_load_cached && ex_rd_cached != 0) begin
            Bit#(5) ex_rd = ex_rd_cached;
            if (dec.use_rs1 && dec.rs1 == ex_rd)
                load_use_hazard = True;
            if (dec.use_rs2 && dec.rs2 == ex_rd)
                load_use_hazard = True;
        end

        if (load_use_hazard) begin
            // 停顿 ID 阶段，不发送包到 EX
            stall_load_use <= True;
            stall_count <= 3;  // Load 需要 3 周期：EX→MEM→SOC响应→WB
            // 立即插入气泡到 id2ex（当前周期）
            id2ex.enq(nopPacket());
            // 更新 EX 缓存（气泡不是 load）
            ex_is_load_cached <= False;
            ex_rd_cached <= 0;
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
                trap_mode: trap_mode,
                predicted_taken: pkt.predicted_taken,
                predicted_target: pkt.predicted_pc
            });
            // 更新 EX 缓存（用于下个周期的冒险检测）
            ex_is_load_cached <= (dec.mem_op == MEM_READ);
            ex_rd_cached <= dec.rd;
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
        // 更新 EX 缓存（气泡不是 load）
        ex_is_load_cached <= False;
        ex_rd_cached <= 0;
    endrule

    // ============================================================
    // EX阶段
    // ============================================================

    (* execution_order = "writebackStage, executeStage" *)
    (* preempts = "executeStage, fetchStage" *)
    rule executeStage (id2ex.notEmpty && ex2mem.notFull && !waiting_for_load_resp);
        ID_EX_Packet pkt = id2ex.first;

        // 前递逻辑 - 使用缓存避免空FIFO访问
        Word op1 = pkt.rs1_val;
        Word op2 = pkt.rs2_val;

        // MEM→EX 前递（最高优先级，使用缓存）
        if (mem_write_reg_cached && !mem_is_load_cached && mem_rd_cached == pkt.rs1 && pkt.rs1 != 0)
            op1 = mem_alu_result_cached;
        // 当前周期 WB bypass（同周期直通，优先于 wb_write_reg_cached）
        else if (wb_bypass_valid && wb_bypass_rd == pkt.rs1 && pkt.rs1 != 0)
            op1 = wb_bypass_data;
        // 上一周期 WB cache
        else if (wb_write_reg_cached && wb_rd_cached == pkt.rs1 && pkt.rs1 != 0)
            op1 = wb_is_load_cached ? wb_mem_data_cached : wb_alu_result_cached;
        // 更早周期 WB 前递
        else if (wb_forward_valid0 && wb_forward_rd0 == pkt.rs1 && pkt.rs1 != 0)
            op1 = wb_forward_data0;
        else if (wb_forward_valid1 && wb_forward_rd1 == pkt.rs1 && pkt.rs1 != 0)
            op1 = wb_forward_data1;

        // rs2 前递（同样优先级）
        if (mem_write_reg_cached && !mem_is_load_cached && mem_rd_cached == pkt.rs2 && pkt.rs2 != 0)
            op2 = mem_alu_result_cached;
        // 当前周期 WB bypass
        else if (wb_bypass_valid && wb_bypass_rd == pkt.rs2 && pkt.rs2 != 0)
            op2 = wb_bypass_data;
        // 上一周期 WB cache
        else if (wb_write_reg_cached && wb_rd_cached == pkt.rs2 && pkt.rs2 != 0)
            op2 = wb_is_load_cached ? wb_mem_data_cached : wb_alu_result_cached;
        // 更早周期 WB 前递
        else if (wb_forward_valid0 && wb_forward_rd0 == pkt.rs2 && pkt.rs2 != 0)
            op2 = wb_forward_data0;
        else if (wb_forward_valid1 && wb_forward_rd1 == pkt.rs2 && pkt.rs2 != 0)
            op2 = wb_forward_data1;

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
        // BHT 更新：条件分支按实际结果，无条件跳转（JAL）设为跳转
        if (pkt.is_branch)
            bht.update(pkt.pc, branch_taken);
        else if (pkt.is_jump)
            bht.update(pkt.pc, True);  // JAL/JALR 总是跳转

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
            // 统一重定向协议
            redirect_pending <= True;
            redirect_target <= trap_base;
            redirect_reason <= 3;  // TRAP
            pcReg <= trap_base;
            $display("REDIRECT_REQ: pc=%h target=%h reason=TRAP", pkt.pc, trap_base);
            $display("PIPE_FLUSH: if2id id2ex");
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

                Addr mepc = csrs.readCSR(12'h341);
                // 统一重定向协议
                redirect_pending <= True;
                redirect_target <= mepc;
                redirect_reason <= 4;  // MRET
                pcReg <= mepc;
                $display("REDIRECT_REQ: pc=%h target=%h reason=MRET", pkt.pc, mepc);
                $display("PIPE_FLUSH: if2id id2ex");
                if2id.clear;
                id2ex.clear;
            end else begin
                // 正常分支/跳转执行
                Bool mispredicted = pkt.is_branch && (pkt.predicted_taken != branch_taken);

                if (branch_taken) begin
                    // Branch/jump taken - go to target
                    // 统一重定向协议
                    Bit#(4) reason = pkt.is_jump ? 2 : 1;  // JAL vs BRANCH
                    redirect_pending <= True;
                    redirect_target <= actual_target;
                    redirect_reason <= reason;
                    pcReg <= actual_target;
                    $display("REDIRECT_REQ: pc=%h target=%h reason=%s", pkt.pc, actual_target, pkt.is_jump ? "JAL" : "BRANCH");
                    $display("PIPE_FLUSH: if2id id2ex");
                    if2id.clear;
                    id2ex.clear;
                end else if (mispredicted) begin
                    // Prediction said taken but branch is not taken - redirect to sequential
                    // 统一重定向协议
                    redirect_pending <= True;
                    redirect_target <= pkt.pc + 4;
                    redirect_reason <= 1;  // BRANCH mispredict
                    pcReg <= pkt.pc + 4;
                    $display("REDIRECT_REQ: pc=%h target=%h reason=BRANCH_MISPREDICT", pkt.pc, pkt.pc + 4);
                    $display("PIPE_FLUSH: if2id id2ex");
                    if2id.clear;
                    id2ex.clear;
                end else begin
                    // Normal execution, no misprediction
                    id2ex.deq;
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
                    predicted_taken: pkt.predicted_taken,
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

    (* execution_order = "writebackStage, memoryStage" *)
    rule memoryStage (ex2mem.notEmpty && !waiting_for_load_resp);
        EX_MEM_Packet pkt = ex2mem.first;
        ex2mem.deq;

        // 更新 MEM 缓存（供下一周期 executeStage 前递使用）
        mem_write_reg_cached <= pkt.write_reg;
        mem_is_load_cached <= pkt.is_load;
        mem_rd_cached <= pkt.rd;
        mem_alu_result_cached <= pkt.alu_result;

        // 对齐检查（阶段1仅打印警告）
        if (pkt.mem_op != MEM_NONE && !checkAlignment(pkt.alu_result, pkt.mem_width)) begin
            $display("WARNING: Misaligned access at PC=%h, addr=%h, width=%s",
                     pkt.pc, pkt.alu_result, pkt.mem_width);
        end

        // 生成内存请求发送给 SOC
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

            // === 提交级 trace ===
            $display("MEM_REQ: pc=%h addr=%h op=%s wdata=%h",
                     pkt.pc, pkt.alu_result, pkt.mem_op, pkt.rs2_val);

            // Store 指令特别标记（最终提交点）
            if (pkt.mem_op == MEM_WRITE) begin
                $display("STORE_COMMIT: pc=%h addr=%h wdata=%h",
                         pkt.pc, pkt.alu_result, pkt.rs2_val);
            end
        end
        current_mem_req <= req;

        // 如果是 Load，设置阻塞状态等待响应
        if (pkt.is_load) begin
            waiting_for_load_resp <= True;
            mem_resp_pending <= True;
        end

        // 内存写入由 SOC 处理，tohost 检测移至 DMem 模块

        mem2wb.enq(MEM_WB_Packet {
            pc: pkt.pc,
            mem_data: 0,  // 等待响应填充
            alu_result: pkt.alu_result,
            rd: pkt.rd,
            write_reg: pkt.write_reg,
            is_load: pkt.is_load
        });
    endrule

    // ============================================================
    // WB阶段
    // ============================================================

    rule writebackStage (mem2wb.notEmpty);
        MEM_WB_Packet pkt = mem2wb.first;

        // Load 指令需要等待响应到达
        // 只有当 pending_mem_resp.valid == True 时才允许提交
        Bool can_commit = !pkt.is_load || pending_mem_resp.valid;

        if (can_commit) begin
            // 确认响应已到达（或非 load 指令），执行写回
            mem2wb.deq;

            Word wb_data = pkt.alu_result;

            // 如果是 Load，使用响应数据并清除阻塞状态
            if (pkt.is_load && pending_mem_resp.valid) begin
                wb_data = pending_mem_resp.rdata;
                mem_resp_pending <= False;
                waiting_for_load_resp <= False;  // 解除流水线阻塞
                // 清除响应（已消费）
                pending_mem_resp <= MemResp {valid: False, rdata: 0};
                // 清除 EX 缓存，防止后续指令误判 Load-Use 冒险
                ex_is_load_cached <= False;
                ex_rd_cached <= 0;
            end

            // 如果不是 load 但有遗留的 pending 状态，也要清除
            //（这种情况发生在 load-use stall 之后的指令）
            if (!pkt.is_load && mem_resp_pending) begin
                mem_resp_pending <= False;
                pending_mem_resp <= MemResp {valid: False, rdata: 0};
            end

            // 更新 WB 缓存（供下一周期 executeStage 前递使用）
            wb_write_reg_cached <= pkt.write_reg;
            wb_is_load_cached <= pkt.is_load;
            wb_rd_cached <= pkt.rd;
            wb_alu_result_cached <= pkt.alu_result;
            wb_mem_data_cached <= wb_data;  // 使用实际数据（可能是 load 结果）

            if (pkt.write_reg && pkt.rd != 0) begin
                regFile.write(pkt.rd, wb_data);
            end

            // === 提交级 trace ===
            $display("WB_COMMIT: pc=%h rd=%d data=%h write=%d is_load=%d",
                     pkt.pc, pkt.rd, wb_data, pkt.write_reg, pkt.is_load);

            // WB 前递设置（Load 数据在此阶段可用）
            // 双缓冲更新：wb_forward_data1 ← wb_forward_data0 ← wb_data
            wb_forward_data1 <= wb_forward_data0;
            wb_forward_rd1 <= wb_forward_rd0;
            wb_forward_valid1 <= wb_forward_valid0;

            wb_forward_data0 <= wb_data;
            wb_forward_rd0 <= pkt.rd;
            wb_forward_valid0 <= pkt.write_reg && pkt.rd != 0;  // 只有写入非零寄存器才标记为有效

            // 当前周期 WB bypass（同周期直通给 executeStage 使用）
            wb_bypass_data <= wb_data;
            wb_bypass_rd <= pkt.rd;
            wb_bypass_valid <= pkt.write_reg && pkt.rd != 0;

            // CSR 指令在 EX 阶段已处理，这里只更新计数器
            csrs.incrementMinstret;

            // 提交边界检查中断（并入 writebackStage 尾部）
            if (csrs.hasPendingInterrupt()) begin
                MStatus ms = unpackMStatus(csrs.readCSR(12'h300));
                if (ms.mie == 1'b1) begin
                    // 保存 trap 信息
                    Maybe#(Bit#(5)) cause_opt = csrs.getPendingInterruptCause();
                    if (cause_opt matches tagged Valid .cause) begin
                        csrs.writeCSR(12'h341, pack(pkt.pc));  // mepc
                        csrs.writeCSR(12'h342, {1'b1, 26'b0, cause});  // mcause (最高位=1表示中断)
                        csrs.writeCSR(12'h343, 0);  // mtval

                        MStatus new_ms = ms;
                        new_ms.mpie = ms.mie;
                        new_ms.mpp = 2'b11;  // M-mode
                        new_ms.mie = 1'b0;
                        csrs.writeCSR(12'h300, packMStatus(new_ms));

                        // flush 流水线
                        if2id.clear;
                        id2ex.clear;
                        ex2mem.clear;

                        // 跳转到 mtvec（统一重定向协议）
                        Addr trap_vec = csrs.readCSR(12'h305) & ~32'h3;
                        redirect_pending <= True;
                        redirect_target <= trap_vec;
                        redirect_reason <= 5;  // INTERRUPT
                        pcReg <= trap_vec;
                        $display("REDIRECT_REQ: target=%h reason=INTERRUPT", trap_vec);
                        $display("PIPE_FLUSH: if2id id2ex ex2mem");
                    end
                end
            end
        end
        // 如果 !can_commit（load 且响应无效），保持 mem2wb 不出队，等待下一周期
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
        // 清除所有 FIFO，确保流水线从空状态开始
        if2id.clear;
        id2ex.clear;
        ex2mem.clear;
        mem2wb.clear;
        programLoaded <= True;
    endmethod

    method Word readReg(Bit#(5) addr);
        return regFile.readReg(addr);
    endmethod

    method MemReq memReq();
        return current_mem_req;
    endmethod

    method Action memReqAck();
        // SOC 确认请求已处理，清除请求
        current_mem_req <= nopMemReq();
    endmethod

    method Action memResp(MemResp resp);
        pending_mem_resp <= resp;
        // === 提交级 trace ===
        if (resp.valid) begin
            $display("MEM_RESP: data=%h valid=1", resp.rdata);
        end
    endmethod

    method CSRs csrModule();
        return csrs;
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
        trap_mode: 0,
        predicted_taken: False,
        predicted_target: 0
    };
endfunction

endpackage
