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

// 数据内存（8KB, 支持tohost监控）
module mkDMem(DMem);
    // 8KB内存 (2048 words)
    Vector#(2048, Reg#(Word)) memory <- replicateM(mkReg(0));

    // tohost 监控 - 只使用寄存器
    Reg#(Bool) tohost_written_reg <- mkReg(False);
    Reg#(Word) tohost_value_reg <- mkReg(0);

    function Addr tohostAddr(); return 32'h80001000; endfunction

    method Word read(Addr addr);
        Bit#(11) index = addr[12:2];  // 11位索引 (8KB = 2048 words)
        return memory[index];
    endmethod

    method Action write(Addr addr, Word data);
        Bit#(11) index = addr[12:2];
        memory[index] <= data;

        // tohost 监控 - 只设置寄存器
        if (addr == tohostAddr()) begin
            tohost_written_reg <= True;
            tohost_value_reg <= data;
        end
    endmethod

    method Bool tohostWritten();
        return tohost_written_reg;
    endmethod

    method Word tohostValue();
        return tohost_value_reg;
    endmethod
endmodule

endpackage