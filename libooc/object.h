#ifndef O_OBJECT_H
#define O_OBJECT_H

#include <stdio.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdbool.h>
#include <inttypes.h>
#include <libooc/macro.h>

typedef intptr_t o_int;
typedef uintptr_t o_uint;
typedef void * o_obj;

#undef O_CLASS
#undef O_PARENT
#define O_CLASS Object
#define O_PARENT Object
#define O_Object_OVERRIDE_METHODS_LEN 0
#define O_Object_PUBLIC_METHODS_LEN 8
#define O_Object_PRIVATE_METHODS_LEN 0
#define O_Object_PUBLIC_METHOD_0 ctor,       void,         (va_list * args_ptr, args_ptr)
#define O_Object_PUBLIC_METHOD_1 dtor,       void
#define O_Object_PUBLIC_METHOD_2 equals,     bool,         (o_obj obj, obj)
#define O_Object_PUBLIC_METHOD_3 hash_code,  o_uint
#define O_Object_PUBLIC_METHOD_4 inspect,    char *
#define O_Object_PUBLIC_METHOD_5 class,      const void *
#define O_Object_PUBLIC_METHOD_6 class_name, char *
#define O_Object_PUBLIC_METHOD_7 is_a,       bool,         (const void * class, class)
#define O_Object_ctor       O_PUBLIC_METHOD_0
#define O_Object_dtor       O_PUBLIC_METHOD_1
#define O_Object_equals     O_PUBLIC_METHOD_2
#define O_Object_hash_code  O_PUBLIC_METHOD_3
#define O_Object_inspect    O_PUBLIC_METHOD_4
#define O_Object_class      O_PUBLIC_METHOD_5
#define O_Object_class_name O_PUBLIC_METHOD_6
#define O_Object_is_a       O_PUBLIC_METHOD_7
O_DEF_GLOBAL_METHODS()

o_obj new(const void * klass, ...);
void  delete(o_obj obj);

#endif
