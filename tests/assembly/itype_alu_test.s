# tests/assembly/itype_alu_test.s
# 测试 SLTI with t0=0

.globl _start
.section .text

.equ tohost, 0x80001000

_start:
    # SLTI 测试 1: -1 < 0
    li   t0, -1
    slti t1, t0, 0       # t1 = 1
    li   t2, 1
    bne  t1, t2, fail

    # SLTI 测试 2: -1 < 1
    slti t1, t0, 1       # t1 = 1
    bne  t1, t2, fail

    # SLTI 测试 3: 修改 t0 后测试
    li   t0, 0           # t0 = 0
    slti t1, t0, 1       # t1 = 1（0 < 1）
    bne  t1, t2, fail

    # 通过
    li   t0, 1
    li   t5, tohost
    sw   t0, 0(t5)

pass:
    jal  zero, pass

fail:
    li   t0, 0xFF
    li   t5, tohost
    sw   t0, 0(t5)
    jal  zero, fail