    .text
    .globl main
main:
    addi sp, sp, -64
    sw ra, 60(sp)
    li t0, 5
    sw t0, 16(sp)
    li t0, 3
    sw t0, 20(sp)
    lw t0, 16(sp)
    sw t0, 0(sp)
    lw t0, 20(sp)
    mv t1, t0
    lw t0, 0(sp)
    sub t0, t0, t1
    sw t0, 0(sp)
    li t0, 2
    mv t1, t0
    lw t0, 0(sp)
    add t0, t0, t1
    mv a0, t0
    lw ra, 60(sp)
    addi sp, sp, 64
    jalr x0, x1, 0
