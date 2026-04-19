/*
 * FreeRTOS Demo for RV32I Processor
 *
 * Simple blink-style demo using UART output.
 */

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

/* UART TX address */
#define UART_TXDATA (*((volatile uint32_t*)0x10000000))

/* Simple putchar */
void putchar(char c)
{
    UART_TXDATA = c;
}

/* Simple puts */
void puts(const char *s)
{
    while (*s) {
        putchar(*s++);
    }
}

/* Task 1: Print 'A' every 100ms */
void vTask1(void *pvParameters)
{
    const TickType_t xDelay = pdMS_TO_TICKS(100);

    for (;;) {
        puts("Task1: A\n");
        vTaskDelay(xDelay);
    }
}

/* Task 2: Print 'B' every 500ms */
void vTask2(void *pvParameters)
{
    const TickType_t xDelay = pdMS_TO_TICKS(500);

    for (;;) {
        puts("Task2: B\n");
        vTaskDelay(xDelay);
    }
}

/* Main */
int main(void)
{
    puts("FreeRTOS Demo Start\n");

    /* Create tasks */
    xTaskCreate(vTask1, "Task1", 128, NULL, 1, NULL);
    xTaskCreate(vTask2, "Task2", 128, NULL, 2, NULL);

    /* Start scheduler */
    vTaskStartScheduler();

    /* Should never reach here */
    for (;;) {
        puts("Error: Scheduler stopped\n");
    }

    return 0;
}

/* Idle hook */
void vApplicationIdleHook(void)
{
    /* Nothing */
}

/* Stack overflow hook */
void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName)
{
    puts("Stack overflow!\n");
    for (;;);
}