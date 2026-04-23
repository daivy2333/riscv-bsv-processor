/* Mini-OS Core */

#include "os.h"
#include "timer.h"

extern void trap_entry(void);

void os_init(void)
{
    uart_init();

    /* Set trap vector */
    __asm__ volatile("csrw mtvec, %0" :: "r"(trap_entry));

    /* Initialize timer */
    timer_init();
}

void os_start(void)
{
    /* Enable timer interrupt (MTIE = bit 7) */
    __asm__ volatile("csrs mie, %0" :: "r"(0x80));

    /* Enable global interrupt (MIE = bit 3) */
    __asm__ volatile("csrs mstatus, %0" :: "r"(0x8));

    /* Trigger first task switch via ecall */
    __asm__ volatile("ecall");
}

void os_halt(void)
{
    __asm__ volatile("csrw mie, 0");
    TOHOST = 1;
    for (;;);
}