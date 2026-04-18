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
    jal  zero, end