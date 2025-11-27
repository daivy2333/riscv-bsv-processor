// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See VmkTestBench.h for the primary calling header

#include "VmkTestBench.h"
#include "VmkTestBench__Syms.h"

//==========

void VmkTestBench::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate VmkTestBench::eval\n"); );
    VmkTestBench__Syms* __restrict vlSymsp = this->__VlSymsp;  // Setup global symbol table
    VmkTestBench* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
#ifdef VL_DEBUG
    // Debug assertions
    _eval_debug_assertions();
#endif  // VL_DEBUG
    // Initialize
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) _eval_initial_loop(vlSymsp);
    // Evaluate till stable
    int __VclockLoop = 0;
    QData __Vchange = 1;
    do {
        VL_DEBUG_IF(VL_DBG_MSGF("+ Clock loop\n"););
        _eval(vlSymsp);
        if (VL_UNLIKELY(++__VclockLoop > 100)) {
            // About to fail, so enable debug to see what's not settling.
            // Note you must run make with OPT=-DVL_DEBUG for debug prints.
            int __Vsaved_debug = Verilated::debug();
            Verilated::debug(1);
            __Vchange = _change_request(vlSymsp);
            Verilated::debug(__Vsaved_debug);
            VL_FATAL_MT("build/mkTestBench.v", 31, "",
                "Verilated model didn't converge\n"
                "- See DIDNOTCONVERGE in the Verilator manual");
        } else {
            __Vchange = _change_request(vlSymsp);
        }
    } while (VL_UNLIKELY(__Vchange));
}

void VmkTestBench::_eval_initial_loop(VmkTestBench__Syms* __restrict vlSymsp) {
    vlSymsp->__Vm_didInit = true;
    _eval_initial(vlSymsp);
    // Evaluate till stable
    int __VclockLoop = 0;
    QData __Vchange = 1;
    do {
        _eval_settle(vlSymsp);
        _eval(vlSymsp);
        if (VL_UNLIKELY(++__VclockLoop > 100)) {
            // About to fail, so enable debug to see what's not settling.
            // Note you must run make with OPT=-DVL_DEBUG for debug prints.
            int __Vsaved_debug = Verilated::debug();
            Verilated::debug(1);
            __Vchange = _change_request(vlSymsp);
            Verilated::debug(__Vsaved_debug);
            VL_FATAL_MT("build/mkTestBench.v", 31, "",
                "Verilated model didn't DC converge\n"
                "- See DIDNOTCONVERGE in the Verilator manual");
        } else {
            __Vchange = _change_request(vlSymsp);
        }
    } while (VL_UNLIKELY(__Vchange));
}

VL_INLINE_OPT void VmkTestBench::_sequent__TOP__2(VmkTestBench__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VmkTestBench::_sequent__TOP__2\n"); );
    VmkTestBench* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (((0x3e8U < vlTOPp->mkTestBench__DOT__cycleCount) 
             | (0xffffffffU == vlTOPp->mkTestBench__DOT__core_pcReg))) {
            vlTOPp->mkTestBench__DOT__simulationDone = 1U;
        }
    } else {
        vlTOPp->mkTestBench__DOT__simulationDone = 0U;
    }
    vlTOPp->done = vlTOPp->mkTestBench__DOT__simulationDone;
    vlTOPp->mkTestBench__DOT__cycleCount = ((IData)(vlTOPp->RST_N)
                                             ? vlTOPp->mkTestBench__DOT__cycleCount__024D_IN
                                             : 0U);
    if (vlTOPp->RST_N) {
        if ((0U == (IData)(vlTOPp->mkTestBench__DOT__core_state))) {
            vlTOPp->mkTestBench__DOT__core_pcReg = vlTOPp->mkTestBench__DOT__core_pcReg__024D_IN;
        }
    } else {
        vlTOPp->mkTestBench__DOT__core_pcReg = 0U;
    }
    vlTOPp->mkTestBench__DOT__cycleCount__024D_IN = 
        ((IData)(1U) + vlTOPp->mkTestBench__DOT__cycleCount);
    vlTOPp->mkTestBench__DOT__core_pcReg__024D_IN = 
        ((IData)(4U) + vlTOPp->mkTestBench__DOT__core_pcReg);
    if ((1U & (~ (IData)(vlTOPp->RST_N)))) {
        vlTOPp->mkTestBench__DOT__core_state = 0U;
    }
}

VL_INLINE_OPT void VmkTestBench::_sequent__TOP__3(VmkTestBench__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VmkTestBench::_sequent__TOP__3\n"); );
    VmkTestBench* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (VL_UNLIKELY(vlTOPp->RST_N)) {
        VL_WRITEF("Cycle %0#: PC=%x\n",32,vlTOPp->mkTestBench__DOT__cycleCount,
                  32,vlTOPp->mkTestBench__DOT__core_pcReg);
    }
    if (vlTOPp->RST_N) {
        if (VL_UNLIKELY(((0x3e8U < vlTOPp->mkTestBench__DOT__cycleCount) 
                         | (0xffffffffU == vlTOPp->mkTestBench__DOT__core_pcReg)))) {
            VL_WRITEF("Simulation finished after %0# cycles\n",
                      32,vlTOPp->mkTestBench__DOT__cycleCount);
        }
    }
}

void VmkTestBench::_eval(VmkTestBench__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VmkTestBench::_eval\n"); );
    VmkTestBench* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (((IData)(vlTOPp->CLK) & (~ (IData)(vlTOPp->__Vclklast__TOP__CLK)))) {
        vlTOPp->_sequent__TOP__2(vlSymsp);
    }
    if (((~ (IData)(vlTOPp->CLK)) & (IData)(vlTOPp->__Vclklast__TOP__CLK))) {
        vlTOPp->_sequent__TOP__3(vlSymsp);
    }
    // Final
    vlTOPp->__Vclklast__TOP__CLK = vlTOPp->CLK;
}

VL_INLINE_OPT QData VmkTestBench::_change_request(VmkTestBench__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VmkTestBench::_change_request\n"); );
    VmkTestBench* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    return (vlTOPp->_change_request_1(vlSymsp));
}

VL_INLINE_OPT QData VmkTestBench::_change_request_1(VmkTestBench__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VmkTestBench::_change_request_1\n"); );
    VmkTestBench* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    // Change detection
    QData __req = false;  // Logically a bool
    return __req;
}

#ifdef VL_DEBUG
void VmkTestBench::_eval_debug_assertions() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VmkTestBench::_eval_debug_assertions\n"); );
    // Body
    if (VL_UNLIKELY((CLK & 0xfeU))) {
        Verilated::overWidthError("CLK");}
    if (VL_UNLIKELY((RST_N & 0xfeU))) {
        Verilated::overWidthError("RST_N");}
}
#endif  // VL_DEBUG
