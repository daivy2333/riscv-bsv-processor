/* Simple bare-metal C test for UART output */

/* Direct UART address - no data segment dependency */
#define UART_TXDATA_ADDR 0x10000000

void putchar(char c) {
    *((volatile unsigned int *)UART_TXDATA_ADDR) = c;
}

void puts(const char *s) {
    while (*s) {
        putchar(*s++);
    }
}

/* Simple main */
int main(void) {
    puts("Hello from C!\n");

    /* Write success to tohost */
    *((volatile unsigned int *)0x80001000) = 1;  /* PASSED */

    /* Infinite loop */
    while(1);

    return 0;
}