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
    vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[0U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[2U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[3U] = 2U;
    vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data1_reg[0U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data1_reg[1U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data1_reg[2U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data1_reg[3U] = 2U;
    vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__empty_reg = 0U;
    vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__full_reg = 1U;
    vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[0U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[1U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[2U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[3U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[4U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[5U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[6U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[7U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[9U] = 0xaaU;
    vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data1_reg[0U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data1_reg[1U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data1_reg[2U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data1_reg[3U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data1_reg[4U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data1_reg[5U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data1_reg[6U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data1_reg[7U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data1_reg[8U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data1_reg[9U] = 0xaaU;
    vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__empty_reg = 0U;
    vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__full_reg = 1U;
    vlTOPp->mkTestBench__DOT__soc_core_mem2wb__DOT__data0_reg[0U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_mem2wb__DOT__data0_reg[1U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_mem2wb__DOT__data0_reg[2U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_mem2wb__DOT__data0_reg[3U] = 0x2aU;
    vlTOPp->mkTestBench__DOT__soc_core_mem2wb__DOT__data1_reg[0U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_mem2wb__DOT__data1_reg[1U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_mem2wb__DOT__data1_reg[2U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_mem2wb__DOT__data1_reg[3U] = 0x2aU;
    vlTOPp->mkTestBench__DOT__soc_core_mem2wb__DOT__empty_reg = 0U;
    vlTOPp->mkTestBench__DOT__soc_core_mem2wb__DOT__full_reg = 1U;
    vlTOPp->mkTestBench__DOT__cycleCount = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__dumpDone = 0U;
    vlTOPp->mkTestBench__DOT__programDone = 0U;
    vlTOPp->mkTestBench__DOT__programLoaded = 0U;
    vlTOPp->mkTestBench__DOT__soc_clint_msip = 0U;
    vlTOPp->mkTestBench__DOT__soc_clint_mtime = 0xaaaaaaaaaaaaaaaaULL;
    vlTOPp->mkTestBench__DOT__soc_clint_mtimecmp = 0xaaaaaaaaaaaaaaaaULL;
    vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_0 = 2U;
    vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_1 = 2U;
    vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_10 = 2U;
    vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_11 = 2U;
    vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_12 = 2U;
    vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_13 = 2U;
    vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_14 = 2U;
    vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_15 = 2U;
    vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_16 = 2U;
    vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_17 = 2U;
    vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_18 = 2U;
    vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_19 = 2U;
    vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_2 = 2U;
    vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_20 = 2U;
    vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_21 = 2U;
    vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_22 = 2U;
    vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_23 = 2U;
    vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_24 = 2U;
    vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_25 = 2U;
    vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_26 = 2U;
    vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_27 = 2U;
    vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_28 = 2U;
    vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_29 = 2U;
    vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_3 = 2U;
    vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_30 = 2U;
    vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_31 = 2U;
    vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_32 = 2U;
    vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_33 = 2U;
    vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_34 = 2U;
    vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_35 = 2U;
    vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_36 = 2U;
    vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_37 = 2U;
    vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_38 = 2U;
    vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_39 = 2U;
    vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_4 = 2U;
    vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_40 = 2U;
    vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_41 = 2U;
    vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_42 = 2U;
    vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_43 = 2U;
    vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_44 = 2U;
    vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_45 = 2U;
    vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_46 = 2U;
    vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_47 = 2U;
    vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_48 = 2U;
    vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_49 = 2U;
    vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_5 = 2U;
    vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_50 = 2U;
    vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_51 = 2U;
    vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_52 = 2U;
    vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_53 = 2U;
    vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_54 = 2U;
    vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_55 = 2U;
    vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_56 = 2U;
    vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_57 = 2U;
    vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_58 = 2U;
    vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_59 = 2U;
    vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_6 = 2U;
    vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_60 = 2U;
    vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_61 = 2U;
    vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_62 = 2U;
    vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_63 = 2U;
    vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_7 = 2U;
    vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_8 = 2U;
    vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_9 = 2U;
    vlTOPp->mkTestBench__DOT__soc_core_branch_flush = 0U;
    vlTOPp->mkTestBench__DOT__soc_core_branch_flush_done = 0U;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_0[0U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_0[1U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_0[2U] = 0U;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_1[0U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_1[1U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_1[2U] = 0U;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_10[0U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_10[1U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_10[2U] = 0U;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_11[0U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_11[1U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_11[2U] = 0U;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_12[0U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_12[1U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_12[2U] = 0U;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_13[0U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_13[1U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_13[2U] = 0U;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_14[0U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_14[1U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_14[2U] = 0U;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_15[0U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_15[1U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_15[2U] = 0U;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_16[0U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_16[1U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_16[2U] = 0U;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_17[0U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_17[1U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_17[2U] = 0U;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_18[0U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_18[1U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_18[2U] = 0U;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_19[0U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_19[1U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_19[2U] = 0U;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_2[0U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_2[1U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_2[2U] = 0U;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_20[0U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_20[1U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_20[2U] = 0U;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_21[0U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_21[1U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_21[2U] = 0U;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_22[0U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_22[1U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_22[2U] = 0U;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_23[0U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_23[1U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_23[2U] = 0U;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_24[0U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_24[1U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_24[2U] = 0U;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_25[0U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_25[1U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_25[2U] = 0U;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_26[0U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_26[1U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_26[2U] = 0U;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_27[0U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_27[1U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_27[2U] = 0U;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_28[0U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_28[1U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_28[2U] = 0U;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_29[0U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_29[1U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_29[2U] = 0U;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_3[0U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_3[1U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_3[2U] = 0U;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_30[0U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_30[1U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_30[2U] = 0U;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_31[0U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_31[1U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_31[2U] = 0U;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_32[0U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_32[1U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_32[2U] = 0U;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_33[0U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_33[1U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_33[2U] = 0U;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_34[0U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_34[1U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_34[2U] = 0U;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_35[0U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_35[1U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_35[2U] = 0U;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_36[0U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_36[1U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_36[2U] = 0U;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_37[0U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_37[1U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_37[2U] = 0U;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_38[0U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_38[1U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_38[2U] = 0U;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_39[0U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_39[1U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_39[2U] = 0U;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_4[0U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_4[1U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_4[2U] = 0U;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_40[0U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_40[1U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_40[2U] = 0U;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_41[0U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_41[1U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_41[2U] = 0U;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_42[0U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_42[1U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_42[2U] = 0U;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_43[0U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_43[1U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_43[2U] = 0U;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_44[0U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_44[1U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_44[2U] = 0U;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_45[0U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_45[1U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_45[2U] = 0U;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_46[0U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_46[1U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_46[2U] = 0U;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_47[0U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_47[1U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_47[2U] = 0U;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_48[0U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_48[1U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_48[2U] = 0U;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_49[0U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_49[1U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_49[2U] = 0U;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_5[0U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_5[1U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_5[2U] = 0U;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_50[0U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_50[1U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_50[2U] = 0U;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_51[0U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_51[1U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_51[2U] = 0U;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_52[0U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_52[1U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_52[2U] = 0U;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_53[0U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_53[1U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_53[2U] = 0U;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_54[0U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_54[1U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_54[2U] = 0U;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_55[0U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_55[1U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_55[2U] = 0U;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_56[0U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_56[1U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_56[2U] = 0U;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_57[0U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_57[1U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_57[2U] = 0U;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_58[0U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_58[1U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_58[2U] = 0U;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_59[0U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_59[1U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_59[2U] = 0U;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_6[0U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_6[1U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_6[2U] = 0U;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_60[0U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_60[1U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_60[2U] = 0U;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_61[0U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_61[1U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_61[2U] = 0U;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_62[0U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_62[1U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_62[2U] = 0U;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_63[0U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_63[1U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_63[2U] = 0U;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_7[0U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_7[1U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_7[2U] = 0U;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_8[0U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_8[1U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_8[2U] = 0U;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_9[0U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_9[1U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_9[2U] = 0U;
    vlTOPp->mkTestBench__DOT__soc_core_csrs_mcause = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_csrs_mcounteren = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_csrs_mcycle = 0xaaaaaaaaaaaaaaaaULL;
    vlTOPp->mkTestBench__DOT__soc_core_csrs_meip = 0U;
    vlTOPp->mkTestBench__DOT__soc_core_csrs_mepc = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_csrs_mie = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_csrs_minstret = 0xaaaaaaaaaaaaaaaaULL;
    vlTOPp->mkTestBench__DOT__soc_core_csrs_mip = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_csrs_misa = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_csrs_msip = 0U;
    vlTOPp->mkTestBench__DOT__soc_core_csrs_mstatus = 0xaaaaaaaaULL;
    vlTOPp->mkTestBench__DOT__soc_core_csrs_mtime = 0xaaaaaaaaaaaaaaaaULL;
    vlTOPp->mkTestBench__DOT__soc_core_csrs_mtimecmp = 0xaaaaaaaaaaaaaaaaULL;
    vlTOPp->mkTestBench__DOT__soc_core_csrs_mtip = 0U;
    vlTOPp->mkTestBench__DOT__soc_core_csrs_mtval = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_csrs_mtvec = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_csrs_priv_mode = 2U;
    vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[0U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[2U] = 0x2aU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_0 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_1 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_10 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_100 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_1000 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_1001 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_1002 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_1003 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_1004 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_1005 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_1006 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_1007 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_1008 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_1009 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_101 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_1010 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_1011 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_1012 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_1013 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_1014 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_1015 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_1016 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_1017 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_1018 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_1019 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_102 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_1020 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_1021 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_1022 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_1023 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_103 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_104 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_105 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_106 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_107 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_108 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_109 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_11 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_110 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_111 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_112 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_113 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_114 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_115 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_116 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_117 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_118 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_119 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_12 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_120 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_121 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_122 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_123 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_124 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_125 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_126 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_127 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_128 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_129 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_13 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_130 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_131 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_132 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_133 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_134 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_135 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_136 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_137 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_138 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_139 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_14 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_140 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_141 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_142 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_143 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_144 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_145 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_146 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_147 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_148 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_149 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_15 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_150 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_151 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_152 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_153 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_154 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_155 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_156 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_157 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_158 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_159 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_16 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_160 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_161 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_162 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_163 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_164 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_165 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_166 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_167 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_168 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_169 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_17 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_170 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_171 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_172 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_173 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_174 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_175 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_176 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_177 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_178 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_179 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_18 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_180 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_181 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_182 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_183 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_184 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_185 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_186 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_187 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_188 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_189 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_19 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_190 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_191 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_192 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_193 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_194 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_195 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_196 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_197 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_198 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_199 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_2 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_20 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_200 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_201 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_202 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_203 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_204 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_205 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_206 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_207 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_208 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_209 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_21 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_210 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_211 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_212 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_213 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_214 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_215 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_216 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_217 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_218 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_219 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_22 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_220 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_221 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_222 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_223 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_224 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_225 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_226 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_227 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_228 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_229 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_23 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_230 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_231 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_232 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_233 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_234 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_235 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_236 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_237 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_238 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_239 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_24 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_240 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_241 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_242 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_243 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_244 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_245 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_246 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_247 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_248 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_249 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_25 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_250 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_251 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_252 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_253 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_254 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_255 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_256 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_257 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_258 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_259 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_26 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_260 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_261 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_262 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_263 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_264 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_265 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_266 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_267 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_268 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_269 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_27 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_270 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_271 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_272 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_273 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_274 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_275 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_276 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_277 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_278 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_279 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_28 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_280 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_281 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_282 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_283 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_284 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_285 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_286 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_287 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_288 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_289 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_29 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_290 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_291 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_292 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_293 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_294 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_295 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_296 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_297 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_298 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_299 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_3 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_30 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_300 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_301 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_302 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_303 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_304 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_305 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_306 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_307 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_308 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_309 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_31 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_310 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_311 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_312 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_313 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_314 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_315 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_316 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_317 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_318 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_319 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_32 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_320 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_321 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_322 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_323 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_324 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_325 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_326 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_327 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_328 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_329 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_33 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_330 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_331 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_332 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_333 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_334 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_335 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_336 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_337 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_338 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_339 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_34 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_340 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_341 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_342 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_343 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_344 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_345 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_346 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_347 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_348 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_349 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_35 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_350 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_351 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_352 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_353 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_354 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_355 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_356 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_357 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_358 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_359 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_36 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_360 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_361 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_362 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_363 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_364 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_365 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_366 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_367 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_368 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_369 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_37 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_370 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_371 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_372 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_373 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_374 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_375 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_376 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_377 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_378 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_379 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_38 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_380 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_381 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_382 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_383 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_384 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_385 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_386 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_387 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_388 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_389 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_39 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_390 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_391 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_392 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_393 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_394 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_395 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_396 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_397 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_398 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_399 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_4 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_40 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_400 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_401 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_402 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_403 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_404 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_405 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_406 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_407 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_408 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_409 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_41 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_410 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_411 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_412 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_413 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_414 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_415 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_416 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_417 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_418 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_419 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_42 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_420 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_421 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_422 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_423 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_424 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_425 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_426 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_427 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_428 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_429 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_43 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_430 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_431 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_432 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_433 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_434 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_435 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_436 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_437 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_438 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_439 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_44 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_440 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_441 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_442 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_443 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_444 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_445 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_446 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_447 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_448 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_449 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_45 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_450 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_451 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_452 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_453 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_454 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_455 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_456 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_457 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_458 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_459 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_46 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_460 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_461 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_462 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_463 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_464 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_465 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_466 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_467 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_468 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_469 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_47 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_470 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_471 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_472 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_473 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_474 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_475 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_476 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_477 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_478 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_479 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_48 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_480 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_481 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_482 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_483 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_484 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_485 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_486 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_487 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_488 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_489 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_49 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_490 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_491 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_492 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_493 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_494 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_495 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_496 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_497 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_498 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_499 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_5 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_50 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_500 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_501 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_502 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_503 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_504 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_505 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_506 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_507 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_508 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_509 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_51 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_510 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_511 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_512 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_513 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_514 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_515 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_516 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_517 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_518 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_519 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_52 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_520 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_521 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_522 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_523 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_524 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_525 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_526 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_527 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_528 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_529 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_53 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_530 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_531 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_532 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_533 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_534 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_535 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_536 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_537 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_538 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_539 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_54 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_540 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_541 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_542 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_543 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_544 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_545 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_546 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_547 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_548 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_549 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_55 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_550 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_551 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_552 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_553 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_554 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_555 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_556 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_557 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_558 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_559 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_56 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_560 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_561 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_562 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_563 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_564 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_565 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_566 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_567 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_568 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_569 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_57 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_570 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_571 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_572 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_573 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_574 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_575 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_576 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_577 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_578 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_579 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_58 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_580 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_581 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_582 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_583 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_584 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_585 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_586 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_587 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_588 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_589 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_59 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_590 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_591 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_592 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_593 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_594 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_595 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_596 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_597 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_598 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_599 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_6 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_60 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_600 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_601 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_602 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_603 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_604 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_605 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_606 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_607 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_608 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_609 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_61 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_610 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_611 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_612 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_613 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_614 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_615 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_616 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_617 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_618 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_619 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_62 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_620 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_621 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_622 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_623 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_624 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_625 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_626 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_627 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_628 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_629 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_63 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_630 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_631 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_632 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_633 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_634 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_635 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_636 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_637 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_638 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_639 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_64 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_640 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_641 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_642 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_643 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_644 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_645 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_646 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_647 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_648 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_649 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_65 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_650 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_651 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_652 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_653 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_654 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_655 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_656 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_657 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_658 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_659 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_66 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_660 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_661 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_662 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_663 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_664 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_665 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_666 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_667 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_668 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_669 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_67 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_670 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_671 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_672 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_673 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_674 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_675 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_676 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_677 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_678 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_679 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_68 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_680 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_681 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_682 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_683 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_684 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_685 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_686 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_687 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_688 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_689 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_69 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_690 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_691 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_692 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_693 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_694 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_695 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_696 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_697 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_698 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_699 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_7 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_70 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_700 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_701 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_702 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_703 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_704 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_705 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_706 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_707 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_708 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_709 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_71 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_710 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_711 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_712 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_713 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_714 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_715 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_716 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_717 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_718 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_719 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_72 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_720 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_721 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_722 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_723 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_724 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_725 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_726 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_727 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_728 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_729 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_73 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_730 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_731 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_732 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_733 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_734 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_735 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_736 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_737 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_738 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_739 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_74 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_740 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_741 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_742 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_743 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_744 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_745 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_746 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_747 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_748 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_749 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_75 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_750 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_751 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_752 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_753 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_754 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_755 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_756 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_757 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_758 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_759 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_76 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_760 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_761 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_762 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_763 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_764 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_765 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_766 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_767 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_768 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_769 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_77 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_770 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_771 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_772 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_773 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_774 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_775 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_776 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_777 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_778 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_779 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_78 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_780 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_781 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_782 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_783 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_784 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_785 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_786 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_787 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_788 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_789 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_79 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_790 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_791 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_792 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_793 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_794 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_795 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_796 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_797 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_798 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_799 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_8 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_80 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_800 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_801 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_802 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_803 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_804 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_805 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_806 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_807 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_808 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_809 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_81 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_810 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_811 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_812 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_813 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_814 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_815 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_816 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_817 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_818 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_819 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_82 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_820 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_821 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_822 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_823 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_824 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_825 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_826 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_827 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_828 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_829 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_83 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_830 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_831 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_832 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_833 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_834 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_835 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_836 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_837 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_838 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_839 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_84 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_840 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_841 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_842 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_843 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_844 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_845 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_846 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_847 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_848 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_849 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_85 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_850 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_851 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_852 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_853 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_854 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_855 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_856 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_857 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_858 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_859 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_86 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_860 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_861 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_862 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_863 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_864 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_865 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_866 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_867 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_868 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_869 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_87 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_870 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_871 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_872 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_873 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_874 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_875 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_876 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_877 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_878 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_879 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_88 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_880 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_881 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_882 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_883 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_884 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_885 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_886 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_887 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_888 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_889 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_89 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_890 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_891 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_892 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_893 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_894 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_895 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_896 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_897 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_898 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_899 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_9 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_90 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_900 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_901 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_902 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_903 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_904 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_905 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_906 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_907 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_908 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_909 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_91 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_910 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_911 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_912 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_913 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_914 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_915 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_916 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_917 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_918 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_919 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_92 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_920 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_921 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_922 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_923 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_924 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_925 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_926 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_927 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_928 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_929 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_93 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_930 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_931 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_932 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_933 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_934 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_935 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_936 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_937 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_938 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_939 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_94 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_940 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_941 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_942 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_943 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_944 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_945 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_946 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_947 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_948 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_949 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_95 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_950 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_951 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_952 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_953 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_954 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_955 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_956 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_957 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_958 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_959 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_96 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_960 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_961 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_962 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_963 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_964 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_965 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_966 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_967 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_968 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_969 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_97 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_970 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_971 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_972 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_973 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_974 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_975 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_976 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_977 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_978 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_979 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_98 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_980 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_981 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_982 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_983 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_984 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_985 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_986 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_987 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_988 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_989 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_99 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_990 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_991 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_992 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_993 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_994 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_995 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_996 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_997 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_998 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_imem_999 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_mem_resp_pending = 0U;
    vlTOPp->mkTestBench__DOT__soc_core_no_pc_update = 0U;
    vlTOPp->mkTestBench__DOT__soc_core_pcReg = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_pending_mem_resp = 0xaaaaaaaaULL;
    vlTOPp->mkTestBench__DOT__soc_core_programLoaded = 0U;
    vlTOPp->mkTestBench__DOT__soc_core_regFile_registers_1 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_regFile_registers_10 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_regFile_registers_11 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_regFile_registers_12 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_regFile_registers_13 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_regFile_registers_14 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_regFile_registers_15 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_regFile_registers_16 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_regFile_registers_17 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_regFile_registers_18 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_regFile_registers_19 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_regFile_registers_2 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_regFile_registers_20 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_regFile_registers_21 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_regFile_registers_22 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_regFile_registers_23 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_regFile_registers_24 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_regFile_registers_25 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_regFile_registers_26 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_regFile_registers_27 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_regFile_registers_28 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_regFile_registers_29 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_regFile_registers_3 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_regFile_registers_30 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_regFile_registers_31 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_regFile_registers_4 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_regFile_registers_5 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_regFile_registers_6 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_regFile_registers_7 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_regFile_registers_8 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_regFile_registers_9 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_stall_count = 2U;
    vlTOPp->mkTestBench__DOT__soc_core_stall_load_use = 0U;
    vlTOPp->mkTestBench__DOT__soc_core_state = 2U;
    vlTOPp->mkTestBench__DOT__soc_core_wb_forward_data0 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_wb_forward_data1 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_wb_forward_rd0 = 0xaU;
    vlTOPp->mkTestBench__DOT__soc_core_wb_forward_rd1 = 0xaU;
    vlTOPp->mkTestBench__DOT__soc_core_wb_forward_valid0 = 0U;
    vlTOPp->mkTestBench__DOT__soc_core_wb_forward_valid1 = 0U;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_0 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_1 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_10 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_100 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_101 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_102 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_103 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_104 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_105 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_106 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_107 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_108 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_109 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_11 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_110 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_111 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_112 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_113 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_114 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_115 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_116 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_117 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_118 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_119 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_12 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_120 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_121 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_122 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_123 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_124 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_125 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_126 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_127 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_128 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_129 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_13 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_130 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_131 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_132 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_133 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_134 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_135 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_136 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_137 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_138 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_139 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_14 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_140 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_141 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_142 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_143 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_144 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_145 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_146 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_147 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_148 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_149 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_15 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_150 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_151 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_152 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_153 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_154 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_155 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_156 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_157 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_158 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_159 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_16 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_160 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_161 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_162 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_163 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_164 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_165 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_166 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_167 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_168 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_169 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_17 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_170 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_171 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_172 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_173 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_174 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_175 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_176 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_177 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_178 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_179 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_18 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_180 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_181 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_182 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_183 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_184 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_185 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_186 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_187 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_188 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_189 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_19 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_190 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_191 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_192 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_193 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_194 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_195 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_196 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_197 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_198 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_199 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_2 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_20 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_200 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_201 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_202 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_203 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_204 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_205 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_206 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_207 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_208 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_209 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_21 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_210 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_211 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_212 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_213 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_214 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_215 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_216 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_217 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_218 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_219 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_22 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_220 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_221 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_222 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_223 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_224 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_225 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_226 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_227 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_228 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_229 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_23 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_230 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_231 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_232 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_233 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_234 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_235 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_236 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_237 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_238 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_239 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_24 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_240 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_241 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_242 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_243 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_244 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_245 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_246 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_247 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_248 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_249 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_25 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_250 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_251 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_252 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_253 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_254 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_255 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_256 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_257 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_258 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_259 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_26 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_260 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_261 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_262 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_263 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_264 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_265 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_266 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_267 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_268 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_269 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_27 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_270 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_271 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_272 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_273 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_274 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_275 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_276 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_277 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_278 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_279 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_28 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_280 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_281 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_282 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_283 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_284 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_285 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_286 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_287 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_288 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_289 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_29 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_290 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_291 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_292 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_293 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_294 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_295 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_296 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_297 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_298 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_299 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_3 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_30 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_300 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_301 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_302 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_303 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_304 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_305 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_306 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_307 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_308 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_309 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_31 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_310 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_311 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_312 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_313 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_314 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_315 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_316 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_317 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_318 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_319 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_32 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_320 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_321 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_322 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_323 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_324 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_325 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_326 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_327 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_328 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_329 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_33 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_330 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_331 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_332 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_333 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_334 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_335 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_336 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_337 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_338 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_339 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_34 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_340 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_341 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_342 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_343 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_344 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_345 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_346 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_347 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_348 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_349 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_35 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_350 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_351 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_352 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_353 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_354 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_355 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_356 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_357 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_358 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_359 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_36 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_360 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_361 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_362 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_363 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_364 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_365 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_366 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_367 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_368 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_369 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_37 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_370 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_371 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_372 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_373 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_374 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_375 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_376 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_377 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_378 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_379 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_38 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_380 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_381 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_382 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_383 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_384 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_385 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_386 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_387 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_388 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_389 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_39 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_390 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_391 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_392 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_393 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_394 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_395 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_396 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_397 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_398 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_399 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_4 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_40 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_400 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_401 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_402 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_403 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_404 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_405 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_406 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_407 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_408 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_409 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_41 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_410 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_411 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_412 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_413 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_414 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_415 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_416 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_417 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_418 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_419 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_42 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_420 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_421 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_422 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_423 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_424 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_425 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_426 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_427 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_428 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_429 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_43 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_430 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_431 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_432 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_433 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_434 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_435 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_436 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_437 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_438 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_439 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_44 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_440 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_441 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_442 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_443 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_444 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_445 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_446 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_447 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_448 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_449 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_45 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_450 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_451 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_452 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_453 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_454 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_455 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_456 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_457 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_458 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_459 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_46 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_460 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_461 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_462 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_463 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_464 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_465 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_466 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_467 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_468 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_469 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_47 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_470 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_471 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_472 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_473 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_474 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_475 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_476 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_477 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_478 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_479 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_48 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_480 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_481 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_482 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_483 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_484 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_485 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_486 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_487 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_488 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_489 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_49 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_490 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_491 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_492 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_493 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_494 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_495 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_496 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_497 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_498 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_499 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_5 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_50 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_500 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_501 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_502 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_503 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_504 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_505 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_506 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_507 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_508 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_509 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_51 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_510 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_511 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_52 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_53 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_54 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_55 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_56 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_57 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_58 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_59 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_6 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_60 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_61 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_62 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_63 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_64 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_65 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_66 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_67 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_68 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_69 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_7 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_70 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_71 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_72 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_73 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_74 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_75 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_76 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_77 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_78 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_79 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_8 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_80 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_81 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_82 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_83 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_84 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_85 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_86 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_87 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_88 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_89 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_9 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_90 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_91 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_92 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_93 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_94 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_95 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_96 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_97 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_98 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_memory_99 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_tohost_value = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_dmem_tohost_written = 0U;
    vlTOPp->mkTestBench__DOT__soc_mem_resp_reg = 0xaaaaaaaaULL;
    vlTOPp->mkTestBench__DOT__soc_plic_enable_bits = 0xaaU;
    vlTOPp->mkTestBench__DOT__soc_plic_irq_pending_1 = 0U;
    vlTOPp->mkTestBench__DOT__soc_plic_irq_pending_2 = 0U;
    vlTOPp->mkTestBench__DOT__soc_plic_irq_pending_3 = 0U;
    vlTOPp->mkTestBench__DOT__soc_plic_irq_pending_4 = 0U;
    vlTOPp->mkTestBench__DOT__soc_plic_irq_pending_5 = 0U;
    vlTOPp->mkTestBench__DOT__soc_plic_irq_pending_6 = 0U;
    vlTOPp->mkTestBench__DOT__soc_plic_irq_pending_7 = 0U;
    vlTOPp->mkTestBench__DOT__soc_plic_irq_priority_0 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_plic_irq_priority_1 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_plic_irq_priority_2 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_plic_irq_priority_3 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_plic_irq_priority_4 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_plic_irq_priority_5 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_plic_irq_priority_6 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_plic_irq_priority_7 = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_plic_threshold = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_resp_ready = 0U;
    vlTOPp->mkTestBench__DOT__soc_uart_ie = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_uart_ip = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_uart_rx_enable = 0U;
    vlTOPp->mkTestBench__DOT__soc_uart_rx_valid = 0U;
    vlTOPp->mkTestBench__DOT__soc_uart_rxdata = 0xaaU;
    vlTOPp->mkTestBench__DOT__soc_uart_tx_enable = 0U;
    vlTOPp->mkTestBench__DOT__soc_uart_tx_full = 0U;
    vlTOPp->mkTestBench__DOT__soc_core_ex2mem__DOT__data0_reg[0U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_ex2mem__DOT__data0_reg[1U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_ex2mem__DOT__data0_reg[2U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_ex2mem__DOT__data0_reg[3U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_ex2mem__DOT__data0_reg[4U] = 0xaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_ex2mem__DOT__data1_reg[0U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_ex2mem__DOT__data1_reg[1U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_ex2mem__DOT__data1_reg[2U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_ex2mem__DOT__data1_reg[3U] = 0xaaaaaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_ex2mem__DOT__data1_reg[4U] = 0xaaaaU;
    vlTOPp->mkTestBench__DOT__soc_core_ex2mem__DOT__empty_reg = 0U;
    vlTOPp->mkTestBench__DOT__soc_core_ex2mem__DOT__full_reg = 1U;
}

void VmkTestBench::_settle__TOP__7(VmkTestBench__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VmkTestBench::_settle__TOP__7\n"); );
    VmkTestBench* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Variables
    WData/*95:0*/ __Vtemp75[3];
    WData/*95:0*/ __Vtemp76[3];
    WData/*127:0*/ __Vtemp78[4];
    WData/*127:0*/ __Vtemp80[4];
    WData/*127:0*/ __Vtemp81[4];
    WData/*127:0*/ __Vtemp88[4];
    WData/*127:0*/ __Vtemp91[4];
    WData/*127:0*/ __Vtemp92[4];
    WData/*127:0*/ __Vtemp93[4];
    WData/*319:0*/ __Vtemp97[10];
    WData/*319:0*/ __Vtemp99[10];
    WData/*159:0*/ __Vtemp106[5];
    // Body
    VL_EXTEND_WQ(68,35, __Vtemp75, (((QData)((IData)(
                                                     ((((0x73U 
                                                         == 
                                                         (0x7fU 
                                                          & ((vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[2U] 
                                                              << 0x1dU) 
                                                             | (vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U] 
                                                                >> 3U)))) 
                                                        & (0U 
                                                           == 
                                                           (7U 
                                                            & ((vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[2U] 
                                                                << 0x11U) 
                                                               | (vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U] 
                                                                  >> 0xfU))))) 
                                                       & ((1U 
                                                           == 
                                                           (0x7fU 
                                                            & ((vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[2U] 
                                                                << 4U) 
                                                               | (vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U] 
                                                                  >> 0x1cU)))) 
                                                          | (0U 
                                                             == 
                                                             (0x7fU 
                                                              & ((vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[2U] 
                                                                  << 4U) 
                                                                 | (vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U] 
                                                                    >> 0x1cU))))))
                                                       ? 
                                                      (3U 
                                                       & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[0U])
                                                       : 0U))) 
                                     << 0x21U) | (((QData)((IData)(
                                                                   (1U 
                                                                    & (vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[0U] 
                                                                       >> 2U)))) 
                                                   << 0x20U) 
                                                  | (QData)((IData)(
                                                                    ((vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U] 
                                                                      << 0x1dU) 
                                                                     | (vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[0U] 
                                                                        >> 3U)))))));
    __Vtemp76[2U] = ((0xfffffff0U & (((((0x73U == (0x7fU 
                                                   & ((vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[2U] 
                                                       << 0x1dU) 
                                                      | (vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U] 
                                                         >> 3U)))) 
                                        & (0U == (7U 
                                                  & ((vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[2U] 
                                                      << 0x11U) 
                                                     | (vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U] 
                                                        >> 0xfU))))) 
                                       & (1U == (0x7fU 
                                                 & ((vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[2U] 
                                                     << 4U) 
                                                    | (vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U] 
                                                       >> 0x1cU)))))
                                       ? 3U : ((((0x73U 
                                                  == 
                                                  (0x7fU 
                                                   & ((vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[2U] 
                                                       << 0x1dU) 
                                                      | (vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U] 
                                                         >> 3U)))) 
                                                 & (0U 
                                                    == 
                                                    (7U 
                                                     & ((vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[2U] 
                                                         << 0x11U) 
                                                        | (vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U] 
                                                           >> 0xfU))))) 
                                                & (0U 
                                                   == 
                                                   (0x7fU 
                                                    & ((vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[2U] 
                                                        << 4U) 
                                                       | (vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U] 
                                                          >> 0x1cU)))))
                                                ? (
                                                   (2U 
                                                    & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[0U])
                                                    ? 0xbU
                                                    : 
                                                   ((1U 
                                                     & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[0U])
                                                     ? 9U
                                                     : 8U))
                                                : 0U)) 
                                     << 4U)) | __Vtemp75[2U]);
    __Vtemp78[3U] = ((0xfffffe00U & ((((0x73U == (0x7fU 
                                                  & ((vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[2U] 
                                                      << 0x1dU) 
                                                     | (vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U] 
                                                        >> 3U)))) 
                                       & (0U == (7U 
                                                 & ((vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[2U] 
                                                     << 0x11U) 
                                                    | (vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U] 
                                                       >> 0xfU))))) 
                                      & ((1U == (0x7fU 
                                                 & ((vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[2U] 
                                                     << 4U) 
                                                    | (vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U] 
                                                       >> 0x1cU)))) 
                                         | (0U == (0x7fU 
                                                   & ((vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[2U] 
                                                       << 4U) 
                                                      | (vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U] 
                                                         >> 0x1cU)))))) 
                                     << 9U)) | (0x1ffU 
                                                & (((((0x73U 
                                                       == 
                                                       (0x7fU 
                                                        & ((vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[2U] 
                                                            << 0x1dU) 
                                                           | (vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U] 
                                                              >> 3U)))) 
                                                      & (0U 
                                                         == 
                                                         (7U 
                                                          & ((vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[2U] 
                                                              << 0x11U) 
                                                             | (vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U] 
                                                                >> 0xfU))))) 
                                                     & ((1U 
                                                         == 
                                                         (0x7fU 
                                                          & ((vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[2U] 
                                                              << 4U) 
                                                             | (vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U] 
                                                                >> 0x1cU)))) 
                                                        | (0U 
                                                           == 
                                                           (0x7fU 
                                                            & ((vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[2U] 
                                                                << 4U) 
                                                               | (vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U] 
                                                                  >> 0x1cU))))))
                                                     ? 
                                                    ((vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[3U] 
                                                      << 0x1dU) 
                                                     | (vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[2U] 
                                                        >> 3U))
                                                     : 0U) 
                                                   >> 0x17U)));
    __Vtemp80[3U] = ((0xfffff800U & (((0x200U & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                                       ? 2U : ((0x100U 
                                                & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                                                ? (
                                                   (0x80U 
                                                    & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                                                    ? 2U
                                                    : 
                                                   ((0x40U 
                                                     & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                                                     ? 2U
                                                     : 
                                                    ((0x20U 
                                                      & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                                                      ? 2U
                                                      : 
                                                     ((0x10U 
                                                       & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                                                       ? 
                                                      ((8U 
                                                        & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                                                        ? 
                                                       ((0U 
                                                         == 
                                                         (7U 
                                                          & ((vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[2U] 
                                                              << 0x11U) 
                                                             | (vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U] 
                                                                >> 0xfU))))
                                                         ? 0U
                                                         : 
                                                        ((1U 
                                                          == 
                                                          (7U 
                                                           & ((vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[2U] 
                                                               << 0x11U) 
                                                              | (vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U] 
                                                                 >> 0xfU))))
                                                          ? 1U
                                                          : 2U))
                                                        : 2U)
                                                       : 2U))))
                                                : (
                                                   (0x80U 
                                                    & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                                                    ? 2U
                                                    : 
                                                   ((0x40U 
                                                     & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                                                     ? 2U
                                                     : 
                                                    ((0x20U 
                                                      & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                                                      ? 2U
                                                      : 
                                                     ((0x10U 
                                                       & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                                                       ? 
                                                      ((8U 
                                                        & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                                                        ? 
                                                       ((0x20000U 
                                                         & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                                                         ? 
                                                        ((0x10000U 
                                                          & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                                                          ? 2U
                                                          : 
                                                         ((0x8000U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                                                           ? 1U
                                                           : 0U))
                                                         : 
                                                        ((0x10000U 
                                                          & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                                                          ? 2U
                                                          : 
                                                         ((0x8000U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                                                           ? 1U
                                                           : 0U)))
                                                        : 2U)
                                                       : 2U)))))) 
                                     << 0xbU)) | ((0xfffffc00U 
                                                   & (((3U 
                                                        == 
                                                        (0x7fU 
                                                         & ((vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[2U] 
                                                             << 0x1dU) 
                                                            | (vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U] 
                                                               >> 3U)))) 
                                                       & ((4U 
                                                           == 
                                                           (7U 
                                                            & ((vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[2U] 
                                                                << 0x11U) 
                                                               | (vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U] 
                                                                  >> 0xfU)))) 
                                                          | (5U 
                                                             == 
                                                             (7U 
                                                              & ((vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[2U] 
                                                                  << 0x11U) 
                                                                 | (vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U] 
                                                                    >> 0xfU)))))) 
                                                      << 0xaU)) 
                                                  | __Vtemp78[3U]));
    __Vtemp81[3U] = ((0xffffe000U & (((((((((0x13U 
                                             == (0x7fU 
                                                 & ((vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[2U] 
                                                     << 0x1dU) 
                                                    | (vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U] 
                                                       >> 3U)))) 
                                            | (3U == 
                                               (0x7fU 
                                                & ((vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[2U] 
                                                    << 0x1dU) 
                                                   | (vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U] 
                                                      >> 3U))))) 
                                           | (0x23U 
                                              == (0x7fU 
                                                  & ((vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[2U] 
                                                      << 0x1dU) 
                                                     | (vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U] 
                                                        >> 3U))))) 
                                          | (0x63U 
                                             == (0x7fU 
                                                 & ((vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[2U] 
                                                     << 0x1dU) 
                                                    | (vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U] 
                                                       >> 3U))))) 
                                         | (0x37U == 
                                            (0x7fU 
                                             & ((vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[2U] 
                                                 << 0x1dU) 
                                                | (vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U] 
                                                   >> 3U))))) 
                                        | (0x17U == 
                                           (0x7fU & 
                                            ((vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[2U] 
                                              << 0x1dU) 
                                             | (vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U] 
                                                >> 3U))))) 
                                       | (0x6fU == 
                                          (0x7fU & 
                                           ((vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[2U] 
                                             << 0x1dU) 
                                            | (vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U] 
                                               >> 3U))))) 
                                      | (0x67U == (0x7fU 
                                                   & ((vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[2U] 
                                                       << 0x1dU) 
                                                      | (vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U] 
                                                         >> 3U))))) 
                                     << 0xdU)) | __Vtemp80[3U]);
    vlTOPp->mkTestBench__DOT__NOT_soc_core_if2id_first___05F414_BITS_41_TO_35_41_ETC___05F_d1667[0U] 
        = __Vtemp75[0U];
    vlTOPp->mkTestBench__DOT__NOT_soc_core_if2id_first___05F414_BITS_41_TO_35_41_ETC___05F_d1667[1U] 
        = __Vtemp75[1U];
    vlTOPp->mkTestBench__DOT__NOT_soc_core_if2id_first___05F414_BITS_41_TO_35_41_ETC___05F_d1667[2U] 
        = ((0xfffffe00U & (((((0x73U == (0x7fU & ((
                                                   vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[2U] 
                                                   << 0x1dU) 
                                                  | (vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U] 
                                                     >> 3U)))) 
                              & (0U == (7U & ((vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[2U] 
                                               << 0x11U) 
                                              | (vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U] 
                                                 >> 0xfU))))) 
                             & ((1U == (0x7fU & ((vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[2U] 
                                                  << 4U) 
                                                 | (vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U] 
                                                    >> 0x1cU)))) 
                                | (0U == (0x7fU & (
                                                   (vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[2U] 
                                                    << 4U) 
                                                   | (vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U] 
                                                      >> 0x1cU))))))
                             ? ((vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[3U] 
                                 << 0x1dU) | (vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[2U] 
                                              >> 3U))
                             : 0U) << 9U)) | __Vtemp76[2U]);
    vlTOPp->mkTestBench__DOT__NOT_soc_core_if2id_first___05F414_BITS_41_TO_35_41_ETC___05F_d1667[3U] 
        = __Vtemp81[3U];
    vlTOPp->mkTestBench__DOT__imm12___05Fh112030 = 
        ((0xfe0U & ((vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[2U] 
                     << 9U) | (0x1e0U & (vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U] 
                                         >> 0x17U)))) 
         | (0x1fU & ((vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[2U] 
                      << 0x16U) | (vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U] 
                                   >> 0xaU))));
    vlTOPp->mkTestBench__DOT__imm13___05Fh112075 = 
        ((0x1000U & (vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[2U] 
                     << 0xaU)) | ((0x800U & (vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U] 
                                             << 1U)) 
                                  | ((0x7e0U & ((vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[2U] 
                                                 << 9U) 
                                                | (0x1e0U 
                                                   & (vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U] 
                                                      >> 0x17U)))) 
                                     | (0x1eU & ((vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[2U] 
                                                  << 0x16U) 
                                                 | (0x3ffffeU 
                                                    & (vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U] 
                                                       >> 0xaU)))))));
    vlTOPp->mkTestBench__DOT__imm21___05Fh112201 = 
        ((0x100000U & (vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[2U] 
                       << 0x12U)) | ((0xff000U & ((
                                                   vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[2U] 
                                                   << 0x1dU) 
                                                  | (0x1ffff000U 
                                                     & (vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U] 
                                                        >> 3U)))) 
                                     | ((0x800U & (
                                                   vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U] 
                                                   >> 0xcU)) 
                                        | (0x7feU & 
                                           ((vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[2U] 
                                             << 9U) 
                                            | (0x1feU 
                                               & (vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U] 
                                                  >> 0x17U)))))));
    vlTOPp->mkTestBench__DOT__imm___05Fh110387 = ((0xfffff000U 
                                                   & ((- (IData)(
                                                                 (1U 
                                                                  & (vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[2U] 
                                                                     >> 2U)))) 
                                                      << 0xcU)) 
                                                  | (0xfffU 
                                                     & ((vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[2U] 
                                                         << 9U) 
                                                        | (vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U] 
                                                           >> 0x17U))));
    vlTOPp->mkTestBench__DOT__actual_target___05F_1___05Fh114832 
        = (((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[9U] 
             << 0x17U) | (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U] 
                          >> 9U)) + ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[5U] 
                                      << 0x17U) | (
                                                   vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[4U] 
                                                   >> 9U)));
    vlTOPp->mkTestBench__DOT__CASE_soc_core_id2exD_OUT_BITS_247_TO_245_0b11_ETC___05Fq4 
        = (((3U == (7U & ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U] 
                           << 0xbU) | (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[7U] 
                                       >> 0x15U)))) 
            | (5U == (7U & ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U] 
                             << 0xbU) | (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[7U] 
                                         >> 0x15U)))))
            ? (0U != (0x1fU & ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U] 
                                << 8U) | (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[7U] 
                                          >> 0x18U))))
            : (((6U == (7U & ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U] 
                               << 0xbU) | (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[7U] 
                                           >> 0x15U)))) 
                | (7U == (7U & ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U] 
                                 << 0xbU) | (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[7U] 
                                             >> 0x15U))))) 
               & (0U != (0x1fU & ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U] 
                                   << 8U) | (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[7U] 
                                             >> 0x18U))))));
    vlTOPp->mkTestBench__DOT__soc_core_if2id_first___05F414_BITS_54_TO_50_461_EQ_ETC___05F_d1462 
        = ((0x1fU & ((vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[2U] 
                      << 0xeU) | (vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U] 
                                  >> 0x12U))) == (0x1fU 
                                                  & ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[4U] 
                                                      << 6U) 
                                                     | (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[3U] 
                                                        >> 0x1aU))));
    vlTOPp->mkTestBench__DOT__soc_core_if2id_first___05F414_BITS_59_TO_55_427_EQ_ETC___05F_d1428 
        = ((0x1fU & ((vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[2U] 
                      << 9U) | (vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U] 
                                >> 0x17U))) == (0x1fU 
                                                & ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[4U] 
                                                    << 6U) 
                                                   | (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[3U] 
                                                      >> 0x1aU))));
    vlTOPp->mkTestBench__DOT__addr___05Fh117366 = (
                                                   (0x8000U 
                                                    & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[7U])
                                                    ? 
                                                   ((0x4000U 
                                                     & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[7U])
                                                     ? 
                                                    ((0x2000U 
                                                      & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[7U])
                                                      ? 
                                                     ((0x1000U 
                                                       & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[7U])
                                                       ? 0U
                                                       : 
                                                      ((0x800U 
                                                        & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[7U])
                                                        ? 0U
                                                        : 
                                                       ((0x400U 
                                                         & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[7U])
                                                         ? 
                                                        ((0x200U 
                                                          & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[7U])
                                                          ? 
                                                         (0xfffU 
                                                          & ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U] 
                                                              << 3U) 
                                                             | (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[7U] 
                                                                >> 0x1dU)))
                                                          : 0U)
                                                         : 0U)))
                                                      : 0U)
                                                     : 0U)
                                                    : 0U);
    vlTOPp->mkTestBench__DOT__op1___05F_1___05Fh113287 
        = ((1U & vlTOPp->mkTestBench__DOT__soc_core_mem2wb__DOT__data0_reg[0U])
            ? ((vlTOPp->mkTestBench__DOT__soc_core_mem2wb__DOT__data0_reg[2U] 
                << 0x19U) | (vlTOPp->mkTestBench__DOT__soc_core_mem2wb__DOT__data0_reg[1U] 
                             >> 7U)) : ((vlTOPp->mkTestBench__DOT__soc_core_mem2wb__DOT__data0_reg[1U] 
                                         << 0x19U) 
                                        | (vlTOPp->mkTestBench__DOT__soc_core_mem2wb__DOT__data0_reg[0U] 
                                           >> 7U)));
    vlTOPp->mkTestBench__DOT__cycleCount__024D_IN = 
        ((IData)(1U) + vlTOPp->mkTestBench__DOT__cycleCount);
    vlTOPp->mkTestBench__DOT__soc_core_regFile_registers_0__024D_IN 
        = ((vlTOPp->mkTestBench__DOT__soc_core_mem2wb__DOT__data0_reg[0U] 
            & (IData)(vlTOPp->mkTestBench__DOT__soc_core_mem_resp_pending))
            ? (IData)(vlTOPp->mkTestBench__DOT__soc_core_pending_mem_resp)
            : ((vlTOPp->mkTestBench__DOT__soc_core_mem2wb__DOT__data0_reg[1U] 
                << 0x19U) | (vlTOPp->mkTestBench__DOT__soc_core_mem2wb__DOT__data0_reg[0U] 
                             >> 7U)));
    vlTOPp->done = vlTOPp->mkTestBench__DOT__dumpDone;
    vlTOPp->mkTestBench__DOT__programLoaded__024EN 
        = (1U & (~ (IData)(vlTOPp->mkTestBench__DOT__programLoaded)));
    vlTOPp->mkTestBench__DOT__programDone__024EN = 
        (((IData)(vlTOPp->mkTestBench__DOT__programLoaded) 
          & (~ (IData)(vlTOPp->mkTestBench__DOT__programDone))) 
         & ((IData)(vlTOPp->mkTestBench__DOT__soc_dmem_tohost_written) 
            | (0x186a0U <= vlTOPp->mkTestBench__DOT__cycleCount)));
    vlTOPp->mkTestBench__DOT__WILL_FIRE_RL_countCycles 
        = ((IData)(vlTOPp->mkTestBench__DOT__programLoaded) 
           & (~ (IData)(vlTOPp->mkTestBench__DOT__dumpDone)));
    vlTOPp->mkTestBench__DOT__rs1_val___05Fh110784 
        = ((0x400000U & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
            ? ((0x200000U & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                ? ((0x100000U & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                    ? ((0x80000U & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                        ? ((0x40000U & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                            ? vlTOPp->mkTestBench__DOT__soc_core_regFile_registers_31
                            : vlTOPp->mkTestBench__DOT__soc_core_regFile_registers_30)
                        : ((0x40000U & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                            ? vlTOPp->mkTestBench__DOT__soc_core_regFile_registers_29
                            : vlTOPp->mkTestBench__DOT__soc_core_regFile_registers_28))
                    : ((0x80000U & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                        ? ((0x40000U & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                            ? vlTOPp->mkTestBench__DOT__soc_core_regFile_registers_27
                            : vlTOPp->mkTestBench__DOT__soc_core_regFile_registers_26)
                        : ((0x40000U & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                            ? vlTOPp->mkTestBench__DOT__soc_core_regFile_registers_25
                            : vlTOPp->mkTestBench__DOT__soc_core_regFile_registers_24)))
                : ((0x100000U & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                    ? ((0x80000U & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                        ? ((0x40000U & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                            ? vlTOPp->mkTestBench__DOT__soc_core_regFile_registers_23
                            : vlTOPp->mkTestBench__DOT__soc_core_regFile_registers_22)
                        : ((0x40000U & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                            ? vlTOPp->mkTestBench__DOT__soc_core_regFile_registers_21
                            : vlTOPp->mkTestBench__DOT__soc_core_regFile_registers_20))
                    : ((0x80000U & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                        ? ((0x40000U & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                            ? vlTOPp->mkTestBench__DOT__soc_core_regFile_registers_19
                            : vlTOPp->mkTestBench__DOT__soc_core_regFile_registers_18)
                        : ((0x40000U & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                            ? vlTOPp->mkTestBench__DOT__soc_core_regFile_registers_17
                            : vlTOPp->mkTestBench__DOT__soc_core_regFile_registers_16))))
            : ((0x200000U & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                ? ((0x100000U & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                    ? ((0x80000U & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                        ? ((0x40000U & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                            ? vlTOPp->mkTestBench__DOT__soc_core_regFile_registers_15
                            : vlTOPp->mkTestBench__DOT__soc_core_regFile_registers_14)
                        : ((0x40000U & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                            ? vlTOPp->mkTestBench__DOT__soc_core_regFile_registers_13
                            : vlTOPp->mkTestBench__DOT__soc_core_regFile_registers_12))
                    : ((0x80000U & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                        ? ((0x40000U & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                            ? vlTOPp->mkTestBench__DOT__soc_core_regFile_registers_11
                            : vlTOPp->mkTestBench__DOT__soc_core_regFile_registers_10)
                        : ((0x40000U & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                            ? vlTOPp->mkTestBench__DOT__soc_core_regFile_registers_9
                            : vlTOPp->mkTestBench__DOT__soc_core_regFile_registers_8)))
                : ((0x100000U & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                    ? ((0x80000U & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                        ? ((0x40000U & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                            ? vlTOPp->mkTestBench__DOT__soc_core_regFile_registers_7
                            : vlTOPp->mkTestBench__DOT__soc_core_regFile_registers_6)
                        : ((0x40000U & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                            ? vlTOPp->mkTestBench__DOT__soc_core_regFile_registers_5
                            : vlTOPp->mkTestBench__DOT__soc_core_regFile_registers_4))
                    : ((0x80000U & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                        ? ((0x40000U & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                            ? vlTOPp->mkTestBench__DOT__soc_core_regFile_registers_3
                            : vlTOPp->mkTestBench__DOT__soc_core_regFile_registers_2)
                        : ((0x40000U & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                            ? vlTOPp->mkTestBench__DOT__soc_core_regFile_registers_1
                            : 0U)))));
    vlTOPp->mkTestBench__DOT__rs2_val___05Fh110785 
        = ((0x8000000U & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
            ? ((0x4000000U & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                ? ((0x2000000U & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                    ? ((0x1000000U & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                        ? ((0x800000U & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                            ? vlTOPp->mkTestBench__DOT__soc_core_regFile_registers_31
                            : vlTOPp->mkTestBench__DOT__soc_core_regFile_registers_30)
                        : ((0x800000U & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                            ? vlTOPp->mkTestBench__DOT__soc_core_regFile_registers_29
                            : vlTOPp->mkTestBench__DOT__soc_core_regFile_registers_28))
                    : ((0x1000000U & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                        ? ((0x800000U & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                            ? vlTOPp->mkTestBench__DOT__soc_core_regFile_registers_27
                            : vlTOPp->mkTestBench__DOT__soc_core_regFile_registers_26)
                        : ((0x800000U & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                            ? vlTOPp->mkTestBench__DOT__soc_core_regFile_registers_25
                            : vlTOPp->mkTestBench__DOT__soc_core_regFile_registers_24)))
                : ((0x2000000U & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                    ? ((0x1000000U & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                        ? ((0x800000U & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                            ? vlTOPp->mkTestBench__DOT__soc_core_regFile_registers_23
                            : vlTOPp->mkTestBench__DOT__soc_core_regFile_registers_22)
                        : ((0x800000U & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                            ? vlTOPp->mkTestBench__DOT__soc_core_regFile_registers_21
                            : vlTOPp->mkTestBench__DOT__soc_core_regFile_registers_20))
                    : ((0x1000000U & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                        ? ((0x800000U & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                            ? vlTOPp->mkTestBench__DOT__soc_core_regFile_registers_19
                            : vlTOPp->mkTestBench__DOT__soc_core_regFile_registers_18)
                        : ((0x800000U & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                            ? vlTOPp->mkTestBench__DOT__soc_core_regFile_registers_17
                            : vlTOPp->mkTestBench__DOT__soc_core_regFile_registers_16))))
            : ((0x4000000U & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                ? ((0x2000000U & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                    ? ((0x1000000U & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                        ? ((0x800000U & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                            ? vlTOPp->mkTestBench__DOT__soc_core_regFile_registers_15
                            : vlTOPp->mkTestBench__DOT__soc_core_regFile_registers_14)
                        : ((0x800000U & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                            ? vlTOPp->mkTestBench__DOT__soc_core_regFile_registers_13
                            : vlTOPp->mkTestBench__DOT__soc_core_regFile_registers_12))
                    : ((0x1000000U & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                        ? ((0x800000U & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                            ? vlTOPp->mkTestBench__DOT__soc_core_regFile_registers_11
                            : vlTOPp->mkTestBench__DOT__soc_core_regFile_registers_10)
                        : ((0x800000U & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                            ? vlTOPp->mkTestBench__DOT__soc_core_regFile_registers_9
                            : vlTOPp->mkTestBench__DOT__soc_core_regFile_registers_8)))
                : ((0x2000000U & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                    ? ((0x1000000U & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                        ? ((0x800000U & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                            ? vlTOPp->mkTestBench__DOT__soc_core_regFile_registers_7
                            : vlTOPp->mkTestBench__DOT__soc_core_regFile_registers_6)
                        : ((0x800000U & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                            ? vlTOPp->mkTestBench__DOT__soc_core_regFile_registers_5
                            : vlTOPp->mkTestBench__DOT__soc_core_regFile_registers_4))
                    : ((0x1000000U & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                        ? ((0x800000U & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                            ? vlTOPp->mkTestBench__DOT__soc_core_regFile_registers_3
                            : vlTOPp->mkTestBench__DOT__soc_core_regFile_registers_2)
                        : ((0x800000U & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                            ? vlTOPp->mkTestBench__DOT__soc_core_regFile_registers_1
                            : 0U)))));
    vlTOPp->mkTestBench__DOT__enabled_interrupts___05Fh128101 
        = (vlTOPp->mkTestBench__DOT__soc_core_csrs_mie 
           & vlTOPp->mkTestBench__DOT__soc_core_csrs_mip);
    if ((0x10000U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])) {
        vlTOPp->mkTestBench__DOT__oldState___05Fh115429 
            = ((0x8000U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                ? ((0x4000U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                    ? ((0x2000U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                        ? ((0x1000U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                            ? ((0x800U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                                ? (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_63)
                                : (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_62))
                            : ((0x800U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                                ? (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_61)
                                : (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_60)))
                        : ((0x1000U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                            ? ((0x800U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                                ? (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_59)
                                : (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_58))
                            : ((0x800U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                                ? (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_57)
                                : (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_56))))
                    : ((0x2000U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                        ? ((0x1000U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                            ? ((0x800U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                                ? (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_55)
                                : (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_54))
                            : ((0x800U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                                ? (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_53)
                                : (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_52)))
                        : ((0x1000U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                            ? ((0x800U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                                ? (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_51)
                                : (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_50))
                            : ((0x800U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                                ? (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_49)
                                : (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_48)))))
                : ((0x4000U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                    ? ((0x2000U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                        ? ((0x1000U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                            ? ((0x800U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                                ? (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_47)
                                : (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_46))
                            : ((0x800U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                                ? (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_45)
                                : (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_44)))
                        : ((0x1000U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                            ? ((0x800U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                                ? (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_43)
                                : (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_42))
                            : ((0x800U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                                ? (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_41)
                                : (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_40))))
                    : ((0x2000U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                        ? ((0x1000U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                            ? ((0x800U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                                ? (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_39)
                                : (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_38))
                            : ((0x800U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                                ? (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_37)
                                : (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_36)))
                        : ((0x1000U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                            ? ((0x800U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                                ? (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_35)
                                : (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_34))
                            : ((0x800U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                                ? (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_33)
                                : (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_32))))));
        vlTOPp->mkTestBench__DOT__SEL_ARR_soc_core_btb_btbTable_0_055_BITS_64_TO_ETC___05F_d1806 
            = ((0x8000U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                ? ((0x4000U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                    ? ((0x2000U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                        ? ((0x1000U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                            ? ((0x800U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                                ? ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_63[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_63[1U] 
                                                 >> 1U))
                                : ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_62[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_62[1U] 
                                                 >> 1U)))
                            : ((0x800U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                                ? ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_61[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_61[1U] 
                                                 >> 1U))
                                : ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_60[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_60[1U] 
                                                 >> 1U))))
                        : ((0x1000U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                            ? ((0x800U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                                ? ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_59[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_59[1U] 
                                                 >> 1U))
                                : ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_58[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_58[1U] 
                                                 >> 1U)))
                            : ((0x800U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                                ? ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_57[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_57[1U] 
                                                 >> 1U))
                                : ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_56[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_56[1U] 
                                                 >> 1U)))))
                    : ((0x2000U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                        ? ((0x1000U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                            ? ((0x800U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                                ? ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_55[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_55[1U] 
                                                 >> 1U))
                                : ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_54[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_54[1U] 
                                                 >> 1U)))
                            : ((0x800U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                                ? ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_53[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_53[1U] 
                                                 >> 1U))
                                : ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_52[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_52[1U] 
                                                 >> 1U))))
                        : ((0x1000U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                            ? ((0x800U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                                ? ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_51[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_51[1U] 
                                                 >> 1U))
                                : ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_50[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_50[1U] 
                                                 >> 1U)))
                            : ((0x800U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                                ? ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_49[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_49[1U] 
                                                 >> 1U))
                                : ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_48[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_48[1U] 
                                                 >> 1U))))))
                : ((0x4000U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                    ? ((0x2000U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                        ? ((0x1000U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                            ? ((0x800U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                                ? ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_47[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_47[1U] 
                                                 >> 1U))
                                : ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_46[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_46[1U] 
                                                 >> 1U)))
                            : ((0x800U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                                ? ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_45[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_45[1U] 
                                                 >> 1U))
                                : ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_44[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_44[1U] 
                                                 >> 1U))))
                        : ((0x1000U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                            ? ((0x800U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                                ? ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_43[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_43[1U] 
                                                 >> 1U))
                                : ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_42[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_42[1U] 
                                                 >> 1U)))
                            : ((0x800U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                                ? ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_41[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_41[1U] 
                                                 >> 1U))
                                : ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_40[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_40[1U] 
                                                 >> 1U)))))
                    : ((0x2000U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                        ? ((0x1000U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                            ? ((0x800U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                                ? ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_39[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_39[1U] 
                                                 >> 1U))
                                : ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_38[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_38[1U] 
                                                 >> 1U)))
                            : ((0x800U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                                ? ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_37[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_37[1U] 
                                                 >> 1U))
                                : ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_36[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_36[1U] 
                                                 >> 1U))))
                        : ((0x1000U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                            ? ((0x800U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                                ? ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_35[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_35[1U] 
                                                 >> 1U))
                                : ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_34[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_34[1U] 
                                                 >> 1U)))
                            : ((0x800U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                                ? ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_33[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_33[1U] 
                                                 >> 1U))
                                : ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_32[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_32[1U] 
                                                 >> 1U)))))));
    } else {
        vlTOPp->mkTestBench__DOT__oldState___05Fh115429 
            = ((0x8000U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                ? ((0x4000U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                    ? ((0x2000U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                        ? ((0x1000U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                            ? ((0x800U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                                ? (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_31)
                                : (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_30))
                            : ((0x800U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                                ? (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_29)
                                : (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_28)))
                        : ((0x1000U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                            ? ((0x800U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                                ? (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_27)
                                : (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_26))
                            : ((0x800U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                                ? (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_25)
                                : (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_24))))
                    : ((0x2000U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                        ? ((0x1000U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                            ? ((0x800U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                                ? (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_23)
                                : (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_22))
                            : ((0x800U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                                ? (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_21)
                                : (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_20)))
                        : ((0x1000U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                            ? ((0x800U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                                ? (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_19)
                                : (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_18))
                            : ((0x800U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                                ? (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_17)
                                : (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_16)))))
                : ((0x4000U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                    ? ((0x2000U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                        ? ((0x1000U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                            ? ((0x800U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                                ? (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_15)
                                : (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_14))
                            : ((0x800U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                                ? (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_13)
                                : (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_12)))
                        : ((0x1000U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                            ? ((0x800U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                                ? (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_11)
                                : (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_10))
                            : ((0x800U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                                ? (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_9)
                                : (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_8))))
                    : ((0x2000U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                        ? ((0x1000U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                            ? ((0x800U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                                ? (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_7)
                                : (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_6))
                            : ((0x800U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                                ? (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_5)
                                : (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_4)))
                        : ((0x1000U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                            ? ((0x800U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                                ? (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_3)
                                : (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_2))
                            : ((0x800U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                                ? (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_1)
                                : (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_0))))));
        vlTOPp->mkTestBench__DOT__SEL_ARR_soc_core_btb_btbTable_0_055_BITS_64_TO_ETC___05F_d1806 
            = ((0x8000U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                ? ((0x4000U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                    ? ((0x2000U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                        ? ((0x1000U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                            ? ((0x800U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                                ? ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_31[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_31[1U] 
                                                 >> 1U))
                                : ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_30[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_30[1U] 
                                                 >> 1U)))
                            : ((0x800U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                                ? ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_29[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_29[1U] 
                                                 >> 1U))
                                : ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_28[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_28[1U] 
                                                 >> 1U))))
                        : ((0x1000U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                            ? ((0x800U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                                ? ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_27[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_27[1U] 
                                                 >> 1U))
                                : ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_26[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_26[1U] 
                                                 >> 1U)))
                            : ((0x800U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                                ? ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_25[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_25[1U] 
                                                 >> 1U))
                                : ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_24[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_24[1U] 
                                                 >> 1U)))))
                    : ((0x2000U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                        ? ((0x1000U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                            ? ((0x800U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                                ? ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_23[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_23[1U] 
                                                 >> 1U))
                                : ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_22[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_22[1U] 
                                                 >> 1U)))
                            : ((0x800U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                                ? ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_21[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_21[1U] 
                                                 >> 1U))
                                : ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_20[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_20[1U] 
                                                 >> 1U))))
                        : ((0x1000U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                            ? ((0x800U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                                ? ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_19[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_19[1U] 
                                                 >> 1U))
                                : ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_18[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_18[1U] 
                                                 >> 1U)))
                            : ((0x800U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                                ? ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_17[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_17[1U] 
                                                 >> 1U))
                                : ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_16[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_16[1U] 
                                                 >> 1U))))))
                : ((0x4000U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                    ? ((0x2000U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                        ? ((0x1000U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                            ? ((0x800U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                                ? ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_15[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_15[1U] 
                                                 >> 1U))
                                : ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_14[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_14[1U] 
                                                 >> 1U)))
                            : ((0x800U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                                ? ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_13[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_13[1U] 
                                                 >> 1U))
                                : ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_12[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_12[1U] 
                                                 >> 1U))))
                        : ((0x1000U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                            ? ((0x800U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                                ? ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_11[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_11[1U] 
                                                 >> 1U))
                                : ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_10[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_10[1U] 
                                                 >> 1U)))
                            : ((0x800U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                                ? ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_9[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_9[1U] 
                                                 >> 1U))
                                : ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_8[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_8[1U] 
                                                 >> 1U)))))
                    : ((0x2000U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                        ? ((0x1000U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                            ? ((0x800U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                                ? ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_7[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_7[1U] 
                                                 >> 1U))
                                : ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_6[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_6[1U] 
                                                 >> 1U)))
                            : ((0x800U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                                ? ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_5[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_5[1U] 
                                                 >> 1U))
                                : ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_4[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_4[1U] 
                                                 >> 1U))))
                        : ((0x1000U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                            ? ((0x800U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                                ? ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_3[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_3[1U] 
                                                 >> 1U))
                                : ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_2[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_2[1U] 
                                                 >> 1U)))
                            : ((0x800U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U])
                                ? ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_1[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_1[1U] 
                                                 >> 1U))
                                : ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_0[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_0[1U] 
                                                 >> 1U)))))));
    }
    vlTOPp->mkTestBench__DOT__WILL_FIRE_RL_soc_core_decrementStall 
        = (((IData)(vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__full_reg) 
            & (IData)(vlTOPp->mkTestBench__DOT__soc_core_stall_load_use)) 
           & (0U != (IData)(vlTOPp->mkTestBench__DOT__soc_core_stall_count)));
    vlTOPp->mkTestBench__DOT__WILL_FIRE_RL_soc_core_decodeStage 
        = ((((IData)(vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__full_reg) 
             & (IData)(vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__empty_reg)) 
            & (IData)(vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__empty_reg)) 
           & (~ (IData)(vlTOPp->mkTestBench__DOT__soc_core_stall_load_use)));
    if ((0x80U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)) {
        vlTOPp->mkTestBench__DOT__prediction_target___05F_1___05Fh109896 
            = ((0x40U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                ? ((0x20U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                    ? ((0x10U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                        ? ((8U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                            ? ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                ? ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_63[1U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_63[0U] 
                                                 >> 1U))
                                : ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_62[1U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_62[0U] 
                                                 >> 1U)))
                            : ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                ? ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_61[1U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_61[0U] 
                                                 >> 1U))
                                : ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_60[1U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_60[0U] 
                                                 >> 1U))))
                        : ((8U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                            ? ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                ? ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_59[1U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_59[0U] 
                                                 >> 1U))
                                : ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_58[1U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_58[0U] 
                                                 >> 1U)))
                            : ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                ? ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_57[1U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_57[0U] 
                                                 >> 1U))
                                : ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_56[1U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_56[0U] 
                                                 >> 1U)))))
                    : ((0x10U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                        ? ((8U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                            ? ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                ? ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_55[1U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_55[0U] 
                                                 >> 1U))
                                : ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_54[1U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_54[0U] 
                                                 >> 1U)))
                            : ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                ? ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_53[1U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_53[0U] 
                                                 >> 1U))
                                : ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_52[1U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_52[0U] 
                                                 >> 1U))))
                        : ((8U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                            ? ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                ? ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_51[1U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_51[0U] 
                                                 >> 1U))
                                : ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_50[1U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_50[0U] 
                                                 >> 1U)))
                            : ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                ? ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_49[1U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_49[0U] 
                                                 >> 1U))
                                : ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_48[1U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_48[0U] 
                                                 >> 1U))))))
                : ((0x20U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                    ? ((0x10U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                        ? ((8U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                            ? ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                ? ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_47[1U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_47[0U] 
                                                 >> 1U))
                                : ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_46[1U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_46[0U] 
                                                 >> 1U)))
                            : ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                ? ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_45[1U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_45[0U] 
                                                 >> 1U))
                                : ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_44[1U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_44[0U] 
                                                 >> 1U))))
                        : ((8U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                            ? ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                ? ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_43[1U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_43[0U] 
                                                 >> 1U))
                                : ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_42[1U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_42[0U] 
                                                 >> 1U)))
                            : ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                ? ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_41[1U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_41[0U] 
                                                 >> 1U))
                                : ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_40[1U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_40[0U] 
                                                 >> 1U)))))
                    : ((0x10U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                        ? ((8U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                            ? ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                ? ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_39[1U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_39[0U] 
                                                 >> 1U))
                                : ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_38[1U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_38[0U] 
                                                 >> 1U)))
                            : ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                ? ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_37[1U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_37[0U] 
                                                 >> 1U))
                                : ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_36[1U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_36[0U] 
                                                 >> 1U))))
                        : ((8U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                            ? ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                ? ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_35[1U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_35[0U] 
                                                 >> 1U))
                                : ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_34[1U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_34[0U] 
                                                 >> 1U)))
                            : ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                ? ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_33[1U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_33[0U] 
                                                 >> 1U))
                                : ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_32[1U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_32[0U] 
                                                 >> 1U)))))));
        vlTOPp->mkTestBench__DOT__state___05Fh107856 
            = ((0x40U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                ? ((0x20U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                    ? ((0x10U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                        ? ((8U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                            ? ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                ? (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_63)
                                : (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_62))
                            : ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                ? (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_61)
                                : (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_60)))
                        : ((8U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                            ? ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                ? (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_59)
                                : (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_58))
                            : ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                ? (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_57)
                                : (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_56))))
                    : ((0x10U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                        ? ((8U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                            ? ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                ? (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_55)
                                : (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_54))
                            : ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                ? (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_53)
                                : (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_52)))
                        : ((8U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                            ? ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                ? (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_51)
                                : (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_50))
                            : ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                ? (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_49)
                                : (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_48)))))
                : ((0x20U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                    ? ((0x10U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                        ? ((8U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                            ? ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                ? (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_47)
                                : (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_46))
                            : ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                ? (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_45)
                                : (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_44)))
                        : ((8U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                            ? ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                ? (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_43)
                                : (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_42))
                            : ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                ? (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_41)
                                : (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_40))))
                    : ((0x10U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                        ? ((8U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                            ? ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                ? (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_39)
                                : (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_38))
                            : ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                ? (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_37)
                                : (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_36)))
                        : ((8U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                            ? ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                ? (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_35)
                                : (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_34))
                            : ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                ? (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_33)
                                : (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_32))))));
        vlTOPp->mkTestBench__DOT__SEL_ARR_soc_core_btb_btbTable_0_055_BIT_0_056___05FETC___05F_d1185 
            = (1U & ((0x40U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                      ? ((0x20U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                          ? ((0x10U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                              ? ((8U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                  ? ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                      ? vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_63[0U]
                                      : vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_62[0U])
                                  : ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                      ? vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_61[0U]
                                      : vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_60[0U]))
                              : ((8U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                  ? ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                      ? vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_59[0U]
                                      : vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_58[0U])
                                  : ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                      ? vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_57[0U]
                                      : vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_56[0U])))
                          : ((0x10U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                              ? ((8U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                  ? ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                      ? vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_55[0U]
                                      : vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_54[0U])
                                  : ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                      ? vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_53[0U]
                                      : vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_52[0U]))
                              : ((8U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                  ? ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                      ? vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_51[0U]
                                      : vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_50[0U])
                                  : ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                      ? vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_49[0U]
                                      : vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_48[0U]))))
                      : ((0x20U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                          ? ((0x10U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                              ? ((8U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                  ? ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                      ? vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_47[0U]
                                      : vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_46[0U])
                                  : ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                      ? vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_45[0U]
                                      : vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_44[0U]))
                              : ((8U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                  ? ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                      ? vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_43[0U]
                                      : vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_42[0U])
                                  : ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                      ? vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_41[0U]
                                      : vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_40[0U])))
                          : ((0x10U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                              ? ((8U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                  ? ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                      ? vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_39[0U]
                                      : vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_38[0U])
                                  : ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                      ? vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_37[0U]
                                      : vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_36[0U]))
                              : ((8U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                  ? ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                      ? vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_35[0U]
                                      : vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_34[0U])
                                  : ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                      ? vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_33[0U]
                                      : vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_32[0U]))))));
        vlTOPp->mkTestBench__DOT__SEL_ARR_soc_core_btb_btbTable_0_055_BITS_64_TO_ETC___05F_d1251 
            = ((0x40U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                ? ((0x20U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                    ? ((0x10U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                        ? ((8U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                            ? ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                ? ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_63[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_63[1U] 
                                                 >> 1U))
                                : ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_62[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_62[1U] 
                                                 >> 1U)))
                            : ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                ? ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_61[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_61[1U] 
                                                 >> 1U))
                                : ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_60[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_60[1U] 
                                                 >> 1U))))
                        : ((8U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                            ? ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                ? ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_59[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_59[1U] 
                                                 >> 1U))
                                : ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_58[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_58[1U] 
                                                 >> 1U)))
                            : ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                ? ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_57[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_57[1U] 
                                                 >> 1U))
                                : ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_56[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_56[1U] 
                                                 >> 1U)))))
                    : ((0x10U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                        ? ((8U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                            ? ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                ? ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_55[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_55[1U] 
                                                 >> 1U))
                                : ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_54[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_54[1U] 
                                                 >> 1U)))
                            : ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                ? ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_53[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_53[1U] 
                                                 >> 1U))
                                : ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_52[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_52[1U] 
                                                 >> 1U))))
                        : ((8U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                            ? ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                ? ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_51[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_51[1U] 
                                                 >> 1U))
                                : ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_50[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_50[1U] 
                                                 >> 1U)))
                            : ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                ? ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_49[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_49[1U] 
                                                 >> 1U))
                                : ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_48[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_48[1U] 
                                                 >> 1U))))))
                : ((0x20U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                    ? ((0x10U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                        ? ((8U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                            ? ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                ? ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_47[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_47[1U] 
                                                 >> 1U))
                                : ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_46[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_46[1U] 
                                                 >> 1U)))
                            : ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                ? ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_45[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_45[1U] 
                                                 >> 1U))
                                : ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_44[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_44[1U] 
                                                 >> 1U))))
                        : ((8U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                            ? ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                ? ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_43[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_43[1U] 
                                                 >> 1U))
                                : ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_42[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_42[1U] 
                                                 >> 1U)))
                            : ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                ? ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_41[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_41[1U] 
                                                 >> 1U))
                                : ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_40[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_40[1U] 
                                                 >> 1U)))))
                    : ((0x10U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                        ? ((8U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                            ? ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                ? ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_39[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_39[1U] 
                                                 >> 1U))
                                : ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_38[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_38[1U] 
                                                 >> 1U)))
                            : ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                ? ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_37[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_37[1U] 
                                                 >> 1U))
                                : ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_36[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_36[1U] 
                                                 >> 1U))))
                        : ((8U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                            ? ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                ? ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_35[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_35[1U] 
                                                 >> 1U))
                                : ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_34[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_34[1U] 
                                                 >> 1U)))
                            : ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                ? ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_33[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_33[1U] 
                                                 >> 1U))
                                : ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_32[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_32[1U] 
                                                 >> 1U)))))));
    } else {
        vlTOPp->mkTestBench__DOT__prediction_target___05F_1___05Fh109896 
            = ((0x40U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                ? ((0x20U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                    ? ((0x10U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                        ? ((8U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                            ? ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                ? ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_31[1U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_31[0U] 
                                                 >> 1U))
                                : ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_30[1U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_30[0U] 
                                                 >> 1U)))
                            : ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                ? ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_29[1U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_29[0U] 
                                                 >> 1U))
                                : ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_28[1U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_28[0U] 
                                                 >> 1U))))
                        : ((8U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                            ? ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                ? ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_27[1U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_27[0U] 
                                                 >> 1U))
                                : ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_26[1U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_26[0U] 
                                                 >> 1U)))
                            : ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                ? ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_25[1U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_25[0U] 
                                                 >> 1U))
                                : ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_24[1U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_24[0U] 
                                                 >> 1U)))))
                    : ((0x10U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                        ? ((8U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                            ? ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                ? ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_23[1U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_23[0U] 
                                                 >> 1U))
                                : ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_22[1U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_22[0U] 
                                                 >> 1U)))
                            : ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                ? ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_21[1U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_21[0U] 
                                                 >> 1U))
                                : ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_20[1U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_20[0U] 
                                                 >> 1U))))
                        : ((8U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                            ? ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                ? ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_19[1U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_19[0U] 
                                                 >> 1U))
                                : ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_18[1U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_18[0U] 
                                                 >> 1U)))
                            : ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                ? ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_17[1U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_17[0U] 
                                                 >> 1U))
                                : ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_16[1U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_16[0U] 
                                                 >> 1U))))))
                : ((0x20U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                    ? ((0x10U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                        ? ((8U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                            ? ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                ? ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_15[1U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_15[0U] 
                                                 >> 1U))
                                : ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_14[1U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_14[0U] 
                                                 >> 1U)))
                            : ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                ? ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_13[1U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_13[0U] 
                                                 >> 1U))
                                : ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_12[1U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_12[0U] 
                                                 >> 1U))))
                        : ((8U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                            ? ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                ? ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_11[1U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_11[0U] 
                                                 >> 1U))
                                : ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_10[1U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_10[0U] 
                                                 >> 1U)))
                            : ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                ? ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_9[1U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_9[0U] 
                                                 >> 1U))
                                : ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_8[1U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_8[0U] 
                                                 >> 1U)))))
                    : ((0x10U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                        ? ((8U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                            ? ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                ? ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_7[1U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_7[0U] 
                                                 >> 1U))
                                : ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_6[1U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_6[0U] 
                                                 >> 1U)))
                            : ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                ? ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_5[1U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_5[0U] 
                                                 >> 1U))
                                : ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_4[1U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_4[0U] 
                                                 >> 1U))))
                        : ((8U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                            ? ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                ? ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_3[1U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_3[0U] 
                                                 >> 1U))
                                : ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_2[1U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_2[0U] 
                                                 >> 1U)))
                            : ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                ? ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_1[1U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_1[0U] 
                                                 >> 1U))
                                : ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_0[1U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_0[0U] 
                                                 >> 1U)))))));
        vlTOPp->mkTestBench__DOT__state___05Fh107856 
            = ((0x40U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                ? ((0x20U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                    ? ((0x10U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                        ? ((8U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                            ? ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                ? (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_31)
                                : (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_30))
                            : ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                ? (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_29)
                                : (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_28)))
                        : ((8U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                            ? ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                ? (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_27)
                                : (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_26))
                            : ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                ? (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_25)
                                : (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_24))))
                    : ((0x10U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                        ? ((8U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                            ? ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                ? (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_23)
                                : (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_22))
                            : ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                ? (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_21)
                                : (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_20)))
                        : ((8U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                            ? ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                ? (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_19)
                                : (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_18))
                            : ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                ? (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_17)
                                : (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_16)))))
                : ((0x20U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                    ? ((0x10U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                        ? ((8U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                            ? ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                ? (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_15)
                                : (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_14))
                            : ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                ? (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_13)
                                : (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_12)))
                        : ((8U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                            ? ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                ? (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_11)
                                : (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_10))
                            : ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                ? (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_9)
                                : (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_8))))
                    : ((0x10U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                        ? ((8U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                            ? ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                ? (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_7)
                                : (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_6))
                            : ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                ? (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_5)
                                : (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_4)))
                        : ((8U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                            ? ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                ? (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_3)
                                : (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_2))
                            : ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                ? (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_1)
                                : (IData)(vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_0))))));
        vlTOPp->mkTestBench__DOT__SEL_ARR_soc_core_btb_btbTable_0_055_BIT_0_056___05FETC___05F_d1185 
            = (1U & ((0x40U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                      ? ((0x20U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                          ? ((0x10U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                              ? ((8U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                  ? ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                      ? vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_31[0U]
                                      : vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_30[0U])
                                  : ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                      ? vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_29[0U]
                                      : vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_28[0U]))
                              : ((8U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                  ? ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                      ? vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_27[0U]
                                      : vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_26[0U])
                                  : ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                      ? vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_25[0U]
                                      : vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_24[0U])))
                          : ((0x10U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                              ? ((8U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                  ? ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                      ? vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_23[0U]
                                      : vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_22[0U])
                                  : ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                      ? vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_21[0U]
                                      : vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_20[0U]))
                              : ((8U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                  ? ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                      ? vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_19[0U]
                                      : vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_18[0U])
                                  : ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                      ? vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_17[0U]
                                      : vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_16[0U]))))
                      : ((0x20U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                          ? ((0x10U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                              ? ((8U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                  ? ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                      ? vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_15[0U]
                                      : vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_14[0U])
                                  : ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                      ? vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_13[0U]
                                      : vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_12[0U]))
                              : ((8U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                  ? ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                      ? vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_11[0U]
                                      : vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_10[0U])
                                  : ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                      ? vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_9[0U]
                                      : vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_8[0U])))
                          : ((0x10U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                              ? ((8U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                  ? ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                      ? vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_7[0U]
                                      : vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_6[0U])
                                  : ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                      ? vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_5[0U]
                                      : vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_4[0U]))
                              : ((8U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                  ? ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                      ? vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_3[0U]
                                      : vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_2[0U])
                                  : ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                      ? vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_1[0U]
                                      : vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_0[0U]))))));
        vlTOPp->mkTestBench__DOT__SEL_ARR_soc_core_btb_btbTable_0_055_BITS_64_TO_ETC___05F_d1251 
            = ((0x40U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                ? ((0x20U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                    ? ((0x10U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                        ? ((8U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                            ? ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                ? ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_31[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_31[1U] 
                                                 >> 1U))
                                : ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_30[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_30[1U] 
                                                 >> 1U)))
                            : ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                ? ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_29[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_29[1U] 
                                                 >> 1U))
                                : ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_28[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_28[1U] 
                                                 >> 1U))))
                        : ((8U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                            ? ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                ? ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_27[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_27[1U] 
                                                 >> 1U))
                                : ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_26[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_26[1U] 
                                                 >> 1U)))
                            : ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                ? ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_25[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_25[1U] 
                                                 >> 1U))
                                : ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_24[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_24[1U] 
                                                 >> 1U)))))
                    : ((0x10U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                        ? ((8U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                            ? ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                ? ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_23[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_23[1U] 
                                                 >> 1U))
                                : ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_22[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_22[1U] 
                                                 >> 1U)))
                            : ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                ? ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_21[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_21[1U] 
                                                 >> 1U))
                                : ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_20[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_20[1U] 
                                                 >> 1U))))
                        : ((8U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                            ? ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                ? ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_19[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_19[1U] 
                                                 >> 1U))
                                : ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_18[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_18[1U] 
                                                 >> 1U)))
                            : ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                ? ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_17[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_17[1U] 
                                                 >> 1U))
                                : ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_16[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_16[1U] 
                                                 >> 1U))))))
                : ((0x20U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                    ? ((0x10U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                        ? ((8U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                            ? ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                ? ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_15[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_15[1U] 
                                                 >> 1U))
                                : ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_14[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_14[1U] 
                                                 >> 1U)))
                            : ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                ? ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_13[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_13[1U] 
                                                 >> 1U))
                                : ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_12[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_12[1U] 
                                                 >> 1U))))
                        : ((8U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                            ? ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                ? ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_11[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_11[1U] 
                                                 >> 1U))
                                : ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_10[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_10[1U] 
                                                 >> 1U)))
                            : ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                ? ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_9[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_9[1U] 
                                                 >> 1U))
                                : ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_8[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_8[1U] 
                                                 >> 1U)))))
                    : ((0x10U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                        ? ((8U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                            ? ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                ? ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_7[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_7[1U] 
                                                 >> 1U))
                                : ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_6[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_6[1U] 
                                                 >> 1U)))
                            : ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                ? ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_5[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_5[1U] 
                                                 >> 1U))
                                : ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_4[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_4[1U] 
                                                 >> 1U))))
                        : ((8U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                            ? ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                ? ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_3[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_3[1U] 
                                                 >> 1U))
                                : ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_2[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_2[1U] 
                                                 >> 1U)))
                            : ((4U & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                ? ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_1[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_1[1U] 
                                                 >> 1U))
                                : ((vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_0[2U] 
                                    << 0x1fU) | (vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_0[1U] 
                                                 >> 1U)))))));
    }
    vlTOPp->mkTestBench__DOT__instr___05Fh73336 = (
                                                   (0x800U 
                                                    & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                    ? 
                                                   ((0x400U 
                                                     & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                     ? 
                                                    ((0x200U 
                                                      & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                      ? 
                                                     ((0x100U 
                                                       & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                       ? 
                                                      ((0x80U 
                                                        & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                        ? 
                                                       ((0x40U 
                                                         & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                         ? 
                                                        ((0x20U 
                                                          & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                          ? 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_1023
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_1022)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_1021
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_1020))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_1019
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_1018)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_1017
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_1016)))
                                                          : 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_1015
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_1014)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_1013
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_1012))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_1011
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_1010)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_1009
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_1008))))
                                                         : 
                                                        ((0x20U 
                                                          & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                          ? 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_1007
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_1006)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_1005
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_1004))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_1003
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_1002)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_1001
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_1000)))
                                                          : 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_999
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_998)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_997
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_996))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_995
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_994)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_993
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_992)))))
                                                        : 
                                                       ((0x40U 
                                                         & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                         ? 
                                                        ((0x20U 
                                                          & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                          ? 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_991
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_990)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_989
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_988))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_987
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_986)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_985
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_984)))
                                                          : 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_983
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_982)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_981
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_980))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_979
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_978)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_977
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_976))))
                                                         : 
                                                        ((0x20U 
                                                          & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                          ? 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_975
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_974)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_973
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_972))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_971
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_970)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_969
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_968)))
                                                          : 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_967
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_966)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_965
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_964))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_963
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_962)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_961
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_960))))))
                                                       : 
                                                      ((0x80U 
                                                        & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                        ? 
                                                       ((0x40U 
                                                         & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                         ? 
                                                        ((0x20U 
                                                          & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                          ? 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_959
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_958)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_957
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_956))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_955
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_954)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_953
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_952)))
                                                          : 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_951
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_950)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_949
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_948))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_947
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_946)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_945
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_944))))
                                                         : 
                                                        ((0x20U 
                                                          & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                          ? 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_943
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_942)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_941
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_940))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_939
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_938)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_937
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_936)))
                                                          : 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_935
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_934)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_933
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_932))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_931
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_930)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_929
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_928)))))
                                                        : 
                                                       ((0x40U 
                                                         & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                         ? 
                                                        ((0x20U 
                                                          & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                          ? 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_927
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_926)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_925
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_924))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_923
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_922)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_921
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_920)))
                                                          : 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_919
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_918)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_917
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_916))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_915
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_914)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_913
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_912))))
                                                         : 
                                                        ((0x20U 
                                                          & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                          ? 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_911
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_910)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_909
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_908))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_907
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_906)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_905
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_904)))
                                                          : 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_903
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_902)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_901
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_900))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_899
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_898)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_897
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_896)))))))
                                                      : 
                                                     ((0x100U 
                                                       & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                       ? 
                                                      ((0x80U 
                                                        & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                        ? 
                                                       ((0x40U 
                                                         & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                         ? 
                                                        ((0x20U 
                                                          & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                          ? 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_895
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_894)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_893
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_892))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_891
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_890)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_889
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_888)))
                                                          : 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_887
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_886)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_885
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_884))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_883
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_882)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_881
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_880))))
                                                         : 
                                                        ((0x20U 
                                                          & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                          ? 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_879
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_878)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_877
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_876))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_875
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_874)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_873
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_872)))
                                                          : 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_871
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_870)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_869
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_868))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_867
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_866)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_865
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_864)))))
                                                        : 
                                                       ((0x40U 
                                                         & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                         ? 
                                                        ((0x20U 
                                                          & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                          ? 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_863
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_862)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_861
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_860))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_859
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_858)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_857
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_856)))
                                                          : 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_855
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_854)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_853
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_852))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_851
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_850)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_849
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_848))))
                                                         : 
                                                        ((0x20U 
                                                          & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                          ? 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_847
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_846)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_845
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_844))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_843
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_842)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_841
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_840)))
                                                          : 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_839
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_838)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_837
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_836))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_835
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_834)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_833
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_832))))))
                                                       : 
                                                      ((0x80U 
                                                        & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                        ? 
                                                       ((0x40U 
                                                         & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                         ? 
                                                        ((0x20U 
                                                          & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                          ? 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_831
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_830)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_829
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_828))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_827
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_826)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_825
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_824)))
                                                          : 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_823
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_822)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_821
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_820))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_819
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_818)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_817
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_816))))
                                                         : 
                                                        ((0x20U 
                                                          & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                          ? 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_815
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_814)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_813
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_812))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_811
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_810)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_809
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_808)))
                                                          : 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_807
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_806)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_805
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_804))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_803
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_802)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_801
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_800)))))
                                                        : 
                                                       ((0x40U 
                                                         & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                         ? 
                                                        ((0x20U 
                                                          & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                          ? 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_799
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_798)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_797
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_796))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_795
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_794)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_793
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_792)))
                                                          : 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_791
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_790)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_789
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_788))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_787
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_786)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_785
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_784))))
                                                         : 
                                                        ((0x20U 
                                                          & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                          ? 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_783
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_782)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_781
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_780))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_779
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_778)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_777
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_776)))
                                                          : 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_775
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_774)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_773
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_772))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_771
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_770)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_769
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_768))))))))
                                                     : 
                                                    ((0x200U 
                                                      & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                      ? 
                                                     ((0x100U 
                                                       & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                       ? 
                                                      ((0x80U 
                                                        & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                        ? 
                                                       ((0x40U 
                                                         & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                         ? 
                                                        ((0x20U 
                                                          & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                          ? 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_767
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_766)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_765
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_764))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_763
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_762)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_761
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_760)))
                                                          : 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_759
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_758)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_757
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_756))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_755
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_754)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_753
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_752))))
                                                         : 
                                                        ((0x20U 
                                                          & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                          ? 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_751
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_750)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_749
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_748))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_747
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_746)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_745
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_744)))
                                                          : 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_743
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_742)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_741
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_740))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_739
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_738)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_737
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_736)))))
                                                        : 
                                                       ((0x40U 
                                                         & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                         ? 
                                                        ((0x20U 
                                                          & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                          ? 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_735
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_734)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_733
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_732))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_731
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_730)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_729
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_728)))
                                                          : 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_727
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_726)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_725
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_724))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_723
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_722)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_721
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_720))))
                                                         : 
                                                        ((0x20U 
                                                          & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                          ? 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_719
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_718)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_717
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_716))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_715
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_714)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_713
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_712)))
                                                          : 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_711
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_710)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_709
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_708))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_707
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_706)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_705
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_704))))))
                                                       : 
                                                      ((0x80U 
                                                        & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                        ? 
                                                       ((0x40U 
                                                         & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                         ? 
                                                        ((0x20U 
                                                          & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                          ? 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_703
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_702)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_701
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_700))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_699
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_698)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_697
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_696)))
                                                          : 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_695
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_694)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_693
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_692))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_691
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_690)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_689
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_688))))
                                                         : 
                                                        ((0x20U 
                                                          & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                          ? 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_687
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_686)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_685
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_684))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_683
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_682)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_681
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_680)))
                                                          : 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_679
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_678)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_677
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_676))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_675
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_674)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_673
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_672)))))
                                                        : 
                                                       ((0x40U 
                                                         & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                         ? 
                                                        ((0x20U 
                                                          & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                          ? 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_671
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_670)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_669
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_668))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_667
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_666)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_665
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_664)))
                                                          : 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_663
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_662)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_661
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_660))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_659
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_658)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_657
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_656))))
                                                         : 
                                                        ((0x20U 
                                                          & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                          ? 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_655
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_654)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_653
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_652))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_651
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_650)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_649
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_648)))
                                                          : 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_647
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_646)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_645
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_644))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_643
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_642)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_641
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_640)))))))
                                                      : 
                                                     ((0x100U 
                                                       & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                       ? 
                                                      ((0x80U 
                                                        & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                        ? 
                                                       ((0x40U 
                                                         & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                         ? 
                                                        ((0x20U 
                                                          & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                          ? 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_639
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_638)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_637
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_636))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_635
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_634)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_633
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_632)))
                                                          : 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_631
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_630)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_629
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_628))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_627
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_626)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_625
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_624))))
                                                         : 
                                                        ((0x20U 
                                                          & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                          ? 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_623
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_622)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_621
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_620))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_619
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_618)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_617
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_616)))
                                                          : 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_615
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_614)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_613
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_612))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_611
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_610)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_609
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_608)))))
                                                        : 
                                                       ((0x40U 
                                                         & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                         ? 
                                                        ((0x20U 
                                                          & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                          ? 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_607
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_606)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_605
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_604))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_603
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_602)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_601
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_600)))
                                                          : 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_599
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_598)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_597
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_596))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_595
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_594)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_593
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_592))))
                                                         : 
                                                        ((0x20U 
                                                          & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                          ? 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_591
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_590)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_589
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_588))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_587
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_586)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_585
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_584)))
                                                          : 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_583
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_582)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_581
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_580))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_579
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_578)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_577
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_576))))))
                                                       : 
                                                      ((0x80U 
                                                        & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                        ? 
                                                       ((0x40U 
                                                         & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                         ? 
                                                        ((0x20U 
                                                          & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                          ? 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_575
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_574)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_573
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_572))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_571
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_570)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_569
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_568)))
                                                          : 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_567
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_566)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_565
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_564))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_563
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_562)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_561
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_560))))
                                                         : 
                                                        ((0x20U 
                                                          & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                          ? 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_559
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_558)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_557
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_556))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_555
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_554)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_553
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_552)))
                                                          : 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_551
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_550)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_549
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_548))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_547
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_546)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_545
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_544)))))
                                                        : 
                                                       ((0x40U 
                                                         & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                         ? 
                                                        ((0x20U 
                                                          & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                          ? 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_543
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_542)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_541
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_540))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_539
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_538)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_537
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_536)))
                                                          : 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_535
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_534)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_533
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_532))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_531
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_530)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_529
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_528))))
                                                         : 
                                                        ((0x20U 
                                                          & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                          ? 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_527
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_526)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_525
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_524))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_523
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_522)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_521
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_520)))
                                                          : 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_519
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_518)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_517
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_516))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_515
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_514)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_513
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_512)))))))))
                                                    : 
                                                   ((0x400U 
                                                     & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                     ? 
                                                    ((0x200U 
                                                      & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                      ? 
                                                     ((0x100U 
                                                       & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                       ? 
                                                      ((0x80U 
                                                        & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                        ? 
                                                       ((0x40U 
                                                         & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                         ? 
                                                        ((0x20U 
                                                          & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                          ? 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_511
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_510)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_509
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_508))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_507
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_506)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_505
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_504)))
                                                          : 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_503
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_502)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_501
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_500))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_499
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_498)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_497
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_496))))
                                                         : 
                                                        ((0x20U 
                                                          & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                          ? 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_495
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_494)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_493
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_492))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_491
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_490)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_489
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_488)))
                                                          : 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_487
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_486)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_485
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_484))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_483
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_482)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_481
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_480)))))
                                                        : 
                                                       ((0x40U 
                                                         & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                         ? 
                                                        ((0x20U 
                                                          & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                          ? 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_479
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_478)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_477
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_476))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_475
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_474)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_473
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_472)))
                                                          : 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_471
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_470)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_469
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_468))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_467
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_466)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_465
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_464))))
                                                         : 
                                                        ((0x20U 
                                                          & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                          ? 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_463
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_462)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_461
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_460))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_459
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_458)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_457
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_456)))
                                                          : 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_455
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_454)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_453
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_452))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_451
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_450)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_449
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_448))))))
                                                       : 
                                                      ((0x80U 
                                                        & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                        ? 
                                                       ((0x40U 
                                                         & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                         ? 
                                                        ((0x20U 
                                                          & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                          ? 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_447
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_446)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_445
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_444))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_443
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_442)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_441
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_440)))
                                                          : 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_439
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_438)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_437
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_436))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_435
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_434)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_433
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_432))))
                                                         : 
                                                        ((0x20U 
                                                          & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                          ? 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_431
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_430)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_429
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_428))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_427
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_426)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_425
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_424)))
                                                          : 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_423
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_422)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_421
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_420))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_419
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_418)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_417
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_416)))))
                                                        : 
                                                       ((0x40U 
                                                         & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                         ? 
                                                        ((0x20U 
                                                          & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                          ? 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_415
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_414)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_413
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_412))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_411
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_410)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_409
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_408)))
                                                          : 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_407
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_406)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_405
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_404))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_403
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_402)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_401
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_400))))
                                                         : 
                                                        ((0x20U 
                                                          & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                          ? 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_399
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_398)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_397
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_396))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_395
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_394)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_393
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_392)))
                                                          : 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_391
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_390)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_389
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_388))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_387
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_386)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_385
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_384)))))))
                                                      : 
                                                     ((0x100U 
                                                       & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                       ? 
                                                      ((0x80U 
                                                        & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                        ? 
                                                       ((0x40U 
                                                         & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                         ? 
                                                        ((0x20U 
                                                          & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                          ? 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_383
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_382)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_381
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_380))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_379
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_378)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_377
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_376)))
                                                          : 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_375
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_374)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_373
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_372))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_371
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_370)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_369
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_368))))
                                                         : 
                                                        ((0x20U 
                                                          & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                          ? 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_367
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_366)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_365
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_364))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_363
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_362)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_361
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_360)))
                                                          : 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_359
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_358)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_357
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_356))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_355
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_354)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_353
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_352)))))
                                                        : 
                                                       ((0x40U 
                                                         & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                         ? 
                                                        ((0x20U 
                                                          & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                          ? 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_351
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_350)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_349
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_348))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_347
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_346)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_345
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_344)))
                                                          : 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_343
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_342)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_341
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_340))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_339
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_338)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_337
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_336))))
                                                         : 
                                                        ((0x20U 
                                                          & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                          ? 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_335
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_334)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_333
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_332))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_331
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_330)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_329
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_328)))
                                                          : 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_327
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_326)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_325
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_324))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_323
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_322)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_321
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_320))))))
                                                       : 
                                                      ((0x80U 
                                                        & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                        ? 
                                                       ((0x40U 
                                                         & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                         ? 
                                                        ((0x20U 
                                                          & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                          ? 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_319
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_318)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_317
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_316))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_315
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_314)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_313
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_312)))
                                                          : 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_311
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_310)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_309
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_308))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_307
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_306)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_305
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_304))))
                                                         : 
                                                        ((0x20U 
                                                          & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                          ? 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_303
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_302)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_301
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_300))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_299
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_298)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_297
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_296)))
                                                          : 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_295
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_294)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_293
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_292))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_291
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_290)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_289
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_288)))))
                                                        : 
                                                       ((0x40U 
                                                         & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                         ? 
                                                        ((0x20U 
                                                          & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                          ? 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_287
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_286)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_285
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_284))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_283
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_282)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_281
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_280)))
                                                          : 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_279
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_278)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_277
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_276))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_275
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_274)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_273
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_272))))
                                                         : 
                                                        ((0x20U 
                                                          & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                          ? 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_271
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_270)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_269
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_268))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_267
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_266)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_265
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_264)))
                                                          : 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_263
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_262)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_261
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_260))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_259
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_258)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_257
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_256))))))))
                                                     : 
                                                    ((0x200U 
                                                      & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                      ? 
                                                     ((0x100U 
                                                       & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                       ? 
                                                      ((0x80U 
                                                        & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                        ? 
                                                       ((0x40U 
                                                         & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                         ? 
                                                        ((0x20U 
                                                          & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                          ? 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_255
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_254)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_253
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_252))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_251
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_250)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_249
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_248)))
                                                          : 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_247
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_246)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_245
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_244))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_243
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_242)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_241
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_240))))
                                                         : 
                                                        ((0x20U 
                                                          & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                          ? 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_239
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_238)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_237
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_236))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_235
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_234)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_233
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_232)))
                                                          : 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_231
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_230)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_229
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_228))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_227
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_226)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_225
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_224)))))
                                                        : 
                                                       ((0x40U 
                                                         & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                         ? 
                                                        ((0x20U 
                                                          & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                          ? 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_223
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_222)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_221
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_220))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_219
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_218)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_217
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_216)))
                                                          : 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_215
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_214)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_213
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_212))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_211
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_210)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_209
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_208))))
                                                         : 
                                                        ((0x20U 
                                                          & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                          ? 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_207
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_206)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_205
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_204))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_203
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_202)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_201
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_200)))
                                                          : 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_199
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_198)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_197
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_196))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_195
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_194)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_193
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_192))))))
                                                       : 
                                                      ((0x80U 
                                                        & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                        ? 
                                                       ((0x40U 
                                                         & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                         ? 
                                                        ((0x20U 
                                                          & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                          ? 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_191
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_190)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_189
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_188))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_187
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_186)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_185
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_184)))
                                                          : 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_183
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_182)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_181
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_180))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_179
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_178)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_177
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_176))))
                                                         : 
                                                        ((0x20U 
                                                          & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                          ? 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_175
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_174)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_173
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_172))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_171
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_170)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_169
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_168)))
                                                          : 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_167
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_166)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_165
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_164))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_163
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_162)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_161
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_160)))))
                                                        : 
                                                       ((0x40U 
                                                         & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                         ? 
                                                        ((0x20U 
                                                          & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                          ? 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_159
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_158)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_157
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_156))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_155
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_154)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_153
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_152)))
                                                          : 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_151
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_150)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_149
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_148))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_147
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_146)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_145
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_144))))
                                                         : 
                                                        ((0x20U 
                                                          & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                          ? 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_143
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_142)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_141
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_140))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_139
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_138)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_137
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_136)))
                                                          : 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_135
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_134)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_133
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_132))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_131
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_130)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_129
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_128)))))))
                                                      : 
                                                     ((0x100U 
                                                       & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                       ? 
                                                      ((0x80U 
                                                        & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                        ? 
                                                       ((0x40U 
                                                         & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                         ? 
                                                        ((0x20U 
                                                          & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                          ? 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_127
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_126)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_125
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_124))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_123
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_122)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_121
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_120)))
                                                          : 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_119
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_118)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_117
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_116))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_115
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_114)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_113
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_112))))
                                                         : 
                                                        ((0x20U 
                                                          & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                          ? 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_111
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_110)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_109
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_108))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_107
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_106)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_105
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_104)))
                                                          : 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_103
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_102)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_101
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_100))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_99
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_98)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_97
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_96)))))
                                                        : 
                                                       ((0x40U 
                                                         & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                         ? 
                                                        ((0x20U 
                                                          & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                          ? 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_95
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_94)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_93
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_92))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_91
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_90)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_89
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_88)))
                                                          : 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_87
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_86)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_85
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_84))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_83
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_82)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_81
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_80))))
                                                         : 
                                                        ((0x20U 
                                                          & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                          ? 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_79
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_78)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_77
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_76))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_75
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_74)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_73
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_72)))
                                                          : 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_71
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_70)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_69
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_68))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_67
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_66)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_65
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_64))))))
                                                       : 
                                                      ((0x80U 
                                                        & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                        ? 
                                                       ((0x40U 
                                                         & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                         ? 
                                                        ((0x20U 
                                                          & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                          ? 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_63
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_62)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_61
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_60))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_59
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_58)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_57
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_56)))
                                                          : 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_55
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_54)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_53
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_52))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_51
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_50)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_49
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_48))))
                                                         : 
                                                        ((0x20U 
                                                          & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                          ? 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_47
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_46)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_45
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_44))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_43
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_42)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_41
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_40)))
                                                          : 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_39
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_38)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_37
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_36))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_35
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_34)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_33
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_32)))))
                                                        : 
                                                       ((0x40U 
                                                         & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                         ? 
                                                        ((0x20U 
                                                          & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                          ? 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_31
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_30)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_29
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_28))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_27
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_26)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_25
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_24)))
                                                          : 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_23
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_22)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_21
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_20))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_19
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_18)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_17
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_16))))
                                                         : 
                                                        ((0x20U 
                                                          & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                          ? 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_15
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_14)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_13
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_12))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_11
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_10)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_9
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_8)))
                                                          : 
                                                         ((0x10U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                           ? 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_7
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_6)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_5
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_4))
                                                           : 
                                                          ((8U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                            ? 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_3
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_2)
                                                            : 
                                                           ((4U 
                                                             & vlTOPp->mkTestBench__DOT__soc_core_pcReg)
                                                             ? vlTOPp->mkTestBench__DOT__soc_core_imem_1
                                                             : vlTOPp->mkTestBench__DOT__soc_core_imem_0))))))))));
    if (((IData)(vlTOPp->mkTestBench__DOT__soc_plic_irq_pending_1) 
         & ((IData)(vlTOPp->mkTestBench__DOT__soc_plic_enable_bits) 
            >> 1U))) {
        vlTOPp->mkTestBench__DOT__IF_soc_plic_irq_pending_1_840_AND_soc_plic_ena_ETC___05F_d3891 
            = ((vlTOPp->mkTestBench__DOT__soc_plic_irq_priority_1 
                > vlTOPp->mkTestBench__DOT__soc_plic_threshold)
                ? 1U : 0U);
        vlTOPp->mkTestBench__DOT__IF_soc_plic_irq_pending_1_840_AND_soc_plic_ena_ETC___05F_d3849 
            = ((vlTOPp->mkTestBench__DOT__soc_plic_irq_priority_1 
                > vlTOPp->mkTestBench__DOT__soc_plic_threshold)
                ? vlTOPp->mkTestBench__DOT__soc_plic_irq_priority_1
                : 0U);
    } else {
        vlTOPp->mkTestBench__DOT__IF_soc_plic_irq_pending_1_840_AND_soc_plic_ena_ETC___05F_d3891 = 0U;
        vlTOPp->mkTestBench__DOT__IF_soc_plic_irq_pending_1_840_AND_soc_plic_ena_ETC___05F_d3849 = 0U;
    }
    vlTOPp->mkTestBench__DOT__WILL_FIRE_RL_soc_core_clearBranchFlushDone 
        = ((IData)(vlTOPp->mkTestBench__DOT__soc_core_branch_flush_done) 
           & (~ (IData)(vlTOPp->mkTestBench__DOT__soc_core_branch_flush)));
    vlTOPp->mkTestBench__DOT__value___05Fh117781 = 
        ((0x80000000U & ((IData)(vlTOPp->mkTestBench__DOT__soc_core_csrs_mstatus) 
                         << 0x1fU)) | ((0x7f800000U 
                                        & ((IData)(
                                                   (vlTOPp->mkTestBench__DOT__soc_core_csrs_mstatus 
                                                    >> 1U)) 
                                           << 0x17U)) 
                                       | ((0x400000U 
                                           & ((IData)(
                                                      (vlTOPp->mkTestBench__DOT__soc_core_csrs_mstatus 
                                                       >> 9U)) 
                                              << 0x16U)) 
                                          | ((0x200000U 
                                              & ((IData)(
                                                         (vlTOPp->mkTestBench__DOT__soc_core_csrs_mstatus 
                                                          >> 0xaU)) 
                                                 << 0x15U)) 
                                             | ((0x100000U 
                                                 & ((IData)(
                                                            (vlTOPp->mkTestBench__DOT__soc_core_csrs_mstatus 
                                                             >> 0xbU)) 
                                                    << 0x14U)) 
                                                | ((0x80000U 
                                                    & ((IData)(
                                                               (vlTOPp->mkTestBench__DOT__soc_core_csrs_mstatus 
                                                                >> 0xcU)) 
                                                       << 0x13U)) 
                                                   | ((0x40000U 
                                                       & ((IData)(
                                                                  (vlTOPp->mkTestBench__DOT__soc_core_csrs_mstatus 
                                                                   >> 0xdU)) 
                                                          << 0x12U)) 
                                                      | ((0x20000U 
                                                          & ((IData)(
                                                                     (vlTOPp->mkTestBench__DOT__soc_core_csrs_mstatus 
                                                                      >> 0xeU)) 
                                                             << 0x11U)) 
                                                         | ((0x18000U 
                                                             & ((IData)(
                                                                        (vlTOPp->mkTestBench__DOT__soc_core_csrs_mstatus 
                                                                         >> 0xfU)) 
                                                                << 0xfU)) 
                                                            | ((0x7000U 
                                                                & ((IData)(
                                                                           (vlTOPp->mkTestBench__DOT__soc_core_csrs_mstatus 
                                                                            >> 0x11U)) 
                                                                   << 0xcU)) 
                                                               | ((0x800U 
                                                                   & ((IData)(
                                                                              (vlTOPp->mkTestBench__DOT__soc_core_csrs_mstatus 
                                                                               >> 0x14U)) 
                                                                      << 0xbU)) 
                                                                  | ((0x400U 
                                                                      & ((IData)(
                                                                                (vlTOPp->mkTestBench__DOT__soc_core_csrs_mstatus 
                                                                                >> 0x16U)) 
                                                                         << 0xaU)) 
                                                                     | ((0x200U 
                                                                         & ((IData)(
                                                                                (vlTOPp->mkTestBench__DOT__soc_core_csrs_mstatus 
                                                                                >> 0x17U)) 
                                                                            << 9U)) 
                                                                        | ((0x100U 
                                                                            & ((IData)(
                                                                                (vlTOPp->mkTestBench__DOT__soc_core_csrs_mstatus 
                                                                                >> 0x18U)) 
                                                                               << 8U)) 
                                                                           | ((0x80U 
                                                                               & ((IData)(
                                                                                (vlTOPp->mkTestBench__DOT__soc_core_csrs_mstatus 
                                                                                >> 0x19U)) 
                                                                                << 7U)) 
                                                                              | ((0x40U 
                                                                                & ((IData)(
                                                                                (vlTOPp->mkTestBench__DOT__soc_core_csrs_mstatus 
                                                                                >> 0x1aU)) 
                                                                                << 6U)) 
                                                                                | ((0x20U 
                                                                                & ((IData)(
                                                                                (vlTOPp->mkTestBench__DOT__soc_core_csrs_mstatus 
                                                                                >> 0x1bU)) 
                                                                                << 5U)) 
                                                                                | ((0x10U 
                                                                                & ((IData)(
                                                                                (vlTOPp->mkTestBench__DOT__soc_core_csrs_mstatus 
                                                                                >> 0x1cU)) 
                                                                                << 4U)) 
                                                                                | ((8U 
                                                                                & ((IData)(
                                                                                (vlTOPp->mkTestBench__DOT__soc_core_csrs_mstatus 
                                                                                >> 0x1dU)) 
                                                                                << 3U)) 
                                                                                | ((4U 
                                                                                & ((IData)(
                                                                                (vlTOPp->mkTestBench__DOT__soc_core_csrs_mstatus 
                                                                                >> 0x1eU)) 
                                                                                << 2U)) 
                                                                                | ((2U 
                                                                                & ((IData)(
                                                                                (vlTOPp->mkTestBench__DOT__soc_core_csrs_mstatus 
                                                                                >> 0x1fU)) 
                                                                                << 1U)) 
                                                                                | ((1U 
                                                                                & (IData)(
                                                                                (vlTOPp->mkTestBench__DOT__soc_core_csrs_mstatus 
                                                                                >> 0x20U)))
                                                                                 ? 1U
                                                                                 : 0U))))))))))))))))))))));
    vlTOPp->mkTestBench__DOT__MUX_soc_resp_ready__024write_1___05FSEL_1 
        = ((vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[2U] 
            >> 5U) & (1U == (3U & ((vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U] 
                                    << 0x1dU) | (vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[0U] 
                                                 >> 3U)))));
    vlTOPp->mkTestBench__DOT__soc_core_current_mem_req_585_BITS_68_TO_37_587_ETC___05F_d2701 
        = ((((((((0x2000000U > ((vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[2U] 
                                 << 0x1bU) | (vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U] 
                                              >> 5U))) 
                 | (0x2010000U <= ((vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[2U] 
                                    << 0x1bU) | (vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U] 
                                                 >> 5U)))) 
                & (0xc000000U <= ((vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[2U] 
                                   << 0x1bU) | (vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U] 
                                                >> 5U)))) 
               & (0xc100000U > ((vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[2U] 
                                 << 0x1bU) | (vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U] 
                                              >> 5U)))) 
              & (2U == (3U & ((vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U] 
                               << 0x1dU) | (vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[0U] 
                                            >> 3U))))) 
             & ((0xc000004U > ((vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[2U] 
                                << 0x1bU) | (vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U] 
                                             >> 5U))) 
                | (0xc000024U <= ((vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[2U] 
                                   << 0x1bU) | (vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U] 
                                                >> 5U))))) 
            & (0xc200004U == ((vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[2U] 
                               << 0x1bU) | (vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U] 
                                            >> 5U)))) 
           & (8U > ((vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U] 
                     << 0x1bU) | (vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[0U] 
                                  >> 5U))));
    vlTOPp->mkTestBench__DOT__soc_core_current_mem_req_585_BITS_68_TO_37_587_ETC___05F_d3794 
        = (((((((0x2000000U > ((vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[2U] 
                                << 0x1bU) | (vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U] 
                                             >> 5U))) 
                | (0x2010000U <= ((vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[2U] 
                                   << 0x1bU) | (vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U] 
                                                >> 5U)))) 
               & ((0xc000000U > ((vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[2U] 
                                  << 0x1bU) | (vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U] 
                                               >> 5U))) 
                  | (0xc100000U <= ((vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[2U] 
                                     << 0x1bU) | (vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U] 
                                                  >> 5U))))) 
              & ((0x10000000U > ((vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[2U] 
                                  << 0x1bU) | (vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U] 
                                               >> 5U))) 
                 | (0x10001000U <= ((vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[2U] 
                                     << 0x1bU) | (vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U] 
                                                  >> 5U))))) 
             & (0x80000000U <= ((vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[2U] 
                                 << 0x1bU) | (vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U] 
                                              >> 5U)))) 
            & (2U == (3U & ((vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U] 
                             << 0x1dU) | (vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[0U] 
                                          >> 3U))))) 
           & (0x80001000U == ((vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[2U] 
                               << 0x1bU) | (vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U] 
                                            >> 5U))));
    vlTOPp->mkTestBench__DOT__soc_core_current_mem_req_585_BIT_69_586_AND_so_ETC___05F_d2659 
        = (((vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[2U] 
             >> 5U) & ((0x2000000U > ((vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[2U] 
                                       << 0x1bU) | 
                                      (vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U] 
                                       >> 5U))) | (0x2010000U 
                                                   <= 
                                                   ((vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[2U] 
                                                     << 0x1bU) 
                                                    | (vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U] 
                                                       >> 5U))))) 
           & ((((((((0xc000000U <= ((vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[2U] 
                                     << 0x1bU) | (vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U] 
                                                  >> 5U))) 
                    & (0xc100000U > ((vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[2U] 
                                      << 0x1bU) | (
                                                   vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U] 
                                                   >> 5U)))) 
                   & (2U == (3U & ((vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U] 
                                    << 0x1dU) | (vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[0U] 
                                                 >> 3U))))) 
                  & (0xc000000U != ((vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[2U] 
                                     << 0x1bU) | (vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U] 
                                                  >> 5U)))) 
                 & (0xc000004U <= ((vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[2U] 
                                    << 0x1bU) | (vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U] 
                                                 >> 5U)))) 
                & (0xc000024U > ((vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[2U] 
                                  << 0x1bU) | (vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U] 
                                               >> 5U)))) 
               & (0U != (0x3fffffffU & ((((vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[2U] 
                                           << 0x1bU) 
                                          | (vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U] 
                                             >> 5U)) 
                                         - (IData)(0xc000004U)) 
                                        >> 2U)))) & 
              (8U > (0x3fffffffU & ((((vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[2U] 
                                       << 0x1bU) | 
                                      (vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U] 
                                       >> 5U)) - (IData)(0xc000004U)) 
                                    >> 2U)))));
    vlTOPp->mkTestBench__DOT__soc_core_current_mem_req_585_BIT_69_586_AND_so_ETC___05F_d2728 
        = (((vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[2U] 
             >> 5U) & ((0x2000000U > ((vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[2U] 
                                       << 0x1bU) | 
                                      (vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U] 
                                       >> 5U))) | (0x2010000U 
                                                   <= 
                                                   ((vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[2U] 
                                                     << 0x1bU) 
                                                    | (vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U] 
                                                       >> 5U))))) 
           & ((((((0xc000000U > ((vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[2U] 
                                  << 0x1bU) | (vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U] 
                                               >> 5U))) 
                  | (0xc100000U <= ((vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[2U] 
                                     << 0x1bU) | (vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U] 
                                                  >> 5U)))) 
                 & (0x10000000U <= ((vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[2U] 
                                     << 0x1bU) | (vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U] 
                                                  >> 5U)))) 
                & (0x10001000U > ((vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[2U] 
                                   << 0x1bU) | (vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U] 
                                                >> 5U)))) 
               & (2U == (3U & ((vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U] 
                                << 0x1dU) | (vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[0U] 
                                             >> 3U))))) 
              & (0U == (0xffU & ((vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[2U] 
                                  << 0x1bU) | (vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U] 
                                               >> 5U))))));
    vlTOPp->mkTestBench__DOT__soc_core_current_mem_req_585_BIT_69_586_AND_so_ETC___05F_d2765 
        = (((vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[2U] 
             >> 5U) & ((0x2000000U > ((vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[2U] 
                                       << 0x1bU) | 
                                      (vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U] 
                                       >> 5U))) | (0x2010000U 
                                                   <= 
                                                   ((vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[2U] 
                                                     << 0x1bU) 
                                                    | (vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U] 
                                                       >> 5U))))) 
           & (((((0xc000000U > ((vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[2U] 
                                 << 0x1bU) | (vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U] 
                                              >> 5U))) 
                 | (0xc100000U <= ((vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[2U] 
                                    << 0x1bU) | (vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U] 
                                                 >> 5U)))) 
                & ((0x10000000U > ((vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[2U] 
                                    << 0x1bU) | (vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U] 
                                                 >> 5U))) 
                   | (0x10001000U <= ((vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[2U] 
                                       << 0x1bU) | 
                                      (vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U] 
                                       >> 5U))))) & 
               (0x80000000U <= ((vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[2U] 
                                 << 0x1bU) | (vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U] 
                                              >> 5U)))) 
              & (2U == (3U & ((vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U] 
                               << 0x1dU) | (vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[0U] 
                                            >> 3U))))));
    vlTOPp->mkTestBench__DOT__MUX_soc_clint_mtime__024write_1___05FVAL_1 
        = ((0x200bff8U == ((vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[2U] 
                            << 0x1bU) | (vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U] 
                                         >> 5U))) ? 
           (((QData)((IData)((vlTOPp->mkTestBench__DOT__soc_clint_mtime 
                              >> 0x20U))) << 0x20U) 
            | (QData)((IData)(((vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U] 
                                << 0x1bU) | (vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[0U] 
                                             >> 5U)))))
            : (((QData)((IData)(((vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U] 
                                  << 0x1bU) | (vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[0U] 
                                               >> 5U)))) 
                << 0x20U) | (QData)((IData)(vlTOPp->mkTestBench__DOT__soc_clint_mtime))));
    vlTOPp->mkTestBench__DOT__MUX_soc_uart_ip__024write_1___05FVAL_1 
        = (vlTOPp->mkTestBench__DOT__soc_uart_ip & 
           (~ ((vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U] 
                << 0x1bU) | (vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[0U] 
                             >> 5U))));
    vlTOPp->mkTestBench__DOT__soc_clint_mtimecmp__024D_IN 
        = ((0x2004000U == ((vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[2U] 
                            << 0x1bU) | (vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U] 
                                         >> 5U))) ? 
           (((QData)((IData)((vlTOPp->mkTestBench__DOT__soc_clint_mtimecmp 
                              >> 0x20U))) << 0x20U) 
            | (QData)((IData)(((vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U] 
                                << 0x1bU) | (vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[0U] 
                                             >> 5U)))))
            : (((QData)((IData)(((vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U] 
                                  << 0x1bU) | (vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[0U] 
                                               >> 5U)))) 
                << 0x20U) | (QData)((IData)(vlTOPp->mkTestBench__DOT__soc_clint_mtimecmp))));
    vlTOPp->mkTestBench__DOT__soc_resp_ready__024EN 
        = (((vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[2U] 
             >> 5U) & (1U == (3U & ((vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U] 
                                     << 0x1dU) | (vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[0U] 
                                                  >> 3U))))) 
           | (IData)(vlTOPp->mkTestBench__DOT__soc_resp_ready));
    vlTOPp->mkTestBench__DOT__result___05F_1___05Fh165630 
        = (((((((((0U == (0x3fffffffU & ((((vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[2U] 
                                            << 0x1bU) 
                                           | (vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U] 
                                              >> 5U)) 
                                          - (IData)(0xc000004U)) 
                                         >> 2U))) | 
                  (1U == (0x3fffffffU & ((((vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[2U] 
                                            << 0x1bU) 
                                           | (vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U] 
                                              >> 5U)) 
                                          - (IData)(0xc000004U)) 
                                         >> 2U)))) 
                 | (2U == (0x3fffffffU & ((((vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[2U] 
                                             << 0x1bU) 
                                            | (vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U] 
                                               >> 5U)) 
                                           - (IData)(0xc000004U)) 
                                          >> 2U)))) 
                | (3U == (0x3fffffffU & ((((vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[2U] 
                                            << 0x1bU) 
                                           | (vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U] 
                                              >> 5U)) 
                                          - (IData)(0xc000004U)) 
                                         >> 2U)))) 
               | (4U == (0x3fffffffU & ((((vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[2U] 
                                           << 0x1bU) 
                                          | (vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U] 
                                             >> 5U)) 
                                         - (IData)(0xc000004U)) 
                                        >> 2U)))) | 
              (5U == (0x3fffffffU & ((((vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[2U] 
                                        << 0x1bU) | 
                                       (vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U] 
                                        >> 5U)) - (IData)(0xc000004U)) 
                                     >> 2U)))) | (6U 
                                                  == 
                                                  (0x3fffffffU 
                                                   & ((((vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[2U] 
                                                         << 0x1bU) 
                                                        | (vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U] 
                                                           >> 5U)) 
                                                       - (IData)(0xc000004U)) 
                                                      >> 2U)))) 
            | (7U == (0x3fffffffU & ((((vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[2U] 
                                        << 0x1bU) | 
                                       (vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U] 
                                        >> 5U)) - (IData)(0xc000004U)) 
                                     >> 2U)))) ? ((0U 
                                                   == 
                                                   (0x3fffffffU 
                                                    & ((((vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[2U] 
                                                          << 0x1bU) 
                                                         | (vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U] 
                                                            >> 5U)) 
                                                        - (IData)(0xc000004U)) 
                                                       >> 2U)))
                                                   ? vlTOPp->mkTestBench__DOT__soc_plic_irq_priority_0
                                                   : 
                                                  ((1U 
                                                    == 
                                                    (0x3fffffffU 
                                                     & ((((vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[2U] 
                                                           << 0x1bU) 
                                                          | (vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U] 
                                                             >> 5U)) 
                                                         - (IData)(0xc000004U)) 
                                                        >> 2U)))
                                                    ? vlTOPp->mkTestBench__DOT__soc_plic_irq_priority_1
                                                    : 
                                                   ((2U 
                                                     == 
                                                     (0x3fffffffU 
                                                      & ((((vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[2U] 
                                                            << 0x1bU) 
                                                           | (vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U] 
                                                              >> 5U)) 
                                                          - (IData)(0xc000004U)) 
                                                         >> 2U)))
                                                     ? vlTOPp->mkTestBench__DOT__soc_plic_irq_priority_2
                                                     : 
                                                    ((3U 
                                                      == 
                                                      (0x3fffffffU 
                                                       & ((((vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[2U] 
                                                             << 0x1bU) 
                                                            | (vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U] 
                                                               >> 5U)) 
                                                           - (IData)(0xc000004U)) 
                                                          >> 2U)))
                                                      ? vlTOPp->mkTestBench__DOT__soc_plic_irq_priority_3
                                                      : 
                                                     ((4U 
                                                       == 
                                                       (0x3fffffffU 
                                                        & ((((vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[2U] 
                                                              << 0x1bU) 
                                                             | (vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U] 
                                                                >> 5U)) 
                                                            - (IData)(0xc000004U)) 
                                                           >> 2U)))
                                                       ? vlTOPp->mkTestBench__DOT__soc_plic_irq_priority_4
                                                       : 
                                                      ((5U 
                                                        == 
                                                        (0x3fffffffU 
                                                         & ((((vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[2U] 
                                                               << 0x1bU) 
                                                              | (vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U] 
                                                                 >> 5U)) 
                                                             - (IData)(0xc000004U)) 
                                                            >> 2U)))
                                                        ? vlTOPp->mkTestBench__DOT__soc_plic_irq_priority_5
                                                        : 
                                                       ((6U 
                                                         == 
                                                         (0x3fffffffU 
                                                          & ((((vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[2U] 
                                                                << 0x1bU) 
                                                               | (vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U] 
                                                                  >> 5U)) 
                                                              - (IData)(0xc000004U)) 
                                                             >> 2U)))
                                                         ? vlTOPp->mkTestBench__DOT__soc_plic_irq_priority_6
                                                         : vlTOPp->mkTestBench__DOT__soc_plic_irq_priority_7)))))))
            : 0xaaaaaaaaU);
    vlTOPp->mkTestBench__DOT__rdata___05F_1___05Fh166694 
        = ((0x8000U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
            ? ((0x4000U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                ? ((0x2000U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                    ? ((0x1000U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                        ? ((0x800U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                            ? ((0x400U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                ? ((0x200U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                    ? ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_511
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_510)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_509
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_508))
                                    : ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_507
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_506)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_505
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_504)))
                                : ((0x200U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                    ? ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_503
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_502)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_501
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_500))
                                    : ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_499
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_498)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_497
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_496))))
                            : ((0x400U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                ? ((0x200U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                    ? ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_495
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_494)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_493
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_492))
                                    : ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_491
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_490)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_489
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_488)))
                                : ((0x200U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                    ? ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_487
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_486)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_485
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_484))
                                    : ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_483
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_482)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_481
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_480)))))
                        : ((0x800U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                            ? ((0x400U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                ? ((0x200U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                    ? ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_479
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_478)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_477
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_476))
                                    : ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_475
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_474)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_473
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_472)))
                                : ((0x200U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                    ? ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_471
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_470)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_469
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_468))
                                    : ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_467
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_466)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_465
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_464))))
                            : ((0x400U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                ? ((0x200U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                    ? ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_463
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_462)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_461
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_460))
                                    : ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_459
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_458)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_457
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_456)))
                                : ((0x200U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                    ? ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_455
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_454)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_453
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_452))
                                    : ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_451
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_450)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_449
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_448))))))
                    : ((0x1000U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                        ? ((0x800U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                            ? ((0x400U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                ? ((0x200U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                    ? ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_447
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_446)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_445
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_444))
                                    : ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_443
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_442)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_441
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_440)))
                                : ((0x200U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                    ? ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_439
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_438)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_437
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_436))
                                    : ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_435
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_434)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_433
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_432))))
                            : ((0x400U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                ? ((0x200U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                    ? ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_431
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_430)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_429
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_428))
                                    : ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_427
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_426)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_425
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_424)))
                                : ((0x200U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                    ? ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_423
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_422)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_421
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_420))
                                    : ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_419
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_418)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_417
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_416)))))
                        : ((0x800U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                            ? ((0x400U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                ? ((0x200U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                    ? ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_415
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_414)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_413
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_412))
                                    : ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_411
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_410)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_409
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_408)))
                                : ((0x200U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                    ? ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_407
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_406)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_405
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_404))
                                    : ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_403
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_402)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_401
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_400))))
                            : ((0x400U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                ? ((0x200U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                    ? ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_399
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_398)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_397
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_396))
                                    : ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_395
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_394)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_393
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_392)))
                                : ((0x200U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                    ? ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_391
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_390)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_389
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_388))
                                    : ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_387
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_386)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_385
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_384)))))))
                : ((0x2000U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                    ? ((0x1000U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                        ? ((0x800U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                            ? ((0x400U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                ? ((0x200U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                    ? ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_383
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_382)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_381
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_380))
                                    : ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_379
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_378)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_377
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_376)))
                                : ((0x200U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                    ? ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_375
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_374)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_373
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_372))
                                    : ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_371
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_370)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_369
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_368))))
                            : ((0x400U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                ? ((0x200U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                    ? ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_367
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_366)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_365
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_364))
                                    : ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_363
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_362)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_361
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_360)))
                                : ((0x200U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                    ? ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_359
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_358)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_357
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_356))
                                    : ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_355
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_354)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_353
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_352)))))
                        : ((0x800U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                            ? ((0x400U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                ? ((0x200U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                    ? ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_351
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_350)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_349
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_348))
                                    : ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_347
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_346)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_345
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_344)))
                                : ((0x200U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                    ? ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_343
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_342)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_341
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_340))
                                    : ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_339
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_338)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_337
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_336))))
                            : ((0x400U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                ? ((0x200U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                    ? ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_335
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_334)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_333
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_332))
                                    : ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_331
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_330)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_329
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_328)))
                                : ((0x200U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                    ? ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_327
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_326)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_325
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_324))
                                    : ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_323
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_322)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_321
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_320))))))
                    : ((0x1000U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                        ? ((0x800U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                            ? ((0x400U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                ? ((0x200U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                    ? ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_319
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_318)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_317
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_316))
                                    : ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_315
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_314)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_313
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_312)))
                                : ((0x200U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                    ? ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_311
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_310)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_309
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_308))
                                    : ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_307
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_306)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_305
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_304))))
                            : ((0x400U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                ? ((0x200U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                    ? ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_303
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_302)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_301
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_300))
                                    : ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_299
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_298)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_297
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_296)))
                                : ((0x200U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                    ? ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_295
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_294)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_293
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_292))
                                    : ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_291
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_290)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_289
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_288)))))
                        : ((0x800U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                            ? ((0x400U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                ? ((0x200U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                    ? ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_287
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_286)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_285
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_284))
                                    : ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_283
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_282)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_281
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_280)))
                                : ((0x200U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                    ? ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_279
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_278)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_277
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_276))
                                    : ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_275
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_274)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_273
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_272))))
                            : ((0x400U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                ? ((0x200U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                    ? ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_271
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_270)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_269
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_268))
                                    : ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_267
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_266)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_265
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_264)))
                                : ((0x200U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                    ? ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_263
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_262)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_261
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_260))
                                    : ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_259
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_258)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_257
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_256))))))))
            : ((0x4000U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                ? ((0x2000U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                    ? ((0x1000U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                        ? ((0x800U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                            ? ((0x400U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                ? ((0x200U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                    ? ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_255
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_254)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_253
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_252))
                                    : ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_251
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_250)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_249
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_248)))
                                : ((0x200U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                    ? ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_247
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_246)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_245
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_244))
                                    : ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_243
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_242)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_241
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_240))))
                            : ((0x400U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                ? ((0x200U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                    ? ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_239
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_238)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_237
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_236))
                                    : ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_235
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_234)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_233
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_232)))
                                : ((0x200U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                    ? ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_231
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_230)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_229
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_228))
                                    : ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_227
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_226)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_225
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_224)))))
                        : ((0x800U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                            ? ((0x400U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                ? ((0x200U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                    ? ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_223
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_222)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_221
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_220))
                                    : ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_219
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_218)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_217
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_216)))
                                : ((0x200U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                    ? ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_215
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_214)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_213
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_212))
                                    : ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_211
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_210)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_209
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_208))))
                            : ((0x400U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                ? ((0x200U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                    ? ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_207
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_206)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_205
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_204))
                                    : ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_203
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_202)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_201
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_200)))
                                : ((0x200U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                    ? ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_199
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_198)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_197
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_196))
                                    : ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_195
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_194)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_193
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_192))))))
                    : ((0x1000U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                        ? ((0x800U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                            ? ((0x400U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                ? ((0x200U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                    ? ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_191
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_190)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_189
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_188))
                                    : ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_187
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_186)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_185
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_184)))
                                : ((0x200U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                    ? ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_183
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_182)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_181
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_180))
                                    : ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_179
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_178)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_177
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_176))))
                            : ((0x400U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                ? ((0x200U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                    ? ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_175
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_174)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_173
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_172))
                                    : ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_171
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_170)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_169
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_168)))
                                : ((0x200U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                    ? ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_167
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_166)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_165
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_164))
                                    : ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_163
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_162)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_161
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_160)))))
                        : ((0x800U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                            ? ((0x400U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                ? ((0x200U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                    ? ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_159
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_158)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_157
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_156))
                                    : ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_155
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_154)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_153
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_152)))
                                : ((0x200U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                    ? ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_151
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_150)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_149
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_148))
                                    : ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_147
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_146)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_145
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_144))))
                            : ((0x400U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                ? ((0x200U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                    ? ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_143
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_142)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_141
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_140))
                                    : ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_139
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_138)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_137
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_136)))
                                : ((0x200U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                    ? ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_135
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_134)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_133
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_132))
                                    : ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_131
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_130)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_129
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_128)))))))
                : ((0x2000U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                    ? ((0x1000U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                        ? ((0x800U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                            ? ((0x400U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                ? ((0x200U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                    ? ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_127
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_126)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_125
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_124))
                                    : ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_123
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_122)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_121
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_120)))
                                : ((0x200U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                    ? ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_119
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_118)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_117
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_116))
                                    : ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_115
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_114)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_113
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_112))))
                            : ((0x400U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                ? ((0x200U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                    ? ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_111
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_110)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_109
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_108))
                                    : ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_107
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_106)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_105
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_104)))
                                : ((0x200U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                    ? ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_103
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_102)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_101
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_100))
                                    : ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_99
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_98)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_97
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_96)))))
                        : ((0x800U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                            ? ((0x400U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                ? ((0x200U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                    ? ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_95
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_94)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_93
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_92))
                                    : ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_91
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_90)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_89
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_88)))
                                : ((0x200U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                    ? ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_87
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_86)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_85
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_84))
                                    : ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_83
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_82)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_81
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_80))))
                            : ((0x400U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                ? ((0x200U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                    ? ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_79
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_78)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_77
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_76))
                                    : ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_75
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_74)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_73
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_72)))
                                : ((0x200U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                    ? ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_71
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_70)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_69
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_68))
                                    : ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_67
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_66)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_65
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_64))))))
                    : ((0x1000U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                        ? ((0x800U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                            ? ((0x400U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                ? ((0x200U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                    ? ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_63
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_62)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_61
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_60))
                                    : ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_59
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_58)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_57
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_56)))
                                : ((0x200U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                    ? ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_55
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_54)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_53
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_52))
                                    : ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_51
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_50)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_49
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_48))))
                            : ((0x400U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                ? ((0x200U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                    ? ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_47
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_46)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_45
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_44))
                                    : ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_43
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_42)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_41
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_40)))
                                : ((0x200U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                    ? ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_39
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_38)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_37
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_36))
                                    : ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_35
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_34)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_33
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_32)))))
                        : ((0x800U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                            ? ((0x400U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                ? ((0x200U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                    ? ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_31
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_30)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_29
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_28))
                                    : ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_27
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_26)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_25
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_24)))
                                : ((0x200U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                    ? ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_23
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_22)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_21
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_20))
                                    : ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_19
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_18)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_17
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_16))))
                            : ((0x400U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                ? ((0x200U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                    ? ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_15
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_14)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_13
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_12))
                                    : ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_11
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_10)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_9
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_8)))
                                : ((0x200U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                    ? ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_7
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_6)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_5
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_4))
                                    : ((0x100U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                        ? ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_3
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_2)
                                        : ((0x80U & 
                                            vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                                            ? vlTOPp->mkTestBench__DOT__soc_dmem_memory_1
                                            : vlTOPp->mkTestBench__DOT__soc_dmem_memory_0)))))))));
    vlTOPp->mkTestBench__DOT__soc_core_mem2wb__024D_IN[0U] 
        = ((0xffffff80U & ((vlTOPp->mkTestBench__DOT__soc_core_ex2mem__DOT__data0_reg[3U] 
                            << 0x17U) | (0x7fff80U 
                                         & (vlTOPp->mkTestBench__DOT__soc_core_ex2mem__DOT__data0_reg[2U] 
                                            >> 9U)))) 
           | ((0x7cU & ((vlTOPp->mkTestBench__DOT__soc_core_ex2mem__DOT__data0_reg[2U] 
                         << 0x17U) | (0x7ffffcU & (
                                                   vlTOPp->mkTestBench__DOT__soc_core_ex2mem__DOT__data0_reg[1U] 
                                                   >> 9U)))) 
              | (3U & ((vlTOPp->mkTestBench__DOT__soc_core_ex2mem__DOT__data0_reg[1U] 
                        << 0x1dU) | (vlTOPp->mkTestBench__DOT__soc_core_ex2mem__DOT__data0_reg[0U] 
                                     >> 3U)))));
    vlTOPp->mkTestBench__DOT__soc_core_mem2wb__024D_IN[1U] 
        = ((0x7fU & (vlTOPp->mkTestBench__DOT__soc_core_ex2mem__DOT__data0_reg[3U] 
                     >> 9U)) | (0xffffff80U & ((IData)(
                                                       ((QData)((IData)(
                                                                        ((vlTOPp->mkTestBench__DOT__soc_core_ex2mem__DOT__data0_reg[4U] 
                                                                          << 0x10U) 
                                                                         | (vlTOPp->mkTestBench__DOT__soc_core_ex2mem__DOT__data0_reg[3U] 
                                                                            >> 0x10U)))) 
                                                        << 0x20U)) 
                                               << 7U)));
    vlTOPp->mkTestBench__DOT__soc_core_mem2wb__024D_IN[2U] 
        = ((0x7fU & ((IData)(((QData)((IData)(((vlTOPp->mkTestBench__DOT__soc_core_ex2mem__DOT__data0_reg[4U] 
                                                << 0x10U) 
                                               | (vlTOPp->mkTestBench__DOT__soc_core_ex2mem__DOT__data0_reg[3U] 
                                                  >> 0x10U)))) 
                              << 0x20U)) >> 0x19U)) 
           | (0xffffff80U & ((IData)((((QData)((IData)(
                                                       ((vlTOPp->mkTestBench__DOT__soc_core_ex2mem__DOT__data0_reg[4U] 
                                                         << 0x10U) 
                                                        | (vlTOPp->mkTestBench__DOT__soc_core_ex2mem__DOT__data0_reg[3U] 
                                                           >> 0x10U)))) 
                                       << 0x20U) >> 0x20U)) 
                             << 7U)));
    vlTOPp->mkTestBench__DOT__soc_core_mem2wb__024D_IN[3U] 
        = (0x7fU & ((IData)((((QData)((IData)(((vlTOPp->mkTestBench__DOT__soc_core_ex2mem__DOT__data0_reg[4U] 
                                                << 0x10U) 
                                               | (vlTOPp->mkTestBench__DOT__soc_core_ex2mem__DOT__data0_reg[3U] 
                                                  >> 0x10U)))) 
                              << 0x20U) >> 0x20U)) 
                    >> 0x19U));
    vlTOPp->mkTestBench__DOT__WILL_FIRE_RL_soc_core_memoryStage 
        = ((IData)(vlTOPp->mkTestBench__DOT__soc_core_ex2mem__DOT__empty_reg) 
           & (IData)(vlTOPp->mkTestBench__DOT__soc_core_mem2wb__DOT__full_reg));
    vlTOPp->mkTestBench__DOT__x___05Fh111983 = ((0x200U 
                                                 & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                                                 ? 
                                                ((0x100U 
                                                  & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                                                  ? 
                                                 ((0x80U 
                                                   & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                                                   ? 0U
                                                   : 
                                                  ((0x40U 
                                                    & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                                                    ? 
                                                   ((0x20U 
                                                     & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                                                     ? 
                                                    ((0x10U 
                                                      & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                                                      ? 
                                                     ((8U 
                                                       & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                                                       ? 
                                                      ((0xffe00000U 
                                                        & ((- (IData)(
                                                                      (1U 
                                                                       & (vlTOPp->mkTestBench__DOT__imm21___05Fh112201 
                                                                          >> 0x14U)))) 
                                                           << 0x15U)) 
                                                       | vlTOPp->mkTestBench__DOT__imm21___05Fh112201)
                                                       : 0U)
                                                      : 0U)
                                                     : 0U)
                                                    : 
                                                   ((0x20U 
                                                     & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                                                     ? 
                                                    ((0x10U 
                                                      & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                                                      ? 
                                                     ((8U 
                                                       & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                                                       ? vlTOPp->mkTestBench__DOT__imm___05Fh110387
                                                       : 0U)
                                                      : 0U)
                                                     : 
                                                    ((0x10U 
                                                      & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                                                      ? 
                                                     ((8U 
                                                       & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                                                       ? 
                                                      ((0xffffe000U 
                                                        & ((- (IData)(
                                                                      (1U 
                                                                       & ((IData)(vlTOPp->mkTestBench__DOT__imm13___05Fh112075) 
                                                                          >> 0xcU)))) 
                                                           << 0xdU)) 
                                                       | (IData)(vlTOPp->mkTestBench__DOT__imm13___05Fh112075))
                                                       : 0U)
                                                      : 0U))))
                                                  : 0U)
                                                 : 
                                                ((0x100U 
                                                  & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                                                  ? 
                                                 ((0x80U 
                                                   & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                                                   ? 
                                                  ((0x40U 
                                                    & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                                                    ? 0U
                                                    : 
                                                   ((0x20U 
                                                     & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                                                     ? 
                                                    ((0x10U 
                                                      & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                                                      ? 
                                                     ((8U 
                                                       & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                                                       ? 
                                                      (0xfffff000U 
                                                       & ((vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[2U] 
                                                           << 0x1dU) 
                                                          | (0x1ffff000U 
                                                             & (vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U] 
                                                                >> 3U))))
                                                       : 0U)
                                                      : 0U)
                                                     : 0U))
                                                   : 
                                                  ((0x40U 
                                                    & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                                                    ? 0U
                                                    : 
                                                   ((0x20U 
                                                     & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                                                     ? 0U
                                                     : 
                                                    ((0x10U 
                                                      & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                                                      ? 
                                                     ((8U 
                                                       & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                                                       ? 
                                                      ((0xfffff000U 
                                                        & ((- (IData)(
                                                                      (1U 
                                                                       & ((IData)(vlTOPp->mkTestBench__DOT__imm12___05Fh112030) 
                                                                          >> 0xbU)))) 
                                                           << 0xcU)) 
                                                       | (IData)(vlTOPp->mkTestBench__DOT__imm12___05Fh112030))
                                                       : 0U)
                                                      : 0U))))
                                                  : 
                                                 ((0x80U 
                                                   & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                                                   ? 
                                                  ((0x40U 
                                                    & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                                                    ? 0U
                                                    : 
                                                   ((0x20U 
                                                     & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                                                     ? 
                                                    ((0x10U 
                                                      & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                                                      ? 
                                                     ((8U 
                                                       & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                                                       ? 
                                                      (0xfffff000U 
                                                       & ((vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[2U] 
                                                           << 0x1dU) 
                                                          | (0x1ffff000U 
                                                             & (vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U] 
                                                                >> 3U))))
                                                       : 0U)
                                                      : 0U)
                                                     : 
                                                    ((0x10U 
                                                      & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                                                      ? 
                                                     ((8U 
                                                       & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                                                       ? vlTOPp->mkTestBench__DOT__imm___05Fh110387
                                                       : 0U)
                                                      : 0U)))
                                                   : 
                                                  ((0x40U 
                                                    & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                                                    ? 0U
                                                    : 
                                                   ((0x20U 
                                                     & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                                                     ? 0U
                                                     : 
                                                    ((0x10U 
                                                      & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                                                      ? 
                                                     ((8U 
                                                       & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                                                       ? vlTOPp->mkTestBench__DOT__imm___05Fh110387
                                                       : 0U)
                                                      : 0U))))));
    vlTOPp->mkTestBench__DOT__soc_core_if2id_first___05F414_BITS_41_TO_35_415_EQ_ETC___05F_d1464 
        = (((((0x33U == (0x7fU & ((vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[2U] 
                                   << 0x1dU) | (vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U] 
                                                >> 3U)))) 
              | (0x23U == (0x7fU & ((vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[2U] 
                                     << 0x1dU) | (vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U] 
                                                  >> 3U))))) 
             | (0x63U == (0x7fU & ((vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[2U] 
                                    << 0x1dU) | (vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U] 
                                                 >> 3U))))) 
            & (IData)(vlTOPp->mkTestBench__DOT__soc_core_if2id_first___05F414_BITS_59_TO_55_427_EQ_ETC___05F_d1428)) 
           | ((((((((0x33U == (0x7fU & ((vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[2U] 
                                         << 0x1dU) 
                                        | (vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U] 
                                           >> 3U)))) 
                    | (0x13U == (0x7fU & ((vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[2U] 
                                           << 0x1dU) 
                                          | (vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U] 
                                             >> 3U))))) 
                   | (3U == (0x7fU & ((vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[2U] 
                                       << 0x1dU) | 
                                      (vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U] 
                                       >> 3U))))) | 
                  (0x23U == (0x7fU & ((vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[2U] 
                                       << 0x1dU) | 
                                      (vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U] 
                                       >> 3U))))) | 
                 (0x63U == (0x7fU & ((vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[2U] 
                                      << 0x1dU) | (
                                                   vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U] 
                                                   >> 3U))))) 
                | (0x67U == (0x7fU & ((vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[2U] 
                                       << 0x1dU) | 
                                      (vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U] 
                                       >> 3U))))) | 
               ((((0x73U == (0x7fU & ((vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[2U] 
                                       << 0x1dU) | 
                                      (vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U] 
                                       >> 3U)))) & 
                  (2U != (7U & ((vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[2U] 
                                 << 0x11U) | (vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U] 
                                              >> 0xfU))))) 
                 & (5U != (7U & ((vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[2U] 
                                  << 0x11U) | (vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U] 
                                               >> 0xfU))))) 
                & (7U != (7U & ((vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[2U] 
                                 << 0x11U) | (vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U] 
                                              >> 0xfU)))))) 
              & (IData)(vlTOPp->mkTestBench__DOT__soc_core_if2id_first___05F414_BITS_54_TO_50_461_EQ_ETC___05F_d1462)));
    vlTOPp->mkTestBench__DOT__soc_core_id2ex_first___05F406_BITS_247_TO_245_074___05FETC___05F_d2110 
        = ((((1U == (7U & ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U] 
                            << 0xbU) | (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[7U] 
                                        >> 0x15U)))) 
             | (2U == (7U & ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U] 
                              << 0xbU) | (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[7U] 
                                          >> 0x15U))))) 
            | (IData)(vlTOPp->mkTestBench__DOT__CASE_soc_core_id2exD_OUT_BITS_247_TO_245_0b11_ETC___05Fq4)) 
           & (0x341U == (IData)(vlTOPp->mkTestBench__DOT__addr___05Fh117366)));
    vlTOPp->mkTestBench__DOT__soc_core_id2ex_first___05F406_BITS_247_TO_245_074___05FETC___05F_d2241 
        = ((((1U == (7U & ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U] 
                            << 0xbU) | (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[7U] 
                                        >> 0x15U)))) 
             | (2U == (7U & ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U] 
                              << 0xbU) | (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[7U] 
                                          >> 0x15U))))) 
            | (IData)(vlTOPp->mkTestBench__DOT__CASE_soc_core_id2exD_OUT_BITS_247_TO_245_0b11_ETC___05Fq4)) 
           & (0x342U == (IData)(vlTOPp->mkTestBench__DOT__addr___05Fh117366)));
    vlTOPp->mkTestBench__DOT__soc_core_id2ex_first___05F406_BITS_247_TO_245_074___05FETC___05F_d2247 
        = ((((1U == (7U & ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U] 
                            << 0xbU) | (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[7U] 
                                        >> 0x15U)))) 
             | (2U == (7U & ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U] 
                              << 0xbU) | (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[7U] 
                                          >> 0x15U))))) 
            | (IData)(vlTOPp->mkTestBench__DOT__CASE_soc_core_id2exD_OUT_BITS_247_TO_245_0b11_ETC___05Fq4)) 
           & (0x343U == (IData)(vlTOPp->mkTestBench__DOT__addr___05Fh117366)));
    vlTOPp->mkTestBench__DOT__soc_core_id2ex_first___05F406_BITS_247_TO_245_074___05FETC___05F_d2411 
        = ((((1U == (7U & ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U] 
                            << 0xbU) | (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[7U] 
                                        >> 0x15U)))) 
             | (2U == (7U & ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U] 
                              << 0xbU) | (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[7U] 
                                          >> 0x15U))))) 
            | (IData)(vlTOPp->mkTestBench__DOT__CASE_soc_core_id2exD_OUT_BITS_247_TO_245_0b11_ETC___05Fq4)) 
           & ((0xb03U == (IData)(vlTOPp->mkTestBench__DOT__addr___05Fh117366)) 
              | (0xb83U == (IData)(vlTOPp->mkTestBench__DOT__addr___05Fh117366))));
    vlTOPp->mkTestBench__DOT__soc_core_id2ex_first___05F406_BITS_247_TO_245_074___05FETC___05F_d2252 
        = ((((1U == (7U & ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U] 
                            << 0xbU) | (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[7U] 
                                        >> 0x15U)))) 
             | (2U == (7U & ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U] 
                              << 0xbU) | (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[7U] 
                                          >> 0x15U))))) 
            | (IData)(vlTOPp->mkTestBench__DOT__CASE_soc_core_id2exD_OUT_BITS_247_TO_245_0b11_ETC___05Fq4)) 
           & (0x300U == (IData)(vlTOPp->mkTestBench__DOT__addr___05Fh117366)));
    vlTOPp->mkTestBench__DOT___theResult___05F___05Fh113081 
        = ((((((IData)(vlTOPp->mkTestBench__DOT__soc_core_ex2mem__DOT__empty_reg) 
               & (vlTOPp->mkTestBench__DOT__soc_core_ex2mem__DOT__data0_reg[0U] 
                  >> 4U)) & (~ (vlTOPp->mkTestBench__DOT__soc_core_ex2mem__DOT__data0_reg[0U] 
                                >> 3U))) & ((0x1fU 
                                             & ((vlTOPp->mkTestBench__DOT__soc_core_ex2mem__DOT__data0_reg[2U] 
                                                 << 0x15U) 
                                                | (vlTOPp->mkTestBench__DOT__soc_core_ex2mem__DOT__data0_reg[1U] 
                                                   >> 0xbU))) 
                                            == (0x1fU 
                                                & ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[5U] 
                                                    << 0x1cU) 
                                                   | (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[4U] 
                                                      >> 4U))))) 
            & (0U != (0x1fU & ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[5U] 
                                << 0x1cU) | (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[4U] 
                                             >> 4U)))))
            ? ((vlTOPp->mkTestBench__DOT__soc_core_ex2mem__DOT__data0_reg[3U] 
                << 0x10U) | (vlTOPp->mkTestBench__DOT__soc_core_ex2mem__DOT__data0_reg[2U] 
                             >> 0x10U)) : (((((IData)(vlTOPp->mkTestBench__DOT__soc_core_mem2wb__DOT__empty_reg) 
                                              & (vlTOPp->mkTestBench__DOT__soc_core_mem2wb__DOT__data0_reg[0U] 
                                                 >> 1U)) 
                                             & ((0x1fU 
                                                 & ((vlTOPp->mkTestBench__DOT__soc_core_mem2wb__DOT__data0_reg[1U] 
                                                     << 0x1eU) 
                                                    | (vlTOPp->mkTestBench__DOT__soc_core_mem2wb__DOT__data0_reg[0U] 
                                                       >> 2U))) 
                                                == 
                                                (0x1fU 
                                                 & ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[5U] 
                                                     << 0x1cU) 
                                                    | (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[4U] 
                                                       >> 4U))))) 
                                            & (0U != 
                                               (0x1fU 
                                                & ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[5U] 
                                                    << 0x1cU) 
                                                   | (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[4U] 
                                                      >> 4U)))))
                                            ? vlTOPp->mkTestBench__DOT__op1___05F_1___05Fh113287
                                            : ((((IData)(vlTOPp->mkTestBench__DOT__soc_core_wb_forward_valid0) 
                                                 & ((IData)(vlTOPp->mkTestBench__DOT__soc_core_wb_forward_rd0) 
                                                    == 
                                                    (0x1fU 
                                                     & ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[5U] 
                                                         << 0x1cU) 
                                                        | (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[4U] 
                                                           >> 4U))))) 
                                                & (0U 
                                                   != 
                                                   (0x1fU 
                                                    & ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[5U] 
                                                        << 0x1cU) 
                                                       | (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[4U] 
                                                          >> 4U)))))
                                                ? vlTOPp->mkTestBench__DOT__soc_core_wb_forward_data0
                                                : (
                                                   (((IData)(vlTOPp->mkTestBench__DOT__soc_core_wb_forward_valid1) 
                                                     & ((IData)(vlTOPp->mkTestBench__DOT__soc_core_wb_forward_rd1) 
                                                        == 
                                                        (0x1fU 
                                                         & ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[5U] 
                                                             << 0x1cU) 
                                                            | (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[4U] 
                                                               >> 4U))))) 
                                                    & (0U 
                                                       != 
                                                       (0x1fU 
                                                        & ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[5U] 
                                                            << 0x1cU) 
                                                           | (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[4U] 
                                                              >> 4U)))))
                                                    ? vlTOPp->mkTestBench__DOT__soc_core_wb_forward_data1
                                                    : 
                                                   ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[7U] 
                                                     << 0x17U) 
                                                    | (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[6U] 
                                                       >> 9U))))));
    vlTOPp->mkTestBench__DOT___theResult___05F___05F_5___05Fh113082 
        = ((((((IData)(vlTOPp->mkTestBench__DOT__soc_core_ex2mem__DOT__empty_reg) 
               & (vlTOPp->mkTestBench__DOT__soc_core_ex2mem__DOT__data0_reg[0U] 
                  >> 4U)) & (~ (vlTOPp->mkTestBench__DOT__soc_core_ex2mem__DOT__data0_reg[0U] 
                                >> 3U))) & ((0x1fU 
                                             & ((vlTOPp->mkTestBench__DOT__soc_core_ex2mem__DOT__data0_reg[2U] 
                                                 << 0x15U) 
                                                | (vlTOPp->mkTestBench__DOT__soc_core_ex2mem__DOT__data0_reg[1U] 
                                                   >> 0xbU))) 
                                            == (0x1fU 
                                                & ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[4U] 
                                                    << 1U) 
                                                   | (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[3U] 
                                                      >> 0x1fU))))) 
            & (0U != (0x1fU & ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[4U] 
                                << 1U) | (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[3U] 
                                          >> 0x1fU)))))
            ? ((vlTOPp->mkTestBench__DOT__soc_core_ex2mem__DOT__data0_reg[3U] 
                << 0x10U) | (vlTOPp->mkTestBench__DOT__soc_core_ex2mem__DOT__data0_reg[2U] 
                             >> 0x10U)) : (((((IData)(vlTOPp->mkTestBench__DOT__soc_core_mem2wb__DOT__empty_reg) 
                                              & (vlTOPp->mkTestBench__DOT__soc_core_mem2wb__DOT__data0_reg[0U] 
                                                 >> 1U)) 
                                             & ((0x1fU 
                                                 & ((vlTOPp->mkTestBench__DOT__soc_core_mem2wb__DOT__data0_reg[1U] 
                                                     << 0x1eU) 
                                                    | (vlTOPp->mkTestBench__DOT__soc_core_mem2wb__DOT__data0_reg[0U] 
                                                       >> 2U))) 
                                                == 
                                                (0x1fU 
                                                 & ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[4U] 
                                                     << 1U) 
                                                    | (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[3U] 
                                                       >> 0x1fU))))) 
                                            & (0U != 
                                               (0x1fU 
                                                & ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[4U] 
                                                    << 1U) 
                                                   | (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[3U] 
                                                      >> 0x1fU)))))
                                            ? vlTOPp->mkTestBench__DOT__op1___05F_1___05Fh113287
                                            : ((((IData)(vlTOPp->mkTestBench__DOT__soc_core_wb_forward_valid0) 
                                                 & ((IData)(vlTOPp->mkTestBench__DOT__soc_core_wb_forward_rd0) 
                                                    == 
                                                    (0x1fU 
                                                     & ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[4U] 
                                                         << 1U) 
                                                        | (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[3U] 
                                                           >> 0x1fU))))) 
                                                & (0U 
                                                   != 
                                                   (0x1fU 
                                                    & ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[4U] 
                                                        << 1U) 
                                                       | (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[3U] 
                                                          >> 0x1fU)))))
                                                ? vlTOPp->mkTestBench__DOT__soc_core_wb_forward_data0
                                                : (
                                                   (((IData)(vlTOPp->mkTestBench__DOT__soc_core_wb_forward_valid1) 
                                                     & ((IData)(vlTOPp->mkTestBench__DOT__soc_core_wb_forward_rd1) 
                                                        == 
                                                        (0x1fU 
                                                         & ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[4U] 
                                                             << 1U) 
                                                            | (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[3U] 
                                                               >> 0x1fU))))) 
                                                    & (0U 
                                                       != 
                                                       (0x1fU 
                                                        & ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[4U] 
                                                            << 1U) 
                                                           | (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[3U] 
                                                              >> 0x1fU)))))
                                                    ? vlTOPp->mkTestBench__DOT__soc_core_wb_forward_data1
                                                    : 
                                                   ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[6U] 
                                                     << 0x17U) 
                                                    | (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[5U] 
                                                       >> 9U))))));
    vlTOPp->mkTestBench__DOT__WILL_FIRE_RL_report = 
        (((IData)(vlTOPp->mkTestBench__DOT__programDone) 
          & (~ (IData)(vlTOPp->mkTestBench__DOT__dumpDone))) 
         & (~ (IData)(vlTOPp->mkTestBench__DOT__WILL_FIRE_RL_countCycles)));
    vlTOPp->mkTestBench__DOT__soc_core_id2ex__024ENQ 
        = ((IData)(vlTOPp->mkTestBench__DOT__WILL_FIRE_RL_soc_core_decodeStage) 
           | (IData)(vlTOPp->mkTestBench__DOT__WILL_FIRE_RL_soc_core_decrementStall));
    vlTOPp->mkTestBench__DOT__soc_core_if2id__024DEQ 
        = ((IData)(vlTOPp->mkTestBench__DOT__WILL_FIRE_RL_soc_core_decodeStage) 
           & ((((~ (IData)(vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__empty_reg)) 
                | (1U != (3U & ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[4U] 
                                 << 0xfU) | (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[3U] 
                                             >> 0x11U))))) 
               | (0U == (0x1fU & ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[4U] 
                                   << 6U) | (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[3U] 
                                             >> 0x1aU))))) 
              | (((((0x33U != (0x7fU & ((vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[2U] 
                                         << 0x1dU) 
                                        | (vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U] 
                                           >> 3U)))) 
                    & (0x23U != (0x7fU & ((vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[2U] 
                                           << 0x1dU) 
                                          | (vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U] 
                                             >> 3U))))) 
                   & (0x63U != (0x7fU & ((vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[2U] 
                                          << 0x1dU) 
                                         | (vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U] 
                                            >> 3U))))) 
                  | (~ (IData)(vlTOPp->mkTestBench__DOT__soc_core_if2id_first___05F414_BITS_59_TO_55_427_EQ_ETC___05F_d1428))) 
                 & ((((((((0x33U != (0x7fU & ((vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[2U] 
                                               << 0x1dU) 
                                              | (vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U] 
                                                 >> 3U)))) 
                          & (0x13U != (0x7fU & ((vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[2U] 
                                                 << 0x1dU) 
                                                | (vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U] 
                                                   >> 3U))))) 
                         & (3U != (0x7fU & ((vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[2U] 
                                             << 0x1dU) 
                                            | (vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U] 
                                               >> 3U))))) 
                        & (0x23U != (0x7fU & ((vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[2U] 
                                               << 0x1dU) 
                                              | (vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U] 
                                                 >> 3U))))) 
                       & (0x63U != (0x7fU & ((vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[2U] 
                                              << 0x1dU) 
                                             | (vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U] 
                                                >> 3U))))) 
                      & (0x67U != (0x7fU & ((vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[2U] 
                                             << 0x1dU) 
                                            | (vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U] 
                                               >> 3U))))) 
                     & ((((0x73U != (0x7fU & ((vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[2U] 
                                               << 0x1dU) 
                                              | (vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U] 
                                                 >> 3U)))) 
                          | (2U == (7U & ((vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[2U] 
                                           << 0x11U) 
                                          | (vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U] 
                                             >> 0xfU))))) 
                         | (5U == (7U & ((vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[2U] 
                                          << 0x11U) 
                                         | (vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U] 
                                            >> 0xfU))))) 
                        | (7U == (7U & ((vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[2U] 
                                         << 0x11U) 
                                        | (vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U] 
                                           >> 0xfU)))))) 
                    | (~ (IData)(vlTOPp->mkTestBench__DOT__soc_core_if2id_first___05F414_BITS_54_TO_50_461_EQ_ETC___05F_d1462))))));
    vlTOPp->mkTestBench__DOT__WILL_FIRE_RL_soc_core_executeStage 
        = ((((((((IData)(vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__empty_reg) 
                 & (IData)(vlTOPp->mkTestBench__DOT__soc_core_mem2wb__DOT__empty_reg)) 
                & (IData)(vlTOPp->mkTestBench__DOT__soc_core_ex2mem__DOT__empty_reg)) 
               & (IData)(vlTOPp->mkTestBench__DOT__soc_core_ex2mem__DOT__full_reg)) 
              & (~ (IData)(vlTOPp->mkTestBench__DOT__soc_core_stall_load_use))) 
             & (IData)(vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__empty_reg)) 
            & (IData)(vlTOPp->mkTestBench__DOT__soc_core_ex2mem__DOT__full_reg)) 
           & (~ (IData)(vlTOPp->mkTestBench__DOT__WILL_FIRE_RL_soc_core_decodeStage)));
    vlTOPp->mkTestBench__DOT__SEL_ARR_soc_core_btb_btbTable_0_055_BIT_0_056___05FETC___05F_d1322 
        = (((IData)(vlTOPp->mkTestBench__DOT__SEL_ARR_soc_core_btb_btbTable_0_055_BIT_0_056___05FETC___05F_d1185) 
            & (vlTOPp->mkTestBench__DOT__SEL_ARR_soc_core_btb_btbTable_0_055_BITS_64_TO_ETC___05F_d1251 
               == vlTOPp->mkTestBench__DOT__soc_core_pcReg)) 
           & (2U <= (IData)(vlTOPp->mkTestBench__DOT__state___05Fh107856)));
    if (((IData)(vlTOPp->mkTestBench__DOT__soc_plic_irq_pending_2) 
         & ((IData)(vlTOPp->mkTestBench__DOT__soc_plic_enable_bits) 
            >> 2U))) {
        vlTOPp->mkTestBench__DOT__IF_soc_plic_irq_pending_2_837_AND_soc_plic_ena_ETC___05F_d3893 
            = (((vlTOPp->mkTestBench__DOT__soc_plic_irq_priority_2 
                 > vlTOPp->mkTestBench__DOT__IF_soc_plic_irq_pending_1_840_AND_soc_plic_ena_ETC___05F_d3849) 
                & (vlTOPp->mkTestBench__DOT__soc_plic_irq_priority_2 
                   > vlTOPp->mkTestBench__DOT__soc_plic_threshold))
                ? 2U : vlTOPp->mkTestBench__DOT__IF_soc_plic_irq_pending_1_840_AND_soc_plic_ena_ETC___05F_d3891);
        vlTOPp->mkTestBench__DOT__IF_soc_plic_irq_pending_2_837_AND_soc_plic_ena_ETC___05F_d3856 
            = (((vlTOPp->mkTestBench__DOT__soc_plic_irq_priority_2 
                 > vlTOPp->mkTestBench__DOT__IF_soc_plic_irq_pending_1_840_AND_soc_plic_ena_ETC___05F_d3849) 
                & (vlTOPp->mkTestBench__DOT__soc_plic_irq_priority_2 
                   > vlTOPp->mkTestBench__DOT__soc_plic_threshold))
                ? vlTOPp->mkTestBench__DOT__soc_plic_irq_priority_2
                : vlTOPp->mkTestBench__DOT__IF_soc_plic_irq_pending_1_840_AND_soc_plic_ena_ETC___05F_d3849);
    } else {
        vlTOPp->mkTestBench__DOT__IF_soc_plic_irq_pending_2_837_AND_soc_plic_ena_ETC___05F_d3893 
            = vlTOPp->mkTestBench__DOT__IF_soc_plic_irq_pending_1_840_AND_soc_plic_ena_ETC___05F_d3891;
        vlTOPp->mkTestBench__DOT__IF_soc_plic_irq_pending_2_837_AND_soc_plic_ena_ETC___05F_d3856 
            = vlTOPp->mkTestBench__DOT__IF_soc_plic_irq_pending_1_840_AND_soc_plic_ena_ETC___05F_d3849;
    }
    vlTOPp->mkTestBench__DOT__v___05Fh117136 = ((0x800U 
                                                 & (IData)(vlTOPp->mkTestBench__DOT__addr___05Fh117366))
                                                 ? 
                                                ((0x400U 
                                                  & (IData)(vlTOPp->mkTestBench__DOT__addr___05Fh117366))
                                                  ? 0U
                                                  : 
                                                 ((0x200U 
                                                   & (IData)(vlTOPp->mkTestBench__DOT__addr___05Fh117366))
                                                   ? 
                                                  ((0x100U 
                                                    & (IData)(vlTOPp->mkTestBench__DOT__addr___05Fh117366))
                                                    ? 
                                                   ((0x80U 
                                                     & (IData)(vlTOPp->mkTestBench__DOT__addr___05Fh117366))
                                                     ? 
                                                    ((0x40U 
                                                      & (IData)(vlTOPp->mkTestBench__DOT__addr___05Fh117366))
                                                      ? 0U
                                                      : 
                                                     ((0x20U 
                                                       & (IData)(vlTOPp->mkTestBench__DOT__addr___05Fh117366))
                                                       ? 0U
                                                       : 
                                                      ((0x10U 
                                                        & (IData)(vlTOPp->mkTestBench__DOT__addr___05Fh117366))
                                                        ? 0U
                                                        : 
                                                       ((8U 
                                                         & (IData)(vlTOPp->mkTestBench__DOT__addr___05Fh117366))
                                                         ? 0U
                                                         : 
                                                        ((4U 
                                                          & (IData)(vlTOPp->mkTestBench__DOT__addr___05Fh117366))
                                                          ? 0U
                                                          : 
                                                         ((2U 
                                                           & (IData)(vlTOPp->mkTestBench__DOT__addr___05Fh117366))
                                                           ? 
                                                          ((1U 
                                                            & (IData)(vlTOPp->mkTestBench__DOT__addr___05Fh117366))
                                                            ? (IData)(
                                                                      (vlTOPp->mkTestBench__DOT__soc_core_csrs_minstret 
                                                                       >> 0x20U))
                                                            : (IData)(
                                                                      (vlTOPp->mkTestBench__DOT__soc_core_csrs_mtimecmp 
                                                                       >> 0x20U)))
                                                           : 
                                                          ((1U 
                                                            & (IData)(vlTOPp->mkTestBench__DOT__addr___05Fh117366))
                                                            ? (IData)(
                                                                      (vlTOPp->mkTestBench__DOT__soc_core_csrs_mtime 
                                                                       >> 0x20U))
                                                            : (IData)(
                                                                      (vlTOPp->mkTestBench__DOT__soc_core_csrs_mcycle 
                                                                       >> 0x20U)))))))))
                                                     : 
                                                    ((0x40U 
                                                      & (IData)(vlTOPp->mkTestBench__DOT__addr___05Fh117366))
                                                      ? 0U
                                                      : 
                                                     ((0x20U 
                                                       & (IData)(vlTOPp->mkTestBench__DOT__addr___05Fh117366))
                                                       ? 0U
                                                       : 
                                                      ((0x10U 
                                                        & (IData)(vlTOPp->mkTestBench__DOT__addr___05Fh117366))
                                                        ? 0U
                                                        : 
                                                       ((8U 
                                                         & (IData)(vlTOPp->mkTestBench__DOT__addr___05Fh117366))
                                                         ? 0U
                                                         : 
                                                        ((4U 
                                                          & (IData)(vlTOPp->mkTestBench__DOT__addr___05Fh117366))
                                                          ? 0U
                                                          : 
                                                         ((2U 
                                                           & (IData)(vlTOPp->mkTestBench__DOT__addr___05Fh117366))
                                                           ? 
                                                          ((1U 
                                                            & (IData)(vlTOPp->mkTestBench__DOT__addr___05Fh117366))
                                                            ? (IData)(vlTOPp->mkTestBench__DOT__soc_core_csrs_minstret)
                                                            : (IData)(vlTOPp->mkTestBench__DOT__soc_core_csrs_mtimecmp))
                                                           : 
                                                          ((1U 
                                                            & (IData)(vlTOPp->mkTestBench__DOT__addr___05Fh117366))
                                                            ? (IData)(vlTOPp->mkTestBench__DOT__soc_core_csrs_mtime)
                                                            : (IData)(vlTOPp->mkTestBench__DOT__soc_core_csrs_mcycle)))))))))
                                                    : 0U)
                                                   : 0U))
                                                 : 
                                                ((0x400U 
                                                  & (IData)(vlTOPp->mkTestBench__DOT__addr___05Fh117366))
                                                  ? 0U
                                                  : 
                                                 ((0x200U 
                                                   & (IData)(vlTOPp->mkTestBench__DOT__addr___05Fh117366))
                                                   ? 
                                                  ((0x100U 
                                                    & (IData)(vlTOPp->mkTestBench__DOT__addr___05Fh117366))
                                                    ? 
                                                   ((0x80U 
                                                     & (IData)(vlTOPp->mkTestBench__DOT__addr___05Fh117366))
                                                     ? 0U
                                                     : 
                                                    ((0x40U 
                                                      & (IData)(vlTOPp->mkTestBench__DOT__addr___05Fh117366))
                                                      ? 
                                                     ((0x20U 
                                                       & (IData)(vlTOPp->mkTestBench__DOT__addr___05Fh117366))
                                                       ? 0U
                                                       : 
                                                      ((0x10U 
                                                        & (IData)(vlTOPp->mkTestBench__DOT__addr___05Fh117366))
                                                        ? 0U
                                                        : 
                                                       ((8U 
                                                         & (IData)(vlTOPp->mkTestBench__DOT__addr___05Fh117366))
                                                         ? 0U
                                                         : 
                                                        ((4U 
                                                          & (IData)(vlTOPp->mkTestBench__DOT__addr___05Fh117366))
                                                          ? 
                                                         ((2U 
                                                           & (IData)(vlTOPp->mkTestBench__DOT__addr___05Fh117366))
                                                           ? 0U
                                                           : 
                                                          ((1U 
                                                            & (IData)(vlTOPp->mkTestBench__DOT__addr___05Fh117366))
                                                            ? 0U
                                                            : vlTOPp->mkTestBench__DOT__soc_core_csrs_mip))
                                                          : 
                                                         ((2U 
                                                           & (IData)(vlTOPp->mkTestBench__DOT__addr___05Fh117366))
                                                           ? 
                                                          ((1U 
                                                            & (IData)(vlTOPp->mkTestBench__DOT__addr___05Fh117366))
                                                            ? vlTOPp->mkTestBench__DOT__soc_core_csrs_mtval
                                                            : vlTOPp->mkTestBench__DOT__soc_core_csrs_mcause)
                                                           : 
                                                          ((1U 
                                                            & (IData)(vlTOPp->mkTestBench__DOT__addr___05Fh117366))
                                                            ? vlTOPp->mkTestBench__DOT__soc_core_csrs_mepc
                                                            : 0U))))))
                                                      : 
                                                     ((0x20U 
                                                       & (IData)(vlTOPp->mkTestBench__DOT__addr___05Fh117366))
                                                       ? 0U
                                                       : 
                                                      ((0x10U 
                                                        & (IData)(vlTOPp->mkTestBench__DOT__addr___05Fh117366))
                                                        ? 0U
                                                        : 
                                                       ((8U 
                                                         & (IData)(vlTOPp->mkTestBench__DOT__addr___05Fh117366))
                                                         ? 0U
                                                         : 
                                                        ((4U 
                                                          & (IData)(vlTOPp->mkTestBench__DOT__addr___05Fh117366))
                                                          ? 
                                                         ((2U 
                                                           & (IData)(vlTOPp->mkTestBench__DOT__addr___05Fh117366))
                                                           ? 
                                                          ((1U 
                                                            & (IData)(vlTOPp->mkTestBench__DOT__addr___05Fh117366))
                                                            ? 0U
                                                            : vlTOPp->mkTestBench__DOT__soc_core_csrs_mcounteren)
                                                           : 
                                                          ((1U 
                                                            & (IData)(vlTOPp->mkTestBench__DOT__addr___05Fh117366))
                                                            ? vlTOPp->mkTestBench__DOT__soc_core_csrs_mtvec
                                                            : vlTOPp->mkTestBench__DOT__soc_core_csrs_mie))
                                                          : 
                                                         ((2U 
                                                           & (IData)(vlTOPp->mkTestBench__DOT__addr___05Fh117366))
                                                           ? 0U
                                                           : 
                                                          ((1U 
                                                            & (IData)(vlTOPp->mkTestBench__DOT__addr___05Fh117366))
                                                            ? vlTOPp->mkTestBench__DOT__soc_core_csrs_misa
                                                            : vlTOPp->mkTestBench__DOT__value___05Fh117781))))))))
                                                    : 0U)
                                                   : 0U)));
    vlTOPp->mkTestBench__DOT__MUX_soc_core_stall_count__024write_1___05FSEL_1 
        = (((((IData)(vlTOPp->mkTestBench__DOT__WILL_FIRE_RL_soc_core_decodeStage) 
              & (IData)(vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__empty_reg)) 
             & (1U == (3U & ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[4U] 
                              << 0xfU) | (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[3U] 
                                          >> 0x11U))))) 
            & (0U != (0x1fU & ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[4U] 
                                << 6U) | (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[3U] 
                                          >> 0x1aU))))) 
           & (IData)(vlTOPp->mkTestBench__DOT__soc_core_if2id_first___05F414_BITS_41_TO_35_415_EQ_ETC___05F_d1464));
    __Vtemp88[3U] = ((0xffffc000U & (((((((((0x33U 
                                             == (0x7fU 
                                                 & ((vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[2U] 
                                                     << 0x1dU) 
                                                    | (vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U] 
                                                       >> 3U)))) 
                                            | (0x13U 
                                               == (0x7fU 
                                                   & ((vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[2U] 
                                                       << 0x1dU) 
                                                      | (vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U] 
                                                         >> 3U))))) 
                                           | (3U == 
                                              (0x7fU 
                                               & ((vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[2U] 
                                                   << 0x1dU) 
                                                  | (vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U] 
                                                     >> 3U))))) 
                                          | (0x37U 
                                             == (0x7fU 
                                                 & ((vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[2U] 
                                                     << 0x1dU) 
                                                    | (vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U] 
                                                       >> 3U))))) 
                                         | (0x17U == 
                                            (0x7fU 
                                             & ((vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[2U] 
                                                 << 0x1dU) 
                                                | (vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U] 
                                                   >> 3U))))) 
                                        | (0x6fU == 
                                           (0x7fU & 
                                            ((vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[2U] 
                                              << 0x1dU) 
                                             | (vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U] 
                                                >> 3U))))) 
                                       | (0x67U == 
                                          (0x7fU & 
                                           ((vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[2U] 
                                             << 0x1dU) 
                                            | (vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U] 
                                               >> 3U))))) 
                                      | (0x73U == (0x7fU 
                                                   & ((vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[2U] 
                                                       << 0x1dU) 
                                                      | (vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U] 
                                                         >> 3U))))) 
                                     << 0xeU)) | vlTOPp->mkTestBench__DOT__NOT_soc_core_if2id_first___05F414_BITS_41_TO_35_41_ETC___05F_d1667[3U]);
    __Vtemp91[3U] = ((0xfffe0000U & (((0x200U & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                                       ? 0U : ((0x100U 
                                                & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                                                ? (
                                                   (0x80U 
                                                    & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                                                    ? 0U
                                                    : 
                                                   ((0x40U 
                                                     & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                                                     ? 0U
                                                     : 
                                                    ((0x20U 
                                                      & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                                                      ? 0U
                                                      : 
                                                     ((0x10U 
                                                       & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                                                       ? 
                                                      ((8U 
                                                        & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                                                        ? 2U
                                                        : 0U)
                                                       : 0U))))
                                                : (
                                                   (0x80U 
                                                    & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                                                    ? 0U
                                                    : 
                                                   ((0x40U 
                                                     & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                                                     ? 0U
                                                     : 
                                                    ((0x20U 
                                                      & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                                                      ? 0U
                                                      : 
                                                     ((0x10U 
                                                       & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                                                       ? 
                                                      ((8U 
                                                        & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                                                        ? 1U
                                                        : 0U)
                                                       : 0U)))))) 
                                     << 0x11U)) | (
                                                   (0xffff0000U 
                                                    & ((0x63U 
                                                        == 
                                                        (0x7fU 
                                                         & ((vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[2U] 
                                                             << 0x1dU) 
                                                            | (vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U] 
                                                               >> 3U)))) 
                                                       << 0x10U)) 
                                                   | ((0xffff8000U 
                                                       & (((0x6fU 
                                                            == 
                                                            (0x7fU 
                                                             & ((vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[2U] 
                                                                 << 0x1dU) 
                                                                | (vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U] 
                                                                   >> 3U)))) 
                                                           | (0x67U 
                                                              == 
                                                              (0x7fU 
                                                               & ((vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[2U] 
                                                                   << 0x1dU) 
                                                                  | (vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U] 
                                                                     >> 3U))))) 
                                                          << 0xfU)) 
                                                      | __Vtemp88[3U])));
    __Vtemp92[3U] = ((0xfff80000U & (((0x200U & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                                       ? ((0x100U & 
                                           vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                                           ? ((0x80U 
                                               & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                                               ? 6U
                                               : ((0x40U 
                                                   & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                                                   ? 6U
                                                   : 
                                                  ((0x20U 
                                                    & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                                                    ? 6U
                                                    : 
                                                   ((0x10U 
                                                     & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                                                     ? 
                                                    ((8U 
                                                      & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                                                      ? 
                                                     (7U 
                                                      & ((0x20000U 
                                                          & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                                                          ? 
                                                         ((0x10000U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                                                           ? 
                                                          ((0x8000U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                                                            ? 5U
                                                            : 4U)
                                                           : 
                                                          ((0x8000U 
                                                            & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                                                            ? 3U
                                                            : 2U))
                                                          : 
                                                         ((0x10000U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                                                           ? 6U
                                                           : 
                                                          ((vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[2U] 
                                                            << 0x11U) 
                                                           | (vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U] 
                                                              >> 0xfU)))))
                                                      : 6U)
                                                     : 6U))))
                                           : 6U) : 6U) 
                                     << 0x13U)) | __Vtemp91[3U]);
    __Vtemp93[3U] = ((0xffc00000U & (((0x200U & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                                       ? 0U : ((0x100U 
                                                & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                                                ? (
                                                   (0x80U 
                                                    & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                                                    ? 
                                                   ((0x40U 
                                                     & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                                                     ? 0U
                                                     : 
                                                    ((0x20U 
                                                      & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                                                      ? 
                                                     ((0x10U 
                                                       & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                                                       ? 
                                                      ((8U 
                                                        & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                                                        ? 0xaU
                                                        : 0U)
                                                       : 0U)
                                                      : 
                                                     ((0x10U 
                                                       & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                                                       ? 
                                                      ((8U 
                                                        & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                                                        ? 
                                                       ((0x20000U 
                                                         & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                                                         ? 
                                                        ((0x10000U 
                                                          & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                                                          ? 
                                                         ((0x8000U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                                                           ? 9U
                                                           : 8U)
                                                          : 
                                                         ((0x8000U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                                                           ? 
                                                          ((0x20U 
                                                            == 
                                                            (0x7fU 
                                                             & ((vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[2U] 
                                                                 << 4U) 
                                                                | (vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U] 
                                                                   >> 0x1cU))))
                                                            ? 7U
                                                            : 6U)
                                                           : 5U))
                                                         : 
                                                        ((0x10000U 
                                                          & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                                                          ? 
                                                         ((0x8000U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                                                           ? 4U
                                                           : 3U)
                                                          : 
                                                         ((0x8000U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                                                           ? 2U
                                                           : 
                                                          ((0x20U 
                                                            == 
                                                            (0x7fU 
                                                             & ((vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[2U] 
                                                                 << 4U) 
                                                                | (vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U] 
                                                                   >> 0x1cU))))
                                                            ? 1U
                                                            : 0U))))
                                                        : 0U)
                                                       : 0U)))
                                                    : 0U)
                                                : (
                                                   (0x80U 
                                                    & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                                                    ? 
                                                   ((0x40U 
                                                     & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                                                     ? 0U
                                                     : 
                                                    ((0x20U 
                                                      & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                                                      ? 
                                                     ((0x10U 
                                                       & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                                                       ? 
                                                      ((8U 
                                                        & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                                                        ? 0xbU
                                                        : 0U)
                                                       : 0U)
                                                      : 
                                                     ((0x10U 
                                                       & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                                                       ? 
                                                      ((8U 
                                                        & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                                                        ? 
                                                       ((0x20000U 
                                                         & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                                                         ? 
                                                        ((0x10000U 
                                                          & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                                                          ? 
                                                         ((0x8000U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                                                           ? 9U
                                                           : 8U)
                                                          : 
                                                         ((0x8000U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                                                           ? 
                                                          ((0x20U 
                                                            == 
                                                            (0x7fU 
                                                             & ((vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[2U] 
                                                                 << 4U) 
                                                                | (vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U] 
                                                                   >> 0x1cU))))
                                                            ? 7U
                                                            : 6U)
                                                           : 5U))
                                                         : 
                                                        ((0x10000U 
                                                          & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                                                          ? 
                                                         ((0x8000U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                                                           ? 4U
                                                           : 3U)
                                                          : 
                                                         ((0x8000U 
                                                           & vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])
                                                           ? 2U
                                                           : 0U)))
                                                        : 0U)
                                                       : 0U)))
                                                    : 0U))) 
                                     << 0x16U)) | __Vtemp92[3U]);
    __Vtemp97[5U] = ((0x1ffU & (vlTOPp->mkTestBench__DOT__x___05Fh111983 
                                >> 0x17U)) | (0xfffffe00U 
                                              & (((((IData)(vlTOPp->mkTestBench__DOT__soc_core_wb_forward_valid0) 
                                                    & ((IData)(vlTOPp->mkTestBench__DOT__soc_core_wb_forward_rd0) 
                                                       == 
                                                       (0x1fU 
                                                        & ((vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[2U] 
                                                            << 9U) 
                                                           | (vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U] 
                                                              >> 0x17U))))) 
                                                   & (0U 
                                                      != 
                                                      (0x1fU 
                                                       & ((vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[2U] 
                                                           << 9U) 
                                                          | (vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U] 
                                                             >> 0x17U)))))
                                                   ? vlTOPp->mkTestBench__DOT__soc_core_wb_forward_data0
                                                   : 
                                                  ((((IData)(vlTOPp->mkTestBench__DOT__soc_core_wb_forward_valid1) 
                                                     & ((IData)(vlTOPp->mkTestBench__DOT__soc_core_wb_forward_rd1) 
                                                        == 
                                                        (0x1fU 
                                                         & ((vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[2U] 
                                                             << 9U) 
                                                            | (vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U] 
                                                               >> 0x17U))))) 
                                                    & (0U 
                                                       != 
                                                       (0x1fU 
                                                        & ((vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[2U] 
                                                            << 9U) 
                                                           | (vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U] 
                                                              >> 0x17U)))))
                                                    ? vlTOPp->mkTestBench__DOT__soc_core_wb_forward_data1
                                                    : vlTOPp->mkTestBench__DOT__rs2_val___05Fh110785)) 
                                                 << 9U)));
    __Vtemp97[6U] = ((0x1ffU & (((((IData)(vlTOPp->mkTestBench__DOT__soc_core_wb_forward_valid0) 
                                   & ((IData)(vlTOPp->mkTestBench__DOT__soc_core_wb_forward_rd0) 
                                      == (0x1fU & (
                                                   (vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[2U] 
                                                    << 9U) 
                                                   | (vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U] 
                                                      >> 0x17U))))) 
                                  & (0U != (0x1fU & 
                                            ((vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[2U] 
                                              << 9U) 
                                             | (vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U] 
                                                >> 0x17U)))))
                                  ? vlTOPp->mkTestBench__DOT__soc_core_wb_forward_data0
                                  : ((((IData)(vlTOPp->mkTestBench__DOT__soc_core_wb_forward_valid1) 
                                       & ((IData)(vlTOPp->mkTestBench__DOT__soc_core_wb_forward_rd1) 
                                          == (0x1fU 
                                              & ((vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[2U] 
                                                  << 9U) 
                                                 | (vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U] 
                                                    >> 0x17U))))) 
                                      & (0U != (0x1fU 
                                                & ((vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[2U] 
                                                    << 9U) 
                                                   | (vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U] 
                                                      >> 0x17U)))))
                                      ? vlTOPp->mkTestBench__DOT__soc_core_wb_forward_data1
                                      : vlTOPp->mkTestBench__DOT__rs2_val___05Fh110785)) 
                                >> 0x17U)) | (0xfffffe00U 
                                              & (((((IData)(vlTOPp->mkTestBench__DOT__soc_core_wb_forward_valid0) 
                                                    & ((IData)(vlTOPp->mkTestBench__DOT__soc_core_wb_forward_rd0) 
                                                       == 
                                                       (0x1fU 
                                                        & ((vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[2U] 
                                                            << 0xeU) 
                                                           | (vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U] 
                                                              >> 0x12U))))) 
                                                   & (0U 
                                                      != 
                                                      (0x1fU 
                                                       & ((vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[2U] 
                                                           << 0xeU) 
                                                          | (vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U] 
                                                             >> 0x12U)))))
                                                   ? vlTOPp->mkTestBench__DOT__soc_core_wb_forward_data0
                                                   : 
                                                  ((((IData)(vlTOPp->mkTestBench__DOT__soc_core_wb_forward_valid1) 
                                                     & ((IData)(vlTOPp->mkTestBench__DOT__soc_core_wb_forward_rd1) 
                                                        == 
                                                        (0x1fU 
                                                         & ((vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[2U] 
                                                             << 0xeU) 
                                                            | (vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U] 
                                                               >> 0x12U))))) 
                                                    & (0U 
                                                       != 
                                                       (0x1fU 
                                                        & ((vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[2U] 
                                                            << 0xeU) 
                                                           | (vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U] 
                                                              >> 0x12U)))))
                                                    ? vlTOPp->mkTestBench__DOT__soc_core_wb_forward_data1
                                                    : vlTOPp->mkTestBench__DOT__rs1_val___05Fh110784)) 
                                                 << 9U)));
    __Vtemp97[7U] = ((0x1ffU & (((((IData)(vlTOPp->mkTestBench__DOT__soc_core_wb_forward_valid0) 
                                   & ((IData)(vlTOPp->mkTestBench__DOT__soc_core_wb_forward_rd0) 
                                      == (0x1fU & (
                                                   (vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[2U] 
                                                    << 0xeU) 
                                                   | (vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U] 
                                                      >> 0x12U))))) 
                                  & (0U != (0x1fU & 
                                            ((vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[2U] 
                                              << 0xeU) 
                                             | (vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U] 
                                                >> 0x12U)))))
                                  ? vlTOPp->mkTestBench__DOT__soc_core_wb_forward_data0
                                  : ((((IData)(vlTOPp->mkTestBench__DOT__soc_core_wb_forward_valid1) 
                                       & ((IData)(vlTOPp->mkTestBench__DOT__soc_core_wb_forward_rd1) 
                                          == (0x1fU 
                                              & ((vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[2U] 
                                                  << 0xeU) 
                                                 | (vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U] 
                                                    >> 0x12U))))) 
                                      & (0U != (0x1fU 
                                                & ((vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[2U] 
                                                    << 0xeU) 
                                                   | (vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U] 
                                                      >> 0x12U)))))
                                      ? vlTOPp->mkTestBench__DOT__soc_core_wb_forward_data1
                                      : vlTOPp->mkTestBench__DOT__rs1_val___05Fh110784)) 
                                >> 0x17U)) | (0xfffffe00U 
                                              & ((IData)(
                                                         (((QData)((IData)(
                                                                           vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[3U])) 
                                                           << 0x3dU) 
                                                          | (((QData)((IData)(
                                                                              vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[2U])) 
                                                              << 0x1dU) 
                                                             | ((QData)((IData)(
                                                                                vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])) 
                                                                >> 3U)))) 
                                                 << 9U)));
    if (((((IData)(vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__empty_reg) 
           & (1U == (3U & ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[4U] 
                            << 0xfU) | (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[3U] 
                                        >> 0x11U))))) 
          & (0U != (0x1fU & ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[4U] 
                              << 6U) | (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[3U] 
                                        >> 0x1aU))))) 
         & (IData)(vlTOPp->mkTestBench__DOT__soc_core_if2id_first___05F414_BITS_41_TO_35_415_EQ_ETC___05F_d1464))) {
        __Vtemp99[8U] = 0U;
        vlTOPp->mkTestBench__DOT__MUX_soc_core_id2ex__024enq_1___05FVAL_1[0U] = 0U;
        vlTOPp->mkTestBench__DOT__MUX_soc_core_id2ex__024enq_1___05FVAL_1[1U] = 0U;
        vlTOPp->mkTestBench__DOT__MUX_soc_core_id2ex__024enq_1___05FVAL_1[2U] = 0U;
        vlTOPp->mkTestBench__DOT__MUX_soc_core_id2ex__024enq_1___05FVAL_1[3U] = 0x301000U;
        vlTOPp->mkTestBench__DOT__MUX_soc_core_id2ex__024enq_1___05FVAL_1[4U] = 0U;
        vlTOPp->mkTestBench__DOT__MUX_soc_core_id2ex__024enq_1___05FVAL_1[5U] = 0U;
        vlTOPp->mkTestBench__DOT__MUX_soc_core_id2ex__024enq_1___05FVAL_1[6U] = 0U;
        vlTOPp->mkTestBench__DOT__MUX_soc_core_id2ex__024enq_1___05FVAL_1[7U] = 0U;
    } else {
        __Vtemp99[8U] = ((0x1ffU & ((IData)((((QData)((IData)(
                                                              vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[3U])) 
                                              << 0x3dU) 
                                             | (((QData)((IData)(
                                                                 vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[2U])) 
                                                 << 0x1dU) 
                                                | ((QData)((IData)(
                                                                   vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])) 
                                                   >> 3U)))) 
                                    >> 0x17U)) | (0xfffffe00U 
                                                  & ((IData)(
                                                             ((((QData)((IData)(
                                                                                vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[3U])) 
                                                                << 0x3dU) 
                                                               | (((QData)((IData)(
                                                                                vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[2U])) 
                                                                   << 0x1dU) 
                                                                  | ((QData)((IData)(
                                                                                vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])) 
                                                                     >> 3U))) 
                                                              >> 0x20U)) 
                                                     << 9U)));
        vlTOPp->mkTestBench__DOT__MUX_soc_core_id2ex__024enq_1___05FVAL_1[0U] 
            = vlTOPp->mkTestBench__DOT__NOT_soc_core_if2id_first___05F414_BITS_41_TO_35_41_ETC___05F_d1667[0U];
        vlTOPp->mkTestBench__DOT__MUX_soc_core_id2ex__024enq_1___05FVAL_1[1U] 
            = vlTOPp->mkTestBench__DOT__NOT_soc_core_if2id_first___05F414_BITS_41_TO_35_41_ETC___05F_d1667[1U];
        vlTOPp->mkTestBench__DOT__MUX_soc_core_id2ex__024enq_1___05FVAL_1[2U] 
            = vlTOPp->mkTestBench__DOT__NOT_soc_core_if2id_first___05F414_BITS_41_TO_35_41_ETC___05F_d1667[2U];
        vlTOPp->mkTestBench__DOT__MUX_soc_core_id2ex__024enq_1___05FVAL_1[3U] 
            = ((0x80000000U & (vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U] 
                               << 8U)) | ((0x7c000000U 
                                           & (vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U] 
                                              << 0x10U)) 
                                          | __Vtemp93[3U]));
        vlTOPp->mkTestBench__DOT__MUX_soc_core_id2ex__024enq_1___05FVAL_1[4U] 
            = ((0xfffffe00U & (vlTOPp->mkTestBench__DOT__x___05Fh111983 
                               << 9U)) | ((0x1f0U & 
                                           ((vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[2U] 
                                             << 0x12U) 
                                            | (0x3fff0U 
                                               & (vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U] 
                                                  >> 0xeU)))) 
                                          | (0xfU & 
                                             ((0x7fffff00U 
                                               & (vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[2U] 
                                                  << 8U)) 
                                              | (vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U] 
                                                 >> 0x18U)))));
        vlTOPp->mkTestBench__DOT__MUX_soc_core_id2ex__024enq_1___05FVAL_1[5U] 
            = __Vtemp97[5U];
        vlTOPp->mkTestBench__DOT__MUX_soc_core_id2ex__024enq_1___05FVAL_1[6U] 
            = __Vtemp97[6U];
        vlTOPp->mkTestBench__DOT__MUX_soc_core_id2ex__024enq_1___05FVAL_1[7U] 
            = __Vtemp97[7U];
    }
    vlTOPp->mkTestBench__DOT__MUX_soc_core_id2ex__024enq_1___05FVAL_1[8U] 
        = __Vtemp99[8U];
    vlTOPp->mkTestBench__DOT__MUX_soc_core_id2ex__024enq_1___05FVAL_1[9U] 
        = (((((IData)(vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__empty_reg) 
              & (1U == (3U & ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[4U] 
                               << 0xfU) | (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[3U] 
                                           >> 0x11U))))) 
             & (0U != (0x1fU & ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[4U] 
                                 << 6U) | (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[3U] 
                                           >> 0x1aU))))) 
            & (IData)(vlTOPp->mkTestBench__DOT__soc_core_if2id_first___05F414_BITS_41_TO_35_415_EQ_ETC___05F_d1464))
            ? 0U : (0x1ffU & ((IData)(((((QData)((IData)(
                                                         vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[3U])) 
                                         << 0x3dU) 
                                        | (((QData)((IData)(
                                                            vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[2U])) 
                                            << 0x1dU) 
                                           | ((QData)((IData)(
                                                              vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__data0_reg[1U])) 
                                              >> 3U))) 
                                       >> 0x20U)) >> 0x17U)));
    vlTOPp->mkTestBench__DOT__IF_soc_core_id2ex_first___05F406_BITS_239_TO_233_8_ETC___05F_d2126 
        = (((0x73U == (0x7fU & ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U] 
                                 << 0x17U) | (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[7U] 
                                              >> 9U)))) 
            & (((2U == (7U & ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U] 
                               << 0xbU) | (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[7U] 
                                           >> 0x15U)))) 
                | (5U == (7U & ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U] 
                                 << 0xbU) | (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[7U] 
                                             >> 0x15U))))) 
               | (7U == (7U & ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U] 
                                << 0xbU) | (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[7U] 
                                            >> 0x15U))))))
            ? ((0x8000U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[7U])
                ? ((0x4000U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[7U])
                    ? ((0x2000U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[7U])
                        ? ((0x1000U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[7U])
                            ? 0U : ((0x800U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[7U])
                                     ? 0U : ((0x400U 
                                              & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[7U])
                                              ? ((0x200U 
                                                  & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[7U])
                                                  ? 
                                                 ((((2U 
                                                     == 
                                                     (7U 
                                                      & ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U] 
                                                          << 0xbU) 
                                                         | (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[7U] 
                                                            >> 0x15U)))) 
                                                    | (5U 
                                                       == 
                                                       (7U 
                                                        & ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U] 
                                                            << 0xbU) 
                                                           | (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[7U] 
                                                              >> 0x15U))))) 
                                                   | (7U 
                                                      == 
                                                      (7U 
                                                       & ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U] 
                                                           << 0xbU) 
                                                          | (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[7U] 
                                                             >> 0x15U)))))
                                                   ? 
                                                  (0x1fU 
                                                   & ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U] 
                                                       << 8U) 
                                                      | (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[7U] 
                                                         >> 0x18U)))
                                                   : 0U)
                                                  : 0U)
                                              : 0U)))
                        : 0U) : 0U) : 0U) : vlTOPp->mkTestBench__DOT___theResult___05F___05Fh113081);
    vlTOPp->mkTestBench__DOT__operand1___05Fh114849 
        = ((0xaU == (0xfU & ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[4U] 
                              << 0xaU) | (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[3U] 
                                          >> 0x16U))))
            ? ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[5U] 
                << 0x17U) | (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[4U] 
                             >> 9U)) : ((0xbU == (0xfU 
                                                  & ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[4U] 
                                                      << 0xaU) 
                                                     | (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[3U] 
                                                        >> 0x16U))))
                                         ? ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[9U] 
                                             << 0x17U) 
                                            | (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U] 
                                               >> 9U))
                                         : vlTOPp->mkTestBench__DOT___theResult___05F___05Fh113081));
    vlTOPp->mkTestBench__DOT__IF_soc_core_ex2mem_notEmpty___05F728_AND_soc_core___05FETC___05F_d1786 
        = (vlTOPp->mkTestBench__DOT___theResult___05F___05Fh113081 
           == vlTOPp->mkTestBench__DOT___theResult___05F___05F_5___05Fh113082);
    vlTOPp->mkTestBench__DOT__IF_soc_core_ex2mem_notEmpty___05F728_AND_soc_core___05FETC___05F_d1790 
        = ((0x80000000U ^ vlTOPp->mkTestBench__DOT___theResult___05F___05Fh113081) 
           < (0x80000000U ^ vlTOPp->mkTestBench__DOT___theResult___05F___05F_5___05Fh113082));
    vlTOPp->mkTestBench__DOT__IF_soc_core_ex2mem_notEmpty___05F728_AND_soc_core___05FETC___05F_d1794 
        = (vlTOPp->mkTestBench__DOT___theResult___05F___05Fh113081 
           < vlTOPp->mkTestBench__DOT___theResult___05F___05F_5___05Fh113082);
    vlTOPp->mkTestBench__DOT__alu_in2___05Fh114905 
        = ((0x2000U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[3U])
            ? ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[5U] 
                << 0x17U) | (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[4U] 
                             >> 9U)) : vlTOPp->mkTestBench__DOT___theResult___05F___05F_5___05Fh113082);
    vlTOPp->mkTestBench__DOT__soc_core_ex2mem__024ENQ 
        = (((IData)(vlTOPp->mkTestBench__DOT__WILL_FIRE_RL_soc_core_executeStage) 
            & (~ (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[3U] 
                  >> 9U))) & (((0x73U != (0x7fU & (
                                                   (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U] 
                                                    << 0x17U) 
                                                   | (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[7U] 
                                                      >> 9U)))) 
                               | (0U != (7U & ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U] 
                                                << 0xbU) 
                                               | (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[7U] 
                                                  >> 0x15U))))) 
                              | (0x18U != (0x7fU & 
                                           ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[9U] 
                                             << 0x1eU) 
                                            | (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U] 
                                               >> 2U))))));
    vlTOPp->mkTestBench__DOT__WILL_FIRE_RL_soc_core_fetchStage 
        = ((((((IData)(vlTOPp->mkTestBench__DOT__soc_core_if2id__DOT__full_reg) 
               & (IData)(vlTOPp->mkTestBench__DOT__soc_core_programLoaded)) 
              & (0U == (IData)(vlTOPp->mkTestBench__DOT__soc_core_state))) 
             & (~ (IData)(vlTOPp->mkTestBench__DOT__soc_core_stall_load_use))) 
            & (~ (IData)(vlTOPp->mkTestBench__DOT__soc_core_branch_flush))) 
           & (~ (IData)(vlTOPp->mkTestBench__DOT__WILL_FIRE_RL_soc_core_executeStage)));
    vlTOPp->mkTestBench__DOT__WILL_FIRE_RL_soc_core_writebackStage 
        = (((IData)(vlTOPp->mkTestBench__DOT__soc_core_mem2wb__DOT__empty_reg) 
            & (~ (IData)(vlTOPp->mkTestBench__DOT__WILL_FIRE_RL_soc_core_memoryStage))) 
           & (~ (IData)(vlTOPp->mkTestBench__DOT__WILL_FIRE_RL_soc_core_executeStage)));
    vlTOPp->mkTestBench__DOT__prediction_target___05Fh73334 
        = ((1U & ((~ (IData)(vlTOPp->mkTestBench__DOT__soc_core_branch_flush_done)) 
                  & (~ (IData)(vlTOPp->mkTestBench__DOT__soc_core_no_pc_update))))
            ? ((IData)(vlTOPp->mkTestBench__DOT__SEL_ARR_soc_core_btb_btbTable_0_055_BIT_0_056___05FETC___05F_d1322)
                ? vlTOPp->mkTestBench__DOT__prediction_target___05F_1___05Fh109896
                : 0U) : 0U);
    if (((IData)(vlTOPp->mkTestBench__DOT__soc_plic_irq_pending_3) 
         & ((IData)(vlTOPp->mkTestBench__DOT__soc_plic_enable_bits) 
            >> 3U))) {
        vlTOPp->mkTestBench__DOT__IF_soc_plic_irq_pending_3_834_AND_soc_plic_ena_ETC___05F_d3895 
            = (((vlTOPp->mkTestBench__DOT__soc_plic_irq_priority_3 
                 > vlTOPp->mkTestBench__DOT__IF_soc_plic_irq_pending_2_837_AND_soc_plic_ena_ETC___05F_d3856) 
                & (vlTOPp->mkTestBench__DOT__soc_plic_irq_priority_3 
                   > vlTOPp->mkTestBench__DOT__soc_plic_threshold))
                ? 3U : vlTOPp->mkTestBench__DOT__IF_soc_plic_irq_pending_2_837_AND_soc_plic_ena_ETC___05F_d3893);
        vlTOPp->mkTestBench__DOT__IF_soc_plic_irq_pending_3_834_AND_soc_plic_ena_ETC___05F_d3863 
            = (((vlTOPp->mkTestBench__DOT__soc_plic_irq_priority_3 
                 > vlTOPp->mkTestBench__DOT__IF_soc_plic_irq_pending_2_837_AND_soc_plic_ena_ETC___05F_d3856) 
                & (vlTOPp->mkTestBench__DOT__soc_plic_irq_priority_3 
                   > vlTOPp->mkTestBench__DOT__soc_plic_threshold))
                ? vlTOPp->mkTestBench__DOT__soc_plic_irq_priority_3
                : vlTOPp->mkTestBench__DOT__IF_soc_plic_irq_pending_2_837_AND_soc_plic_ena_ETC___05F_d3856);
    } else {
        vlTOPp->mkTestBench__DOT__IF_soc_plic_irq_pending_3_834_AND_soc_plic_ena_ETC___05F_d3895 
            = vlTOPp->mkTestBench__DOT__IF_soc_plic_irq_pending_2_837_AND_soc_plic_ena_ETC___05F_d3893;
        vlTOPp->mkTestBench__DOT__IF_soc_plic_irq_pending_3_834_AND_soc_plic_ena_ETC___05F_d3863 
            = vlTOPp->mkTestBench__DOT__IF_soc_plic_irq_pending_2_837_AND_soc_plic_ena_ETC___05F_d3856;
    }
    vlTOPp->mkTestBench__DOT__soc_core_stall_count__024D_IN 
        = ((IData)(vlTOPp->mkTestBench__DOT__MUX_soc_core_stall_count__024write_1___05FSEL_1)
            ? 2U : (3U & ((IData)(vlTOPp->mkTestBench__DOT__soc_core_stall_count) 
                          - (IData)(1U))));
    if (vlTOPp->mkTestBench__DOT__WILL_FIRE_RL_soc_core_decodeStage) {
        vlTOPp->mkTestBench__DOT__soc_core_id2ex__024D_IN[0U] 
            = vlTOPp->mkTestBench__DOT__MUX_soc_core_id2ex__024enq_1___05FVAL_1[0U];
        vlTOPp->mkTestBench__DOT__soc_core_id2ex__024D_IN[1U] 
            = vlTOPp->mkTestBench__DOT__MUX_soc_core_id2ex__024enq_1___05FVAL_1[1U];
        vlTOPp->mkTestBench__DOT__soc_core_id2ex__024D_IN[2U] 
            = vlTOPp->mkTestBench__DOT__MUX_soc_core_id2ex__024enq_1___05FVAL_1[2U];
        vlTOPp->mkTestBench__DOT__soc_core_id2ex__024D_IN[3U] 
            = vlTOPp->mkTestBench__DOT__MUX_soc_core_id2ex__024enq_1___05FVAL_1[3U];
        vlTOPp->mkTestBench__DOT__soc_core_id2ex__024D_IN[4U] 
            = vlTOPp->mkTestBench__DOT__MUX_soc_core_id2ex__024enq_1___05FVAL_1[4U];
        vlTOPp->mkTestBench__DOT__soc_core_id2ex__024D_IN[5U] 
            = vlTOPp->mkTestBench__DOT__MUX_soc_core_id2ex__024enq_1___05FVAL_1[5U];
        vlTOPp->mkTestBench__DOT__soc_core_id2ex__024D_IN[6U] 
            = vlTOPp->mkTestBench__DOT__MUX_soc_core_id2ex__024enq_1___05FVAL_1[6U];
        vlTOPp->mkTestBench__DOT__soc_core_id2ex__024D_IN[7U] 
            = vlTOPp->mkTestBench__DOT__MUX_soc_core_id2ex__024enq_1___05FVAL_1[7U];
        vlTOPp->mkTestBench__DOT__soc_core_id2ex__024D_IN[8U] 
            = vlTOPp->mkTestBench__DOT__MUX_soc_core_id2ex__024enq_1___05FVAL_1[8U];
        vlTOPp->mkTestBench__DOT__soc_core_id2ex__024D_IN[9U] 
            = vlTOPp->mkTestBench__DOT__MUX_soc_core_id2ex__024enq_1___05FVAL_1[9U];
    } else {
        vlTOPp->mkTestBench__DOT__soc_core_id2ex__024D_IN[0U] = 0U;
        vlTOPp->mkTestBench__DOT__soc_core_id2ex__024D_IN[1U] = 0U;
        vlTOPp->mkTestBench__DOT__soc_core_id2ex__024D_IN[2U] = 0U;
        vlTOPp->mkTestBench__DOT__soc_core_id2ex__024D_IN[3U] = 0x301000U;
        vlTOPp->mkTestBench__DOT__soc_core_id2ex__024D_IN[4U] = 0U;
        vlTOPp->mkTestBench__DOT__soc_core_id2ex__024D_IN[5U] = 0U;
        vlTOPp->mkTestBench__DOT__soc_core_id2ex__024D_IN[6U] = 0U;
        vlTOPp->mkTestBench__DOT__soc_core_id2ex__024D_IN[7U] = 0U;
        vlTOPp->mkTestBench__DOT__soc_core_id2ex__024D_IN[8U] = 0U;
        vlTOPp->mkTestBench__DOT__soc_core_id2ex__024D_IN[9U] = 0U;
    }
    vlTOPp->mkTestBench__DOT__new_csr___05Fh117140 
        = (((0x73U == (0x7fU & ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U] 
                                 << 0x17U) | (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[7U] 
                                              >> 9U)))) 
            & ((1U == (7U & ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U] 
                              << 0xbU) | (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[7U] 
                                          >> 0x15U)))) 
               | (2U == (7U & ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U] 
                                << 0xbU) | (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[7U] 
                                            >> 0x15U))))))
            ? vlTOPp->mkTestBench__DOT__IF_soc_core_id2ex_first___05F406_BITS_239_TO_233_8_ETC___05F_d2126
            : ((((0x73U == (0x7fU & ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U] 
                                      << 0x17U) | (
                                                   vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[7U] 
                                                   >> 9U)))) 
                 & ((3U == (7U & ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U] 
                                   << 0xbU) | (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[7U] 
                                               >> 0x15U)))) 
                    | (5U == (7U & ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U] 
                                     << 0xbU) | (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[7U] 
                                                 >> 0x15U)))))) 
                & (0U != (0x1fU & ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U] 
                                    << 8U) | (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[7U] 
                                              >> 0x18U)))))
                ? (vlTOPp->mkTestBench__DOT__v___05Fh117136 
                   | vlTOPp->mkTestBench__DOT__IF_soc_core_id2ex_first___05F406_BITS_239_TO_233_8_ETC___05F_d2126)
                : ((((0x73U == (0x7fU & ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U] 
                                          << 0x17U) 
                                         | (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[7U] 
                                            >> 9U)))) 
                     & ((6U == (7U & ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U] 
                                       << 0xbU) | (
                                                   vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[7U] 
                                                   >> 0x15U)))) 
                        | (7U == (7U & ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U] 
                                         << 0xbU) | 
                                        (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[7U] 
                                         >> 0x15U)))))) 
                    & (0U != (0x1fU & ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U] 
                                        << 8U) | (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[7U] 
                                                  >> 0x18U)))))
                    ? (vlTOPp->mkTestBench__DOT__v___05Fh117136 
                       & (~ vlTOPp->mkTestBench__DOT__IF_soc_core_id2ex_first___05F406_BITS_239_TO_233_8_ETC___05F_d2126))
                    : vlTOPp->mkTestBench__DOT__v___05Fh117136)));
    vlTOPp->mkTestBench__DOT__IF_soc_core_id2ex_first___05F406_BITS_117_TO_115_7_ETC___05F_d1802 
        = (1U & ((0x200000U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[3U])
                  ? ((0x100000U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[3U])
                      ? ((5U == (7U & ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[4U] 
                                        << 0xdU) | 
                                       (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[3U] 
                                        >> 0x13U)))) 
                         & (~ (IData)(vlTOPp->mkTestBench__DOT__IF_soc_core_ex2mem_notEmpty___05F728_AND_soc_core___05FETC___05F_d1794)))
                      : ((0x80000U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[3U])
                          ? ((5U == (7U & ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[4U] 
                                            << 0xdU) 
                                           | (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[3U] 
                                              >> 0x13U)))) 
                             & (~ (IData)(vlTOPp->mkTestBench__DOT__IF_soc_core_ex2mem_notEmpty___05F728_AND_soc_core___05FETC___05F_d1794)))
                          : (IData)(vlTOPp->mkTestBench__DOT__IF_soc_core_ex2mem_notEmpty___05F728_AND_soc_core___05FETC___05F_d1794)))
                  : ((0x100000U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[3U])
                      ? ((0x80000U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[3U])
                          ? (~ (IData)(vlTOPp->mkTestBench__DOT__IF_soc_core_ex2mem_notEmpty___05F728_AND_soc_core___05FETC___05F_d1790))
                          : (IData)(vlTOPp->mkTestBench__DOT__IF_soc_core_ex2mem_notEmpty___05F728_AND_soc_core___05FETC___05F_d1790))
                      : ((0x80000U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[3U])
                          ? (~ (IData)(vlTOPp->mkTestBench__DOT__IF_soc_core_ex2mem_notEmpty___05F728_AND_soc_core___05FETC___05F_d1786))
                          : (IData)(vlTOPp->mkTestBench__DOT__IF_soc_core_ex2mem_notEmpty___05F728_AND_soc_core___05FETC___05F_d1786)))));
    vlTOPp->mkTestBench__DOT__operand2___05Fh114850 
        = ((0x2000000U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[3U])
            ? ((0x1000000U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[3U])
                ? vlTOPp->mkTestBench__DOT__alu_in2___05Fh114905
                : ((0x800000U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[3U])
                    ? ((0x400000U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[3U])
                        ? ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[5U] 
                            << 0x17U) | (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[4U] 
                                         >> 9U)) : 0U)
                    : vlTOPp->mkTestBench__DOT__alu_in2___05Fh114905))
            : ((0x1000000U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[3U])
                ? vlTOPp->mkTestBench__DOT__alu_in2___05Fh114905
                : ((0x800000U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[3U])
                    ? vlTOPp->mkTestBench__DOT__alu_in2___05Fh114905
                    : ((0x400000U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[3U])
                        ? vlTOPp->mkTestBench__DOT___theResult___05F___05F_5___05Fh113082
                        : vlTOPp->mkTestBench__DOT__alu_in2___05Fh114905))));
    vlTOPp->mkTestBench__DOT__MUX_soc_core_mem_resp_pending__024write_1___05FSEL_1 
        = (((IData)(vlTOPp->mkTestBench__DOT__WILL_FIRE_RL_soc_core_writebackStage) 
            & vlTOPp->mkTestBench__DOT__soc_core_mem2wb__DOT__data0_reg[0U]) 
           & (IData)(vlTOPp->mkTestBench__DOT__soc_core_mem_resp_pending));
    vlTOPp->mkTestBench__DOT__soc_core_mem_resp_pending__024EN 
        = ((((IData)(vlTOPp->mkTestBench__DOT__WILL_FIRE_RL_soc_core_writebackStage) 
             & vlTOPp->mkTestBench__DOT__soc_core_mem2wb__DOT__data0_reg[0U]) 
            & (IData)(vlTOPp->mkTestBench__DOT__soc_core_mem_resp_pending)) 
           | ((IData)(vlTOPp->mkTestBench__DOT__WILL_FIRE_RL_soc_core_memoryStage) 
              & (1U == (3U & ((vlTOPp->mkTestBench__DOT__soc_core_ex2mem__DOT__data0_reg[2U] 
                               << 0x17U) | (vlTOPp->mkTestBench__DOT__soc_core_ex2mem__DOT__data0_reg[1U] 
                                            >> 9U))))));
    vlTOPp->mkTestBench__DOT__soc_core_csrs_mstatus__024EN 
        = ((((IData)(vlTOPp->mkTestBench__DOT__WILL_FIRE_RL_soc_core_writebackStage) 
             & (IData)((vlTOPp->mkTestBench__DOT__soc_core_csrs_mstatus 
                        >> 0x1dU))) & (((vlTOPp->mkTestBench__DOT__enabled_interrupts___05Fh128101 
                                         >> 0xbU) | 
                                        (vlTOPp->mkTestBench__DOT__enabled_interrupts___05Fh128101 
                                         >> 7U)) | 
                                       (vlTOPp->mkTestBench__DOT__enabled_interrupts___05Fh128101 
                                        >> 3U))) | 
           ((IData)(vlTOPp->mkTestBench__DOT__WILL_FIRE_RL_soc_core_executeStage) 
            & ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[3U] 
                >> 9U) | ((0x73U == (0x7fU & ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U] 
                                               << 0x17U) 
                                              | (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[7U] 
                                                 >> 9U)))) 
                          & ((IData)(vlTOPp->mkTestBench__DOT__soc_core_id2ex_first___05F406_BITS_247_TO_245_074___05FETC___05F_d2252) 
                             | ((0U == (7U & ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U] 
                                               << 0xbU) 
                                              | (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[7U] 
                                                 >> 0x15U)))) 
                                & (0x18U == (0x7fU 
                                             & ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[9U] 
                                                 << 0x1eU) 
                                                | (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U] 
                                                   >> 2U))))))))));
    vlTOPp->mkTestBench__DOT__MUX_soc_core_branch_flush__024write_1___05FSEL_1 
        = (((IData)(vlTOPp->mkTestBench__DOT__WILL_FIRE_RL_soc_core_writebackStage) 
            & (IData)((vlTOPp->mkTestBench__DOT__soc_core_csrs_mstatus 
                       >> 0x1dU))) & (((vlTOPp->mkTestBench__DOT__enabled_interrupts___05Fh128101 
                                        >> 0xbU) | 
                                       (vlTOPp->mkTestBench__DOT__enabled_interrupts___05Fh128101 
                                        >> 7U)) | (vlTOPp->mkTestBench__DOT__enabled_interrupts___05Fh128101 
                                                   >> 3U)));
    vlTOPp->mkTestBench__DOT__soc_core_if2id__024D_IN[0U] 
        = ((0xfffffff8U & (vlTOPp->mkTestBench__DOT__prediction_target___05Fh73334 
                           << 3U)) | (((((~ (IData)(vlTOPp->mkTestBench__DOT__soc_core_branch_flush_done)) 
                                         & (~ (IData)(vlTOPp->mkTestBench__DOT__soc_core_no_pc_update))) 
                                        & (IData)(vlTOPp->mkTestBench__DOT__SEL_ARR_soc_core_btb_btbTable_0_055_BIT_0_056___05FETC___05F_d1322)) 
                                       << 2U) | (IData)(vlTOPp->mkTestBench__DOT__soc_core_csrs_priv_mode)));
    vlTOPp->mkTestBench__DOT__soc_core_if2id__024D_IN[1U] 
        = ((7U & (vlTOPp->mkTestBench__DOT__prediction_target___05Fh73334 
                  >> 0x1dU)) | (0xfffffff8U & ((IData)(
                                                       (((QData)((IData)(vlTOPp->mkTestBench__DOT__soc_core_pcReg)) 
                                                         << 0x20U) 
                                                        | (QData)((IData)(vlTOPp->mkTestBench__DOT__instr___05Fh73336)))) 
                                               << 3U)));
    vlTOPp->mkTestBench__DOT__soc_core_if2id__024D_IN[2U] 
        = ((7U & ((IData)((((QData)((IData)(vlTOPp->mkTestBench__DOT__soc_core_pcReg)) 
                            << 0x20U) | (QData)((IData)(vlTOPp->mkTestBench__DOT__instr___05Fh73336)))) 
                  >> 0x1dU)) | (0xfffffff8U & ((IData)(
                                                       ((((QData)((IData)(vlTOPp->mkTestBench__DOT__soc_core_pcReg)) 
                                                          << 0x20U) 
                                                         | (QData)((IData)(vlTOPp->mkTestBench__DOT__instr___05Fh73336))) 
                                                        >> 0x20U)) 
                                               << 3U)));
    vlTOPp->mkTestBench__DOT__soc_core_if2id__024D_IN[3U] 
        = (7U & ((IData)(((((QData)((IData)(vlTOPp->mkTestBench__DOT__soc_core_pcReg)) 
                            << 0x20U) | (QData)((IData)(vlTOPp->mkTestBench__DOT__instr___05Fh73336))) 
                          >> 0x20U)) >> 0x1dU));
    if (((IData)(vlTOPp->mkTestBench__DOT__soc_plic_irq_pending_4) 
         & ((IData)(vlTOPp->mkTestBench__DOT__soc_plic_enable_bits) 
            >> 4U))) {
        vlTOPp->mkTestBench__DOT__IF_soc_plic_irq_pending_4_831_AND_soc_plic_ena_ETC___05F_d3897 
            = (((vlTOPp->mkTestBench__DOT__soc_plic_irq_priority_4 
                 > vlTOPp->mkTestBench__DOT__IF_soc_plic_irq_pending_3_834_AND_soc_plic_ena_ETC___05F_d3863) 
                & (vlTOPp->mkTestBench__DOT__soc_plic_irq_priority_4 
                   > vlTOPp->mkTestBench__DOT__soc_plic_threshold))
                ? 4U : vlTOPp->mkTestBench__DOT__IF_soc_plic_irq_pending_3_834_AND_soc_plic_ena_ETC___05F_d3895);
        vlTOPp->mkTestBench__DOT__IF_soc_plic_irq_pending_4_831_AND_soc_plic_ena_ETC___05F_d3870 
            = (((vlTOPp->mkTestBench__DOT__soc_plic_irq_priority_4 
                 > vlTOPp->mkTestBench__DOT__IF_soc_plic_irq_pending_3_834_AND_soc_plic_ena_ETC___05F_d3863) 
                & (vlTOPp->mkTestBench__DOT__soc_plic_irq_priority_4 
                   > vlTOPp->mkTestBench__DOT__soc_plic_threshold))
                ? vlTOPp->mkTestBench__DOT__soc_plic_irq_priority_4
                : vlTOPp->mkTestBench__DOT__IF_soc_plic_irq_pending_3_834_AND_soc_plic_ena_ETC___05F_d3863);
    } else {
        vlTOPp->mkTestBench__DOT__IF_soc_plic_irq_pending_4_831_AND_soc_plic_ena_ETC___05F_d3897 
            = vlTOPp->mkTestBench__DOT__IF_soc_plic_irq_pending_3_834_AND_soc_plic_ena_ETC___05F_d3895;
        vlTOPp->mkTestBench__DOT__IF_soc_plic_irq_pending_4_831_AND_soc_plic_ena_ETC___05F_d3870 
            = vlTOPp->mkTestBench__DOT__IF_soc_plic_irq_pending_3_834_AND_soc_plic_ena_ETC___05F_d3863;
    }
    vlTOPp->mkTestBench__DOT__soc_core_csrs_mcycle__024D_IN 
        = ((0xb00U == (IData)(vlTOPp->mkTestBench__DOT__addr___05Fh117366))
            ? (((QData)((IData)((vlTOPp->mkTestBench__DOT__soc_core_csrs_mcycle 
                                 >> 0x20U))) << 0x20U) 
               | (QData)((IData)(vlTOPp->mkTestBench__DOT__new_csr___05Fh117140)))
            : (((QData)((IData)(vlTOPp->mkTestBench__DOT__new_csr___05Fh117140)) 
                << 0x20U) | (QData)((IData)(vlTOPp->mkTestBench__DOT__soc_core_csrs_mcycle))));
    vlTOPp->mkTestBench__DOT__soc_core_csrs_mtime__024D_IN 
        = ((0xb01U == (IData)(vlTOPp->mkTestBench__DOT__addr___05Fh117366))
            ? (((QData)((IData)((vlTOPp->mkTestBench__DOT__soc_core_csrs_mtime 
                                 >> 0x20U))) << 0x20U) 
               | (QData)((IData)(vlTOPp->mkTestBench__DOT__new_csr___05Fh117140)))
            : (((QData)((IData)(vlTOPp->mkTestBench__DOT__new_csr___05Fh117140)) 
                << 0x20U) | (QData)((IData)(vlTOPp->mkTestBench__DOT__soc_core_csrs_mtime))));
    vlTOPp->mkTestBench__DOT__soc_core_csrs_mtimecmp__024D_IN 
        = ((0xb02U == (IData)(vlTOPp->mkTestBench__DOT__addr___05Fh117366))
            ? (((QData)((IData)((vlTOPp->mkTestBench__DOT__soc_core_csrs_mtimecmp 
                                 >> 0x20U))) << 0x20U) 
               | (QData)((IData)(vlTOPp->mkTestBench__DOT__new_csr___05Fh117140)))
            : (((QData)((IData)(vlTOPp->mkTestBench__DOT__new_csr___05Fh117140)) 
                << 0x20U) | (QData)((IData)(vlTOPp->mkTestBench__DOT__soc_core_csrs_mtimecmp))));
    vlTOPp->mkTestBench__DOT__soc_core_csrs_minstret__024D_IN 
        = (((((IData)(vlTOPp->mkTestBench__DOT__WILL_FIRE_RL_soc_core_executeStage) 
              & (~ (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[3U] 
                    >> 9U))) & (0x73U == (0x7fU & (
                                                   (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U] 
                                                    << 0x17U) 
                                                   | (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[7U] 
                                                      >> 9U))))) 
            & (IData)(vlTOPp->mkTestBench__DOT__soc_core_id2ex_first___05F406_BITS_247_TO_245_074___05FETC___05F_d2411))
            ? ((0xb03U == (IData)(vlTOPp->mkTestBench__DOT__addr___05Fh117366))
                ? (((QData)((IData)((vlTOPp->mkTestBench__DOT__soc_core_csrs_minstret 
                                     >> 0x20U))) << 0x20U) 
                   | (QData)((IData)(vlTOPp->mkTestBench__DOT__new_csr___05Fh117140)))
                : (((QData)((IData)(vlTOPp->mkTestBench__DOT__new_csr___05Fh117140)) 
                    << 0x20U) | (QData)((IData)(vlTOPp->mkTestBench__DOT__soc_core_csrs_minstret))))
            : (1ULL + vlTOPp->mkTestBench__DOT__soc_core_csrs_minstret));
    vlTOPp->mkTestBench__DOT__IF_soc_core_id2ex_first___05F406_BIT_105_072_THEN___05FETC___05F_d2300 
        = ((0x200U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[3U])
            ? (((QData)((IData)((((1U & (IData)((vlTOPp->mkTestBench__DOT__soc_core_csrs_mstatus 
                                                 >> 0x20U)))
                                   ? 1U : 0U) ? 1U : 0U))) 
                << 0x20U) | (QData)((IData)(((0xc0000000U 
                                              & ((IData)(
                                                         (vlTOPp->mkTestBench__DOT__soc_core_csrs_mstatus 
                                                          >> 0x1eU)) 
                                                 << 0x1eU)) 
                                             | ((0x1c000000U 
                                                 & ((IData)(
                                                            (vlTOPp->mkTestBench__DOT__soc_core_csrs_mstatus 
                                                             >> 0x1aU)) 
                                                    << 0x1aU)) 
                                                | ((0x2000000U 
                                                    & ((IData)(
                                                               (vlTOPp->mkTestBench__DOT__soc_core_csrs_mstatus 
                                                                >> 0x1dU)) 
                                                       << 0x19U)) 
                                                   | ((0x1c00000U 
                                                       & ((IData)(
                                                                  (vlTOPp->mkTestBench__DOT__soc_core_csrs_mstatus 
                                                                   >> 0x16U)) 
                                                          << 0x16U)) 
                                                      | ((0x200000U 
                                                          & ((IData)(
                                                                     (vlTOPp->mkTestBench__DOT__soc_core_csrs_mstatus 
                                                                      >> 0x11U)) 
                                                             << 0x15U)) 
                                                         | ((0x100000U 
                                                             & (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[1U] 
                                                                << 0x13U)) 
                                                            | (0xfffffU 
                                                               & (IData)(vlTOPp->mkTestBench__DOT__soc_core_csrs_mstatus)))))))))))
            : (((QData)((IData)(((0x80000000U & (vlTOPp->mkTestBench__DOT__new_csr___05Fh117140 
                                                 << 0x1fU)) 
                                 | ((0x40000000U & 
                                     (vlTOPp->mkTestBench__DOT__new_csr___05Fh117140 
                                      << 0x1dU)) | 
                                    ((0x20000000U & 
                                      (vlTOPp->mkTestBench__DOT__new_csr___05Fh117140 
                                       << 0x1bU)) | 
                                     ((0x10000000U 
                                       & (vlTOPp->mkTestBench__DOT__new_csr___05Fh117140 
                                          << 0x19U)) 
                                      | ((0x8000000U 
                                          & (vlTOPp->mkTestBench__DOT__new_csr___05Fh117140 
                                             << 0x17U)) 
                                         | ((0x4000000U 
                                             & (vlTOPp->mkTestBench__DOT__new_csr___05Fh117140 
                                                << 0x15U)) 
                                            | ((0x2000000U 
                                                & (vlTOPp->mkTestBench__DOT__new_csr___05Fh117140 
                                                   << 0x13U)) 
                                               | ((0x1000000U 
                                                   & (vlTOPp->mkTestBench__DOT__new_csr___05Fh117140 
                                                      << 0x11U)) 
                                                  | ((0x800000U 
                                                      & (vlTOPp->mkTestBench__DOT__new_csr___05Fh117140 
                                                         << 0xfU)) 
                                                     | ((0x400000U 
                                                         & (vlTOPp->mkTestBench__DOT__new_csr___05Fh117140 
                                                            << 0xdU)) 
                                                        | ((0x200000U 
                                                            & (vlTOPp->mkTestBench__DOT__new_csr___05Fh117140 
                                                               << 0xbU)) 
                                                           | ((0x180000U 
                                                               & (vlTOPp->mkTestBench__DOT__new_csr___05Fh117140 
                                                                  << 8U)) 
                                                              | ((0x70000U 
                                                                  & (vlTOPp->mkTestBench__DOT__new_csr___05Fh117140 
                                                                     << 4U)) 
                                                                 | ((0xc000U 
                                                                     & (vlTOPp->mkTestBench__DOT__new_csr___05Fh117140 
                                                                        >> 1U)) 
                                                                    | ((0x2000U 
                                                                        & (vlTOPp->mkTestBench__DOT__new_csr___05Fh117140 
                                                                           >> 4U)) 
                                                                       | ((0x1000U 
                                                                           & (vlTOPp->mkTestBench__DOT__new_csr___05Fh117140 
                                                                              >> 6U)) 
                                                                          | ((0x800U 
                                                                              & (vlTOPp->mkTestBench__DOT__new_csr___05Fh117140 
                                                                                >> 8U)) 
                                                                             | ((0x400U 
                                                                                & (vlTOPp->mkTestBench__DOT__new_csr___05Fh117140 
                                                                                >> 0xaU)) 
                                                                                | ((0x200U 
                                                                                & (vlTOPp->mkTestBench__DOT__new_csr___05Fh117140 
                                                                                >> 0xcU)) 
                                                                                | ((0x100U 
                                                                                & (vlTOPp->mkTestBench__DOT__new_csr___05Fh117140 
                                                                                >> 0xeU)) 
                                                                                | (0xffU 
                                                                                & (vlTOPp->mkTestBench__DOT__new_csr___05Fh117140 
                                                                                >> 0x17U)))))))))))))))))))))))) 
                << 1U) | (QData)((IData)((1U & (vlTOPp->mkTestBench__DOT__new_csr___05Fh117140 
                                                >> 0x1fU))))));
    vlTOPp->mkTestBench__DOT__soc_core_bht_bhtTable_0__024D_IN 
        = ((2U & (IData)(vlTOPp->mkTestBench__DOT__oldState___05Fh115429))
            ? ((1U & (IData)(vlTOPp->mkTestBench__DOT__oldState___05Fh115429))
                ? ((1U & ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[3U] 
                           >> 0xfU) | ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[3U] 
                                        >> 0x10U) & (IData)(vlTOPp->mkTestBench__DOT__IF_soc_core_id2ex_first___05F406_BITS_117_TO_115_7_ETC___05F_d1802))))
                    ? 3U : 2U) : ((1U & ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[3U] 
                                          >> 0xfU) 
                                         | ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[3U] 
                                             >> 0x10U) 
                                            & (IData)(vlTOPp->mkTestBench__DOT__IF_soc_core_id2ex_first___05F406_BITS_117_TO_115_7_ETC___05F_d1802))))
                                   ? 3U : 1U)) : ((1U 
                                                   & (IData)(vlTOPp->mkTestBench__DOT__oldState___05Fh115429))
                                                   ? 
                                                  ((1U 
                                                    & ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[3U] 
                                                        >> 0xfU) 
                                                       | ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[3U] 
                                                           >> 0x10U) 
                                                          & (IData)(vlTOPp->mkTestBench__DOT__IF_soc_core_id2ex_first___05F406_BITS_117_TO_115_7_ETC___05F_d1802))))
                                                    ? 2U
                                                    : 0U)
                                                   : 
                                                  ((1U 
                                                    & ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[3U] 
                                                        >> 0xfU) 
                                                       | ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[3U] 
                                                           >> 0x10U) 
                                                          & (IData)(vlTOPp->mkTestBench__DOT__IF_soc_core_id2ex_first___05F406_BITS_117_TO_115_7_ETC___05F_d1802))))
                                                    ? 1U
                                                    : 0U)));
    vlTOPp->mkTestBench__DOT__soc_core_id2ex_first___05F406_BIT_111_724_OR_soc_c_ETC___05F_d1809 
        = (1U & (((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[3U] 
                   >> 0xfU) | ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[3U] 
                                >> 0x10U) & ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[3U] 
                                              >> 0xfU) 
                                             | (IData)(vlTOPp->mkTestBench__DOT__IF_soc_core_id2ex_first___05F406_BITS_117_TO_115_7_ETC___05F_d1802)))) 
                 | (vlTOPp->mkTestBench__DOT__SEL_ARR_soc_core_btb_btbTable_0_055_BITS_64_TO_ETC___05F_d1806 
                    == ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[9U] 
                         << 0x17U) | (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U] 
                                      >> 9U)))));
    vlTOPp->mkTestBench__DOT__soc_core_id2ex_first___05F406_BIT_32_309_EQ_soc_co_ETC___05F_d2310 
        = ((1U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[1U]) 
           == (1U & ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[3U] 
                      >> 0xfU) | (IData)(vlTOPp->mkTestBench__DOT__IF_soc_core_id2ex_first___05F406_BITS_117_TO_115_7_ETC___05F_d1802))));
    vlTOPp->mkTestBench__DOT__result___05Fh114861 = 
        (vlTOPp->mkTestBench__DOT__operand1___05Fh114849 
         + vlTOPp->mkTestBench__DOT__operand2___05Fh114850);
    if (((IData)(vlTOPp->mkTestBench__DOT__soc_plic_irq_pending_5) 
         & ((IData)(vlTOPp->mkTestBench__DOT__soc_plic_enable_bits) 
            >> 5U))) {
        vlTOPp->mkTestBench__DOT__IF_soc_plic_irq_pending_5_828_AND_soc_plic_ena_ETC___05F_d3899 
            = (((vlTOPp->mkTestBench__DOT__soc_plic_irq_priority_5 
                 > vlTOPp->mkTestBench__DOT__IF_soc_plic_irq_pending_4_831_AND_soc_plic_ena_ETC___05F_d3870) 
                & (vlTOPp->mkTestBench__DOT__soc_plic_irq_priority_5 
                   > vlTOPp->mkTestBench__DOT__soc_plic_threshold))
                ? 5U : vlTOPp->mkTestBench__DOT__IF_soc_plic_irq_pending_4_831_AND_soc_plic_ena_ETC___05F_d3897);
        vlTOPp->mkTestBench__DOT__IF_soc_plic_irq_pending_5_828_AND_soc_plic_ena_ETC___05F_d3877 
            = (((vlTOPp->mkTestBench__DOT__soc_plic_irq_priority_5 
                 > vlTOPp->mkTestBench__DOT__IF_soc_plic_irq_pending_4_831_AND_soc_plic_ena_ETC___05F_d3870) 
                & (vlTOPp->mkTestBench__DOT__soc_plic_irq_priority_5 
                   > vlTOPp->mkTestBench__DOT__soc_plic_threshold))
                ? vlTOPp->mkTestBench__DOT__soc_plic_irq_priority_5
                : vlTOPp->mkTestBench__DOT__IF_soc_plic_irq_pending_4_831_AND_soc_plic_ena_ETC___05F_d3870);
    } else {
        vlTOPp->mkTestBench__DOT__IF_soc_plic_irq_pending_5_828_AND_soc_plic_ena_ETC___05F_d3899 
            = vlTOPp->mkTestBench__DOT__IF_soc_plic_irq_pending_4_831_AND_soc_plic_ena_ETC___05F_d3897;
        vlTOPp->mkTestBench__DOT__IF_soc_plic_irq_pending_5_828_AND_soc_plic_ena_ETC___05F_d3877 
            = vlTOPp->mkTestBench__DOT__IF_soc_plic_irq_pending_4_831_AND_soc_plic_ena_ETC___05F_d3870;
    }
    vlTOPp->mkTestBench__DOT__soc_core_csrs_mstatus__024D_IN 
        = ((IData)(vlTOPp->mkTestBench__DOT__MUX_soc_core_branch_flush__024write_1___05FSEL_1)
            ? (((QData)((IData)((((1U & (IData)((vlTOPp->mkTestBench__DOT__soc_core_csrs_mstatus 
                                                 >> 0x20U)))
                                   ? 1U : 0U) ? 1U : 0U))) 
                << 0x20U) | (QData)((IData)((0x2100000U 
                                             | ((0xc0000000U 
                                                 & ((IData)(
                                                            (vlTOPp->mkTestBench__DOT__soc_core_csrs_mstatus 
                                                             >> 0x1eU)) 
                                                    << 0x1eU)) 
                                                | ((0x1c000000U 
                                                    & ((IData)(
                                                               (vlTOPp->mkTestBench__DOT__soc_core_csrs_mstatus 
                                                                >> 0x1aU)) 
                                                       << 0x1aU)) 
                                                   | ((0x1c00000U 
                                                       & ((IData)(
                                                                  (vlTOPp->mkTestBench__DOT__soc_core_csrs_mstatus 
                                                                   >> 0x16U)) 
                                                          << 0x16U)) 
                                                      | ((0x200000U 
                                                          & ((IData)(
                                                                     (vlTOPp->mkTestBench__DOT__soc_core_csrs_mstatus 
                                                                      >> 0x11U)) 
                                                             << 0x15U)) 
                                                         | (0xfffffU 
                                                            & (IData)(vlTOPp->mkTestBench__DOT__soc_core_csrs_mstatus))))))))))
            : ((1U & ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[3U] 
                       >> 9U) | ((0x73U == (0x7fU & 
                                            ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U] 
                                              << 0x17U) 
                                             | (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[7U] 
                                                >> 9U)))) 
                                 & (IData)(vlTOPp->mkTestBench__DOT__soc_core_id2ex_first___05F406_BITS_247_TO_245_074___05FETC___05F_d2252))))
                ? vlTOPp->mkTestBench__DOT__IF_soc_core_id2ex_first___05F406_BIT_105_072_THEN___05FETC___05F_d2300
                : (((QData)((IData)((((1U & (IData)(
                                                    (vlTOPp->mkTestBench__DOT__soc_core_csrs_mstatus 
                                                     >> 0x20U)))
                                       ? 1U : 0U) ? 1U
                                      : 0U))) << 0x20U) 
                   | (QData)((IData)((0x2000000U | 
                                      ((0xc0000000U 
                                        & ((IData)(
                                                   (vlTOPp->mkTestBench__DOT__soc_core_csrs_mstatus 
                                                    >> 0x1eU)) 
                                           << 0x1eU)) 
                                       | ((0x20000000U 
                                           & ((IData)(
                                                      (vlTOPp->mkTestBench__DOT__soc_core_csrs_mstatus 
                                                       >> 0x19U)) 
                                              << 0x1dU)) 
                                          | ((0x1c000000U 
                                              & ((IData)(
                                                         (vlTOPp->mkTestBench__DOT__soc_core_csrs_mstatus 
                                                          >> 0x1aU)) 
                                                 << 0x1aU)) 
                                             | ((0x1c00000U 
                                                 & ((IData)(
                                                            (vlTOPp->mkTestBench__DOT__soc_core_csrs_mstatus 
                                                             >> 0x16U)) 
                                                    << 0x16U)) 
                                                | ((0x200000U 
                                                    & ((IData)(
                                                               (vlTOPp->mkTestBench__DOT__soc_core_csrs_mstatus 
                                                                >> 0x11U)) 
                                                       << 0x15U)) 
                                                   | (0x1fffffU 
                                                      & (IData)(vlTOPp->mkTestBench__DOT__soc_core_csrs_mstatus)))))))))))));
    vlTOPp->mkTestBench__DOT__soc_core_id2ex__024DEQ 
        = ((((((IData)(vlTOPp->mkTestBench__DOT__WILL_FIRE_RL_soc_core_executeStage) 
               & (~ (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[3U] 
                     >> 9U))) & (((0x73U != (0x7fU 
                                             & ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U] 
                                                 << 0x17U) 
                                                | (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[7U] 
                                                   >> 9U)))) 
                                  | (0U != (7U & ((
                                                   vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U] 
                                                   << 0xbU) 
                                                  | (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[7U] 
                                                     >> 0x15U))))) 
                                 | (0x18U != (0x7fU 
                                              & ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[9U] 
                                                  << 0x1eU) 
                                                 | (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U] 
                                                    >> 2U)))))) 
             & (~ (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[3U] 
                   >> 0xfU))) & ((~ (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[3U] 
                                     >> 0x10U)) | (
                                                   (0x200000U 
                                                    & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[3U])
                                                    ? 
                                                   ((0x100000U 
                                                     & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[3U])
                                                     ? 
                                                    ((5U 
                                                      != 
                                                      (7U 
                                                       & ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[4U] 
                                                           << 0xdU) 
                                                          | (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[3U] 
                                                             >> 0x13U)))) 
                                                     | (IData)(vlTOPp->mkTestBench__DOT__IF_soc_core_ex2mem_notEmpty___05F728_AND_soc_core___05FETC___05F_d1794))
                                                     : 
                                                    ((0x80000U 
                                                      & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[3U])
                                                      ? 
                                                     ((5U 
                                                       != 
                                                       (7U 
                                                        & ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[4U] 
                                                            << 0xdU) 
                                                           | (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[3U] 
                                                              >> 0x13U)))) 
                                                      | (IData)(vlTOPp->mkTestBench__DOT__IF_soc_core_ex2mem_notEmpty___05F728_AND_soc_core___05FETC___05F_d1794))
                                                      : 
                                                     (~ (IData)(vlTOPp->mkTestBench__DOT__IF_soc_core_ex2mem_notEmpty___05F728_AND_soc_core___05FETC___05F_d1794))))
                                                    : 
                                                   ((0x100000U 
                                                     & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[3U])
                                                     ? 
                                                    ((0x80000U 
                                                      & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[3U])
                                                      ? (IData)(vlTOPp->mkTestBench__DOT__IF_soc_core_ex2mem_notEmpty___05F728_AND_soc_core___05FETC___05F_d1790)
                                                      : 
                                                     (~ (IData)(vlTOPp->mkTestBench__DOT__IF_soc_core_ex2mem_notEmpty___05F728_AND_soc_core___05FETC___05F_d1790)))
                                                     : 
                                                    ((0x80000U 
                                                      & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[3U])
                                                      ? (IData)(vlTOPp->mkTestBench__DOT__IF_soc_core_ex2mem_notEmpty___05F728_AND_soc_core___05FETC___05F_d1786)
                                                      : 
                                                     (~ (IData)(vlTOPp->mkTestBench__DOT__IF_soc_core_ex2mem_notEmpty___05F728_AND_soc_core___05FETC___05F_d1786))))))) 
           & ((~ (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[3U] 
                  >> 0x10U)) | (IData)(vlTOPp->mkTestBench__DOT__soc_core_id2ex_first___05F406_BIT_32_309_EQ_soc_co_ETC___05F_d2310)));
    vlTOPp->mkTestBench__DOT__soc_core_id2ex_first___05F406_BITS_239_TO_233_811___05FETC___05F_d2314 
        = (1U & (((((0x73U == (0x7fU & ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U] 
                                         << 0x17U) 
                                        | (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[7U] 
                                           >> 9U)))) 
                    & (0U == (7U & ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U] 
                                     << 0xbU) | (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[7U] 
                                                 >> 0x15U))))) 
                   & (0x18U == (0x7fU & ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[9U] 
                                          << 0x1eU) 
                                         | (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U] 
                                            >> 2U))))) 
                  | (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[3U] 
                     >> 0xfU)) | ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[3U] 
                                   >> 0x10U) & ((IData)(vlTOPp->mkTestBench__DOT__IF_soc_core_id2ex_first___05F406_BITS_117_TO_115_7_ETC___05F_d1802) 
                                                | (~ (IData)(vlTOPp->mkTestBench__DOT__soc_core_id2ex_first___05F406_BIT_32_309_EQ_soc_co_ETC___05F_d2310))))));
    vlTOPp->mkTestBench__DOT__alu_result___05Fh113086 
        = ((0x2000000U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[3U])
            ? ((0x1000000U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[3U])
                ? 0U : ((0x800000U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[3U])
                         ? ((0x400000U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[3U])
                             ? vlTOPp->mkTestBench__DOT__result___05Fh114861
                             : vlTOPp->mkTestBench__DOT__operand1___05Fh114849)
                         : ((0x400000U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[3U])
                             ? (vlTOPp->mkTestBench__DOT__operand1___05Fh114849 
                                & vlTOPp->mkTestBench__DOT__operand2___05Fh114850)
                             : (vlTOPp->mkTestBench__DOT__operand1___05Fh114849 
                                | vlTOPp->mkTestBench__DOT__operand2___05Fh114850))))
            : ((0x1000000U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[3U])
                ? ((0x800000U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[3U])
                    ? ((0x400000U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[3U])
                        ? ((vlTOPp->mkTestBench__DOT__operand1___05Fh114849 
                            >> (0x1fU & vlTOPp->mkTestBench__DOT__operand2___05Fh114850)) 
                           | ((~ (0xffffffffU >> (0x1fU 
                                                  & vlTOPp->mkTestBench__DOT__operand2___05Fh114850))) 
                              & (- (IData)((1U & (vlTOPp->mkTestBench__DOT__operand1___05Fh114849 
                                                  >> 0x1fU))))))
                        : (vlTOPp->mkTestBench__DOT__operand1___05Fh114849 
                           >> (0x1fU & vlTOPp->mkTestBench__DOT__operand2___05Fh114850)))
                    : ((0x400000U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[3U])
                        ? (vlTOPp->mkTestBench__DOT__operand1___05Fh114849 
                           ^ vlTOPp->mkTestBench__DOT__operand2___05Fh114850)
                        : ((vlTOPp->mkTestBench__DOT__operand1___05Fh114849 
                            < vlTOPp->mkTestBench__DOT__operand2___05Fh114850)
                            ? 1U : 0U))) : ((0x800000U 
                                             & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[3U])
                                             ? ((0x400000U 
                                                 & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[3U])
                                                 ? 
                                                (((0x80000000U 
                                                   ^ vlTOPp->mkTestBench__DOT__operand1___05Fh114849) 
                                                  < 
                                                  (0x80000000U 
                                                   ^ vlTOPp->mkTestBench__DOT__operand2___05Fh114850))
                                                  ? 1U
                                                  : 0U)
                                                 : 
                                                (vlTOPp->mkTestBench__DOT__operand1___05Fh114849 
                                                 << 
                                                 (0x1fU 
                                                  & vlTOPp->mkTestBench__DOT__operand2___05Fh114850)))
                                             : ((0x400000U 
                                                 & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[3U])
                                                 ? 
                                                (vlTOPp->mkTestBench__DOT__operand1___05Fh114849 
                                                 - vlTOPp->mkTestBench__DOT__operand2___05Fh114850)
                                                 : vlTOPp->mkTestBench__DOT__result___05Fh114861))));
    vlTOPp->mkTestBench__DOT__IF_soc_plic_irq_pending_6_825_AND_soc_plic_ena_ETC___05F_d3901 
        = (((IData)(vlTOPp->mkTestBench__DOT__soc_plic_irq_pending_6) 
            & ((IData)(vlTOPp->mkTestBench__DOT__soc_plic_enable_bits) 
               >> 6U)) ? (((vlTOPp->mkTestBench__DOT__soc_plic_irq_priority_6 
                            > vlTOPp->mkTestBench__DOT__IF_soc_plic_irq_pending_5_828_AND_soc_plic_ena_ETC___05F_d3877) 
                           & (vlTOPp->mkTestBench__DOT__soc_plic_irq_priority_6 
                              > vlTOPp->mkTestBench__DOT__soc_plic_threshold))
                           ? 6U : vlTOPp->mkTestBench__DOT__IF_soc_plic_irq_pending_5_828_AND_soc_plic_ena_ETC___05F_d3899)
            : vlTOPp->mkTestBench__DOT__IF_soc_plic_irq_pending_5_828_AND_soc_plic_ena_ETC___05F_d3899);
    vlTOPp->mkTestBench__DOT__soc_core_id2ex__024CLR 
        = (((IData)(vlTOPp->mkTestBench__DOT__WILL_FIRE_RL_soc_core_executeStage) 
            & ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[3U] 
                >> 9U) | (IData)(vlTOPp->mkTestBench__DOT__soc_core_id2ex_first___05F406_BITS_239_TO_233_811___05FETC___05F_d2314))) 
           | (((IData)(vlTOPp->mkTestBench__DOT__WILL_FIRE_RL_soc_core_writebackStage) 
               & (IData)((vlTOPp->mkTestBench__DOT__soc_core_csrs_mstatus 
                          >> 0x1dU))) & (((vlTOPp->mkTestBench__DOT__enabled_interrupts___05Fh128101 
                                           >> 0xbU) 
                                          | (vlTOPp->mkTestBench__DOT__enabled_interrupts___05Fh128101 
                                             >> 7U)) 
                                         | (vlTOPp->mkTestBench__DOT__enabled_interrupts___05Fh128101 
                                            >> 3U))));
    vlTOPp->mkTestBench__DOT__soc_core_if2id__024CLR 
        = (((IData)(vlTOPp->mkTestBench__DOT__WILL_FIRE_RL_soc_core_executeStage) 
            & ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[3U] 
                >> 9U) | (IData)(vlTOPp->mkTestBench__DOT__soc_core_id2ex_first___05F406_BITS_239_TO_233_811___05FETC___05F_d2314))) 
           | (((IData)(vlTOPp->mkTestBench__DOT__WILL_FIRE_RL_soc_core_writebackStage) 
               & (IData)((vlTOPp->mkTestBench__DOT__soc_core_csrs_mstatus 
                          >> 0x1dU))) & (((vlTOPp->mkTestBench__DOT__enabled_interrupts___05Fh128101 
                                           >> 0xbU) 
                                          | (vlTOPp->mkTestBench__DOT__enabled_interrupts___05Fh128101 
                                             >> 7U)) 
                                         | (vlTOPp->mkTestBench__DOT__enabled_interrupts___05Fh128101 
                                            >> 3U))));
    vlTOPp->mkTestBench__DOT__soc_core_branch_flush__024EN 
        = ((((IData)(vlTOPp->mkTestBench__DOT__WILL_FIRE_RL_soc_core_executeStage) 
             & ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[3U] 
                 >> 9U) | (IData)(vlTOPp->mkTestBench__DOT__soc_core_id2ex_first___05F406_BITS_239_TO_233_811___05FETC___05F_d2314))) 
            | (((IData)(vlTOPp->mkTestBench__DOT__WILL_FIRE_RL_soc_core_writebackStage) 
                & (IData)((vlTOPp->mkTestBench__DOT__soc_core_csrs_mstatus 
                           >> 0x1dU))) & (((vlTOPp->mkTestBench__DOT__enabled_interrupts___05Fh128101 
                                            >> 0xbU) 
                                           | (vlTOPp->mkTestBench__DOT__enabled_interrupts___05Fh128101 
                                              >> 7U)) 
                                          | (vlTOPp->mkTestBench__DOT__enabled_interrupts___05Fh128101 
                                             >> 3U)))) 
           | (IData)(vlTOPp->mkTestBench__DOT__soc_core_branch_flush));
    vlTOPp->mkTestBench__DOT__MUX_soc_core_branch_flush__024write_1___05FSEL_2 
        = ((IData)(vlTOPp->mkTestBench__DOT__WILL_FIRE_RL_soc_core_executeStage) 
           & ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[3U] 
               >> 9U) | (IData)(vlTOPp->mkTestBench__DOT__soc_core_id2ex_first___05F406_BITS_239_TO_233_811___05FETC___05F_d2314)));
    vlTOPp->mkTestBench__DOT__actual_target___05Fh113093 
        = ((0x8000U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[3U])
            ? ((0x6fU == (0x7fU & ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U] 
                                    << 0x17U) | (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[7U] 
                                                 >> 9U))))
                ? vlTOPp->mkTestBench__DOT__actual_target___05F_1___05Fh114832
                : (0xfffffffeU & vlTOPp->mkTestBench__DOT__alu_result___05Fh113086))
            : ((0x10000U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[3U])
                ? vlTOPp->mkTestBench__DOT__actual_target___05F_1___05Fh114832
                : 0U));
    vlTOPp->mkTestBench__DOT__v___05Fh164458 = ((1U 
                                                 == 
                                                 (3U 
                                                  & ((vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U] 
                                                      << 0x1dU) 
                                                     | (vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[0U] 
                                                        >> 3U))))
                                                 ? 
                                                ((0xc000000U 
                                                  == 
                                                  ((vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[2U] 
                                                    << 0x1bU) 
                                                   | (vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U] 
                                                      >> 5U)))
                                                  ? vlTOPp->mkTestBench__DOT__soc_plic_threshold
                                                  : 
                                                 (((0xc000004U 
                                                    <= 
                                                    ((vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[2U] 
                                                      << 0x1bU) 
                                                     | (vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U] 
                                                        >> 5U))) 
                                                   & (0xc000024U 
                                                      > 
                                                      ((vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[2U] 
                                                        << 0x1bU) 
                                                       | (vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U] 
                                                          >> 5U))))
                                                   ? 
                                                  (((0U 
                                                     != 
                                                     (0x3fffffffU 
                                                      & ((((vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[2U] 
                                                            << 0x1bU) 
                                                           | (vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U] 
                                                              >> 5U)) 
                                                          - (IData)(0xc000004U)) 
                                                         >> 2U))) 
                                                    & (8U 
                                                       > 
                                                       (0x3fffffffU 
                                                        & ((((vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[2U] 
                                                              << 0x1bU) 
                                                             | (vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U] 
                                                                >> 5U)) 
                                                            - (IData)(0xc000004U)) 
                                                           >> 2U))))
                                                    ? vlTOPp->mkTestBench__DOT__result___05F_1___05Fh165630
                                                    : 0U)
                                                   : 
                                                  ((0xc002000U 
                                                    == 
                                                    ((vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[2U] 
                                                      << 0x1bU) 
                                                     | (vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U] 
                                                        >> 5U)))
                                                    ? (IData)(vlTOPp->mkTestBench__DOT__soc_plic_enable_bits)
                                                    : 
                                                   ((0xc200004U 
                                                     == 
                                                     ((vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[2U] 
                                                       << 0x1bU) 
                                                      | (vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U] 
                                                         >> 5U)))
                                                     ? 
                                                    (((IData)(vlTOPp->mkTestBench__DOT__soc_plic_irq_pending_7) 
                                                      & ((IData)(vlTOPp->mkTestBench__DOT__soc_plic_enable_bits) 
                                                         >> 7U))
                                                      ? 
                                                     (((vlTOPp->mkTestBench__DOT__soc_plic_irq_priority_7 
                                                        > 
                                                        (((IData)(vlTOPp->mkTestBench__DOT__soc_plic_irq_pending_6) 
                                                          & ((IData)(vlTOPp->mkTestBench__DOT__soc_plic_enable_bits) 
                                                             >> 6U))
                                                          ? 
                                                         (((vlTOPp->mkTestBench__DOT__soc_plic_irq_priority_6 
                                                            > vlTOPp->mkTestBench__DOT__IF_soc_plic_irq_pending_5_828_AND_soc_plic_ena_ETC___05F_d3877) 
                                                           & (vlTOPp->mkTestBench__DOT__soc_plic_irq_priority_6 
                                                              > vlTOPp->mkTestBench__DOT__soc_plic_threshold))
                                                           ? vlTOPp->mkTestBench__DOT__soc_plic_irq_priority_6
                                                           : vlTOPp->mkTestBench__DOT__IF_soc_plic_irq_pending_5_828_AND_soc_plic_ena_ETC___05F_d3877)
                                                          : vlTOPp->mkTestBench__DOT__IF_soc_plic_irq_pending_5_828_AND_soc_plic_ena_ETC___05F_d3877)) 
                                                       & (vlTOPp->mkTestBench__DOT__soc_plic_irq_priority_7 
                                                          > vlTOPp->mkTestBench__DOT__soc_plic_threshold))
                                                       ? 7U
                                                       : vlTOPp->mkTestBench__DOT__IF_soc_plic_irq_pending_6_825_AND_soc_plic_ena_ETC___05F_d3901)
                                                      : vlTOPp->mkTestBench__DOT__IF_soc_plic_irq_pending_6_825_AND_soc_plic_ena_ETC___05F_d3901)
                                                     : 0U))))
                                                 : 0U);
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_0__024D_IN[0U] 
        = ((0xfffffffeU & ((IData)((((QData)((IData)(
                                                     ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[9U] 
                                                       << 0x17U) 
                                                      | (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U] 
                                                         >> 9U)))) 
                                     << 0x20U) | (QData)((IData)(vlTOPp->mkTestBench__DOT__actual_target___05Fh113093)))) 
                           << 1U)) | (1U & ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[3U] 
                                             >> 0xfU) 
                                            | ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[3U] 
                                                >> 0x10U) 
                                               & ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[3U] 
                                                   >> 0xfU) 
                                                  | (IData)(vlTOPp->mkTestBench__DOT__IF_soc_core_id2ex_first___05F406_BITS_117_TO_115_7_ETC___05F_d1802))))));
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_0__024D_IN[1U] 
        = ((1U & ((IData)((((QData)((IData)(((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[9U] 
                                              << 0x17U) 
                                             | (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U] 
                                                >> 9U)))) 
                            << 0x20U) | (QData)((IData)(vlTOPp->mkTestBench__DOT__actual_target___05Fh113093)))) 
                  >> 0x1fU)) | (0xfffffffeU & ((IData)(
                                                       ((((QData)((IData)(
                                                                          ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[9U] 
                                                                            << 0x17U) 
                                                                           | (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U] 
                                                                              >> 9U)))) 
                                                          << 0x20U) 
                                                         | (QData)((IData)(vlTOPp->mkTestBench__DOT__actual_target___05Fh113093))) 
                                                        >> 0x20U)) 
                                               << 1U)));
    vlTOPp->mkTestBench__DOT__soc_core_btb_btbTable_0__024D_IN[2U] 
        = (1U & ((IData)(((((QData)((IData)(((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[9U] 
                                              << 0x17U) 
                                             | (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U] 
                                                >> 9U)))) 
                            << 0x20U) | (QData)((IData)(vlTOPp->mkTestBench__DOT__actual_target___05Fh113093))) 
                          >> 0x20U)) >> 0x1fU));
    __Vtemp106[0U] = (IData)((((QData)((IData)((0x1fU 
                                                & ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[4U] 
                                                    << 6U) 
                                                   | (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[3U] 
                                                      >> 0x1aU))))) 
                               << 0x2bU) | (((QData)((IData)(
                                                             (0xfU 
                                                              & ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[4U] 
                                                                  << 0x11U) 
                                                                 | (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[3U] 
                                                                    >> 0xfU))))) 
                                             << 0x27U) 
                                            | (((QData)((IData)(
                                                                (1U 
                                                                 & ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[3U] 
                                                                     >> 0xfU) 
                                                                    | ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[3U] 
                                                                        >> 0x10U) 
                                                                       & (IData)(vlTOPp->mkTestBench__DOT__IF_soc_core_id2ex_first___05F406_BITS_117_TO_115_7_ETC___05F_d1802)))))) 
                                                << 0x26U) 
                                               | (((QData)((IData)(vlTOPp->mkTestBench__DOT__actual_target___05Fh113093)) 
                                                   << 6U) 
                                                  | (QData)((IData)(
                                                                    ((0x20U 
                                                                      & (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[1U] 
                                                                         << 5U)) 
                                                                     | ((0x10U 
                                                                         & (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[3U] 
                                                                            >> 0xaU)) 
                                                                        | (((1U 
                                                                             == 
                                                                             (3U 
                                                                              & ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[4U] 
                                                                                << 0xfU) 
                                                                                | (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[3U] 
                                                                                >> 0x11U)))) 
                                                                            << 3U) 
                                                                           | (7U 
                                                                              & ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[4U] 
                                                                                << 0x16U) 
                                                                                | (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[3U] 
                                                                                >> 0xaU)))))))))))));
    __Vtemp106[1U] = ((0xffff0000U & (vlTOPp->mkTestBench__DOT___theResult___05F___05F_5___05Fh113082 
                                      << 0x10U)) | (IData)(
                                                           ((((QData)((IData)(
                                                                              (0x1fU 
                                                                               & ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[4U] 
                                                                                << 6U) 
                                                                                | (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[3U] 
                                                                                >> 0x1aU))))) 
                                                              << 0x2bU) 
                                                             | (((QData)((IData)(
                                                                                (0xfU 
                                                                                & ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[4U] 
                                                                                << 0x11U) 
                                                                                | (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[3U] 
                                                                                >> 0xfU))))) 
                                                                 << 0x27U) 
                                                                | (((QData)((IData)(
                                                                                (1U 
                                                                                & ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[3U] 
                                                                                >> 0xfU) 
                                                                                | ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[3U] 
                                                                                >> 0x10U) 
                                                                                & (IData)(vlTOPp->mkTestBench__DOT__IF_soc_core_id2ex_first___05F406_BITS_117_TO_115_7_ETC___05F_d1802)))))) 
                                                                    << 0x26U) 
                                                                   | (((QData)((IData)(vlTOPp->mkTestBench__DOT__actual_target___05Fh113093)) 
                                                                       << 6U) 
                                                                      | (QData)((IData)(
                                                                                ((0x20U 
                                                                                & (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[1U] 
                                                                                << 5U)) 
                                                                                | ((0x10U 
                                                                                & (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[3U] 
                                                                                >> 0xaU)) 
                                                                                | (((1U 
                                                                                == 
                                                                                (3U 
                                                                                & ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[4U] 
                                                                                << 0xfU) 
                                                                                | (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[3U] 
                                                                                >> 0x11U)))) 
                                                                                << 3U) 
                                                                                | (7U 
                                                                                & ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[4U] 
                                                                                << 0x16U) 
                                                                                | (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[3U] 
                                                                                >> 0xaU)))))))))))) 
                                                            >> 0x20U)));
    __Vtemp106[3U] = ((0xffffU & ((IData)((((QData)((IData)(
                                                            ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[9U] 
                                                              << 0x17U) 
                                                             | (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U] 
                                                                >> 9U)))) 
                                            << 0x20U) 
                                           | (QData)((IData)(
                                                             ((0x73U 
                                                               == 
                                                               (0x7fU 
                                                                & ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U] 
                                                                    << 0x17U) 
                                                                   | (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[7U] 
                                                                      >> 9U))))
                                                               ? vlTOPp->mkTestBench__DOT__v___05Fh117136
                                                               : 
                                                              ((0x8000U 
                                                                & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[3U])
                                                                ? 
                                                               ((IData)(4U) 
                                                                + 
                                                                ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[9U] 
                                                                  << 0x17U) 
                                                                 | (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U] 
                                                                    >> 9U)))
                                                                : vlTOPp->mkTestBench__DOT__alu_result___05Fh113086)))))) 
                                  >> 0x10U)) | (0xffff0000U 
                                                & ((IData)(
                                                           ((((QData)((IData)(
                                                                              ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[9U] 
                                                                                << 0x17U) 
                                                                               | (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U] 
                                                                                >> 9U)))) 
                                                              << 0x20U) 
                                                             | (QData)((IData)(
                                                                               ((0x73U 
                                                                                == 
                                                                                (0x7fU 
                                                                                & ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U] 
                                                                                << 0x17U) 
                                                                                | (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[7U] 
                                                                                >> 9U))))
                                                                                 ? vlTOPp->mkTestBench__DOT__v___05Fh117136
                                                                                 : 
                                                                                ((0x8000U 
                                                                                & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[3U])
                                                                                 ? 
                                                                                ((IData)(4U) 
                                                                                + 
                                                                                ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[9U] 
                                                                                << 0x17U) 
                                                                                | (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U] 
                                                                                >> 9U)))
                                                                                 : vlTOPp->mkTestBench__DOT__alu_result___05Fh113086))))) 
                                                            >> 0x20U)) 
                                                   << 0x10U)));
    vlTOPp->mkTestBench__DOT__soc_core_ex2mem__024D_IN[0U] 
        = __Vtemp106[0U];
    vlTOPp->mkTestBench__DOT__soc_core_ex2mem__024D_IN[1U] 
        = __Vtemp106[1U];
    vlTOPp->mkTestBench__DOT__soc_core_ex2mem__024D_IN[2U] 
        = ((0xffffU & (vlTOPp->mkTestBench__DOT___theResult___05F___05F_5___05Fh113082 
                       >> 0x10U)) | (0xffff0000U & 
                                     ((IData)((((QData)((IData)(
                                                                ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[9U] 
                                                                  << 0x17U) 
                                                                 | (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U] 
                                                                    >> 9U)))) 
                                                << 0x20U) 
                                               | (QData)((IData)(
                                                                 ((0x73U 
                                                                   == 
                                                                   (0x7fU 
                                                                    & ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U] 
                                                                        << 0x17U) 
                                                                       | (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[7U] 
                                                                          >> 9U))))
                                                                   ? vlTOPp->mkTestBench__DOT__v___05Fh117136
                                                                   : 
                                                                  ((0x8000U 
                                                                    & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[3U])
                                                                    ? 
                                                                   ((IData)(4U) 
                                                                    + 
                                                                    ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[9U] 
                                                                      << 0x17U) 
                                                                     | (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U] 
                                                                        >> 9U)))
                                                                    : vlTOPp->mkTestBench__DOT__alu_result___05Fh113086)))))) 
                                      << 0x10U)));
    vlTOPp->mkTestBench__DOT__soc_core_ex2mem__024D_IN[3U] 
        = __Vtemp106[3U];
    vlTOPp->mkTestBench__DOT__soc_core_ex2mem__024D_IN[4U] 
        = (0xffffU & ((IData)(((((QData)((IData)(((
                                                   vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[9U] 
                                                   << 0x17U) 
                                                  | (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U] 
                                                     >> 9U)))) 
                                 << 0x20U) | (QData)((IData)(
                                                             ((0x73U 
                                                               == 
                                                               (0x7fU 
                                                                & ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U] 
                                                                    << 0x17U) 
                                                                   | (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[7U] 
                                                                      >> 9U))))
                                                               ? vlTOPp->mkTestBench__DOT__v___05Fh117136
                                                               : 
                                                              ((0x8000U 
                                                                & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[3U])
                                                                ? 
                                                               ((IData)(4U) 
                                                                + 
                                                                ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[9U] 
                                                                  << 0x17U) 
                                                                 | (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U] 
                                                                    >> 9U)))
                                                                : vlTOPp->mkTestBench__DOT__alu_result___05Fh113086))))) 
                               >> 0x20U)) >> 0x10U));
    vlTOPp->mkTestBench__DOT__soc_core_pcReg__024D_IN 
        = ((IData)(vlTOPp->mkTestBench__DOT__MUX_soc_core_branch_flush__024write_1___05FSEL_1)
            ? (0xfffffffcU & vlTOPp->mkTestBench__DOT__soc_core_csrs_mtvec)
            : ((IData)(vlTOPp->mkTestBench__DOT__MUX_soc_core_branch_flush__024write_1___05FSEL_2)
                ? ((0x200U & vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[3U])
                    ? (0xfffffffcU & vlTOPp->mkTestBench__DOT__soc_core_csrs_mtvec)
                    : ((((0x73U == (0x7fU & ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U] 
                                              << 0x17U) 
                                             | (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[7U] 
                                                >> 9U)))) 
                         & (0U == (7U & ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U] 
                                          << 0xbU) 
                                         | (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[7U] 
                                            >> 0x15U))))) 
                        & (0x18U == (0x7fU & ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[9U] 
                                               << 0x1eU) 
                                              | (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U] 
                                                 >> 2U)))))
                        ? vlTOPp->mkTestBench__DOT__soc_core_csrs_mepc
                        : ((1U & ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[3U] 
                                   >> 0xfU) | ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[3U] 
                                                >> 0x10U) 
                                               & (IData)(vlTOPp->mkTestBench__DOT__IF_soc_core_id2ex_first___05F406_BITS_117_TO_115_7_ETC___05F_d1802))))
                            ? vlTOPp->mkTestBench__DOT__actual_target___05Fh113093
                            : ((IData)(4U) + ((vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[9U] 
                                               << 0x17U) 
                                              | (vlTOPp->mkTestBench__DOT__soc_core_id2ex__DOT__data0_reg[8U] 
                                                 >> 9U))))))
                : ((((IData)(vlTOPp->mkTestBench__DOT__WILL_FIRE_RL_soc_core_fetchStage) 
                     & (~ (IData)(vlTOPp->mkTestBench__DOT__soc_core_branch_flush_done))) 
                    & (~ (IData)(vlTOPp->mkTestBench__DOT__soc_core_no_pc_update)))
                    ? ((IData)(vlTOPp->mkTestBench__DOT__SEL_ARR_soc_core_btb_btbTable_0_055_BIT_0_056___05FETC___05F_d1322)
                        ? vlTOPp->mkTestBench__DOT__prediction_target___05Fh73334
                        : ((IData)(4U) + vlTOPp->mkTestBench__DOT__soc_core_pcReg))
                    : 0xaaaaaaaaU)));
    vlTOPp->mkTestBench__DOT__v___05Fh164045 = (((0x2000000U 
                                                  <= 
                                                  ((vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[2U] 
                                                    << 0x1bU) 
                                                   | (vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U] 
                                                      >> 5U))) 
                                                 & (0x2010000U 
                                                    > 
                                                    ((vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[2U] 
                                                      << 0x1bU) 
                                                     | (vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U] 
                                                        >> 5U))))
                                                 ? 
                                                ((1U 
                                                  == 
                                                  (3U 
                                                   & ((vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U] 
                                                       << 0x1dU) 
                                                      | (vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[0U] 
                                                         >> 3U))))
                                                  ? 
                                                 ((0x2000000U 
                                                   == 
                                                   ((vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[2U] 
                                                     << 0x1bU) 
                                                    | (vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U] 
                                                       >> 5U)))
                                                   ? 
                                                  ((IData)(vlTOPp->mkTestBench__DOT__soc_clint_msip)
                                                    ? 1U
                                                    : 0U)
                                                   : 
                                                  ((0x2004000U 
                                                    == 
                                                    ((vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[2U] 
                                                      << 0x1bU) 
                                                     | (vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U] 
                                                        >> 5U)))
                                                    ? (IData)(vlTOPp->mkTestBench__DOT__soc_clint_mtimecmp)
                                                    : 
                                                   ((0x2004004U 
                                                     == 
                                                     ((vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[2U] 
                                                       << 0x1bU) 
                                                      | (vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U] 
                                                         >> 5U)))
                                                     ? (IData)(
                                                               (vlTOPp->mkTestBench__DOT__soc_clint_mtimecmp 
                                                                >> 0x20U))
                                                     : 
                                                    ((0x200bff8U 
                                                      == 
                                                      ((vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[2U] 
                                                        << 0x1bU) 
                                                       | (vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U] 
                                                          >> 5U)))
                                                      ? (IData)(vlTOPp->mkTestBench__DOT__soc_clint_mtime)
                                                      : 
                                                     ((0x200bffcU 
                                                       == 
                                                       ((vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[2U] 
                                                         << 0x1bU) 
                                                        | (vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U] 
                                                           >> 5U)))
                                                       ? (IData)(
                                                                 (vlTOPp->mkTestBench__DOT__soc_clint_mtime 
                                                                  >> 0x20U))
                                                       : 0U)))))
                                                  : 0U)
                                                 : 
                                                (((0xc000000U 
                                                   <= 
                                                   ((vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[2U] 
                                                     << 0x1bU) 
                                                    | (vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U] 
                                                       >> 5U))) 
                                                  & (0xc100000U 
                                                     > 
                                                     ((vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[2U] 
                                                       << 0x1bU) 
                                                      | (vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U] 
                                                         >> 5U))))
                                                  ? vlTOPp->mkTestBench__DOT__v___05Fh164458
                                                  : 
                                                 (((0x10000000U 
                                                    <= 
                                                    ((vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[2U] 
                                                      << 0x1bU) 
                                                     | (vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U] 
                                                        >> 5U))) 
                                                   & (0x10001000U 
                                                      > 
                                                      ((vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[2U] 
                                                        << 0x1bU) 
                                                       | (vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U] 
                                                          >> 5U))))
                                                   ? 
                                                  ((1U 
                                                    == 
                                                    (3U 
                                                     & ((vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U] 
                                                         << 0x1dU) 
                                                        | (vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[0U] 
                                                           >> 3U))))
                                                    ? 
                                                   ((0U 
                                                     == 
                                                     (0xffU 
                                                      & ((vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[2U] 
                                                          << 0x1bU) 
                                                         | (vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U] 
                                                            >> 5U))))
                                                     ? 
                                                    ((IData)(vlTOPp->mkTestBench__DOT__soc_uart_tx_full)
                                                      ? 1U
                                                      : 0U)
                                                     : 
                                                    ((4U 
                                                      == 
                                                      (0xffU 
                                                       & ((vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[2U] 
                                                           << 0x1bU) 
                                                          | (vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U] 
                                                             >> 5U))))
                                                      ? 
                                                     ((IData)(vlTOPp->mkTestBench__DOT__soc_uart_rx_valid)
                                                       ? (IData)(vlTOPp->mkTestBench__DOT__soc_uart_rxdata)
                                                       : 0U)
                                                      : 
                                                     ((8U 
                                                       == 
                                                       (0xffU 
                                                        & ((vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[2U] 
                                                            << 0x1bU) 
                                                           | (vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U] 
                                                              >> 5U))))
                                                       ? 
                                                      ((IData)(vlTOPp->mkTestBench__DOT__soc_uart_tx_enable)
                                                        ? 1U
                                                        : 0U)
                                                       : 
                                                      ((0xcU 
                                                        == 
                                                        (0xffU 
                                                         & ((vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[2U] 
                                                             << 0x1bU) 
                                                            | (vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U] 
                                                               >> 5U))))
                                                        ? 
                                                       ((IData)(vlTOPp->mkTestBench__DOT__soc_uart_rx_enable)
                                                         ? 1U
                                                         : 0U)
                                                        : 
                                                       ((0x10U 
                                                         == 
                                                         (0xffU 
                                                          & ((vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[2U] 
                                                              << 0x1bU) 
                                                             | (vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U] 
                                                                >> 5U))))
                                                         ? vlTOPp->mkTestBench__DOT__soc_uart_ie
                                                         : 
                                                        ((0x14U 
                                                          == 
                                                          (0xffU 
                                                           & ((vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[2U] 
                                                               << 0x1bU) 
                                                              | (vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U] 
                                                                 >> 5U))))
                                                          ? vlTOPp->mkTestBench__DOT__soc_uart_ip
                                                          : 0U))))))
                                                    : 0U)
                                                   : 
                                                  ((0x80000000U 
                                                    > 
                                                    ((vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[2U] 
                                                      << 0x1bU) 
                                                     | (vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U] 
                                                        >> 5U)))
                                                    ? 0U
                                                    : 
                                                   ((1U 
                                                     == 
                                                     (3U 
                                                      & ((vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U] 
                                                          << 0x1dU) 
                                                         | (vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[0U] 
                                                            >> 3U))))
                                                     ? vlTOPp->mkTestBench__DOT__rdata___05F_1___05Fh166694
                                                     : 0U)))));
    if ((0x40U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])) {
        vlTOPp->mkTestBench__DOT__half_val___05Fh192578 
            = (0xffffU & (vlTOPp->mkTestBench__DOT__v___05Fh164045 
                          >> 0x10U));
        vlTOPp->mkTestBench__DOT__byte_val___05Fh192654 
            = (0xffU & ((0x20U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                         ? (vlTOPp->mkTestBench__DOT__v___05Fh164045 
                            >> 0x18U) : (vlTOPp->mkTestBench__DOT__v___05Fh164045 
                                         >> 0x10U)));
    } else {
        vlTOPp->mkTestBench__DOT__half_val___05Fh192578 
            = (0xffffU & vlTOPp->mkTestBench__DOT__v___05Fh164045);
        vlTOPp->mkTestBench__DOT__byte_val___05Fh192654 
            = (0xffU & ((0x20U & vlTOPp->mkTestBench__DOT__soc_core_current_mem_req[1U])
                         ? (vlTOPp->mkTestBench__DOT__v___05Fh164045 
                            >> 8U) : vlTOPp->mkTestBench__DOT__v___05Fh164045));
    }
}
