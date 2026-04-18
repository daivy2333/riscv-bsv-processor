// src/peripheral/PLIC.bsv
package PLIC;

import Types::*;
import RegFile::*;
import Vector::*;

interface PLIC;
    method Word read(Addr addr);
    method Action write(Addr addr, Word data);
    method Bool externalIRQ();          // MEIP 输出
    method Action setIRQ(Bit#(32) source_id, Bool v);  // 外设 IRQ 输入
endinterface

module mkPLIC(PLIC);
    // 简化实现：支持最多 32 个中断源
    Vector#(32, Reg#(Bool)) irq_pending <- replicateM(mkReg(False));
    Vector#(32, Reg#(Bit#(32))) irq_priority <- replicateM(mkReg(1));  // 默认优先级 1

    Reg#(Bit#(32)) threshold <- mkReg(0);       // 优先级阈值
    Reg#(Bit#(32)) enable_bits <- mkReg(0);     // 使能位

    // 地址定义（使用 function）
    function Addr addrThreshold(); return 32'h0C000000; endfunction
    function Addr addrPriorityBase(); return 32'h0C000004; endfunction  // priority[1] 开始
    function Addr addrEnable(); return 32'h0C002000; endfunction
    function Addr addrClaimComplete(); return 32'h0C200004; endfunction

    // 计算最高优先级挂起中断
    function Bit#(32) getHighestPending();
        Bit#(32) highest_id = 0;
        Bit#(32) highest_pri = 0;
        for (Integer i = 1; i < 32; i = i + 1) begin
            if (irq_pending[i] && (enable_bits[i] == 1)) begin
                Bit#(32) pri = irq_priority[i];
                if (pri > highest_pri && pri > threshold) begin
                    highest_pri = pri;
                    highest_id = fromInteger(i);
                end
            end
        end
        return highest_id;
    endfunction

    method Word read(Addr addr);
        Word result = 0;
        if (addr == addrThreshold()) begin
            result = threshold;
        end else if (addr >= addrPriorityBase() && addr < addrPriorityBase() + 32*4) begin
            Bit#(32) src_id = (addr - addrPriorityBase()) >> 2;
            if (src_id > 0 && src_id < 32)
                result = irq_priority[src_id];
        end else if (addr == addrEnable()) begin
            result = enable_bits;
        end else if (addr == addrClaimComplete()) begin
            // claim: 返回最高优先级挂起中断
            result = getHighestPending();
        end
        return result;
    endmethod

    method Action write(Addr addr, Word data);
        if (addr == addrThreshold()) begin
            threshold <= data;
        end else if (addr >= addrPriorityBase() && addr < addrPriorityBase() + 32*4) begin
            Bit#(32) src_id = (addr - addrPriorityBase()) >> 2;
            if (src_id > 0 && src_id < 32)
                irq_priority[src_id] <= data;
        end else if (addr == addrEnable()) begin
            enable_bits <= data;
        end else if (addr == addrClaimComplete()) begin
            // complete: 清除挂起状态
            Bit#(32) id = data;
            if (id > 0 && id < 32)
                irq_pending[id] <= False;
        end
    endmethod

    method Bool externalIRQ();
        return getHighestPending() != 0;
    endmethod

    method Action setIRQ(Bit#(32) source_id, Bool v);
        if (source_id > 0 && source_id < 32)
            irq_pending[source_id] <= v;
    endmethod
endmodule

endpackage