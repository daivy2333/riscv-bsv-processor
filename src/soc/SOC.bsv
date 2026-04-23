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
import SpecialFIFOs::*;

// SOC 实现 MemChannel 接口（Core 使用）
module mkSOC(MemChannel);
    CLINT clint <- mkCLINT;
    PLIC plic <- mkPLIC;
    UART uart <- mkUART;
    DMem dmem <- mkDMem;

    // 内存消息通道（SOC 内部 FIFOF）
    FIFOF#(MemReq) mem_req_fifo <- mkFIFOF;   // Core → SOC
    FIFOF#(MemResp) mem_resp_fifo <- mkBypassFIFOF; // SOC → Core（bypass 支持同周期读写）

    // CSR 模块（处理中断）
    CSRs csrs <- mkCSR;

    // SOC 内部处理内存请求（不涉及 Core）
    rule handle_mem_req (mem_req_fifo.notEmpty);
        MemReq req = mem_req_fifo.first;
        mem_req_fifo.deq;

        Addr addr = req.addr;
        Word rdata = 0;

        // 调试：追踪 CLINT 写入
        if (addr >= 32'h02000000 && addr < 32'h02010000 && req.op == MEM_WRITE) begin
            $display("[SOC] CLINT write: addr=%x data=%x", addr, req.wdata);
        end

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

        // 只为 Load 请求发送响应
        if (req.op == MEM_READ)
            mem_resp_fifo.enq(MemResp {valid: True, rdata: rdata});
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

    // 直接驱动中断信号（通过方法，每周期由 Core 调用）
    method Action timerIRQWire(Bool irq);
        csrs.timerIRQWire(irq);
    endmethod

    method Action softwareIRQWire(Bool irq);
        csrs.softwareIRQWire(irq);
    endmethod

    method Action externalIRQWire(Bool irq);
        csrs.externalIRQWire(irq);
    endmethod

    // 中断状态直接读取方法（供 Core 每周期调用）
    method Bool clintTimerIRQ();
        return clint.timerIRQ();
    endmethod

    method Bool clintSoftwareIRQ();
        return clint.softwareIRQStatus();
    endmethod

    method Bool plicExternalIRQ();
        return plic.externalIRQ();
    endmethod

    method Action uartRXInput(Bit#(8) data, Bool valid);
        uart.setRX(data, valid);
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

    // 程序加载方法（用于初始化 DMem）
    method Action loadProgram(Vector#(8192, Word) prog);
        dmem.loadProgram(prog);
    endmethod

    // 调试方法：获取 mtime 和 mtimecmp
    method Bit#(64) getMtime();
        return clint.getMtime();
    endmethod

    method Bit#(64) getMtimecmp();
        return clint.getMtimecmp();
    endmethod

    // 调试方法：获取 CSR 状态
    method Word getMStatus();
        return csrs.getMStatus();
    endmethod

    method Word getMIE();
        return csrs.getMIE();
    endmethod

    method Word getMIP();
        return csrs.getMIP();
    endmethod
endmodule

endpackage