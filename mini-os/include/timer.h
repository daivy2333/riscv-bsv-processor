#ifndef TIMER_H
#define TIMER_H

#include "types.h"

void timer_init(void);
void timer_handler(void);

uint64_t get_mtime(void);
void set_mtimecmp(uint64_t val);

#endif /* TIMER_H */