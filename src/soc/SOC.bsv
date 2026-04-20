// src/soc/SOC.bsv - 彻底重构版（实现 MemChannel 接口）
package SOC;

import Types::*;
import CLINT::*;
import PLIC::*;
import UART::*;
import DMem::*;
import CSR::*;
import PrivilegedTypes::*;
import MemInterface::*;
import Vector::*;
import FIFOF::*;

// SOC 实现 MemChannel 接口（Core 使用）
module mkSOC(MemChannel);
    CLINT clint <- mkCLINT;
    PLIC plic <- mkPLIC;
    UART uart <- mkUART;
    DMem dmem <- mkDMem;

    // 内存消息通道（SOC 内部 FIFOF）
    FIFOF#(MemReq) mem_req_fifo <- mkFIFOF;   // Core → SOC
    FIFOF#(MemResp) mem_resp_fifo <- mkFIFOF; // SOC → Core

    // CSR 模块（处理中断）
    CSRs csrs <- mkCSR;

    // SOC 内部处理内存请求（不涉及 Core）
    rule handle_mem_req (mem_req_fifo.notEmpty);
        MemReq req = mem_req_fifo.first;
        mem_req_fifo.deq;

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

        // 发送响应
        mem_resp_fifo.enq(MemResp {valid: True, rdata: rdata});
    endrule

    // SOC 内部驱动中断信号（PLIC/CLINT → CSR）
    rule drive_interrupts;
        csrs.timerIRQWire(clint.timerIRQ());
        csrs.softwareIRQWire(clint.softwareIRQStatus());
        csrs.externalIRQWire(plic.externalIRQ());
        plic.irqWire(1, uart.hasIRQ());
    endrule

    // MemChannel 接口方法
    method Action sendMemReq(MemReq req);
        mem_req_fifo.enq(req);
    endmethod

    method Bool hasMemResp();
        return mem_resp_fifo.notEmpty;
    endmethod

    method MemResp peekMemResp();
        return mem_resp_fifo.first;
    endmethod

    method Action deqMemResp();
        mem_resp_fifo.deq;
    endmethod

    method Action timerIRQWire(Bool irq);
        csrs.timerIRQWire(irq);
    endmethod

    method Action softwareIRQWire(Bool irq);
        csrs.softwareIRQWire(irq);
    endmethod

    method Action externalIRQWire(Bool irq);
        csrs.externalIRQWire(irq);
    endmethod

    method Bool testDone();
        return dmem.tohostWritten();
    endmethod

    method Word tohostValue();
        return dmem.tohostValue();
    endmethod

    method CSRs csrModule();
        return csrs;
    endmethod
endmodule

endpackage