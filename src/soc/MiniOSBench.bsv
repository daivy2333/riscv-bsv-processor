// src/soc/MiniOSBench.bsv - Mini-OS 专用测试平台
package MiniOSBench;

import Types::*;
import SOC::*;
import Core::*;
import MemInterface::*;
import Vector::*;
import TestProgram::*;
import GetPut::*;

interface MiniOSBench;
    method Bool done();
    method Action uartRXInput(Bit#(8) data);
endinterface

module mkMiniOSBench(MiniOSBench);
    MemChannel soc <- mkSOC;
    Core core <- mkCore("mini-os", soc);

    Reg#(Bit#(32)) cycleCount <- mkReg(0);
    Reg#(Bool) dumpDone <- mkReg(False);
    Reg#(Bool) programLoaded <- mkReg(False);

    rule load (!programLoaded);
        Vector#(4096, Word) imem_prog = testProgramForIMem();
        Vector#(8192, Word) dmem_prog = testProgram();
        core.loadProgram(imem_prog);  // 加载到 Core 的 IMem (4096 words)
        soc.loadProgram(dmem_prog);   // 加载到 SOC 的 DMem (8192 words)
        programLoaded <= True;
    endrule

    rule countCycles (programLoaded && !dumpDone);
        cycleCount <= cycleCount + 1;
        // 每10000周期打印一次进度
        if (cycleCount % 10000 == 0) begin
            $display("Cycle %0d running...", cycleCount);
        end
        if (cycleCount >= 500000) begin
            $display("\n=== Mini-OS ran for %0d cycles ===", cycleCount);
            dumpDone <= True;
        end
    endrule

    rule checkCompletion (programLoaded && !dumpDone && soc.tohostValue() != 0);
        $display("\n=== Test Results: tohost=0x%x ===", soc.tohostValue());
        dumpDone <= True;
    endrule

    rule finish (dumpDone);
        $finish(0);
    endrule

    method Bool done = dumpDone;

    method Action uartRXInput(Bit#(8) data);
        soc.uartRXInput(data, True);
    endmethod
endmodule

endpackage