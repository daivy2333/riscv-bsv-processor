# tests/assembly/simple_branch_test.s
# 简单分支测试

.globl _start
.section .text

_start:
    li   t0, 10
    li   t1, 10
    beq  t0, t1, target  # 应该跳转
    li   t2, 0           # 不应该执行
    jal  zero, end

target:
    li   t2, 1           # 应该执行

end:
    # 写入 tohost 表示成功
    li   t6, 0x80001000
    li   t5, 1
    sw   t5, 0(t6)
    jal  zero, end