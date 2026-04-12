// src/soc/TestBenchSimple.bsv
// 简化版测试：无流水线、无分支预测
package TestBenchSimple;

import Types::*;
import Decoder::*;
import ALU::*;
import RegFile::*;
import Vector::*;

module mkTestBenchSimple(Empty);
    Reg#(Addr) pcReg <- mkReg(32'h80000000);
    Reg#(Word) instrReg <- mkReg(0);
    Decoder decoder <- mkDecoder;
    ALU alu <- mkALU;
    RegFile regFile <- mkRegFile;

    // 简化的指令内存
    Vector#(256, Reg#(Word)) imem <- replicateM(mkReg(0));

    // 程序加载
    Reg#(Bool) loaded <- mkReg(False);

    rule load (!loaded);
        imem[0] <= 32'h00a00093;  // li x1, 10
        imem[1] <= 32'h01400113;  // li x2, 20
        imem[2] <= 32'h002081b3;  // add x3, x1, x2
        imem[3] <= 32'h00118233;  // add x4, x3, x1
        imem[4] <= 32'h003202b3;  // add x5, x4, x3
        imem[5] <= 32'h0000006f;  // j end
        loaded <= True;
        $display("Program loaded");
    endrule

    rule step (loaded);
        Bit#(8) index = pcReg[9:2];
        Word instr = imem[index];
        instrReg <= instr;

        DecodedInstr dec = decoder.decode(instr);

        Word rs1 = regFile.read1(dec.rs1);
        Word rs2 = regFile.read2(dec.rs2);

        Word op1 = (dec.alu_op == ALU_PASS) ? dec.imm : rs1;
        Word op2 = (dec.mem_op != MEM_NONE || dec.is_branch) ? dec.imm : rs2;
        Word result = alu.execute(dec.alu_op, op1, op2);

        if (dec.write_reg && dec.rd != 0) begin
            regFile.write(dec.rd, result);
        end

        pcReg <= pcReg + 4;

        $display("PC=%h Instr=%h Rs1=%h Rs2=%h Result=%h RegW=%d",
                 pcReg, instr, rs1, rs2, result, dec.rd);
    endrule

    Reg#(Bit#(32)) cycleCount <- mkReg(0);

    rule finish (cycleCount >= 100);
        $display("\n=== Done: %0d cycles ===", cycleCount);
        $finish(0);
    endrule

    rule count;
        cycleCount <= cycleCount + 1;
    endrule
endmodule

endpackage