#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>
#include <stddef.h>

typedef uint32_t Word;
typedef uint32_t TaskID;
typedef void (*TaskFunc)(void *arg);

/* 硬件地址定义 */
#define UART_BASE       0x10000000
#define UART_TXDATA     (*((volatile uint32_t*)(UART_BASE + 0x00)))

#define CLINT_MTIME_LO  (*((volatile uint32_t*)0x0200BFF8))
#define CLINT_MTIME_HI  (*((volatile uint32_t*)0x0200BFFC))
#define CLINT_MTIMECMP_LO (*((volatile uint32_t*)0x02004000))
#define CLINT_MTIMECMP_HI (*((volatile uint32_t*)0x02004004))

#define TOHOST_ADDR     0x80001000
#define TOHOST          (*((volatile uint32_t*)TOHOST_ADDR))

/* 配置参数 */
#define MAX_TASKS           4
#define TASK_STACK_SIZE     512     /* bytes */
#define TICK_INTERVAL_CYCLES 10000  /* 10ms @ 1MHz */
#define FRAME_SIZE          128     /* bytes */

#endif /* TYPES_H */