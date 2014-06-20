#ifndef O_ARRAY_H
#define O_ARRAY_H

#include <libooc/object.h>
// Please put included files here.
// Please put macros/type declarations here.


#undef O_CLASS
#undef O_PARENT
#define O_CLASS Array
#define O_PARENT Object
#define O_Array_OVERRIDE_METHODS_LEN 2
#define O_Array_PUBLIC_METHODS_LEN 11
#define O_Array_PRIVATE_METHODS_LEN 1
#define O_Array_OVERRIDE_METHOD_0 ctor, void, (va_list * args_ptr, args_ptr)
#define O_Array_OVERRIDE_METHOD_1 dtor, void
#define O_Array_PUBLIC_METHOD_0 len, o_uint
#define O_Array_PUBLIC_METHOD_1 get, void *, (o_uint index, index)
#define O_Array_PUBLIC_METHOD_2 first, void *
#define O_Array_PUBLIC_METHOD_3 last, void *
#define O_Array_PUBLIC_METHOD_4 push, void, (void * data, data)
#define O_Array_PUBLIC_METHOD_5 pop, void *
#define O_Array_PUBLIC_METHOD_6 unshift, void, (void * data, data)
#define O_Array_PUBLIC_METHOD_7 shift, void *
#define O_Array_PUBLIC_METHOD_8 each, void, (void (* iter)(void * _self_, void * obj, o_uint index), iter), (void * _self_, _self_)
#define O_Array_PUBLIC_METHOD_9 reverse_each, void, (void (* iter)(void * _self_, void * obj, o_uint index), iter), (void * _self_, _self_)
#define O_Array_PUBLIC_METHOD_10 any_p, bool, (bool (* iter)(void * _self_, void * obj, o_uint index), iter), (void * _self_, _self_)
#define O_Array_PRIVATE_METHOD_0 double_capa, void, (o_uint offset, offset)
#define O_Array_ctor O_Array_OVERRIDE_METHOD_0
#define O_Array_dtor O_Array_OVERRIDE_METHOD_1
#define O_Array_len O_Array_PUBLIC_METHOD_0
#define O_Array_get O_Array_PUBLIC_METHOD_1
#define O_Array_first O_Array_PUBLIC_METHOD_2
#define O_Array_last O_Array_PUBLIC_METHOD_3
#define O_Array_push O_Array_PUBLIC_METHOD_4
#define O_Array_pop O_Array_PUBLIC_METHOD_5
#define O_Array_unshift O_Array_PUBLIC_METHOD_6
#define O_Array_shift O_Array_PUBLIC_METHOD_7
#define O_Array_each O_Array_PUBLIC_METHOD_8
#define O_Array_reverse_each O_Array_PUBLIC_METHOD_9
#define O_Array_any_p O_Array_PUBLIC_METHOD_10
#define O_Array_double_capa O_Array_PRIVATE_METHOD_0
O_DEF_GLOBAL_METHODS()

#endif
