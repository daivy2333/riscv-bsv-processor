    .text
    .globl main
main:
    addi sp, sp, -64
    sw ra, 60(sp)
    li t0, 3
    sw t0, 0(sp)
    li t0, 5
    mv t1, t0
    lw t0, 0(sp)
    mv a0, t0
    mv a1, t1
    jal ra, __mulsi3
    mv t0, a0
    sw t0, 16(sp)
    lw t0, 16(sp)
    mv a0, t0
    lw ra, 60(sp)
    addi sp, sp, 64
    jalr x0, x1, 0
