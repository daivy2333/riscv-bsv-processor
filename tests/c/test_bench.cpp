// tests/c/test_bench.cpp
#include "VmkTestBench.h"
#include "verilated.h"
#include <iostream>
#include <iomanip>

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);
    VmkTestBench* top = new VmkTestBench;
    
    std::cout << "=== Starting RISC-V Processor Simulation ===" << std::endl;
    
    // 初始状态
    top->CLK = 0;
    top->RST_N = 0;  // 激活复位
    
    std::cout << "Applying reset..." << std::endl;
    // 应用复位
    for (int i = 0; i < 5; i++) {
        top->CLK = !top->CLK;
        top->eval();
    }
    
    // 释放复位
    top->RST_N = 1;
    std::cout << "Reset released. Starting simulation..." << std::endl;
    
    // 运行仿真
    for (int cycle = 0; cycle < 200; cycle++) {
        // 时钟上升沿
        top->CLK = 1;
        top->eval();
        
        // 时钟下降沿
        top->CLK = 0;
        top->eval();
        
        // 每10个周期输出一次状态
        if (cycle % 10 == 0) {
            std::cout << "Cycle " << cycle << ": CLK=" << (int)top->CLK 
                      << ", RST_N=" << (int)top->RST_N 
                      << ", done=" << (int)top->done << std::endl;
        }
        
        // 检查仿真是否完成
        if (top->done) {
            std::cout << "TestBench reported simulation done at cycle " << cycle << std::endl;
            break;
        }
        
        if (cycle == 199) {
            std::cout << "Reached maximum cycle count (200)" << std::endl;
        }
    }
    
    delete top;
    std::cout << "=== Simulation Completed ===" << std::endl;
    return 0;
}