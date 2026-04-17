# tests/assembly/rtype_test.s
# 测试 R-Type 指令: SUB, SLL, SRL, SRA, SLT, AND, OR, XOR

.section .text
.global _start

_start:
    # 基础值设置
    li x1, 10          # x1 = 10
    li x2, 3           # x2 = 3
    li x3, -5          # x3 = -5 (测试有符号操作)

    # SUB 测试
    sub x4, x1, x2     # x4 = 10 - 3 = 7

    # SLL 测试 (逻辑左移)
    sll x5, x1, x2     # x5 = 10 << 3 = 80

    # SRL 测试 (逻辑右移)
    li x6, 128
    srl x7, x6, x2     # x7 = 128 >> 3 = 16

    # SRA 测试 (算术右移，保持符号)
    li x8, 2           # shift amount = 2
    sra x9, x3, x8     # x9 = -5 >> 2 = -2 (算术移位)

    # SLT 测试 (有符号小于)
    slt x10, x3, x1    # x10 = (-5 < 10) ? 1 : 0 = 1
    slt x11, x1, x3    # x11 = (10 < -5) ? 1 : 0 = 0

    # SLTU 测试 (无符号小于)
    sltu x12, x1, x2   # x12 = (10 < 3) ? 1 : 0 = 0

    # AND 测试
    li x13, 15         # 0xF
    li x14, 7          # 0x7
    and x15, x13, x14  # x15 = 15 & 7 = 7

    # OR 测试
    li x16, 8          # 0x8
    li x17, 3          # 0x3
    or x18, x16, x17   # x18 = 8 | 3 = 11

    # XOR 测试
    li x19, 12         # 0xC
    li x20, 6          # 0x6
    xor x21, x19, x20  # x21 = 12 ^ 6 = 10

    # 结束标记
    li x31, 0xDEAD
end:
    j end