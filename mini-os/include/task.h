#ifndef TASK_H
#define TASK_H

#include "types.h"

typedef enum {
    TASK_READY,
    TASK_RUNNING,
    TASK_BLOCKED
} TaskState;

typedef struct {
    TaskID      id;
    TaskFunc    entry;
    void       *arg;
    Word       *stack_top;
    TaskState   state;
    uint32_t    delay_ticks;
    const char *name;
} TCB;

extern TCB task_table[MAX_TASKS];
extern volatile TaskID current_task;
extern volatile uint32_t task_count;

TaskID task_create(TaskFunc entry, void *arg, const char *name);
void   task_delay(uint32_t ticks);
void   task_yield(void);

#endif /* TASK_H */