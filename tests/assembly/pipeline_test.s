# tests/assembly/pipeline_test.s
# 五级流水线测试程序

.section .text
.global _start

_start:
    # 测试1: 简单算术（前递测试）
    li x1, 10
    li x2, 20
    add x3, x1, x2     # x3 = 30
    add x4, x3, x1     # x4 = 40 (前递)
    add x5, x4, x3     # x5 = 70 (前递)

    # 测试2: Load-Use冒险
    li x6, 0x1000
    sw x5, 0(x6)       # 存储
    lw x7, 0(x6)       # 加载
    add x8, x7, x1     # Load-Use冒险

    # 测试3: 循环（分支预测）
    li x10, 5
loop1:
    addi x10, x10, -1
    bne x10, x0, loop1

    # 测试4: 条件分支
    li x11, 10
    li x12, 20
    blt x11, x12, branch_taken
    li x13, 999
branch_taken:
    li x13, 100

    # 测试5: JAL跳转
    jal x14, jump_target
    li x15, 999
jump_target:
    li x15, 200

    # 测试结束
    li x31, 0xDEAD
end:
    j end