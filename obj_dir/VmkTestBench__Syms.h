// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef _VMKTESTBENCH__SYMS_H_
#define _VMKTESTBENCH__SYMS_H_  // guard

#include "verilated_heavy.h"

// INCLUDE MODULE CLASSES
#include "VmkTestBench.h"

// SYMS CLASS
class VmkTestBench__Syms : public VerilatedSyms {
  public:
    
    // LOCAL STATE
    const char* __Vm_namep;
    bool __Vm_didInit;
    
    // SUBCELL STATE
    VmkTestBench*                  TOPp;
    
    // SCOPE NAMES
    VerilatedScope __Vscope_mkTestBench__core_ex2mem;
    VerilatedScope __Vscope_mkTestBench__core_ex2mem__error_checks;
    VerilatedScope __Vscope_mkTestBench__core_id2ex;
    VerilatedScope __Vscope_mkTestBench__core_id2ex__error_checks;
    VerilatedScope __Vscope_mkTestBench__core_if2id;
    VerilatedScope __Vscope_mkTestBench__core_if2id__error_checks;
    VerilatedScope __Vscope_mkTestBench__core_mem2wb;
    VerilatedScope __Vscope_mkTestBench__core_mem2wb__error_checks;
    
    // CREATORS
    VmkTestBench__Syms(VmkTestBench* topp, const char* namep);
    ~VmkTestBench__Syms() {}
    
    // METHODS
    inline const char* name() { return __Vm_namep; }
    
} VL_ATTR_ALIGNED(VL_CACHE_LINE_BYTES);

#endif  // guard
