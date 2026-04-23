/*
 * Mini-OS Trap Handler for RV32I
 *
 * Stack frame: 128 bytes (32 words)
 * [0]  mepc
 * [1]  mstatus
 * [2-31] registers (x1-x31, x10=a0 at word 22)
 */

.section .text
.global trap_entry
.global task_switch
.global task_table
.global current_task
.global task_count

.equ FRAME_SIZE, 128

trap_entry:
    /* Get current task TCB */
    la      x28, current_task
    lbu     x28, 0(x28)              /* x28 = current_task ID */
    la      x29, task_table
    slli    x30, x28, 3              /* x30 = ID * 8 (TCB struct offset, assuming 8-byte aligned) */
    add     x29, x29, x30
    lw      x29, 12(x29)             /* x29 = stack_top (offset 12 in TCB) */

    /* Save CSR */
    csrr    x30, mepc
    sw      x30, 0(x29)
    csrr    x30, mstatus
    sw      x30, 4(x29)

    /* Save registers (x1-x31, skip x0) */
    sw      x1,  124(x29)            /* ra */
    sw      x3,  116(x29)            /* gp */
    sw      x4,  112(x29)            /* tp */
    sw      x5,  108(x29)            /* t0 */
    sw      x6,  104(x29)            /* t1 */
    sw      x7,  100(x29)            /* t2 */
    sw      x8,  96(x29)             /* s0/fp */
    sw      x9,  92(x29)             /* s1 */
    sw      x10, 88(x29)             /* a0 */
    sw      x11, 84(x29)             /* a1 */
    sw      x12, 80(x29)             /* a2 */
    sw      x13, 76(x29)             /* a3 */
    sw      x14, 72(x29)             /* a4 */
    sw      x15, 68(x29)             /* a5 */
    sw      x16, 64(x29)             /* a6 */
    sw      x17, 60(x29)             /* a7 */
    sw      x18, 56(x29)             /* s2 */
    sw      x19, 52(x29)             /* s3 */
    sw      x20, 48(x29)             /* s4 */
    sw      x21, 44(x29)             /* s5 */
    sw      x22, 40(x29)             /* s6 */
    sw      x23, 36(x29)             /* s7 */
    sw      x24, 32(x29)             /* s8 */
    sw      x25, 28(x29)             /* s9 */
    sw      x26, 24(x29)             /* s10 */
    sw      x27, 20(x29)             /* s11 */
    sw      x28, 16(x29)             /* t3 (saved late) */
    sw      x29, 8(x29)              /* t4 (frame pointer) */
    sw      x30, 12(x29)             /* t5 */
    sw      x31, 16(x29)             /* t6 - actually saved at offset 16 */

    /* Check interrupt type */
    csrr    x28, mcause
    srli    x29, x28, 31
    beqz    x29, exception           /* Not interrupt = exception */

    andi    x29, x28, 0x7F
    li      x30, 7
    beq     x29, x30, timer_irq      /* Timer IRQ */
    j       restore

timer_irq:
    call    timer_handler
    call    task_switch
    j       restore

exception:
    andi    x29, x28, 0x1F
    li      x30, 11                  /* ECALL */
    bne     x29, x30, restore

    /* ECALL: mepc += 4 */
    csrr    x28, mepc
    addi    x28, x28, 4
    csrw    mepc, x28

    /* Update frame mepc */
    la      x29, current_task
    lbu     x29, 0(x29)
    la      x30, task_table
    slli    x29, x29, 3
    add     x30, x30, x29
    lw      x30, 12(x30)             /* x30 = stack_top */
    sw      x28, 0(x30)              /* Update frame mepc */

    call    task_switch

restore:
    /* Get new task stack_top */
    la      x28, current_task
    lbu     x28, 0(x28)
    la      x29, task_table
    slli    x30, x28, 3
    add     x29, x29, x30
    lw      x29, 12(x29)             /* x29 = new stack_top */

    /* Restore CSR */
    lw      x30, 0(x29)
    csrw    mepc, x30
    lw      x30, 4(x29)
    csrw    mstatus, x30

    /* Restore registers */
    lw      x1,  124(x29)
    lw      x3,  116(x29)
    lw      x4,  112(x29)
    lw      x5,  108(x29)
    lw      x6,  104(x29)
    lw      x7,  100(x29)
    lw      x8,  96(x29)
    lw      x9,  92(x29)
    lw      x10, 88(x29)             /* a0 */
    lw      x11, 84(x29)
    lw      x12, 80(x29)
    lw      x13, 76(x29)
    lw      x14, 72(x29)
    lw      x15, 68(x29)
    lw      x16, 64(x29)
    lw      x17, 60(x29)
    lw      x18, 56(x29)
    lw      x19, 52(x29)
    lw      x20, 48(x29)
    lw      x21, 44(x29)
    lw      x22, 40(x29)
    lw      x23, 36(x29)
    lw      x24, 32(x29)
    lw      x25, 28(x29)
    lw      x26, 24(x29)
    lw      x27, 20(x29)
    lw      x31, 16(x29)
    lw      x30, 12(x29)
    lw      x28, 16(x29)

    /* Set sp = stack_top + FRAME_SIZE */
    addi    sp, x29, FRAME_SIZE

    mret

.size trap_entry, . - trap_entry