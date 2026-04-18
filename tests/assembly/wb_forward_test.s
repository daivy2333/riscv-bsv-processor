# tests/assembly/wb_forward_test.s
# WB 前递测试（不依赖 MEM 前递）

.globl _start
.section .text

_start:
    # 指令序列：确保 beq 只依赖 WB 前递
    li   t0, 1       # 写 t0
    nop              # 增加间隔
    nop              # 增加间隔
    li   t1, 1       # 写 t1，这条会在 MEM 阶段
    nop              # 增加间隔，t1 到 WB 阶段
    beq  t0, t1, pass  # t0 从 WB 前递，t1 从 WB 前递（两个 nop 间隔）
fail:
    li   t2, 0
    jal  zero, end
pass:
    li   t2, 1
end:
    jal  zero, end