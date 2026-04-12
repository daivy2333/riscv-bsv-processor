// tests/c/test_bench.cpp
// Verilator仿真测试驱动

#include "VmkTestBench.h"
#include "verilated.h"
#include <iostream>
#include <cstdint>

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);

    // 创建仿真实例
    VmkTestBench* top = new VmkTestBench;

    std::cout << "\n========================================" << std::endl;
    std::cout << "  RISC-V 五级流水线处理器仿真" << std::endl;
    std::cout << "========================================\n" << std::endl;

    // 初始化时钟和复位
    top->CLK = 0;
    top->RST_N = 0;

    std::cout << "Phase 1: Reset..." << std::endl;

    // 复位周期
    for (int i = 0; i < 10; i++) {
        top->CLK = !top->CLK;
        top->eval();
    }

    // 释放复位
    top->RST_N = 1;
    std::cout << "Phase 2: Running simulation...\n" << std::endl;

    // 仿真主循环
    uint64_t max_cycles = 500;
    uint64_t cycle = 0;
    bool done = false;

    while (cycle < max_cycles && !done) {
        // 时钟上升沿
        top->CLK = 1;
        top->eval();

        // 时钟下降沿
        top->CLK = 0;
        top->eval();

        cycle++;

        // 检查结束条件
        if (top->done) {
            std::cout << "\nTestBench signaled done at cycle " << cycle << std::endl;
            done = true;
        }
    }

    std::cout << "\n========================================" << std::endl;
    std::cout << "  Simulation Completed" << std::endl;
    std::cout << "========================================\n" << std::endl;

    std::cout << "Final state:" << std::endl;
    std::cout << "  Total cycles: " << cycle << std::endl;
    std::cout << "  Done signal: " << (done ? "asserted" : "not asserted") << std::endl;

    delete top;
    return 0;
}
