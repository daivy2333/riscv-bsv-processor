# tests/assembly/stability_test.s
# 长期稳定性测试 - 无限循环不写入 tohost

.globl _start
.section .text

_start:
    li x1, 0          # 计数器
    li x2, 100000     # 目标计数（如果中断工作会触发）

loop:
    addi x1, x1, 1    # 增加计数
    # 每 1000 次写入 UART（用于观察）
    andi x3, x1, 0x3ff
    bne x3, x0, skip_uart
    li x4, 0x10000000
    li x5, 0x41       # 'A'
    sw x5, 0(x4)

skip_uart:
    jal x0, loop      # 无限循环