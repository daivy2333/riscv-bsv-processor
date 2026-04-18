# tests/assembly/simple_pass.s
# 简单通过测试（写入 tohost）

.globl _start
.section .text

.equ tohost, 0x80001000

_start:
    # R-Type 指令测试
    li   t0, 10
    li   t1, 3
    sub  t2, t0, t1    # t2 = 7

    sll  t3, t0, t1    # t3 = 80 (10 << 3)

    li   t4, 128
    srl  t5, t4, t1    # t5 = 16 (128 >> 3)

    # 通过写入 tohost
    li   t0, 1
    li   t5, tohost
    sw   t0, 0(t5)

end:
    jal  zero, end