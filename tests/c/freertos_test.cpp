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

    while (cycle < max_cycles) {
        top->CLK = 1; top->eval();
        top->CLK = 0; top->eval();
        cycle++;

        if (cycle % 100000 == 0) {
            std::cout << "Cycle " << cycle << std::endl;
        }
    }

    std::cout << "\nFreeRTOS ran for " << cycle << " cycles" << std::endl;
    delete top;
    return 0;
}
