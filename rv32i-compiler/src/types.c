#include "types.h"
#include <stdio.h>

Type type_make_int(void)
{
    Type t = { .base_type = TYPE_INT, .ptr_level = 0, .array_size = 0, .struct_id = -1, .is_const = 0, .is_volatile = 0 };
    return t;
}

Type type_make_int_ptr(void)
{
    Type t = { .base_type = TYPE_INT, .ptr_level = 1, .array_size = 0, .struct_id = -1, .is_const = 0, .is_volatile = 0 };
    return t;
}

Type type_make_array(int size)
{
    Type t = { .base_type = TYPE_INT, .ptr_level = 0, .array_size = size, .struct_id = -1, .is_const = 0, .is_volatile = 0 };
    return t;
}

Type type_make_char(void)
{
    Type t = { .base_type = TYPE_CHAR, .ptr_level = 0, .array_size = 0, .struct_id = -1, .is_const = 0, .is_volatile = 0 };
    return t;
}

Type type_make_char_ptr(void)
{
    Type t = { .base_type = TYPE_CHAR, .ptr_level = 1, .array_size = 0, .struct_id = -1, .is_const = 0, .is_volatile = 0 };
    return t;
}

Type type_make_char_array(int size)
{
    Type t = { .base_type = TYPE_CHAR, .ptr_level = 0, .array_size = size, .struct_id = -1, .is_const = 0, .is_volatile = 0 };
    return t;
}

int type_is_ptr(Type t)
{
    return t.ptr_level > 0;
}

int type_is_array(Type t)
{
    return t.array_size > 0;
}

int type_is_char(Type t)
{
    return t.base_type == TYPE_CHAR;
}

void type_check_single_ptr(Type t)
{
    if (t.ptr_level > 1) {
        fprintf(stderr, "error: multi-level pointer not supported in phase 5\n");
    }
}

Type type_make_struct_ptr(int struct_id)
{
    Type t = { .base_type = TYPE_STRUCT, .ptr_level = 1, .array_size = 0, .struct_id = struct_id, .is_const = 0, .is_volatile = 0 };
    return t;
}

Type type_make_struct_val(int struct_id)
{
    Type t = { .base_type = TYPE_STRUCT, .ptr_level = 0, .array_size = 0, .struct_id = struct_id, .is_const = 0, .is_volatile = 0 };
    return t;
}

int type_is_struct(Type t)
{
    return t.base_type == TYPE_STRUCT;
}