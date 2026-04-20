// tests/c/test_bench.cpp - FreeRTOS测试（更长周期）
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

    uint64_t max_cycles = 5000000;  // 500万周期
    uint64_t cycle = 0;
    bool done = false;
    uint64_t print_interval = 100000;

    while (cycle < max_cycles && !done) {
        top->CLK = 1; top->eval();
        top->CLK = 0; top->eval();
        cycle++;

        if (cycle % print_interval == 0) {
            std::cout << "Cycle " << cycle << " running..." << std::endl;
        }

        if (top->done) {
            std::cout << "\nTest completed at cycle " << cycle << std::endl;
            done = true;
        }
    }

    if (!done) {
        std::cout << "\nTimeout at cycle " << max_cycles << std::endl;
    }

    delete top;
    return done ? 0 : 1;
}