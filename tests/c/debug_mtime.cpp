// tests/c/debug_mtime.cpp - mtime 调试测试
#include "VmkTestBench.h"
#include "verilated.h"
#include <iostream>
#include <cstdint>

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);
    VmkTestBench* top = new VmkTestBench;
    top->CLK = 0;
    top->RST_N = 0;

    for (int i = 0; i < 10; i++) { top->CLK = !top->CLK; top->eval(); }
    top->RST_N = 1;
    top->eval();

    uint64_t max_cycles = 200;
    uint64_t cycle = 0;

    while (cycle < max_cycles) {
        top->CLK = 1; top->eval();
        top->CLK = 0; top->eval();
        cycle++;

        // 检查 handle_mem_req 规则是否执行
        if (top->mkTestBench__DOT__WILL_FIRE_RL_soc_handle_mem_req) {
            std::cout << "Cycle " << cycle << " handle_mem_req fired" << std::endl;
        }

        // 每周期输出 mtime 值
        if (cycle % 10 == 0) {
            std::cout << "Cycle " << cycle
                      << " soc_clint_mtime=" << top->mkTestBench__DOT__soc_clint_mtime
                      << std::endl;
        }
    }

    delete top;
    return 0;
}