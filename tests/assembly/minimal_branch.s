# tests/assembly/minimal_branch.s
# 最小分支测试

.globl _start
.section .text

_start:
    li   t0, 1
    li   t1, 1
    beq  t0, t1, pass    # 应该跳转
fail:
    li   t2, 0           # 不应执行
    jal  zero, end
pass:
    li   t2, 1           # 应执行
end:
    jal  zero, end       # 死循环