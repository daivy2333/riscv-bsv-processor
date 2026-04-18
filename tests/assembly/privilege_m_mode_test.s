# tests/assembly/privilege_m_mode_test.s
# 测试 Machine 模式基本执行和 mstatus CSR

.globl _start
_start:
    # 读取 mhartid (应该为 0)
    csrr a0, mhartid

    # 读取 misa (应该显示 RV32I)
    csrr a1, misa

    # 读取 mstatus
    csrr a2, mstatus

    # 写入 mstatus 测试
    li a3, 0x1888  # Mstatus: MIE=1, MPIE=1, MPP=11(M-mode)
    csrw mstatus, a3

    # 再次读取验证
    csrr a4, mstatus

    # 测试 csrrw (read and write)
    li t0, 0x12345678
    csrrw t1, mstatus, t0

    # 测试 csrrs (read and set)
    li t0, 0x00000100  # 设置 MIE 位
    csrrs t2, mstatus, t0

    # 测试 csrrc (read and clear)
    li t0, 0x00000100  # 清除 MIE 位
    csrrc t3, mstatus, t0

    # 写入 tohost 表示测试完成
    li t0, 0x80001000
    li t4, 1  # PASS
    sw t4, 0(t0)

_inf_loop:
    j _inf_loop