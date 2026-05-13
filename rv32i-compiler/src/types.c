#include "types.h"
#include <stdio.h>

Type type_make_int(void)
{
    Type t = { .base_type = 0, .ptr_level = 0 };
    return t;
}

Type type_make_int_ptr(void)
{
    Type t = { .base_type = 0, .ptr_level = 1 };
    return t;
}

int type_is_ptr(Type t)
{
    return t.ptr_level > 0;
}

void type_check_single_ptr(Type t)
{
    if (t.ptr_level > 1) {
        fprintf(stderr, "error: multi-level pointer not supported in phase 5\n");
    }
}