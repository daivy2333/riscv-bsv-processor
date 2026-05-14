    .text
    .globl main
strlen:
    addi sp, sp, -64
    sw ra, 60(sp)
    sw a0, 16(sp)
    li t0, 0
    sw t0, 20(sp)
.L0:
    lw t0, 16(sp)
    lb t0, 0(t0)
    beqz t0, .L1
    lw t0, 20(sp)
    sw t0, 0(sp)
    li t0, 1
    mv t1, t0
    lw t0, 0(sp)
    add t0, t0, t1
    sw t0, 20(sp)
    lw t0, 16(sp)
    sw t0, 0(sp)
    li t0, 1
    mv t1, t0
    lw t0, 0(sp)
    add t0, t0, t1
    sw t0, 16(sp)
    j .L0
.L1:
    lw t0, 20(sp)
    mv a0, t0
    lw ra, 60(sp)
    addi sp, sp, 64
    jalr x0, x1, 0
main:
    addi sp, sp, -64
    sw ra, 60(sp)
    la t0, .Lstr0
    la t1, .global_g_msg
    sw t0, 0(t1)
    la t0, .global_g_msg
    lw t0, 0(t0)
    sw t0, 28(sp)
    lw a0, 28(sp)
    jal ra, strlen
    mv t0, a0
    mv a0, t0
    lw ra, 60(sp)
    addi sp, sp, 64
    jalr x0, x1, 0
    .data
.global_g_msg:
    .word 0
.Lstr0:
    .byte 119,111,114,108,100,0
    .align 4
