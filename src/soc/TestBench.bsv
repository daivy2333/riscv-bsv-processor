// src/soc/TestBench.bsv
package TestBench;

import Types::*;
import Core::*;
import Vector::*;

interface TestBench;
    method Bool done();
endinterface

module mkTestBench(TestBench);
    Core core <- mkCore("test");

    Reg#(Bit#(32)) cycleCount <- mkReg(0);
    Reg#(Bool) programDone <- mkReg(False);
    Reg#(Bool) dumpDone <- mkReg(False);
    Reg#(Bool) programLoaded <- mkReg(False);
    Reg#(Bit#(32)) waitCount <- mkReg(0);

    // 测试 Load-Use 冒险
    function Vector#(1024, Word) testProgram();
        Vector#(1024, Word) prog = replicate(0);

        // 测试1: 基本 Load-Use 冒险
        // 正确的指令编码:
        // li x1, 10 = addi x1, x0, 10 = 0x00a00093 ✓
        // li x2, 4 = addi x2, x0, 4 = 0x00400113 ✓
        // sw x1, 0(x2) = 0x00112023 ✓
        // lw x3, 0(x2): imm=0, rs1=2, funct3=010, rd=3, opcode=0000011
        //   = 000000000000_00010_010_00011_0000011 = 0x00012403
        // add x4, x3, x1: funct7=0, rs2=1, rs1=3, funct3=0, rd=4, opcode=0110011
        //   = 0000000_00001_00011_000_00100_0110011 = 0x00118033
        prog[0] = 32'h00a00093;    // li x1, 10
        prog[1] = 32'h00400113;    // li x2, 4
        prog[2] = 32'h00112023;    // sw x1, 0(x2) - store x1=10 to address x2=4
        prog[3] = 32'h00012403;    // lw x3, 0(x2) - Load x3 = dmem[1] = 10
        prog[4] = 32'h00118033;    // add x4, x3, x1 - x4 = x3 + x1 = 10 + 10 = 20

        return prog;
    endfunction

    rule load (!programLoaded);
        core.loadProgram(testProgram());
        programLoaded <= True;
    endrule

    rule countCycles (programLoaded && !dumpDone);
        cycleCount <= cycleCount + 1;
    endrule

    rule checkDone (programLoaded && !programDone && core.pc >= 32'h80000014);
        programDone <= True;
    endrule

    rule waitForWB (programDone && !dumpDone);
        waitCount <= waitCount + 1;
        if (waitCount >= 25) begin
            dumpDone <= True;
        end
    endrule

    rule report (dumpDone);
        $display("\n====================================");
        $display("  Load-Use Hazard Test Results");
        $display("====================================");
        $display("Cycles: %0d", cycleCount);
        $display("Register dump:");
        $display("  x1 = %0d (expected 10)", core.readReg(1));
        $display("  x2 = %0d (expected 4)", core.readReg(2));
        $display("  x3 = %0d (expected 10)", core.readReg(3));
        $display("  x4 = %0d (expected 20)", core.readReg(4));
    endrule

    rule finish (dumpDone);
        $finish(0);
    endrule

    method Bool done = dumpDone;
endmodule

endpackage
