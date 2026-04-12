// src/memory/IMem.bsv
package IMem;

import Types::*;
import Vector::*;

// 指令内存接口
interface IMem;
    method Word read(Addr addr);
    method Action write(Addr addr, Word data);
endinterface

// 简化版指令内存（用于测试，无延迟）
module mkIMem(IMem);
    // 使用Reg数组模拟内存（4KB）
    Vector#(1024, Reg#(Word)) memory <- replicateM(mkReg(0));

    method Word read(Addr addr);
        Bit#(10) index = addr[11:2];  // 字地址对齐
        return memory[index];
    endmethod

    method Action write(Addr addr, Word data);
        Bit#(10) index = addr[11:2];
        memory[index] <= data;
    endmethod
endmodule

endpackage