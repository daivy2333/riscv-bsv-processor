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
    method Word atomicOp(Bit#(12) addr, Word rs1_val, CSROp op);
    method Word atomicOpImm(Bit#(12) addr, Bit#(5) zimm, CSROp op);
    method PrivilegeMode currentMode();
    method Action setMode(PrivilegeMode mode);
    method Addr getTrapVector(TrapInfo trap);
    method Bool hasPendingInterrupt();
    method Action setMEIP(Bool v);
    method Action setMSIP(Bool v);
    method Action setMTIP(Bool v);
    method Action incrementCycle;
    method Action incrementMinstret;
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
    return { s.sd, s._reserved23, s.tsr, s.tw, s.tvm,
             s.mxr, s.sum, s.mprv, s.xs, s.fs, s.mpp, s._reserved10,
             s._reserved9, s.spp, s.mpie, s._reserved6, s.spie,
             s.upie, s.mie, s._reserved2, s.sie, s.uie };
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
        mpp:        w[12:11],
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
    }));
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
    Reg#(Bit#(64)) mtimecmp <- mkReg(0);      // Machine time compare
    Reg#(Bit#(64)) minstret <- mkReg(0);      // Machine instructions retired

    // Interrupt pending signals from external sources
    Reg#(Bool) meip <- mkReg(False);  // Machine external interrupt pending (bit 11)
    Reg#(Bool) msip <- mkReg(False);  // Machine software interrupt pending (bit 3)
    Reg#(Bool) mtip <- mkReg(False);  // Machine timer interrupt pending (bit 7)

    // Update mip register based on interrupt signals
    rule update_mip;
        Bit#(32) new_mip = 0;
        new_mip[11] = meip ? 1 : 0;  // MEIP
        new_mip[7] = mtip ? 1 : 0;   // MTIP
        new_mip[3] = msip ? 1 : 0;   // MSIP
        mip <= new_mip;
    endrule

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
            12'h344: value = mip;       // mip

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
                12'h305: mtvec <= data;                    // mtvec
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

    // Atomic operation: read-modify-write on CSR (register version)
    method Word atomicOp(Bit#(12) addr, Word rs1_val, CSROp op);
        Word old_val = readCSR(addr);
        Word new_val = case (op)
            CSR_OP_WRITE: rs1_val;
            CSR_OP_SET:   old_val | rs1_val;
            CSR_OP_CLR:   old_val & ~rs1_val;
            CSR_OP_READ:  old_val;
            default:      old_val;
        endcase;

        // Update CSR if not read-only and not READ op
        if (op != CSR_OP_READ && !isReadOnlyCSR(addr)) begin
            writeCSR(addr, new_val);
        end

        return old_val;
    endmethod

    // Atomic operation with immediate (zimm is zero-extended to Word)
    method Word atomicOpImm(Bit#(12) addr, Bit#(5) zimm, CSROp op);
        Word rs1_val = { 27'b0, zimm };
        return atomicOp(addr, rs1_val, op);
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
            return base + (zeroExtend(trap.cause) << 2);
        end else begin
            // Direct mode: just base
            return base;
        end
    endmethod

    // Check if there is a pending interrupt
    // Interrupt is pending if (mie & mip) & mstatus.mie
    method Bool hasPendingInterrupt();
        Bit#(32) enabled_interrupts = mie & mip;
        Bool global_enable = mstatus.mie == 1;
        return (enabled_interrupts != 0) && global_enable;
    endmethod

    method Action setMEIP(Bool v);
        meip <= v;
    endmethod

    method Action setMSIP(Bool v);
        msip <= v;
    endmethod

    method Action setMTIP(Bool v);
        mtip <= v;
    endmethod

    method Action incrementCycle;
        mcycle <= mcycle + 1;
    endmethod

    method Action incrementMinstret;
        minstret <= minstret + 1;
    endmethod
endmodule

endpackage