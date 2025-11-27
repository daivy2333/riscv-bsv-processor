// src/core/ALU.bsv
package ALU;
import Types::*;

interface ALU;
    method Word execute(Bit#(4) alu_op, Word operand1, Word operand2);
endinterface

module mkALU(ALU);
    method Word execute(Bit#(4) alu_op, Word operand1, Word operand2);
        Word result = 0;
        case (alu_op)
            4'b0000: result = operand1 + operand2;      // ADD
            4'b1000: result = operand1 - operand2;      // SUB
            4'b0001: result = operand1 << operand2[4:0]; // SLL
            4'b0010: result = signedLT(operand1, operand2) ? 1 : 0; // SLT
            4'b0011: result = (operand1 < operand2) ? 1 : 0; // SLTU
            4'b0100: result = operand1 ^ operand2;      // XOR
            4'b0101: result = operand1 >> operand2[4:0]; // SRL
            4'b1101: result = signedShiftRight(operand1, operand2[4:0]); // SRA
            4'b0110: result = operand1 | operand2;      // OR
            4'b0111: result = operand1 & operand2;      // AND
            default: result = 0;
        endcase
        return result;
    endmethod
endmodule
endpackage