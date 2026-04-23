#ifndef OS_H
#define OS_H

#include "task.h"
#include "uart.h"
#include "timer.h"

void os_init(void);
void os_start(void);
void os_halt(void);

#endif /* OS_H */