# tests/assembly/mtime_increment_verify.s
# mtime 严格递增验证测试
# 目标: 验证 mtime 在每个周期递增 1

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

    # 读取 mtime_lo 第一次
    li x5, 0x0200BFF8        # mtime_lo 地址
    lw x6, 0(x5)             # x6 = mtime_lo (第一次)

    # 等待 10 周期（NOP 序列）
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

    # 再次读取 mtime_lo
    lw x7, 0(x5)             # x7 = mtime_lo (第二次)

    # 检查差值: x7 - x6 应 >= 10（每周期递增 1）
    sub x8, x7, x6           # x8 = delta

    # 验证: x8 >= 10 表示 mtime 正确递增
    li x9, 10
    bge x8, x9, passed       # 如果 x8 >= 10, 测试通过

    # 如果 mtime 递增不够，输出差值作为失败码
    li x31, 0xDEAD           # FAILED marker（加上差值）
    add x31, x31, x8         # x31 = 0xDEAD + delta（用于调试）
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