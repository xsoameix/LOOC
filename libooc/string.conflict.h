#ifndef O_STRING_H
#define O_STRING_H

#include <libooc/object.h>
// Please put included files here.
// Please put macros/type declarations here.


#undef O_CLASS
#undef O_PARENT
#define O_CLASS String
#define O_PARENT Object
#define O_String_OVERRIDE_METHODS_LEN 5
#define O_String_PUBLIC_METHODS_LEN 4
#define O_String_PRIVATE_METHODS_LEN 0
#define O_String_OVERRIDE_METHOD_0 ctor, void, (va_list * args_ptr, args_ptr)
#define O_String_OVERRIDE_METHOD_1 dtor, void
#define O_String_OVERRIDE_METHOD_2 equals, bool, (void * _obj, _obj)
#define O_String_OVERRIDE_METHOD_3 hash_code, o_uint
#define O_String_OVERRIDE_METHOD_4 inspect, char *
#define O_String_PUBLIC_METHOD_0 set, void, (char * chars, chars)
#define O_String_PUBLIC_METHOD_1 index, o_uint, (bool (* func)(void * _self_, char c), func), (void * _self_, _self_)
#define O_String_PUBLIC_METHOD_2 rindex, o_uint, (bool (* func)(void * _self_, char c), func), (void * _self_, _self_)
#define O_String_PUBLIC_METHOD_3 strip, void
#define O_String_ctor O_String_OVERRIDE_METHOD_0
#define O_String_dtor O_String_OVERRIDE_METHOD_1
#define O_String_equals O_String_OVERRIDE_METHOD_2
#define O_String_hash_code O_String_OVERRIDE_METHOD_3
#define O_String_inspect O_String_OVERRIDE_METHOD_4
#define O_String_set O_String_PUBLIC_METHOD_0
#define O_String_index O_String_PUBLIC_METHOD_1
#define O_String_rindex O_String_PUBLIC_METHOD_2
#define O_String_strip O_String_PUBLIC_METHOD_3
O_DEF_GLOBAL_METHODS()

#endif
