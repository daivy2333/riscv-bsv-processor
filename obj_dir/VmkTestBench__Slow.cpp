// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See VmkTestBench.h for the primary calling header

#include "VmkTestBench.h"
#include "VmkTestBench__Syms.h"

//==========

VL_CTOR_IMP(VmkTestBench) {
    VmkTestBench__Syms* __restrict vlSymsp = __VlSymsp = new VmkTestBench__Syms(this, name());
    VmkTestBench* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Reset internal values
    
    // Reset structure values
    _ctor_var_reset();
}

void VmkTestBench::__Vconfigure(VmkTestBench__Syms* vlSymsp, bool first) {
    if (false && first) {}  // Prevent unused
    this->__VlSymsp = vlSymsp;
    if (false && this->__VlSymsp) {}  // Prevent unused
    Verilated::timeunit(-12);
    Verilated::timeprecision(-12);
}

VmkTestBench::~VmkTestBench() {
    VL_DO_CLEAR(delete __VlSymsp, __VlSymsp = NULL);
}

void VmkTestBench::_initial__TOP__1(VmkTestBench__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VmkTestBench::_initial__TOP__1\n"); );
    VmkTestBench* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->RDY_done = 1U;
    vlTOPp->mkTestBench__DOT__core_pcReg = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__core_state = 2U;
    vlTOPp->mkTestBench__DOT__cycleCount = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__simulationDone = 0U;
}

void VmkTestBench::_settle__TOP__4(VmkTestBench__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VmkTestBench::_settle__TOP__4\n"); );
    VmkTestBench* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkTestBench__DOT__core_pcReg__024D_IN = 
        ((IData)(4U) + vlTOPp->mkTestBench__DOT__core_pcReg);
    vlTOPp->mkTestBench__DOT__cycleCount__024D_IN = 
        ((IData)(1U) + vlTOPp->mkTestBench__DOT__cycleCount);
    vlTOPp->done = vlTOPp->mkTestBench__DOT__simulationDone;
}

void VmkTestBench::_eval_initial(VmkTestBench__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VmkTestBench::_eval_initial\n"); );
    VmkTestBench* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->_initial__TOP__1(vlSymsp);
    vlTOPp->__Vclklast__TOP__CLK = vlTOPp->CLK;
}

void VmkTestBench::final() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VmkTestBench::final\n"); );
    // Variables
    VmkTestBench__Syms* __restrict vlSymsp = this->__VlSymsp;
    VmkTestBench* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
}

void VmkTestBench::_eval_settle(VmkTestBench__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VmkTestBench::_eval_settle\n"); );
    VmkTestBench* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->_settle__TOP__4(vlSymsp);
}

void VmkTestBench::_ctor_var_reset() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VmkTestBench::_ctor_var_reset\n"); );
    // Body
    CLK = VL_RAND_RESET_I(1);
    RST_N = VL_RAND_RESET_I(1);
    done = VL_RAND_RESET_I(1);
    RDY_done = VL_RAND_RESET_I(1);
    mkTestBench__DOT__core_pcReg = VL_RAND_RESET_I(32);
    mkTestBench__DOT__core_pcReg__024D_IN = VL_RAND_RESET_I(32);
    mkTestBench__DOT__core_state = VL_RAND_RESET_I(2);
    mkTestBench__DOT__cycleCount = VL_RAND_RESET_I(32);
    mkTestBench__DOT__cycleCount__024D_IN = VL_RAND_RESET_I(32);
    mkTestBench__DOT__simulationDone = VL_RAND_RESET_I(1);
}
