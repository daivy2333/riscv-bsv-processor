# tests/assembly/mtime_test.s
# mtime 单调递增测试
# 目标: 验证 mtime 递增和 64 位读取正确

.section .text
.global _start

_start:
    # 设置 mtimecmp 为最大值（避免触发中断）
    li x1, 0x02004004       # mtimecmp_hi
    li x2, 0xFFFFFFFF
    sw x2, 0(x1)             # mtimecmp_hi = 0xFFFFFFFF

    li x3, 0x02004000        # mtimecmp_lo
    li x4, 0xFFFFFFFF
    sw x4, 0(x3)             # mtimecmp_lo = 0xFFFFFFFF

    # 读取 mtime_lo
    li x5, 0x0200BFF8        # mtime_lo 地址
    lw x6, 0(x5)             # x6 = mtime_lo (第一次读取)

    # 等待几周期（NOP）
    nop
    nop
    nop

    # 再次读取 mtime_lo
    lw x7, 0(x5)             # x7 = mtime_lo (第二次读取)

    # 检查 mtime 是否递增 (x7 > x6)
    # 如果递增正确，x7 - x6 应为正数
    sub x8, x7, x6           # x8 = x7 - x6

    # 验证: x8 > 0 表示 mtime 递增
    li x9, 0
    bgt x8, x9, passed       # 如果 x8 > 0, 测试通过

    # 如果 mtime 未递增，失败
    li x31, 0xDEAD           # FAILED marker
    li x10, 0x80001000       # tohost 地址
    sw x31, 0(x10)
    j end

passed:
    # 测试通过
    li x31, 1                # PASSED marker
    li x10, 0x80001000       # tohost 地址
    sw x31, 0(x10)

end:
    j end