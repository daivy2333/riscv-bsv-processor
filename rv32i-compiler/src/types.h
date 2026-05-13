#ifndef TYPES_H
#define TYPES_H

/* Type structure for variable/parameter type tracking */
typedef struct {
    int base_type;    /* 0 = int (future: 1 = struct, 2 = array) */
    int ptr_level;    /* Pointer level: 0 = int, 1 = int*, 2 = int** */
} Type;

/* Type helper functions */
Type type_make_int(void);           /* Create int type (ptr_level=0) */
Type type_make_int_ptr(void);       /* Create int* type (ptr_level=1) */
int  type_is_ptr(Type t);           /* Check if type is pointer */
void type_check_single_ptr(Type t); /* Error if ptr_level > 1 */

#endif /* TYPES_H */