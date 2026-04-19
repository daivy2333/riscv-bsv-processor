# tests/assembly/uart_putchar_test.s
# UART TX putchar 测试
# 目标: 写入 0x10000000 后立即打印字符

.section .text
.global _start

_start:
    # 测试 UART TX - 写入 'A' (0x41)
    li x1, 0x10000000     # UART TXDATA 地址
    li x2, 0x41           # 'A' 字符
    sw x2, 0(x1)          # 写入 UART

    # 写入 'B' (0x42)
    li x3, 0x42           # 'B' 字符
    sw x3, 0(x1)          # 写入 UART

    # 写入换行符 (0x0A)
    li x4, 0x0A           # '\n'
    sw x4, 0(x1)

    # 写入 'T' (0x54) 和 'E' (0x45) 和 'S' (0x53) 和 'T' (0x54)
    li x5, 0x54           # 'T'
    sw x5, 0(x1)
    li x6, 0x45           # 'E'
    sw x6, 0(x1)
    li x7, 0x53           # 'S'
    sw x7, 0(x1)
    li x8, 0x54           # 'T'
    sw x8, 0(x1)
    li x9, 0x0A           # '\n'
    sw x9, 0(x1)

    # 结束标记: tohost = 1 (PASSED)
    li x31, 1
    li x10, 0x80001000    # tohost 地址
    sw x31, 0(x10)

end:
    j end