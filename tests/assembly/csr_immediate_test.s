# tests/assembly/csr_immediate_test.s
# 测试 CSRRWI, CSRRSI, CSRRCI

.globl _start
_start:
    # 测试 CSRRWI (write immediate)
    csrrwi a0, mstatus, 0x10

    csrrwi a1, mstatus, 0

    # 测试 CSRRSI (set immediate)
    csrrsi a2, mstatus, 0x08

    # 测试 CSRRCI (clear immediate)
    csrrci a3, mstatus, 0x18

    # 验证结果
    csrr a4, mstatus

    # 写入 tohost
    li t0, 0x80001000
    li t4, 1
    sw t4, 0(t0)

_inf_loop:
    j _inf_loop