// src/soc/TestBench.bsv
package TestBench;
import Types::*;
import Core::*;

interface TestBench;
    method Bool done();
endinterface

module mkTestBench(TestBench);
    // 处理器核心
    Core core <- mkCore;
    
    // 仿真控制
    Reg#(Bit#(32)) cycleCount <- mkReg(0);
    Reg#(Bool) simulationDone <- mkReg(False);
    
    // 每周期驱动处理器执行一步
    rule tick;
        // 驱动处理器执行
        core.step();
        
        cycleCount <= cycleCount + 1;
        $display("Cycle %0d: PC=%h", cycleCount, core.pc);
        
        // 仿真结束条件
        if (cycleCount > 1000 || core.pc == 32'hFFFFFFFF) begin
            simulationDone <= True;
            $display("Simulation finished after %0d cycles", cycleCount);
        end
    endrule
    
    method Bool done();
        return simulationDone;
    endmethod
endmodule
endpackage