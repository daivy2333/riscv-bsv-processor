// src/peripheral/CLINT.bsv
package CLINT;

import Types::*;
import RegFile::*;
import Vector::*;

interface CLINT;
    method Word read(Addr addr);
    method Action write(Addr addr, Word data);
    method Bool timerIRQ();             // MTIP: mtime >= mtimecmp
    method Bool softwareIRQStatus();   // MSIP 读状态
    method Action softwareIRQ(Bool v); // MSIP 写入
endinterface

module mkCLINT(CLINT);
    // mtime: 64-bit 自动递增计数器
    Reg#(Bit#(64)) mtime <- mkReg(0);

    // mtimecmp: 64-bit 比较器
    Reg#(Bit#(64)) mtimecmp <- mkReg(64'hFFFFFFFFFFFFFFFF);  // 初始化为最大值

    // msip: 软件中断触发
    Reg#(Bool) msip <- mkReg(False);

    // 地址定义（使用 function）
    function Addr addrMSIP(); return 32'h02000000; endfunction
    function Addr addrMTIME(); return 32'h0200BFF8; endfunction
    function Addr addrMTIME_H(); return 32'h0200BFFC; endfunction
    function Addr addrMTIMECMP(); return 32'h02004000; endfunction
    function Addr addrMTIMECMP_H(); return 32'h02004004; endfunction

    // 每 cycle 自动递增 mtime
    rule increment_mtime;
        mtime <= mtime + 1;
    endrule

    method Word read(Addr addr);
        Word result = 0;
        if (addr == addrMSIP()) begin
            result = msip ? 1 : 0;
        end else if (addr == addrMTIME()) begin
            result = mtime[31:0];  // 低 32-bit
        end else if (addr == addrMTIME_H()) begin
            result = mtime[63:32]; // 高 32-bit
        end else if (addr == addrMTIMECMP()) begin
            result = mtimecmp[31:0];
        end else if (addr == addrMTIMECMP_H()) begin
            result = mtimecmp[63:32];
        end
        return result;
    endmethod

    method Action write(Addr addr, Word data);
        if (addr == addrMSIP()) begin
            msip <= (data[0] == 1);
        end else if (addr == addrMTIME()) begin
            mtime <= {mtime[63:32], data};  // 写低 32-bit
        end else if (addr == addrMTIME_H()) begin
            mtime <= {data, mtime[31:0]};   // 写高 32-bit
        end else if (addr == addrMTIMECMP()) begin
            mtimecmp <= {mtimecmp[63:32], data};
        end else if (addr == addrMTIMECMP_H()) begin
            mtimecmp <= {data, mtimecmp[31:0]};
        end
    endmethod

    method Bool timerIRQ();
        return mtime >= mtimecmp;
    endmethod

    method Bool softwareIRQStatus();
        return msip;
    endmethod

    method Action softwareIRQ(Bool v);
        msip <= v;
    endmethod
endmodule

endpackage