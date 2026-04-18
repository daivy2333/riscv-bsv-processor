# tests/assembly/addi_test.s
# ADDI 指令专项验证（无跳转，用 PC 检测结束）

.globl _start
.section .text

_start:
    # ADDI 测试 1: 基本加法
    li   t0, 100
    addi t1, t0, -50      # t1 = 50
    li   t2, 50
    bne  t1, t2, end

    # ADDI 测试 2: 零立即数
    li   t0, 0
    addi t1, t0, 0        # t1 = 0
    bnez t1, end

    # ADDI 测试 3: 最大正立即数
    addi t1, t0, 2047     # t1 = 2047
    li   t2, 2047
    bne  t1, t2, end

    # ADDI 测试 4: 最小负立即数
    addi t1, t0, -2048    # t1 = -2048
    li   t2, -2048
    bne  t1, t2, end

    # ADDI 测试 5: 溢出
    li   t0, 0x7FFFFFFF
    addi t1, t0, 1        # t1 = 0x80000000
    li   t2, 0x80000000
    bne  t1, t2, end

end:
    jal  zero, end