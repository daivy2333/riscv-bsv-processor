// src/memory/DMem.bsv
package DMem;

import Types::*;
import Vector::*;

// 数据内存接口
interface DMem;
    method Word read(Addr addr);
    method Action write(Addr addr, Word data);
endinterface

// 简化版数据内存（用于测试，无延迟）
module mkDMem(DMem);
    // 使用Reg数组模拟内存（2KB）
    Vector#(512, Reg#(Word)) memory <- replicateM(mkReg(0));

    method Word read(Addr addr);
        Bit#(9) index = addr[10:2];  // 字地址对齐
        return memory[index];
    endmethod

    method Action write(Addr addr, Word data);
        Bit#(9) index = addr[10:2];
        memory[index] <= data;
    endmethod
endmodule

endpackage