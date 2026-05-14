    .text
    .globl main
main:
    addi sp, sp, -64
    sw ra, 60(sp)
    li t0, 100
    la t1, .global_g_val
    sw t0, 0(t1)
    la t0, .global_g_val
    lw t0, 0(t0)
    mv a0, t0
    lw ra, 60(sp)
    addi sp, sp, 64
    jalr x0, x1, 0
    .data
.global_g_val:
    .word 0
