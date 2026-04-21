#include "VmkFreeRTOSBench.h"
#include "verilated.h"
#include <iostream>
#include <cstdint>
#include <thread>
#include <atomic>
#include <unistd.h>
#include <fcntl.h>
#include <poll.h>
#include <termios.h>

std::atomic<bool> sim_running(true);
std::atomic<uint8_t> rx_char(0);
std::atomic<bool> rx_valid(false);

// 设置终端为非阻塞模式
void set_terminal_nonblock() {
    struct termios tty;
    tcgetattr(STDIN_FILENO, &tty);
    tty.c_lflag &= ~(ICANON | ECHO);  // 禁用行缓冲和回显
    tty.c_cc[VMIN] = 0;
    tty.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSANOW, &tty);
    fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);
}

void restore_terminal() {
    struct termios tty;
    tcgetattr(STDIN_FILENO, &tty);
    tty.c_lflag |= (ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &tty);
}

// stdin 输入线程
void stdin_thread() {
    while (sim_running) {
        char c;
        if (read(STDIN_FILENO, &c, 1) == 1) {
            rx_char = (uint8_t)c;
            rx_valid = true;
        }
        usleep(1000);  // 1ms sleep
    }
}

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);
    VmkFreeRTOSBench* top = new VmkFreeRTOSBench;
    top->CLK = 0;
    top->RST_N = 0;

    // 设置终端非阻塞
    set_terminal_nonblock();

    // 启动 stdin 线程
    std::thread input_thread(stdin_thread);

    // 复位
    for (int i = 0; i < 10; i++) { top->CLK = !top->CLK; top->eval(); }
    top->RST_N = 1;
    top->eval();

    std::cout << "\n=== UART Echo Test ===" << std::endl;
    std::cout << "Type characters (echoed by CPU)..." << std::endl;
    std::cout << "Press Ctrl+C to exit\n" << std::endl;

    uint64_t max_cycles = 100000000;  // 100M 周期
    uint64_t cycle = 0;

    while (cycle < max_cycles) {
        // 检查是否有输入字符
        if (rx_valid) {
            top->uartRXInput_data = rx_char.load();
            top->EN_uartRXInput = 1;
            rx_valid = false;
        } else {
            top->EN_uartRXInput = 0;
        }

        top->CLK = 1; top->eval();
        top->CLK = 0; top->eval();
        cycle++;
    }

    sim_running = false;
    input_thread.join();
    restore_terminal();

    std::cout << "\nFreeRTOS ran for " << cycle << " cycles" << std::endl;
    delete top;
    return 0;
}