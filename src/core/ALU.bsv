// src/core/ALU.bsv
package ALU;

import Types::*;

interface ALU;
    method Word execute(ALUOp alu_op, Word operand1, Word operand2);
endinterface

module mkALU(ALU);
    method Word execute(ALUOp alu_op, Word operand1, Word operand2);
        Word result = 0;
        case (alu_op)
            ALU_ADD: result = operand1 + operand2;
            ALU_SUB: result = operand1 - operand2;
            ALU_SLL: result = operand1 << operand2[4:0];
            ALU_SLT: result = signedLT(operand1, operand2) ? 1 : 0;
            ALU_SLTU: result = (operand1 < operand2) ? 1 : 0;
            ALU_XOR: result = operand1 ^ operand2;
            ALU_SRL: result = operand1 >> operand2[4:0];
            ALU_SRA: result = signedShiftRight(operand1, operand2[4:0]);
            ALU_OR: result = operand1 | operand2;
            ALU_AND: result = operand1 & operand2;
            ALU_PASS: result = operand1;  // 直接传递（LUI）
            ALU_PC: result = operand1 + operand2;  // PC + imm（AUIPC）
            default: result = 0;
        endcase
        return result;
    endmethod
endmodule

// ============================================================
// 辅助函数
// ============================================================

function Bool signedLT(Word a, Word b);
    Int#(32) sa = unpack(a);
    Int#(32) sb = unpack(b);
    return (sa < sb);
endfunction

function Word signedShiftRight(Word a, Bit#(5) shamt);
    Int#(32) sa = unpack(a);
    Int#(32) shifted = sa >> shamt;
    return pack(shifted);
endfunction

endpackage