# tests/assembly/simple_arith_test.s
# 简单算术测试（无 Load，无循环）

.section .text
.global _start

_start:
    # 测试基本算术
    li x1, 10
    li x2, 20
    add x3, x1, x2     # x3 = 30
    add x4, x3, x1     # x4 = 40 (前递)
    add x5, x4, x3     # x5 = 70 (前递)

    # 测试 li (I-Type)
    li x10, 5          # x10 = 5
    li x11, 100        # x11 = 100

    # 写入 tohost 表示成功
    li x6, 0x80001000
    li x7, 1
    sw x7, 0(x6)

end:
    j end