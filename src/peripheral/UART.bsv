// src/peripheral/UART.bsv
package UART;

import Types::*;
import RegFile::*;

interface UART;
    method Word read(Addr addr);
    method Action write(Addr addr, Word data);
    method Bool hasIRQ();              // IRQ 输出（接 PLIC）
endinterface

module mkUART(UART);
    Reg#(Bit#(8)) txdata <- mkReg(0);
    Reg#(Bool) tx_full <- mkReg(False);
    Reg#(Bit#(8)) rxdata <- mkReg(0);
    Reg#(Bool) rx_valid <- mkReg(False);

    Reg#(Bool) tx_enable <- mkReg(False);
    Reg#(Bool) rx_enable <- mkReg(False);

    Reg#(Bit#(32)) ie <- mkReg(0);     // 中断使能
    Reg#(Bit#(32)) ip <- mkReg(0);     // 中断挂起

    // 模拟发送完成（简化实现）
    rule tx_complete (tx_full);
        tx_full <= False;
        ip[0] <= 1;  // TX 完成 interrupt
        $display("UART TX: %h", txdata);
    endrule

    method Word read(Addr addr);
        Addr offset = addr & 32'hFF;  // 取低 8 位
        Word result = 0;
        if (offset == 0)
            result = tx_full ? 1 : 0;  // TXDATA: TX 状态
        else if (offset == 4)
            result = rx_valid ? {24'b0, rxdata} : 0;  // RXDATA
        else if (offset == 8)
            result = tx_enable ? 1 : 0;  // TXCTRL
        else if (offset == 12)
            result = rx_enable ? 1 : 0;  // RXCTRL
        else if (offset == 16)
            result = ie;  // IE
        else if (offset == 20)
            result = ip;  // IP
        return result;
    endmethod

    method Action write(Addr addr, Word data);
        Addr offset = addr & 32'hFF;
        if (offset == 0) begin  // TXDATA
            txdata <= data[7:0];
            tx_full <= True;
        end else if (offset == 8) begin  // TXCTRL
            tx_enable <= (data[0] == 1'b1);
        end else if (offset == 12) begin  // RXCTRL
            rx_enable <= (data[0] == 1'b1);
        end else if (offset == 16) begin  // IE
            ie <= data;
        end else if (offset == 20) begin  // IP
            ip <= ip & ~data;  // 写 1 清除
        end
    endmethod

    method Bool hasIRQ();
        // TXWM (bit 0) 或 RXWM (bit 1) 中断
        return (ip & ie) != 0;
    endmethod
endmodule

endpackage