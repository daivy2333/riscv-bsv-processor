# tests/assembly/debug_slti.s
# SLTI 最简单诊断测试

.globl _start
.section .text

.equ tohost, 0x80001000

_start:
    # SLTI 测试: -1 < 0 应返回 1
    li   t0, -1
    slti t1, t0, 0       # t1 = 1

    # 直接写入 tohost，t1 的值作为结果
    li   t5, tohost
    sw   t1, 0(t5)       # tohost = 1 表示成功

end:
    jal  zero, end