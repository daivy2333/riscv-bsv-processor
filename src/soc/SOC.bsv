// src/soc/SOC.bsv
package SOC;

import Types::*;
import Core::*;
import CLINT::*;
import PLIC::*;
import UART::*;
import DMem::*;
import CSR::*;
import PrivilegedTypes::*;
import Vector::*;
import FIFO::*;

interface SOC;
    method Bool testDone();
    method Word tohostValue();
    method Action loadProgram(Vector#(1024, Word) prog);
    method Word readReg(Bit#(5) addr);
    method Action sync_mtime();  // 同步 mtime 递增
endinterface

module mkSOC(SOC);
    Core core <- mkCore("test");
    CLINT clint <- mkCLINT;
    PLIC plic <- mkPLIC;
    UART uart <- mkUART;
    DMem dmem <- mkDMem;

    // 内存请求响应寄存器
    Reg#(MemResp) mem_resp_reg <- mkReg(MemResp {valid: False, rdata: 0});
    Reg#(Bool) resp_ready <- mkReg(False);

    // 处理 Core 内存请求
    rule handle_mem_req;
        MemReq req = core.memReq();

        if (req.valid) begin
            Addr addr = req.addr;
            Word rdata = 0;

            // 地址路由
            if (addr >= 32'h02000000 && addr < 32'h02010000) begin
                // CLINT
                if (req.op == MEM_READ)
                    rdata = clint.read(addr);
                else if (req.op == MEM_WRITE)
                    clint.write(addr, req.wdata);
            end else if (addr >= 32'h0C000000 && addr < 32'h0C100000) begin
                // PLIC
                if (req.op == MEM_READ)
                    rdata = plic.read(addr);
                else if (req.op == MEM_WRITE)
                    plic.write(addr, req.wdata);
            end else if (addr >= 32'h10000000 && addr < 32'h10001000) begin
                // UART
                if (req.op == MEM_READ)
                    rdata = uart.read(addr);
                else if (req.op == MEM_WRITE)
                    uart.write(addr, req.wdata);
            end else if (addr >= 32'h80000000) begin
                // RAM
                if (req.op == MEM_READ)
                    rdata = dmem.read(addr);
                else if (req.op == MEM_WRITE)
                    dmem.write(addr, req.wdata);
            end

            // 响应
            if (req.op == MEM_READ) begin
                // 字节/半字扩展（由 SOC 处理）
                rdata = processMemWidth(rdata, req.addr, req.width, req.is_unsigned);
                mem_resp_reg <= MemResp {valid: True, rdata: rdata};
                resp_ready <= True;
            end
        end
    endrule

    // 发送响应给 Core
    rule send_mem_resp (resp_ready);
        core.memResp(mem_resp_reg);
        resp_ready <= False;
    endrule

    // 中断信号连接
    rule connect_interrupts;
        core.csrModule().setMTIP(clint.timerIRQ());
        core.csrModule().setMSIP(clint.softwareIRQStatus());
        core.csrModule().setMEIP(plic.externalIRQ());
        plic.setIRQ(1, uart.hasIRQ());  // UART -> PLIC source_id=1
    endrule

    method Bool testDone();
        return dmem.tohostWritten();
    endmethod

    method Word tohostValue();
        return dmem.tohostValue();
    endmethod

    method Action loadProgram(Vector#(1024, Word) prog);
        core.loadProgram(prog);
    endmethod

    method Word readReg(Bit#(5) addr);
        return core.readReg(addr);
    endmethod

    method Action sync_mtime();
        clint.increment_mtime();
    endmethod
endmodule

// 字节/半字扩展处理函数
function Word processMemWidth(Word word_val, Addr addr, MemWidth width, Bool is_unsigned);
    Word result = word_val;
    case (width)
        MEM_WORD: result = word_val;

        MEM_HALF: begin
            Bit#(1) half_offset = addr[1];
            Bit#(16) half_val = half_offset == 0
                ? word_val[15:0]
                : word_val[31:16];
            result = is_unsigned
                ? zeroExtend(half_val)
                : signExtend(half_val);
        end

        MEM_BYTE: begin
            Bit#(2) byte_offset = addr[1:0];
            Bit#(8) byte_val = case (byte_offset)
                0: word_val[7:0];
                1: word_val[15:8];
                2: word_val[23:16];
                3: word_val[31:24];
            endcase;
            result = is_unsigned
                ? zeroExtend(byte_val)
                : signExtend(byte_val);
        end
    endcase
    return result;
endfunction

endpackage