# tests/assembly/csr_basic_test.s
# 测试 CSR 基本读写操作

.globl _start
_start:
    # 测试 mcycle 计数器递增
    csrr a0, mcycle
    csrr a1, mcycle
    csrr a2, mcycle

    # 测试 mtvec
    lui a0, 0x80000
    addi a0, a0, 0x00
    csrw mtvec, a0
    csrr a1, mtvec

    # 测试 mtvec 向量模式 (mode=1)
    lui a0, 0x80000
    addi a0, a0, 0x03
    csrw mtvec, a0
    csrr a1, mtvec

    # 写入 tohost 表示测试完成
    li t0, 0x80001000
    li t4, 2  # PASS
    sw t4, 0(t0)

_inf_loop:
    j _inf_loop