# tests/assembly/itype_alu_test.s
# I-Type ALU 指令验证测试 (9 条指令)

.globl _start
.section .text

.equ tohost, 0x80001000

_start:
    # ========== ADDI 测试 ==========
    # 基本加法
    li   t0, 100
    addi t1, t0, -50      # t1 = 50
    li   t2, 50
    bne  t1, t2, fail

    # 立即数边界
    li   t0, 0
    addi t1, t0, 0        # t1 = 0（零值）
    bnez t1, fail

    addi t1, t0, 2047     # t1 = 2047（最大正立即数）
    li   t2, 2047
    bne  t1, t2, fail

    addi t1, t0, -2048    # t1 = -2048（最小负立即数）
    li   t2, -2048
    bne  t1, t2, fail

    # 溢出测试
    li   t0, 0x7FFFFFFF
    addi t1, t0, 1        # t1 = 0x80000000
    li   t2, 0x80000000
    bne  t1, t2, fail

    # ========== SLTI/SLTIU 测试 ==========
    # 有符号比较
    li   t0, -1           # 0xFFFFFFFF
    slti t1, t0, 0        # t1 = 1（-1 < 0）
    li   t2, 1
    bne  t1, t2, fail

    slti t1, t0, 1        # t1 = 1（-1 < 1）
    bne  t1, t2, fail

    li   t0, 0
    slti t1, t0, 1        # t1 = 1（0 < 1）
    bne  t1, t2, fail

    slti t1, t0, 0        # t1 = 0（0 < 0 为假）
    bnez t1, fail

    slti t1, t0, -1       # t1 = 0（0 < -1 为假）
    bnez t1, fail

    # 无符号比较
    li   t0, -1           # 0xFFFFFFFF = MAX_UINT
    sltiu t1, t0, 0       # t1 = 0（MAX_UINT < 0 为假）
    bnez t1, fail

    sltiu t1, t0, 1       # t1 = 0（MAX_UINT < 1 为假）
    bnez t1, fail

    li   t0, 0
    sltiu t1, t0, 1       # t1 = 1（0 < 1）
    li   t2, 1
    bne  t1, t2, fail

    sltiu t1, t0, 0       # t1 = 0（0 < 0 为假）
    bnez t1, fail

    # 有符号 vs 无符号差异
    li   t0, 1
    slti t1, t0, -2       # t1 = 1（1 < -2，有符号）
    bne  t1, t2, fail

    sltiu t1, t0, -2      # t1 = 0（1 < MAX_UINT-1，无符号）
    bnez t1, fail

    # ========== 移位指令测试 ==========
    # SLLI 边界
    li   t0, 1
    slli t1, t0, 0        # t1 = 1（不移位）
    bne  t1, t0, fail

    slli t1, t0, 4        # t1 = 16
    li   t2, 16
    bne  t1, t2, fail

    slli t1, t0, 31       # t1 = 0x80000000
    li   t2, 0x80000000
    bne  t1, t2, fail

    # SRLI 边界
    li   t0, 0xFFFFFFFF
    srli t1, t0, 0        # t1 = 0xFFFFFFFF（不移位）
    bne  t1, t0, fail

    srli t1, t0, 4        # t1 = 0x0FFFFFFF
    li   t2, 0x0FFFFFFF
    bne  t1, t2, fail

    srli t1, t0, 31       # t1 = 1
    li   t2, 1
    bne  t1, t2, fail

    # SRAI 正数测试（符号位为 0）
    li   t0, 0x7FFFFFFF
    srai t1, t0, 0        # t1 = 0x7FFFFFFF（不移位）
    bne  t1, t0, fail

    srai t1, t0, 4        # t1 = 0x07FFFFFF（0 填充）
    li   t2, 0x07FFFFFF
    bne  t1, t2, fail

    # SRAI 负数测试（符号位为 1）
    li   t0, 0x80000000
    srai t1, t0, 0        # t1 = 0x80000000（不移位）
    bne  t1, t0, fail

    srai t1, t0, 4        # t1 = 0xF8000000（1 填充）
    li   t2, 0xF8000000
    bne  t1, t2, fail

    srai t1, t0, 31       # t1 = 0xFFFFFFFF（全 1）
    li   t2, 0xFFFFFFFF
    bne  t1, t2, fail

    # ========== 逻辑指令测试 ==========
    # ANDI
    li   t0, 0xFF
    andi t1, t0, 0x0F     # t1 = 0x0F
    li   t2, 0x0F
    bne  t1, t2, fail

    andi t1, t0, 0xFFF    # t1 = 0xFF（高 8 位被 mask）
    bne  t1, t0, fail

    andi t1, t0, 0        # t1 = 0
    bnez t1, fail

    # ORI
    li   t0, 0
    ori  t1, t0, 0xF0F    # t1 = 0xF0F
    li   t2, 0xF0F
    bne  t1, t2, fail

    ori  t1, t0, -1       # t1 = 0xFFFFFFFF
    li   t2, 0xFFFFFFFF
    bne  t1, t2, fail

    # XORI
    li   t0, 0xFF
    xori t1, t0, 0xFF     # t1 = 0
    bnez t1, fail

    xori t1, t0, 0xFFF    # t1 = 0xF00（高 12 位翻转）
    li   t2, 0xF00
    bne  t1, t2, fail

    xori t1, t0, -1       # t1 = 0xFFFFFF00
    li   t2, 0xFFFFFF00
    bne  t1, t2, fail

    # ========== 测试通过 ==========
    li   t0, 1
    li   t5, tohost
    sw   t0, 0(t5)        # tohost = 1

pass:
    jal  zero, pass

fail:
    li   t0, 0xFF
    li   t5, tohost
    sw   t0, 0(t5)        # tohost = 0xFF（失败）
    jal  zero, fail