# tests/assembly/trap_mret_test.s
# trap + mret 返回测试
# 目标: 验证 trap 入口和 mret 返回正确设置 mepc/mcause/mstatus

.section .text
.global _start
.global trap_handler

_start:
    # 设置 mtvec（Direct mode）
    la x1, trap_handler      # 加载 trap handler 地址
    csrw mtvec, x1           # mtvec = trap_handler (Direct mode)

    # 触发 ECALL 异常
    ecall

after_ecall:
    # ECALL 后，mret 应返回到这里
    # x10 应保存了测试状态（由 trap_handler 设置）

    # 检查 x10 状态
    li x11, 1
    beq x10, x11, passed     # 如果 x10 == 1，测试通过

    # trap handler 未正确设置状态
    li x31, 0xDEAD           # FAILED marker
    li x12, 0x80001000       # tohost 地址
    sw x31, 0(x12)
    j end

# Trap handler
trap_handler:
    # 检查 mcause (异常号应为 11 - ECALL)
    csrr x5, mcause
    andi x5, x5, 0x1F        # 取低 5 位（异常号）
    li x6, 11                # ECALL 异常号
    bne x5, x6, trap_failed  # 如果 mcause != 11，失败

    # 检查 mepc（应指向 ecall 后的指令）
    la x6, after_ecall       # 预期 mepc 值
    csrr x5, mepc
    bne x5, x6, trap_failed  # 如果 mepc != after_ecall，失败

    # 检查 mstatus.MIE（应为 0，中断被禁用）
    csrr x5, mstatus
    andi x5, x5, 0x8         # 取 MIE 位 (bit 3)
    bne x5, x0, trap_failed  # 如果 MIE != 0，失败

    # 设置返回状态为 PASSED
    li x10, 1                # PASSED marker

    # 返回
    mret

trap_failed:
    # trap 处理失败
    li x10, 0                # FAILED marker
    mret                      # 尝试返回

passed:
    # 测试通过
    li x31, 1                # PASSED marker
    li x12, 0x80001000       # tohost 地址
    sw x31, 0(x12)

end:
    j end