// tests/c/test_bench.cpp
// Verilator 仿真测试驱动（简化版）

#include "VmkTestBench.h"
#include "verilated.h"
#include <iostream>
#include <cstdint>

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);

    VmkTestBench* top = new VmkTestBench;

    std::cout << "\n========================================" << std::endl;
    std::cout << "  RISC-V 五级流水线处理器仿真" << std::endl;
    std::cout << "========================================\n" << std::endl;

    top->CLK = 0;
    top->RST_N = 0;

    // Reset
    for (int i = 0; i < 10; i++) {
        top->CLK = !top->CLK;
        top->eval();
    }
    top->RST_N = 1;

    std::cout << "Running simulation...\n" << std::endl;

    uint64_t max_cycles = 100000;
    uint64_t cycle = 0;
    bool done = false;

    while (cycle < max_cycles && !done) {
        top->CLK = 1;
        top->eval();
        top->CLK = 0;
        top->eval();
        cycle++;

        // 检查模块完成信号
        if (top->mkTestBench__DOT__dumpDone) {
            std::cout << "\nTestBench done at cycle " << cycle << std::endl;
            done = true;
        }
    }

    std::cout << "\n========================================" << std::endl;
    std::cout << "  Simulation Completed" << std::endl;
    std::cout << "========================================\n" << std::endl;
    std::cout << "Total cycles: " << cycle << std::endl;
    std::cout << "Status: " << (done ? "DONE" : "TIMEOUT") << std::endl;

    delete top;
    return done ? 0 : 1;
}
