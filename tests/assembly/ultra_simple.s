# tests/assembly/ultra_simple.s
# 最简单测试：无 CSR 指令，直接写入 tohost
.text
.globl _start

_start:
    # 不使用 CSR 指令
    # li t0, 1
    addi t0, x0, 1
    # li t1, 0x80001000
    lui t1, 0x80001
    # sw t0, 0(t1)  -> t1 已经是 0x80001000
    sw t0, 0(t1)

halt:
    j halt