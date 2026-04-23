// tests/c/mini_os_bench.cpp - Mini-OS 测试
#include "VmkMiniOSBench.h"
#include "verilated.h"
#include <iostream>
#include <cstdint>
#include <thread>
#include <atomic>

// UART TX 检测
std::atomic<bool> running{true};

void uart_monitor(VmkMiniOSBench* top) {
    while (running) {
        // 简单输出监控，不处理 stdin
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);
    VmkMiniOSBench* top = new VmkMiniOSBench;
    top->CLK = 0;
    top->RST_N = 0;

    // Reset
    for (int i = 0; i < 10; i++) { top->CLK = !top->CLK; top->eval(); }
    top->RST_N = 1;
    top->eval();

    uint64_t max_cycles = 500000;
    uint64_t cycle = 0;
    bool done = false;

    // 启动 UART 监控线程
    std::thread monitor(uart_monitor, top);

    while (cycle < max_cycles && !done) {
        top->CLK = 1; top->eval();
        top->CLK = 0; top->eval();
        cycle++;

        if (top->done) {
            std::cout << "\nMini-OS completed at cycle " << cycle << std::endl;
            done = true;
        }
    }

    running = false;
    monitor.join();

    if (!done) {
        std::cout << "\nTimeout at cycle " << max_cycles << std::endl;
    }

    delete top;
    return done ? 0 : 1;
}