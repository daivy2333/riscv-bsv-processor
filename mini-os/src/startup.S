/* Mini-OS Startup Code for RV32I Processor */

.section .text.init
.global _start
.extern trap_entry

_start:
    /* Disable interrupts */
    csrw mie, 0
    csrw mstatus, 0

    /* Set trap vector early */
    la t0, trap_entry
    csrw mtvec, t0

    /* Initialize stack pointer */
    la sp, _stack_top

    /* Clear .bss section */
    la t0, _bss_start
    la t1, _bss_end
    bgeu t0, t1, bss_done

bss_loop:
    sw zero, 0(t0)
    addi t0, t0, 4
    bltu t0, t1, bss_loop

bss_done:
    /* Jump to main */
    call main

halt:
    j halt

.size _start, . - _start