# tests/assembly/mtimecmp_mtip_test.s
# mtimecmp MTIP 触发测试
# 目标: 验证 mtime >= mtimecmp 时 MTIP 触发

.section .text
.global _start

_start:
    # 先设置 mtime 为 0（可选，确保从已知状态开始）
    li x1, 0x0200BFFC        # mtime_hi 地址
    li x2, 0
    sw x2, 0(x1)             # mtime_hi = 0

    li x3, 0x0200BFF8        # mtime_lo 地址
    li x4, 0
    sw x4, 0(x3)             # mtime_lo = 0

    # 设置 mtimecmp = 50（需要先设置高位为 0）
    li x5, 0x02004004        # mtimecmp_hi 地址
    li x6, 0
    sw x6, 0(x5)             # mtimecmp_hi = 0

    li x7, 0x02004000        # mtimecmp_lo 地址
    li x8, 50
    sw x8, 0(x7)             # mtimecmp_lo = 50

    # 等待 mtime 超过 50（约 60 周期）
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop

    # 读取 mip CSR 检查 MTIP (bit 7)
    csrr x9, mip             # x9 = mip
    andi x10, x9, 0x80       # x10 = mip[7] (MTIP)

    # 如果 MTIP=1，测试通过
    bne x10, x0, passed      # 如果 MTIP != 0，跳转 passed

    # MTIP 未触发，失败
    li x31, 0xDEAD           # FAILED marker
    li x11, 0x80001000       # tohost 地址
    sw x31, 0(x11)
    j end

passed:
    # 测试通过
    li x31, 1                # PASSED marker
    li x11, 0x80001000       # tohost 地址
    sw x31, 0(x11)

end:
    j end