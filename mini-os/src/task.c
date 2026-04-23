/* Mini-OS Task Management - Round-Robin Scheduler */

#include "task.h"
#include "types.h"

TCB task_table[MAX_TASKS];
volatile TaskID current_task = 0;
volatile uint32_t task_count = 0;

/* Pre-allocated task stacks */
static Word task_stacks[MAX_TASKS][TASK_STACK_SIZE / sizeof(Word)];

extern void trap_entry(void);

TaskID task_create(TaskFunc entry, void *arg, const char *name)
{
    if (task_count >= MAX_TASKS) return (TaskID)-1;

    TaskID id = task_count++;
    TCB *tcb = &task_table[id];

    tcb->id = id;
    tcb->entry = entry;
    tcb->arg = arg;
    tcb->name = name;
    tcb->state = TASK_READY;
    tcb->delay_ticks = 0;

    /* Initialize stack frame */
    Word *stack = &task_stacks[id][0];
    tcb->stack_top = stack;

    /* Frame layout (128 bytes = 32 words):
     * [0]  mepc = entry
     * [1]  mstatus = 0x1880 (MPIE=1, MPP=3, MIE=0)
     * [2-31] registers = 0
     * [22] a0 (x10) = arg (offset 88 bytes = word 22)
     */
    stack[0] = (Word)entry;      /* mepc */
    stack[1] = 0x1880;           /* mstatus */
    for (int i = 2; i < 32; i++) {
        stack[i] = 0;
    }
    stack[22] = (Word)arg;       /* a0 at offset 88 bytes */

    return id;
}

void task_delay(uint32_t ticks)
{
    task_table[current_task].delay_ticks = ticks;
    task_table[current_task].state = TASK_BLOCKED;
    task_yield();
}

void task_yield(void)
{
    __asm__ volatile("ecall");
}

void task_switch(void)
{
    /* Update delay ticks for current task */
    if (task_table[current_task].delay_ticks > 0) {
        task_table[current_task].delay_ticks--;
        if (task_table[current_task].delay_ticks == 0) {
            task_table[current_task].state = TASK_READY;
        }
    }

    /* Round-Robin: find next READY task */
    TaskID next = current_task;
    for (uint32_t i = 0; i < task_count; i++) {
        next = (next + 1) % task_count;
        if (task_table[next].state == TASK_READY) {
            break;
        }
    }

    current_task = next;
}