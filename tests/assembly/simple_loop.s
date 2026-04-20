# tests/assembly/simple_loop.s
# 测试无限循环（不依赖 Store）

.globl _start
.section .text

_start:
    li   t0, 100
    li   t1, 100
    beq  t0, t1, end    # 应该跳转
    li   t2, 0          # 不应该执行
end:
    # 写入 tohost 表示成功
    li   t6, 0x80001000
    li   t5, 1
    sw   t5, 0(t6)
    jal  zero, end      # 无限循环