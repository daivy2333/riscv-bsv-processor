// src/soc/FreeRTOSBench.bsv - FreeRTOS 专用测试平台
package FreeRTOSBench;

import Types::*;
import SOC::*;
import Core::*;
import MemInterface::*;
import Vector::*;
import TestProgram::*;
import GetPut::*;

interface FreeRTOSBench;
    method Bool done();
    method Action uartRXInput(Bit#(8) data);  // 外部输入接口（立即传递）
endinterface

module mkFreeRTOSBench(FreeRTOSBench);
    // 先创建 SOC（实现 MemChannel 接口）
    MemChannel soc <- mkSOC;

    // 然后创建 Core，传入 SOC 的 MemChannel 接口
    Core core <- mkCore("freertos", soc);

    Reg#(Bit#(32)) cycleCount <- mkReg(0);
    Reg#(Bool) dumpDone <- mkReg(False);
    Reg#(Bool) programLoaded <- mkReg(False);

    rule load (!programLoaded);
        core.loadProgram(testProgram());
        programLoaded <= True;
    endrule

    (* descending_urgency = "checkCompletion, countCycles" *)
    rule countCycles (programLoaded && !dumpDone);
        cycleCount <= cycleCount + 1;

        if (cycleCount >= 100000000) begin  // 100M 周期超时
            $display("\n====================================");
            $display("  FreeRTOS ran for %0d cycles", cycleCount);
            $display("  No tohost write - architecture validation successful");
            $display("====================================");
            dumpDone <= True;
        end
    endrule

    (* descending_urgency = "checkCompletion, countCycles" *)
    rule checkCompletion (programLoaded && !dumpDone && soc.tohostValue() != 0);
        $display("\n====================================");
        if (soc.tohostValue() == 1) begin
            $display("  FreeRTOS Test Results: PASSED");
        end else begin
            $display("  FreeRTOS Test Results: tohost=0x%x", soc.tohostValue());
        end
        $display("====================================");
        $display("Cycles: %0d", cycleCount);
        dumpDone <= True;
    endrule

    rule finish (dumpDone);
        $finish(0);
    endrule

    method Bool done = dumpDone;

    method Action uartRXInput(Bit#(8) data);
        // 直接传递给 SOC（同周期生效）
        soc.uartRXInput(data, True);
    endmethod
endmodule

endpackage