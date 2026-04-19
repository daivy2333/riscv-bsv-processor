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

// 数据内存（32KB, 支持tohost监控）
module mkDMem(DMem);
    // 32KB内存 (8192 words)
    Vector#(8192, Reg#(Word)) memory <- replicateM(mkReg(0));

    // tohost 监控 - 只使用寄存器
    Reg#(Bool) tohost_written_reg <- mkReg(False);
    Reg#(Word) tohost_value_reg <- mkReg(0);

    function Addr tohostAddr(); return 32'h80001000; endfunction

    method Word read(Addr addr);
        Bit#(13) index = addr[14:2];  // 13位索引 (32KB = 8K words)
        return memory[index];
    endmethod

    method Action write(Addr addr, Word data);
        Bit#(13) index = addr[14:2];  // 13位索引 (32KB = 8K words)
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