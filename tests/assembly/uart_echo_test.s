# UART Echo Test - 最简单的回显程序
# 程序流程：
# 1. 初始化 UART（启用 RX）
# 2. 循环读取 UART RXDATA
# 3. 收到字符后写入 UART TXDATA 回显

.section .text
.globl _start

_start:
    # 设置 UART 基址
    li t0, 0x10000000

    # 设置 UART RXCTRL = 1 (启用 RX)
    li t1, 1
    sw t1, 12(t0)        # UART_RXCTRL = 1

    # 设置 UART IE = 2 (启用 RX 中断)
    li t1, 2
    sw t1, 16(t0)        # UART_IE = 2 (bit 1 = RXWM)

echo_loop:
    # 读取 UART IP (检查 RX 挂起)
    lw t3, 20(t0)        # 读取 UART_IP
    andi t3, t3, 2       # 检查 bit 1 (RXWM)
    beqz t3, echo_loop   # 如果无 RX 数据，继续等待

    # 读取 UART RXDATA (offset 4)
    lw t2, 4(t0)         # 读取 RXDATA

    # 收到字符，回显到 TXDATA
    andi t2, t2, 0xFF    # 只取低 8 位
    sw t2, 0(t0)         # 写入 TXDATA (回显)

    # 清除 RX 中断挂起 (写 1 清除)
    li t3, 2
    sw t3, 20(t0)        # UART_IP = RXWM 清除

    # 继续循环
    j echo_loop