// src/memory/DMem.bsv
package DMem;

import Types::*;
import Vector::*;

// 数据内存接口
interface DMem;
    method Word read(Addr addr);
    method Action write(Addr addr, Word data);
    method Bool tohostWritten();   // tohost 写入检测
    method Word tohostValue();     // tohost 写入值
endinterface

// 数据内存（64KB, 支持tohost监控）
module mkDMem(DMem);
    // 64KB内存 (16K words)
    Vector#(16384, Reg#(Word)) memory <- replicateM(mkReg(0));

    // tohost 监控
    Reg#(Bool) tohost_written <- mkReg(False);
    Reg#(Word) tohost_value <- mkReg(0);
    function Addr tohostAddr(); return 32'h80001000; endfunction

    method Word read(Addr addr);
        Bit#(14) index = addr[15:2];  // 14位索引 (64KB)
        return memory[index];
    endmethod

    method Action write(Addr addr, Word data);
        Bit#(14) index = addr[15:2];
        memory[index] <= data;

        // tohost 监控
        if (addr == tohostAddr()) begin
            tohost_written <= True;
            tohost_value <= data;
        end
    endmethod

    method Bool tohostWritten();
        return tohost_written;
    endmethod

    method Word tohostValue();
        return tohost_value;
    endmethod
endmodule

endpackage