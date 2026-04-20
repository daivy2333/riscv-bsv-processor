# tests/assembly/direct_tohost.s
# 最简单测试：直接写入 tohost = 1
.text
.globl _start

_start:
    # 禁用中断
    csrwi mie, 0

    # 直接写入 tohost = 1
    li t0, 1
    li t1, 0x80001000
    sw t0, 0(t1)

    # 无限循环
halt:
    j halt