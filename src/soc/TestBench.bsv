// src/soc/TestBench.bsv
package TestBench;

import Types::*;
import Core::*;
import Vector::*;
import TestProgram::*;  // 导入自动生成的测试程序

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

    rule load (!programLoaded);
        core.loadProgram(testProgram());
        programLoaded <= True;
    endrule

    rule countCycles (programLoaded && !dumpDone);
        cycleCount <= cycleCount + 1;
    endrule

    rule checkDone (programLoaded && !programDone && core.pc >= 32'h8000005c);
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
        $display("  R-Type Instructions Test Results");
        $display("====================================");
        $display("Cycles: %0d", cycleCount);
        $display("Register dump:");
        $display("  x1  (ra)  = %0d (expected 10)", core.readReg(1));
        $display("  x2  (sp)  = %0d (expected 3)", core.readReg(2));
        $display("  x3  (gp)  = %0d (expected -5)", core.readReg(3));
        $display("  x4  (tp)  = %0d (expected 7)    SUB", core.readReg(4));
        $display("  x5  (t0)  = %0d (expected 80)   SLL", core.readReg(5));
        $display("  x7  (t2)  = %0d (expected 16)   SRL", core.readReg(7));
        $display("  x9  (s1)  = %0d (expected -2)   SRA", core.readReg(9));
        $display("  x10 (a0)  = %0d (expected 1)    SLT", core.readReg(10));
        $display("  x11 (a1)  = %0d (expected 0)    SLT", core.readReg(11));
        $display("  x12 (a2)  = %0d (expected 0)    SLTU", core.readReg(12));
        $display("  x15 (a5)  = %0d (expected 7)    AND", core.readReg(15));
        $display("  x18 (s2)  = %0d (expected 11)   OR", core.readReg(18));
        $display("  x21 (s5)  = %0d (expected 10)   XOR", core.readReg(21));
        $display("  x31 (t6)  = %0d (expected 0xDEAD)", core.readReg(31));
    endrule

    rule finish (dumpDone);
        $finish(0);
    endrule

    method Bool done = dumpDone;
endmodule

endpackage
