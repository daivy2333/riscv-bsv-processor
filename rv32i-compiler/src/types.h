#ifndef TYPES_H
#define TYPES_H

/* Type structure for variable/parameter type tracking */
typedef enum {
    TYPE_INT = 0,
    TYPE_CHAR = 1,
    TYPE_STRUCT = 2  /* 结构体类型 */
} BaseType;

typedef struct {
    BaseType base_type;  /* TYPE_INT, TYPE_CHAR, TYPE_STRUCT */
    int ptr_level;       /* Pointer level: 0 = scalar, 1 = pointer */
    int array_size;      /* Array size: 0 = not array, >0 = array elements count */
    int struct_id;       /* struct_table 索引 (仅 TYPE_STRUCT 有效) */
} Type;

/* 结构体成员信息 */
typedef struct MemberInfo {
    char *name;         /* 成员名称 */
    Type type;          /* 成员类型 */
    int offset;         /* 字节偏移 */
} MemberInfo;

/* 结构体定义信息 */
typedef struct StructInfo {
    char *name;         /* 结构体名称 */
    MemberInfo *members; /* 成员数组 */
    int member_count;   /* 成员数量 */
    int total_size;     /* 总字节大小 */
} StructInfo;

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

/* 结构体类型辅助函数 */
Type type_make_struct_ptr(int struct_id);  /* 创建 struct Name* 类型 */
Type type_make_struct_val(int struct_id);  /* 创建 struct Name 类型 */
int  type_is_struct(Type t);                /* 检查是否为结构体类型 */

#endif /* TYPES_H */