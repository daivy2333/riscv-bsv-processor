#ifndef TYPES_H
#define TYPES_H

/* Type structure for variable/parameter type tracking */
typedef struct {
    int base_type;    /* 0 = int */
    int ptr_level;    /* Pointer level: 0 = int, 1 = int* */
    int array_size;   /* Array size: 0 = not array, >0 = array elements count */
} Type;

/* Type helper functions */
Type type_make_int(void);           /* Create int type (ptr_level=0) */
Type type_make_int_ptr(void);       /* Create int* type (ptr_level=1) */
Type type_make_array(int size);     /* Create array type with given size */
int  type_is_ptr(Type t);           /* Check if type is pointer */
int  type_is_array(Type t);         /* Check if type is array */
void type_check_single_ptr(Type t); /* Error if ptr_level > 1 */

#endif /* TYPES_H */