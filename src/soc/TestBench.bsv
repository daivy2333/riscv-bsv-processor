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
    Reg#(Bool) programDone <- mkReg(False);
    Reg#(Bool) dumpDone <- mkReg(False);
    Reg#(Bool) programLoaded <- mkReg(False);

    rule load (!programLoaded);
        soc.loadProgram(testProgram());
        programLoaded <= True;
    endrule

    rule countCycles (programLoaded && !dumpDone);
        cycleCount <= cycleCount + 1;
    endrule

    rule checkDone (programLoaded && !programDone);
        Bool done = soc.testDone() || (cycleCount >= 100000);
        if (done) begin
            if (cycleCount >= 100000)
                $display("WARNING: Timeout at cycle %0d", cycleCount);
            programDone <= True;
        end
    endrule

    rule report (programDone && !dumpDone);
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