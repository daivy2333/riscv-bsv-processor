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
    Reg#(Bit#(32)) stallCycles <- mkReg(0);  // 检测死循环
    Reg#(Addr) lastPC <- mkReg(0);            // 记录上一周期 PC

    rule load (!programLoaded);
        core.loadProgram(testProgram());
        programLoaded <= True;
    endrule

    rule countCycles (programLoaded && !dumpDone);
        cycleCount <= cycleCount + 1;
    endrule

    rule checkDone (programLoaded && !programDone);
        // 调试：每周期输出状态
        if (cycleCount < 30) begin
            $display("Cycle %0d: PC=%h, x10=%0d, wb_fwd0=%h(rd=%d,v=%b), wb_fwd1=%h(rd=%d,v=%b), testDone=%b",
                     cycleCount, core.pc, core.readReg(10),
                     core.readReg(31),  // 用 readReg 读取 wb_forward 值不准确，只作参考
                     0, False,
                     0, 0, False,
                     core.testDone);
        end
        // tohost 写入检测（标准 riscv-tests）
        if (core.testDone) begin
            programDone <= True;
        end
        // 死循环检测（PC 重复 20 次以上，表示测试结束）
        else if (core.pc == lastPC) begin
            stallCycles <= stallCycles + 1;
            if (stallCycles >= 20) begin
                programDone <= True;
            end
        end
        else begin
            stallCycles <= 0;
            lastPC <= core.pc;
        end
    endrule

    rule waitForWB (programDone && !dumpDone);
        waitCount <= waitCount + 1;
        if (waitCount >= 25) begin
            dumpDone <= True;
        end
    endrule

    rule report (dumpDone);
        $display("\n====================================");
        if (core.testDone && core.tohostValue == 1) begin
            $display("  Test Results: PASSED");
        end else if (core.testDone) begin
            $display("  Test Results: FAILED (tohost=0x%x)", core.tohostValue);
        end else begin
            $display("  Test completed (PC reached end)");
            $display("  Note: No tohost write detected");
        end
        $display("====================================");
        $display("Cycles: %0d", cycleCount);
        $display("Final PC: 0x%h", core.pc);
        $display("Key registers:");
        $display("  x5  (t0)  = %0d", core.readReg(5));
        $display("  x6  (t1)  = %0d", core.readReg(6));
        $display("  x7  (t2)  = %0d", core.readReg(7));
    endrule

    rule finish (dumpDone);
        $finish(0);
    endrule

    method Bool done = dumpDone;
endmodule

endpackage
