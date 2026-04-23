// src/soc/TestBench.bsv - 彻底重构版
package TestBench;

import Types::*;
import SOC::*;
import Core::*;
import MemInterface::*;
import Vector::*;
import TestProgram::*;

interface TestBench;
    method Bool done();
endinterface

module mkTestBench(TestBench);
    // 先创建 SOC（实现 MemChannel 接口）
    MemChannel soc <- mkSOC;

    // 然后创建 Core，传入 SOC 的 MemChannel 接口
    Core core <- mkCore("test", soc);

    Reg#(Bit#(32)) cycleCount <- mkReg(0);
    Reg#(Bool) dumpDone <- mkReg(False);
    Reg#(Bool) programLoaded <- mkReg(False);

    rule load (!programLoaded);
        Vector#(4096, Word) imem_prog = testProgramForIMem();
        Vector#(8192, Word) dmem_prog = testProgram();
        core.loadProgram(imem_prog);
        soc.loadProgram(dmem_prog);
        programLoaded <= True;
    endrule

    (* descending_urgency = "checkCompletion, countCycles" *)
    rule countCycles (programLoaded && !dumpDone);
        cycleCount <= cycleCount + 1;

        if (cycleCount >= 100000) begin  // 100K 周期超时（普通测试）
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