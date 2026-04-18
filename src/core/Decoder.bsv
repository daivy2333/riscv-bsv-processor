// src/core/Decoder.bsv
package Decoder;

import Types::*;
import PrivilegedTypes::*;

// 解码结果
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
    Bool        use_imm;    // 是否使用立即数作为ALU第二个操作数
    Bool        use_rs1;    // 新增：是否使用 rs1
    Bool        use_rs2;    // 新增：是否使用 rs2
    MemWidth    mem_width;      // 内存访问宽度
    Bool        mem_unsigned;   // 是否无符号扩展
    // CSR 指令字段
    Bool        is_csr;         // 是否 CSR 指令
    Bool        is_csr_imm;     // 是否是立即数版本 (CSRRWI等)
    Bit#(12)    csr_addr;       // CSR 地址
    CSROp       csr_op;         // CSR 操作类型
    Bit#(5)     csr_zimm;      // 立即数版本的 zimm
} DecodedInstr deriving (Bits, Eq, FShow);

interface Decoder;
    method DecodedInstr decode(Word instruction);
endinterface

module mkDecoder(Decoder);
    method DecodedInstr decode(Word instruction);
        Bit#(7) opcode = getOpcode(instruction);
        Bit#(3) funct3 = getFunct3(instruction);
        Bit#(7) funct7 = getFunct7(instruction);
        Bit#(5) rs1_addr = getRs1(instruction);
        Bit#(5) rs2_addr = getRs2(instruction);
        Bit#(5) rd_addr = getRd(instruction);

        ALUOp alu_op = ALU_ADD;
        BranchCond branch_cond = BR_NONE;
        MemOp mem_op = MEM_NONE;
        Word imm = 0;
        Bool is_branch = False;
        Bool is_jump = False;
        Bool write_reg = False;
        Bool is_load = False;
        Bool use_imm = False;
        Bool use_rs1 = False;
        Bool use_rs2 = False;
        MemWidth mem_width = MEM_WORD;     // 新增：默认值
        Bool mem_unsigned = False;         // 新增：默认值
        // CSR 指令字段默认值
        Bool is_csr = False;
        Bool is_csr_imm = False;
        Bit#(12) csr_addr = 0;
        CSROp csr_op = CSR_OP_READ;
        Bit#(5) csr_zimm = 0;

        case (opcode)
            // R-Type
            7'b0110011: begin
                write_reg = True;
                use_imm = False;
                use_rs1 = True;
                use_rs2 = True;
                case (funct3)
                    3'b000: alu_op = (funct7 == 7'b0100000) ? ALU_SUB : ALU_ADD;
                    3'b001: alu_op = ALU_SLL;
                    3'b010: alu_op = ALU_SLT;
                    3'b011: alu_op = ALU_SLTU;
                    3'b100: alu_op = ALU_XOR;
                    3'b101: alu_op = (funct7 == 7'b0100000) ? ALU_SRA : ALU_SRL;
                    3'b110: alu_op = ALU_OR;
                    3'b111: alu_op = ALU_AND;
                endcase
            end

            // I-Type (立即数操作)
            7'b0010011: begin
                write_reg = True;
                use_imm = True;
                use_rs1 = True;
                use_rs2 = False;
                imm = signExtendI(instruction);
                case (funct3)
                    3'b000: alu_op = ALU_ADD;   // ADDI
                    3'b001: alu_op = ALU_SLL;
                    3'b010: alu_op = ALU_SLT;
                    3'b011: alu_op = ALU_SLTU;
                    3'b100: alu_op = ALU_XOR;
                    3'b101: alu_op = (funct7 == 7'b0100000) ? ALU_SRA : ALU_SRL;
                    3'b110: alu_op = ALU_OR;
                    3'b111: alu_op = ALU_AND;
                endcase
            end

            // Load
            7'b0000011: begin
                write_reg = True;
                is_load = True;
                mem_op = MEM_READ;
                use_imm = True;
                use_rs1 = True;
                use_rs2 = False;
                imm = signExtendI(instruction);
                alu_op = ALU_ADD;

                // 根据 funct3 区分不同宽度的 Load
                case (funct3)
                    3'b000: begin  // LB - 有符号字节
                        mem_width = MEM_BYTE;
                        mem_unsigned = False;
                    end
                    3'b001: begin  // LH - 有符号半字
                        mem_width = MEM_HALF;
                        mem_unsigned = False;
                    end
                    3'b010: begin  // LW - 字
                        mem_width = MEM_WORD;
                        mem_unsigned = False;
                    end
                    3'b100: begin  // LBU - 无符号字节
                        mem_width = MEM_BYTE;
                        mem_unsigned = True;
                    end
                    3'b101: begin  // LHU - 无符号半字
                        mem_width = MEM_HALF;
                        mem_unsigned = True;
                    end
                    default: begin  // 未定义 funct3
                        mem_width = MEM_WORD;
                        mem_unsigned = False;
                    end
                endcase
            end

            // Store
            7'b0100011: begin
                mem_op = MEM_WRITE;
                use_imm = True;
                use_rs1 = True;
                use_rs2 = True;
                imm = signExtendS(instruction);
                alu_op = ALU_ADD;

                // 根据 funct3 区分不同宽度的 Store
                case (funct3)
                    3'b000: mem_width = MEM_BYTE;   // SB
                    3'b001: mem_width = MEM_HALF;   // SH
                    3'b010: mem_width = MEM_WORD;   // SW
                    default: mem_width = MEM_WORD;  // 未定义 funct3
                endcase
                // mem_unsigned 对 Store 无意义，保持默认 False
            end

            // Branch
            7'b1100011: begin
                is_branch = True;
                use_imm = True;
                use_rs1 = True;
                use_rs2 = True;
                imm = signExtendB(instruction);
                case (funct3)
                    3'b000: branch_cond = BR_EQ;
                    3'b001: branch_cond = BR_NE;
                    3'b100: branch_cond = BR_LT;
                    3'b101: branch_cond = BR_GE;
                    3'b110: branch_cond = BR_LTU;
                    3'b111: branch_cond = BR_GEU;
                endcase
            end

            // LUI
            7'b0110111: begin
                write_reg = True;
                use_imm = True;
                use_rs1 = False;
                use_rs2 = False;
                imm = getUImm(instruction);
                alu_op = ALU_PASS;
            end

            // AUIPC
            7'b0010111: begin
                write_reg = True;
                use_imm = True;
                use_rs1 = False;
                use_rs2 = False;
                imm = getUImm(instruction);
                alu_op = ALU_PC;
            end

            // JAL
            7'b1101111: begin
                write_reg = True;
                is_jump = True;
                use_imm = True;
                use_rs1 = False;
                use_rs2 = False;
                imm = signExtendJ(instruction);
            end

            // JALR
            7'b1100111: begin
                write_reg = True;
                is_jump = True;
                use_imm = True;
                use_rs1 = True;
                use_rs2 = False;
                imm = signExtendI(instruction);
                alu_op = ALU_ADD;
            end

            // CSR 指令 (SYSTEM) - opcode = 7'b1110011
            7'b1110011: begin
                write_reg = True;
                use_rs1 = True;
                use_rs2 = False;
                use_imm = False;
                is_csr = True;
                is_csr_imm = False;
                csr_addr = instruction[31:20];
                csr_op = CSR_OP_READ;

                case (funct3)
                    3'b001: csr_op = CSR_OP_WRITE;              // CSRRW
                    3'b010: begin                               // CSRRS
                        csr_op = CSR_OP_WRITE;
                        is_csr_imm = True;
                        use_rs1 = False;
                    end
                    3'b011: begin                               // CSRRC
                        csr_op = (rs1_addr == 0) ? CSR_OP_READ : CSR_OP_SET;
                    end
                    3'b101: begin                              // CSRRWI
                        csr_op = (instruction[19:15] == 0) ? CSR_OP_READ : CSR_OP_SET;
                        is_csr_imm = True;
                        use_rs1 = False;
                    end
                    3'b110: begin                               // CSRRSI
                        csr_op = (rs1_addr == 0) ? CSR_OP_READ : CSR_OP_CLR;
                    end
                    3'b111: begin                               // CSRRCI
                        csr_op = (instruction[19:15] == 0) ? CSR_OP_READ : CSR_OP_CLR;
                        is_csr_imm = True;
                        use_rs1 = False;
                    end
                    default: begin
                        // ECALL/EBREAK/MRET/SFENCE.VMA 等在 Core 处理
                    end
                endcase

                if (is_csr_imm)
                    csr_zimm = instruction[19:15];  // zimm = rs1 字段
            end

            default: begin
                // 未实现指令
            end
        endcase

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
            use_rs1: use_rs1,
            use_rs2: use_rs2,
            mem_width: mem_width,
            mem_unsigned: mem_unsigned,
            is_csr: is_csr,
            is_csr_imm: is_csr_imm,
            csr_addr: csr_addr,
            csr_op: csr_op,
            csr_zimm: csr_zimm
        };
    endmethod
endmodule

endpackage