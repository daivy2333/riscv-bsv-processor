/* Mini-OS Timer */

#include "timer.h"
#include "types.h"

uint64_t get_mtime(void)
{
    uint32_t lo, hi;
    do {
        hi = CLINT_MTIME_HI;
        lo = CLINT_MTIME_LO;
    } while (hi != CLINT_MTIME_HI);
    return ((uint64_t)hi << 32) | lo;
}

void set_mtimecmp(uint64_t val)
{
    CLINT_MTIMECMP_HI = (uint32_t)(val >> 32);
    CLINT_MTIMECMP_LO = (uint32_t)(val & 0xFFFFFFFF);
}

void timer_init(void)
{
    uint64_t first = get_mtime() + TICK_INTERVAL_CYCLES;
    set_mtimecmp(first);
}

void timer_handler(void)
{
    uint64_t next = get_mtime() + TICK_INTERVAL_CYCLES;
    set_mtimecmp(next);
}