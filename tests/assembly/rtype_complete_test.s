# tests/assembly/rtype_complete_test.s
# 完整 R-Type 测试（带 tohost）

.globl _start
.section .text

.equ tohost, 0x80001000

_start:
    # 基本算术测试
    li   t0, 10
    li   t1, 3
    sub  t2, t0, t1    # t2 = 7

    # 移位测试
    sll  t3, t0, t1    # t3 = 80
    li   t4, 128
    srl  t5, t4, t1    # t5 = 16

    # 比较测试
    li   t6, -5
    slt  s0, t6, t0    # s0 = 1 (负数 < 正数)

    # 逻辑测试
    li   s1, 15
    li   s2, 7
    and  s3, s1, s2    # s3 = 7
    or   s4, s1, s2    # s4 = 15
    xor  s5, s1, s2    # s5 = 8

    # 验证结果
    li   t0, 7
    bne  t2, t0, fail

    li   t0, 80
    bne  t3, t0, fail

    li   t0, 16
    bne  t5, t0, fail

    li   t0, 1
    bne  s0, t0, fail

    li   t0, 7
    bne  s3, t0, fail

    li   t0, 15
    bne  s4, t0, fail

    li   t0, 8
    bne  s5, t0, fail

    # 通过
    li   t0, 1
    li   t5, tohost
    sw   t0, 0(t5)

end:
    jal  zero, end

fail:
    li   t0, 0
    li   t5, tohost
    sw   t0, 0(t5)
    jal  zero, end