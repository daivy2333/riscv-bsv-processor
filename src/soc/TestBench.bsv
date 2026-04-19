// src/soc/TestBench.bsv
package TestBench;

import Types::*;
import SOC::*;
import Vector::*;
import TestProgram::*;

interface TestBench;
    method Bool done();
endinterface

module mkTestBench(TestBench);
    SOC soc <- mkSOC;

    Reg#(Bit#(32)) cycleCount <- mkReg(0);
    Reg#(Bool) dumpDone <- mkReg(False);
    Reg#(Bool) programLoaded <- mkReg(False);

    rule load (!programLoaded);
        soc.loadProgram(testProgram());
        programLoaded <= True;
    endrule

    // 使用 descending_urgency 设置优先级：checkCompletion > countCycles
    // 这样当两者条件都满足时，checkCompletion 先执行
    (* descending_urgency = "checkCompletion, countCycles" *)
    rule countCycles (programLoaded && !dumpDone);
        cycleCount <= cycleCount + 1;

        // 超时检查
        if (cycleCount >= 100000) begin
            $display("WARNING: Timeout at cycle %0d", cycleCount);
            dumpDone <= True;
        end
    endrule

    (* descending_urgency = "checkCompletion, countCycles" *)
    rule checkCompletion (programLoaded && !dumpDone && soc.tohostValue() != 0);
        $display("\n====================================");
        if (soc.tohostValue() == 1) begin
            $display("  Test Results: PASSED");
        end else begin
            $display("  Test Results: FAILED (tohost=0x%x)", soc.tohostValue());
        end
        $display("====================================");
        $display("Cycles: %0d", cycleCount);
        dumpDone <= True;
    endrule

    rule finish (dumpDone);
        $finish(0);
    endrule

    method Bool done = dumpDone;
endmodule

endpackage