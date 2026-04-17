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

    rule checkDone (programLoaded && !programDone && core.pc >= 32'h80000058);
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
        $display("  Pipeline Test Results");
        $display("====================================");
        $display("Cycles: %0d", cycleCount);
        $display("Register dump:");
        $display("  x1  (ra)  = %0d (expected 10)", core.readReg(1));
        $display("  x2  (sp)  = %0d (expected 20)", core.readReg(2));
        $display("  x3  (gp)  = %0d (expected 30)", core.readReg(3));
        $display("  x4  (tp)  = %0d (expected 40)", core.readReg(4));
        $display("  x5  (t0)  = %0d (expected 70)", core.readReg(5));
        $display("  x31 (t6)  = %0d (expected 0xDEAD)", core.readReg(31));
    endrule

    rule finish (dumpDone);
        $finish(0);
    endrule

    method Bool done = dumpDone;
endmodule

endpackage
