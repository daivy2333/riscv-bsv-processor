#ifndef TYPES_H
#define TYPES_H

/* Type structure for variable/parameter type tracking */
typedef enum {
    TYPE_INT = 0,
    TYPE_CHAR = 1
} BaseType;

typedef struct {
    BaseType base_type;  /* TYPE_INT or TYPE_CHAR */
    int ptr_level;       /* Pointer level: 0 = scalar, 1 = pointer */
    int array_size;      /* Array size: 0 = not array, >0 = array elements count */
} Type;

/* Type helper functions */
Type type_make_int(void);           /* Create int type */
Type type_make_int_ptr(void);       /* Create int* type */
Type type_make_array(int size);     /* Create int array type */
Type type_make_char(void);          /* Create char type */
Type type_make_char_ptr(void);      /* Create char* type */
Type type_make_char_array(int size);/* Create char array type */
int  type_is_ptr(Type t);           /* Check if type is pointer */
int  type_is_array(Type t);         /* Check if type is array */
int  type_is_char(Type t);          /* Check if base type is char */
void type_check_single_ptr(Type t); /* Error if ptr_level > 1 */

#endif /* TYPES_H */