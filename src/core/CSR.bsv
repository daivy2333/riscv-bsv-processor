// src/core/CSR.bsv
package CSR;

import Types::*;
import PrivilegedTypes::*;

// ============================================================
// CSR Register File Module
// ============================================================

interface CSRs;
    method Word readCSR(Bit#(12) addr);
    method Action writeCSR(Bit#(12) addr, Word data);
    method PrivilegeMode currentMode();
    method Action setMode(PrivilegeMode mode);
    method Addr getTrapVector(TrapInfo trap);
    method Bool hasPendingInterrupt();
    method Maybe#(Bit#(5)) getPendingInterruptCause();
    // 中断信号 Wire 输入（由 SOC 每周期驱动）
    method Action timerIRQWire(Bool irq);      // MTIP 输入
    method Action softwareIRQWire(Bool irq);   // MSIP 输入
    method Action externalIRQWire(Bool irq);   // MEIP 输入
    method Action incrementCycle;
    method Action incrementMinstret;
    method Bit#(64) getMtime();
    method Action setMtime(Bit#(64) v);
    method Bit#(64) getMtimecmp();
    method Action setMtimecmp(Bit#(64) v);
    // 调试方法：读取关键寄存器
    method Word getMStatus();
    method Word getMIE();
    method Word getMIP();
endinterface

// Helper function: check if CSR is read-only
function Bool isReadOnlyCSR(Bit#(12) addr);
    return case (addr)
        12'hF11: True;  // mvendorid
        12'hF12: True;  // marchid
        12'hF13: True;  // mimpid
        12'hF14: True;  // mhartid
        12'h301: True;  // misa (mostly read-only, but we treat as RO)
        default: False;
    endcase;
endfunction

// Helper function: pack MStatus struct to Word
function Word packMStatus(MStatus s);
    Bit#(32) result = 0;
    result[0] = s.uie;
    result[1] = s.sie;
    result[2] = s._reserved2;
    result[3] = s.mie;
    result[4] = s.upie;
    result[5] = s.spie;
    result[6] = s._reserved6;
    result[7] = s.mpie;
    result[8] = s.spp;
    result[9] = s._reserved9;
    result[10] = s._reserved10;
    // 修复：MPP = bit 11:10 (不是 bit 12:11)
    result[11:10] = s.mpp;
    // FS = bit 14:12 (3 bits，和 MPP 不重叠)
    result[14:12] = s.fs;
    result[16:15] = s.xs;
    result[17] = s.mprv;
    result[18] = s.sum;
    result[19] = s.mxr;
    result[20] = s.tvm;
    result[21] = s.tw;
    result[22] = s.tsr;
    result[30:23] = s._reserved23;
    result[31] = s.sd;
    return result;
endfunction

// Helper function: unpack Word to MStatus struct
function MStatus unpackMStatus(Bit#(32) w);
    return MStatus {
        uie:        w[0],
        sie:        w[1],
        _reserved2: w[2],
        mie:        w[3],
        upie:       w[4],
        spie:       w[5],
        _reserved6: w[6],
        mpie:       w[7],
        spp:        w[8],
        _reserved9:  w[9],
        _reserved10: w[10],
        // 修复：MPP = bit 11:10
        mpp:        w[11:10],
        fs:         w[14:12],
        xs:         w[16:15],
        mprv:       w[17],
        sum:        w[18],
        mxr:        w[19],
        tvm:        w[20],
        tw:         w[21],
        tsr:        w[22],
        _reserved23: w[30:23],
        sd:         w[31]
    };
endfunction

module mkCSR(CSRs);
    // Current privilege mode
    Reg#(PrivilegeMode) priv_mode <- mkReg(M_MODE);

    // Machine Information Registers (read-only, return 0)
    // mvendorid = 0, marchid = 0, mimpid = 0, mhartid = 0

    // Machine Trap Setup
    Reg#(MStatus) mstatus <- mkReg(MStatus {
        uie: 0, sie: 0, _reserved2: 0, mie: 0, upie: 0, spie: 0,
        _reserved6: 0, mpie: 0, spp: 0, _reserved9: 0, _reserved10: 0,
        mpp: 0, fs: 0, xs: 0, mprv: 0, sum: 0, mxr: 0, tvm: 0, tw: 0, tsr: 0,
        _reserved23: 0, sd: 0
    });
    Reg#(Word) misa <- mkReg(32'h40001100);  // RV32I + M-mode
    Reg#(Word) mie <- mkReg(0);               // Machine Interrupt Enable
    Reg#(Word) mtvec <- mkReg(0);             // Trap Vector Base
    Reg#(Word) mcounteren <- mkReg(0);        // Machine Counter Enable

    // Machine Trap Handling
    Reg#(Word) mepc <- mkReg(0);              // Machine Exception PC
    Reg#(Word) mcause <- mkReg(0);            // Machine Cause
    Reg#(Word) mtval <- mkReg(0);             // Machine Trap Value
    Reg#(Word) mip <- mkReg(0);               // Machine Interrupt Pending

    // Machine Counter/Timer (64-bit)
    Reg#(Bit#(64)) mcycle <- mkReg(0);         // Machine cycle count
    Reg#(Bit#(64)) mtime <- mkReg(0);         // Machine time
    Reg#(Bit#(64)) mtimecmp <- mkReg('hFFFFFFFFFFFFFFFF);      // Machine time compare (初始化为最大值，避免立即触发定时器中断)
    Reg#(Bit#(64)) minstret <- mkReg(0);      // Machine instructions retired

    // 中断信号 Wire 输入（由 SOC 每周期驱动）
    // 使用 mkDWire：默认值为 False，SOC 必须每周期驱动
    Wire#(Bool) timer_irq_wire <- mkDWire(False);      // MTIP 来源
    Wire#(Bool) software_irq_wire <- mkDWire(False);   // MSIP 来源
    Wire#(Bool) external_irq_wire <- mkDWire(False);   // MEIP 来源

    // 注意：不再使用 update_mip 规则
    // mip 寄存器只存储软件写入的部分，MTIP/MSIP/MEIP 在 readCSR 时直接从 Wire 读取

    method Word readCSR(Bit#(12) addr);
        Word value = 0;
        case (addr)
            // Machine Information Registers (read-only, return 0)
            12'hF11: value = 0;  // mvendorid
            12'hF12: value = 0;  // marchid
            12'hF13: value = 0;  // mimpid
            12'hF14: value = 0;  // mhartid

            // Machine Trap Setup
            12'h300: value = packMStatus(mstatus);  // mstatus
            12'h301: value = misa;                   // misa
            12'h304: value = mie;                     // mie
            12'h305: value = mtvec;                   // mtvec
            12'h306: value = mcounteren;             // mcounteren

            // Machine Trap Handling
            12'h341: value = mepc;      // mepc
            12'h342: value = mcause;    // mcause
            12'h343: value = mtval;     // mtval
            12'h344: begin              // mip - 直接从 Wire 读取当前值
                value = mip;
                value[11] = external_irq_wire ? 1 : 0;   // MEIP（当前值）
                value[7] = timer_irq_wire ? 1 : 0;       // MTIP（当前值）
                value[3] = software_irq_wire ? 1 : 0;    // MSIP（当前值）
            end

            // Machine Counter/Timer (lower 32 bits)
            12'hB00: value = mcycle[31:0];   // mcycle
            12'hB01: value = mtime[31:0];    // mtime
            12'hB02: value = mtimecmp[31:0]; // mtimecmp
            12'hB03: value = minstret[31:0]; // minstret

            // Machine Counter/Timer (upper 32 bits)
            12'hB80: value = mcycle[63:32];  // mcycleh
            12'hB81: value = mtime[63:32];    // mtimeh
            12'hB82: value = mtimecmp[63:32]; // mtimecmph
            12'hB83: value = minstret[63:32]; // minstreth

            // Default
            default: value = 0;
        endcase
        return value;
    endmethod

    method Action writeCSR(Bit#(12) addr, Word data);
        if (!isReadOnlyCSR(addr)) begin
            case (addr)
                // Machine Trap Setup
                12'h300: mstatus <= unpackMStatus(data);  // mstatus
                12'h304: mie <= data;                      // mie
                12'h305: begin
                    mtvec <= data;
                    // $display("[CSR] mtvec written: addr=%x, data=%x, new_mtvec=%x", addr, data, data);
                end
                12'h306: mcounteren <= data;               // mcounteren

                // Machine Trap Handling
                12'h341: mepc <= data;    // mepc
                12'h342: mcause <= data;  // mcause
                12'h343: mtval <= data;   // mtval
                // mip is updated via setMEIP/setMSIP/setMTIP

                // Machine Counter/Timer (lower 32 bits)
                12'hB00: mcycle[31:0] <= data;   // mcycle
                12'hB01: mtime[31:0] <= data;    // mtime
                12'hB02: mtimecmp[31:0] <= data; // mtimecmp
                12'hB03: minstret[31:0] <= data;  // minstret

                // Machine Counter/Timer (upper 32 bits)
                12'hB80: mcycle[63:32] <= data;   // mcycleh
                12'hB81: mtime[63:32] <= data;    // mtimeh
                12'hB82: mtimecmp[63:32] <= data;  // mtimecmph
                12'hB83: minstret[63:32] <= data;  // minstreth

                // No default action for read-only or unimplemented CSRs
                default: noAction;
            endcase
        end
    endmethod

    method PrivilegeMode currentMode();
        return priv_mode;
    endmethod

    method Action setMode(PrivilegeMode mode);
        priv_mode <= mode;
    endmethod

    // Get trap vector address
    // base = mtvec & ~3
    // if vectored mode (mtvec[1:0]==1) and is_interrupt, return base + 4*cause
    // else return base
    method Addr getTrapVector(TrapInfo trap);
        Addr base = mtvec & ~32'h3;
        Bit#(2) mode = mtvec[1:0];

        // Check if vectored mode and is an interrupt
        if (mode == 2'b01 && trap.is_interrupt) begin
            // Vectored mode: base + 4 * cause
            return base + (zeroExtend(pack(trap.cause)) << 2);
        end else begin
            // Direct mode: just base
            return base;
        end
    endmethod

    // Check if there is a pending interrupt
    // Interrupt is pending if (mie & mip) & mstatus.mie
    method Bool hasPendingInterrupt();
        // 动态构建 mip：包含 Wire 值
        Bit#(32) dynamic_mip = mip;
        dynamic_mip[11] = external_irq_wire ? 1 : 0;   // MEIP（当前值）
        dynamic_mip[7] = timer_irq_wire ? 1 : 0;       // MTIP（当前值）
        dynamic_mip[3] = software_irq_wire ? 1 : 0;    // MSIP（当前值）
        Bit#(32) enabled_interrupts = mie & dynamic_mip;
        Bool global_enable = mstatus.mie == 1;
        return (enabled_interrupts != 0) && global_enable;
    endmethod

    // Get the highest priority pending interrupt cause
    // Returns Nothing if no interrupt pending
    // Priority: MEIP(11) > MTIP(7) > MSIP(3) for M-mode
    method Maybe#(Bit#(5)) getPendingInterruptCause();
        Maybe#(Bit#(5)) result = Invalid;
        // 动态构建 mip：包含 Wire 值
        Bit#(32) dynamic_mip = mip;
        dynamic_mip[11] = external_irq_wire ? 1 : 0;   // MEIP
        dynamic_mip[7] = timer_irq_wire ? 1 : 0;       // MTIP
        dynamic_mip[3] = software_irq_wire ? 1 : 0;    // MSIP
        Bit#(32) enabled_interrupts = mie & dynamic_mip;
        Bool global_enable = mstatus.mie == 1;

        if (global_enable) begin
            if (enabled_interrupts[11] == 1) begin
                result = Valid (5'd11);  // INT_EXTERNAL_M
            end else if (enabled_interrupts[7] == 1) begin
                result = Valid (5'd7);   // INT_TIMER_M
            end else if (enabled_interrupts[3] == 1) begin
                result = Valid (5'd3);  // INT_SOFTWARE_M
            end
        end

        return result;
    endmethod

    // Wire 输入方法实现（由 SOC 每周期驱动）
    method Action timerIRQWire(Bool irq);
        timer_irq_wire <= irq;
    endmethod

    method Action softwareIRQWire(Bool irq);
        software_irq_wire <= irq;
    endmethod

    method Action externalIRQWire(Bool irq);
        external_irq_wire <= irq;
    endmethod

    method Action incrementCycle;
        mcycle <= mcycle + 1;
    endmethod

    method Action incrementMinstret;
        minstret <= minstret + 1;
    endmethod

    method Bit#(64) getMtime();
        return mtime;
    endmethod

    method Action setMtime(Bit#(64) v);
        mtime <= v;
    endmethod

    method Bit#(64) getMtimecmp();
        return mtimecmp;
    endmethod

    method Action setMtimecmp(Bit#(64) v);
        mtimecmp <= v;
    endmethod

    // 调试方法：读取关键寄存器
    method Word getMStatus();
        return packMStatus(mstatus);
    endmethod
    method Word getMIE();
        return mie;
    endmethod
    method Word getMIP();
        // 返回动态的 mip（包含 Wire 值）
        Bit#(32) dynamic_mip = mip;
        dynamic_mip[11] = external_irq_wire ? 1 : 0;
        dynamic_mip[7] = timer_irq_wire ? 1 : 0;
        dynamic_mip[3] = software_irq_wire ? 1 : 0;
        return dynamic_mip;
    endmethod
endmodule

endpackage