    .text
    .globl main
swap:
    addi sp, sp, -64
    sw ra, 60(sp)
    sw a0, 16(sp)
    sw a1, 20(sp)
    lw t0, 16(sp)
    lw t0, 0(t0)
    sw t0, 24(sp)
    lw t0, 20(sp)
    lw t0, 0(t0)
    sw t0, 0(sp)
    lw t0, 16(sp)
    lw t1, 0(sp)
    sw t1, 0(t0)
    lw t0, 24(sp)
    sw t0, 0(sp)
    lw t0, 20(sp)
    lw t1, 0(sp)
    sw t1, 0(t0)
    lw t0, 24(sp)
    mv a0, t0
    lw ra, 60(sp)
    addi sp, sp, 64
    jalr x0, x1, 0
main:
    addi sp, sp, -64
    sw ra, 60(sp)
    li t0, 1
    sw t0, 16(sp)
    li t0, 2
    sw t0, 20(sp)
    addi t0, sp, 16
    sw t0, 28(sp)
    addi t0, sp, 20
    sw t0, 32(sp)
    lw a0, 28(sp)
    lw a1, 32(sp)
    jal ra, swap
    mv t0, a0
    lw t0, 16(sp)
    mv a0, t0
    lw ra, 60(sp)
    addi sp, sp, 64
    jalr x0, x1, 0
