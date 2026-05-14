    .text
    .globl main
main:
    addi sp, sp, -64
    sw ra, 60(sp)
    la t0, .global_g_count
    lw t0, 0(t0)
    mv a0, t0
    lw ra, 60(sp)
    addi sp, sp, 64
    jalr x0, x1, 0
    .data
.global_g_count:
    .word 42
