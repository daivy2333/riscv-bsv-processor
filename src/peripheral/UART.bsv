// src/peripheral/UART.bsv
package UART;

import Types::*;

interface UART;
    method Word read(Addr addr);
    method Action write(Addr addr, Word data);
    method Bool hasIRQ();              // IRQ 输出（接 PLIC）
    method Action setRX(Bit#(8) data, Bool valid);  // 外部输入接口
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
        else if (offset == 20) begin
            // IP: 组合逻辑读取实时状态
            // bit 0 = TXWM (从寄存器)
            // bit 1 = RXWM (从 rx_valid 实时读取)
            Bit#(32) real_ip = ip;
            real_ip[1] = rx_valid ? 1 : 0;  // RXWM 实时
            result = real_ip;
        end
        return result;
    endmethod

    method Action write(Addr addr, Word data);
        Addr offset = addr & 32'hFF;
        if (offset == 0) begin  // TXDATA
            // 立即输出字符（无 backpressure）
            $display("%c", data[7:0]);  // 直接输出字符，不带调试前缀
            txdata <= data[7:0];
            tx_full <= False;  // 始终为空（无阻塞）
            ip[0] <= 1;        // TX 完成 interrupt
        end else if (offset == 8) begin  // TXCTRL
            tx_enable <= (data[0] == 1'b1);
        end else if (offset == 12) begin  // RXCTRL
            rx_enable <= (data[0] == 1'b1);
        end else if (offset == 16) begin  // IE
            ie <= data;
        end else if (offset == 20) begin  // IP
            // 写 1 清除，同时清除对应的 rx_valid
            if (data[1] == 1) rx_valid <= False;  // 清除 RXWM 时清除 rx_valid
            ip <= ip & ~data;
        end
    endmethod

    method Bool hasIRQ();
        // TXWM (bit 0) 或 RXWM (bit 1) 中断
        return (ip & ie) != 0;
    endmethod

    method Action setRX(Bit#(8) data, Bool valid);
        // 外部输入接口：仿真环境传入字符
        if (valid) begin
            rxdata <= data;
            rx_valid <= True;
            ip <= ip | 32'h2;  // RX 中断挂起（bit 1）
        end
    endmethod
endmodule

endpackage