/* Mini-OS UART Driver */

#include "uart.h"
#include "types.h"

void uart_init(void)
{
    /* UART is simple memory-mapped, no init needed */
}

void uart_putchar(char c)
{
    UART_TXDATA = c;
}

void uart_puts(const char *s)
{
    while (*s) {
        uart_putchar(*s++);
    }
}