# tests/assembly/loop_test.s
# 循环测试

.section .text
.global _start

_start:
    # 基本算术
    li x1, 10
    li x2, 20
    add x3, x1, x2     # x3 = 30

    # 循环
    li x10, 5          # x10 = 5 (循环计数)
loop1:
    addi x10, x10, -1
    bne x10, x0, loop1

    # 写入 tohost 表示成功
    li x6, 0x80001000
    li x7, 1
    sw x7, 0(x6)

end:
    j end