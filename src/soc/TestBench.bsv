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

    // 测试简单的lw（无Load-Use冒险）
    function Vector#(1024, Word) testProgram();
        Vector#(1024, Word) prog = replicate(0);
        // 只测试sw/lw
        prog[0] = 32'h00b00093;    // li x1, 11
        prog[1] = 32'h00100113;    // li x2, 1
        prog[2] = 32'h00112123;    // sw x1, 4(x2) - 存储11到dmem[1]
        prog[3] = 32'h00112083;    // lw x1, 4(x2) - 从dmem[1]加载到x1
        prog[4] = 32'h0000006f;    // j end
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
        $display("  SW/LW Test Results");
        $display("====================================");
        $display("Cycles: %0d", cycleCount);
        $display("Register dump:");
        $display("  x1 = %0d (expected 11)", core.readReg(1));
        $display("  x2 = %0d (expected 1)", core.readReg(2));
    endrule

    rule finish (dumpDone);
        $finish(0);
    endrule

    method Bool done = dumpDone;
endmodule

endpackage
