// src/memory/IMem.bsv
package IMem;

import Types::*;
import Vector::*;

// 指令内存接口
interface IMem;
    method Word read(Addr addr);
    method Action write(Addr addr, Word data);
endinterface

// 指令内存（32KB, 8K words）
module mkIMem(IMem);
    // 32KB = 8192 words
    Vector#(8192, Reg#(Word)) memory <- replicateM(mkReg(0));

    method Word read(Addr addr);
        Bit#(13) index = addr[14:2];  // 13位索引 (32KB = 8K words)
        return memory[index];
    endmethod

    method Action write(Addr addr, Word data);
        Bit#(13) index = addr[14:2];
        memory[index] <= data;
    endmethod
endmodule

endpackage