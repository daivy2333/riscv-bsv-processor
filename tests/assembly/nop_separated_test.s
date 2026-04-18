# tests/assembly/nop_separated_test.s
# 使用 nop 分隔的前递测试

.globl _start
.section .text

.equ tohost, 0x80001000

_start:
    # 基本算术测试（带 nop 分隔）
    li   t0, 10
    nop           # 确保 t0 在 WB 阶段后 wb_forward_data 可用
    li   t1, 3
    nop           # 确保 t1 在 WB 阶段后 wb_forward_data 可用
    sub  t2, t0, t1    # t2 = 7

    # 移位测试
    sll  t3, t0, t1    # t3 = 80 (10 << 3)
    nop
    li   t4, 128
    nop
    srl  t5, t4, t1    # t5 = 16 (128 >> 3)

    # 通过写入 tohost
    li   t0, 1
    li   t5, tohost
    sw   t0, 0(t5)

end:
    jal  zero, end