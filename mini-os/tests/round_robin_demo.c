/* Mini-OS Round-Robin Demo */

#include "os.h"
#include "task.h"

void task1(void *arg)
{
    uart_puts("\n[T1] Start\n");
    for (int i = 0; i < 5; i++) {
        uart_puts("[T1] iter ");
        uart_putchar('0' + i);
        uart_puts("\n");
        task_delay(10);
    }
    uart_puts("[T1] Done\n");
}

void task2(void *arg)
{
    uart_puts("\n[T2] Start\n");
    for (int i = 0; i < 5; i++) {
        uart_puts("[T2] iter ");
        uart_putchar('0' + i);
        uart_puts("\n");
        task_delay(5);
    }
    uart_puts("[T2] Done\n");
}

void task3(void *arg)
{
    uart_puts("\n[T3] Start\n");
    for (int i = 0; i < 5; i++) {
        uart_puts("[T3] iter ");
        uart_putchar('0' + i);
        uart_puts("\n");
        task_delay(3);
    }
    uart_puts("[T3] Done\n");
    os_halt();
}

int main(void)
{
    uart_puts("\n=== Mini-OS Round-Robin Demo ===\n");

    os_init();

    task_create(task1, NULL, "Task1");
    task_create(task2, NULL, "Task2");
    task_create(task3, NULL, "Task3");

    uart_puts("Tasks created. Starting...\n");

    os_start();

    uart_puts("Error: os_start returned!\n");
    os_halt();

    return 0;
}