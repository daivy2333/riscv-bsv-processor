#include "VmkFreeRTOSBench.h"
#include "verilated.h"
#include <iostream>
#include <cstdint>

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);
    VmkFreeRTOSBench* top = new VmkFreeRTOSBench;
    top->CLK = 0;
    top->RST_N = 0;

    // 复位
    for (int i = 0; i < 10; i++) { top->CLK = !top->CLK; top->eval(); }
    top->RST_N = 1;
    top->eval();

    std::cout << "\n=== UART Echo Auto Test ===" << std::endl;
    std::cout << "Testing UART RX -> TX echo..." << std::endl;

    uint64_t max_cycles = 20000;  // 20K 周期
    uint64_t cycle = 0;

    // 自动发送测试字符
    char test_char = 'H';  // 发送 'H'
    uint64_t send_cycle = 5000;  // 在 5K 周期时发送
    bool test_sent = false;

    while (cycle < max_cycles) {
        // 在指定周期发送测试字符
        if (!test_sent && cycle == send_cycle) {
            std::cout << "[test] Sending '" << test_char << "' to UART RX..." << std::endl;
            top->uartRXInput_data = (uint8_t)test_char;
            top->EN_uartRXInput = 1;
            test_sent = true;
        } else {
            top->EN_uartRXInput = 0;
        }

        top->CLK = 1; top->eval();
        top->CLK = 0; top->eval();
        cycle++;

        if (cycle % 10000000 == 0) {
            std::cout << "[Cycle " << cycle << "]" << std::endl;
        }
    }

    std::cout << "\n=== Test Complete ===" << std::endl;
    std::cout << "If you saw [UART_RX] and character output above, RX works!" << std::endl;
    delete top;
    return 0;
}