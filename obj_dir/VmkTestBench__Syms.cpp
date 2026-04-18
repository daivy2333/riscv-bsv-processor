// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table implementation internals

#include "VmkTestBench__Syms.h"
#include "VmkTestBench.h"



// FUNCTIONS
VmkTestBench__Syms::VmkTestBench__Syms(VmkTestBench* topp, const char* namep)
    // Setup locals
    : __Vm_namep(namep)
    , __Vm_didInit(false)
    // Setup submodule names
{
    // Pointer to top level
    TOPp = topp;
    // Setup each module's pointers to their submodules
    // Setup each module's pointer back to symbol table (for public functions)
    TOPp->__Vconfigure(this, true);
    // Setup scopes
    __Vscope_mkTestBench__soc_core_ex2mem.configure(this, name(), "mkTestBench.soc_core_ex2mem", "soc_core_ex2mem", -12, VerilatedScope::SCOPE_OTHER);
    __Vscope_mkTestBench__soc_core_ex2mem__error_checks.configure(this, name(), "mkTestBench.soc_core_ex2mem.error_checks", "error_checks", -12, VerilatedScope::SCOPE_OTHER);
    __Vscope_mkTestBench__soc_core_id2ex.configure(this, name(), "mkTestBench.soc_core_id2ex", "soc_core_id2ex", -12, VerilatedScope::SCOPE_OTHER);
    __Vscope_mkTestBench__soc_core_id2ex__error_checks.configure(this, name(), "mkTestBench.soc_core_id2ex.error_checks", "error_checks", -12, VerilatedScope::SCOPE_OTHER);
    __Vscope_mkTestBench__soc_core_if2id.configure(this, name(), "mkTestBench.soc_core_if2id", "soc_core_if2id", -12, VerilatedScope::SCOPE_OTHER);
    __Vscope_mkTestBench__soc_core_if2id__error_checks.configure(this, name(), "mkTestBench.soc_core_if2id.error_checks", "error_checks", -12, VerilatedScope::SCOPE_OTHER);
    __Vscope_mkTestBench__soc_core_mem2wb.configure(this, name(), "mkTestBench.soc_core_mem2wb", "soc_core_mem2wb", -12, VerilatedScope::SCOPE_OTHER);
    __Vscope_mkTestBench__soc_core_mem2wb__error_checks.configure(this, name(), "mkTestBench.soc_core_mem2wb.error_checks", "error_checks", -12, VerilatedScope::SCOPE_OTHER);
}
