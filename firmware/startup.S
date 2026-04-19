/* FreeRTOS Startup Code for RV32I Processor
 *
 * Responsibilities:
 * - Clear .bss section
 * - Initialize stack pointer
 * - Jump to main()
 */

.section .text.init
.global _start

_start:
    /* Disable interrupts during startup */
    csrw mie, 0

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
    /* Set mtvec to trap handler (will be set by FreeRTOS later) */
    /* For now, use default */

    /* Enable global interrupt (MIE) - optional, can be done in FreeRTOS */
    /* li t0, 0x8 */
    /* csrs mstatus, t0 */

    /* Jump to main */
    call main

    /* If main returns, infinite loop */
halt:
    j halt

.size _start, . - _start