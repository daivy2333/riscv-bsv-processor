// tests/c/test_bench.cpp
// Verilator 仿真测试驱动 - 检查 redirect 状态

#include "VmkTestBench.h"
#include "verilated.h"
#include <iostream>
#include <cstdint>

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);

    VmkTestBench* top = new VmkTestBench;

    top->CLK = 0;
    top->RST_N = 0;

    // Reset
    for (int i = 0; i < 10; i++) {
        top->CLK = !top->CLK;
        top->eval();
    }
    top->RST_N = 1;
    top->eval();

    uint64_t max_cycles = 200;  // 正常测试周期限制
    uint64_t cycle = 0;
    bool done = false;

    while (cycle < max_cycles && !done) {
        top->CLK = 1;
        top->eval();
        top->CLK = 0;
        top->eval();
        cycle++;

        uint32_t pc = top->mkTestBench__DOT__soc_core_pcReg;
        uint32_t x7 = top->mkTestBench__DOT__soc_core_regFile_registers_7;
        uint32_t waiting = top->mkTestBench__DOT__soc_core_waiting_for_load_resp;
        uint32_t redirect = top->mkTestBench__DOT__soc_core_redirect_pending;
        uint32_t redirect_target = top->mkTestBench__DOT__soc_core_redirect_target;
        uint32_t stall = top->mkTestBench__DOT__soc_core_stall_load_use;

        // 只打印 C17-C30 的详细信息
        if (cycle >= 17 && cycle <= 30) {
            std::cout << "C" << std::dec << cycle << ": "
                      << "PC=" << std::hex << pc
                      << " wait=" << waiting
                      << " stall=" << stall
                      << " redirect=" << redirect
                      << " target=" << redirect_target
                      << " x7=" << x7
                      << std::dec << std::endl;
        }

        if (top->done) done = true;
    }

    delete top;
    return done ? 0 : 1;
}