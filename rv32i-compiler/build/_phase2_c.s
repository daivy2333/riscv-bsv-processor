    .text
    .globl main
main:
    addi sp, sp, -64
    sw ra, 60(sp)
    li t0, 42
    sw t0, 16(sp)
    lw t0, 16(sp)
    mv a0, t0
    lw ra, 60(sp)
    addi sp, sp, 64
    jalr x0, x1, 0
