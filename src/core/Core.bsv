package Core;
import Types::*;
import ALU::*;
import RegFile::*;

// Core接口定义
interface Core;
    method Addr pc;       // 程序计数器 (输出 PC)
    method Action step;   // 执行一步
endinterface

// Core模块实现
module mkCore(Core);
    // 程序计数器寄存器（避免与接口方法重名）
    Reg#(Addr) pcReg <- mkReg(0);

    // 实例化ALU和寄存器文件
    ALU alu <- mkALU;
    RegFile regFile <- mkRegFile;

    // Core状态
    Reg#(ProcessorState) state <- mkReg(RUNNING);

    // 执行一步
    method Action step();
        if (state == RUNNING) begin
            // 简单的PC递增，实际实现需要获取和执行指令
            pcReg <= pcReg + 4;
        end
    endmethod

    // 获取PC值（返回 pcReg）
    method Addr pc();
        return pcReg;
    endmethod
endmodule

endpackage
