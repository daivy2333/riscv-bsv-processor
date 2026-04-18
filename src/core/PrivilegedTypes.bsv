// src/core/PrivilegedTypes.bsv
package PrivilegedTypes;

import Types::*;

// ============================================================
// Privilege Mode
// ============================================================

typedef enum {
    U_MODE = 2'b00,    // User Mode
    S_MODE = 2'b01,    // Supervisor Mode
    M_MODE = 2'b11     // Machine Mode
} PrivilegeMode deriving (Bits, Eq, FShow);

// ============================================================
// CSR Addresses
// ============================================================

typedef enum {
    // Machine Information Registers
    MVENDORID  = 12'hF11,
    MARCHID    = 12'hF12,
    MIMPID     = 12'hF13,
    MHARTID    = 12'hF14,

    // Machine Trap Setup
    MSTATUS    = 12'h300,
    MISA       = 12'h301,
    MIE        = 12'h304,
    MTVEC      = 12'h305,

    // Machine Trap Handling
    MEPC       = 12'h341,
    MCAUSE     = 12'h342,
    MTVAL      = 12'h343,
    MIP        = 12'h344,

    // Machine Counter/Timers
    MCYCLE     = 12'hB00,
    MTIME      = 12'hB01,
    MTIMECMP   = 12'hB02,
    MINSTRET   = 12'hB03,

    // Machine Counter Enable
    MCOUNTEREN = 12'h306,

    // Supervisor Trap Setup
    SSTATUS    = 12'h100,
    SIE        = 12'h104,
    STVEC      = 12'h105,
    SEPC       = 12'h141,
    SCAUSE     = 12'h142,
    STVAL      = 12'h143,
    SATP       = 12'h180
} CSRArea deriving (Bits, Eq, FShow);

// ============================================================
// Exception Codes
// ============================================================

typedef enum {
    EXC_INST_MISALIGNED     = 0,     // Instruction address misaligned
    EXC_INST_ACCESS_FAULT   = 1,     // Instruction access fault
    EXC_ILLEGAL_INST        = 2,     // Illegal instruction
    EXC_BREAKPOINT          = 3,     // Breakpoint
    EXC_LOAD_MISALIGNED     = 4,     // Load address misaligned
    EXC_LOAD_ACCESS_FAULT  = 5,     // Load access fault
    EXC_STORE_MISALIGNED   = 6,     // Store/AMO address misaligned
    EXC_STORE_ACCESS_FAULT  = 7,     // Store/AMO access fault
    EXC_ECALL_U             = 8,     // Environment call from U-mode
    EXC_ECALL_S             = 9,     // Environment call from S-mode
    EXC_ECALL_M             = 11,    // Environment call from M-mode
    EXC_INST_PAGE_FAULT     = 12,    // Instruction page fault
    EXC_LOAD_PAGE_FAULT     = 13,    // Load page fault
    EXC_STORE_PAGE_FAULT    = 15     // Store/AMO page fault
} ExceptionCode deriving (Bits, Eq, FShow);

// ============================================================
// Interrupt Codes
// ============================================================

typedef enum {
    INT_SOFTWARE_S  = 1,    // Supervisor software interrupt
    INT_SOFTWARE_M  = 3,    // Machine software interrupt
    INT_TIMER_S     = 5,    // Supervisor timer interrupt
    INT_TIMER_M     = 7,    // Machine timer interrupt
    INT_EXTERNAL_S  = 9,    // Supervisor external interrupt
    INT_EXTERNAL_M  = 11    // Machine external interrupt
} InterruptCode deriving (Bits, Eq, FShow);

// ============================================================
// Trap Information
// ============================================================

typedef struct {
    Addr            epc;            // Exception program counter
    ExceptionCode   cause;          // Exception cause
    Bool            is_interrupt;   // True if interrupt, False if exception
    Addr            tval;           // Trap value (faulting address or instruction)
    PrivilegeMode   mode;           // Privilege mode at time of trap
} TrapInfo deriving (Bits, Eq, FShow);

// ============================================================
// CSR Operation
// ============================================================

typedef enum {
    CSR_OP_CLR,     // Clear bits in CSR (write with ~src & CSR)
    CSR_OP_SET,     // Set bits in CSR (write with src | CSR)
    CSR_OP_WRITE,   // Write value to CSR directly
    CSR_OP_READ     // Read value from CSR (no write)
} CSROp deriving (Bits, Eq, FShow);

// ============================================================
// MStatus Register (Machine Status Register)
// Per RISC-V Specification - bit positions
// ============================================================

typedef struct {
    Bit#(1) uie;        // 0: User Interrupt Enable
    Bit#(1) sie;        // 1: Supervisor Interrupt Enable
    Bit#(1) _reserved2; // 2: Reserved
    Bit#(1) mie;        // 3: Machine Interrupt Enable (CRITICAL: bit 3, NOT 4!)
    Bit#(1) upie;      // 4: User Previous Interrupt Enable
    Bit#(1) spie;      // 5: Supervisor Previous Interrupt Enable
    Bit#(1) _reserved6; // 6: Reserved
    Bit#(1) mpie;      // 7: Machine Previous Interrupt Enable
    Bit#(1) spp;       // 8: Supervisor Previous Privilege mode (1 bit)
    Bit#(1) _reserved9;  // 9: Reserved
    Bit#(1) _reserved10; // 10: Reserved
    Bit#(2) mpp;       // 11:10: Machine Previous Privilege mode (2 bits)
    Bit#(3) fs;        // 14:12: Floating-point Status (3 bits)
    Bit#(2) xs;        // 16:15: Additional State Status (2 bits)
    Bit#(1) mprv;      // 17: Modify Privilege bit
    Bit#(1) sum;       // 18: Supervisor User Memory Access
    Bit#(1) mxr;       // 19: Make Executable Readable
    Bit#(1) tvm;       // 20: Trap Virtual Memory
    Bit#(1) tw;        // 21: Timeout Wait
    Bit#(1) tsr;       // 22: Trap SRET
    Bit#(8) _reserved23; // 30:23: Reserved
    Bit#(1) sd;        // 31: Summary Dirty (read-only)
} MStatus deriving (Bits, Eq, FShow);

endpackage