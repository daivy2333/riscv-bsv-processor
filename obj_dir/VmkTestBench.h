// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Primary design header
//
// This header should be included by all source files instantiating the design.
// The class here is then constructed to instantiate the design.
// See the Verilator manual for examples.

#ifndef _VMKTESTBENCH_H_
#define _VMKTESTBENCH_H_  // guard

#include "verilated_heavy.h"

//==========

class VmkTestBench__Syms;

//----------

VL_MODULE(VmkTestBench) {
  public:
    
    // PORTS
    // The application code writes and reads these signals to
    // propagate new values into/out from the Verilated model.
    VL_IN8(CLK,0,0);
    VL_IN8(RST_N,0,0);
    VL_OUT8(done,0,0);
    VL_OUT8(RDY_done,0,0);
    
    // LOCAL SIGNALS
    // Internals; generally not touched by application code
    CData/*1:0*/ mkTestBench__DOT__core_state;
    CData/*0:0*/ mkTestBench__DOT__simulationDone;
    IData/*31:0*/ mkTestBench__DOT__core_pcReg;
    IData/*31:0*/ mkTestBench__DOT__core_pcReg__024D_IN;
    IData/*31:0*/ mkTestBench__DOT__cycleCount;
    IData/*31:0*/ mkTestBench__DOT__cycleCount__024D_IN;
    
    // LOCAL VARIABLES
    // Internals; generally not touched by application code
    CData/*0:0*/ __Vclklast__TOP__CLK;
    
    // INTERNAL VARIABLES
    // Internals; generally not touched by application code
    VmkTestBench__Syms* __VlSymsp;  // Symbol table
    
    // CONSTRUCTORS
  private:
    VL_UNCOPYABLE(VmkTestBench);  ///< Copying not allowed
  public:
    /// Construct the model; called by application code
    /// The special name  may be used to make a wrapper with a
    /// single model invisible with respect to DPI scope names.
    VmkTestBench(const char* name = "TOP");
    /// Destroy the model; called (often implicitly) by application code
    ~VmkTestBench();
    
    // API METHODS
    /// Evaluate the model.  Application must call when inputs change.
    void eval() { eval_step(); }
    /// Evaluate when calling multiple units/models per time step.
    void eval_step();
    /// Evaluate at end of a timestep for tracing, when using eval_step().
    /// Application must call after all eval() and before time changes.
    void eval_end_step() {}
    /// Simulation complete, run final blocks.  Application must call on completion.
    void final();
    
    // INTERNAL METHODS
  private:
    static void _eval_initial_loop(VmkTestBench__Syms* __restrict vlSymsp);
  public:
    void __Vconfigure(VmkTestBench__Syms* symsp, bool first);
  private:
    static QData _change_request(VmkTestBench__Syms* __restrict vlSymsp);
    static QData _change_request_1(VmkTestBench__Syms* __restrict vlSymsp);
    void _ctor_var_reset() VL_ATTR_COLD;
  public:
    static void _eval(VmkTestBench__Syms* __restrict vlSymsp);
  private:
#ifdef VL_DEBUG
    void _eval_debug_assertions();
#endif  // VL_DEBUG
  public:
    static void _eval_initial(VmkTestBench__Syms* __restrict vlSymsp) VL_ATTR_COLD;
    static void _eval_settle(VmkTestBench__Syms* __restrict vlSymsp) VL_ATTR_COLD;
    static void _initial__TOP__1(VmkTestBench__Syms* __restrict vlSymsp) VL_ATTR_COLD;
    static void _sequent__TOP__2(VmkTestBench__Syms* __restrict vlSymsp);
    static void _sequent__TOP__3(VmkTestBench__Syms* __restrict vlSymsp);
    static void _settle__TOP__4(VmkTestBench__Syms* __restrict vlSymsp) VL_ATTR_COLD;
} VL_ATTR_ALIGNED(VL_CACHE_LINE_BYTES);

//----------


#endif  // guard
