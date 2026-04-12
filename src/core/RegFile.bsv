package RegFile;
import Types::*;
import Vector::*;     // ★★★ 必须添加，否则无法使用 Vector

interface RegFile;
    method Action write(Bit#(5) addr, Word data);
    method Word read1(Bit#(5) addr);
    method Word read2(Bit#(5) addr);
    method Word readReg(Bit#(5) addr);  // Debug: read any register
endinterface

module mkRegFile(RegFile);
    // RISC-V有32个寄存器，x0硬连线为0
    Vector#(32, Reg#(Word)) registers <- replicateM(mkReg(0));
    
    method Action write(Bit#(5) addr, Word data);
        if (addr != 0) begin  // x0是只读的，始终为0
            registers[addr] <= data;
        end
    endmethod
    
    method Word read1(Bit#(5) addr);
        return (addr == 0) ? 0 : registers[addr];
    endmethod
    
    method Word read2(Bit#(5) addr);
        return (addr == 0) ? 0 : registers[addr];
    endmethod

    method Word readReg(Bit#(5) addr);
        return (addr == 0) ? 0 : registers[addr];
    endmethod
endmodule

endpackage
