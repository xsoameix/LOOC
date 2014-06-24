#ifndef O_ARRAY_H
#define O_ARRAY_H

#include <libooc/object.h>

// Please put included files here.


// Please put macros/type declarations here.
#define O_ARY_ITOR(name, ...) void O_ARY_ITOR_NAME(name)(o_obj O_ARY_ITEM, o_uint O_ARY_INDEX, ## __VA_ARGS__)
#define O_ARY_ITOR_NAME(name) O_STR_CAT(__o_ary_each_itor_, name)
#define O_ARY_EACH(...) O_DEFAULT_ARG(O_ARY_EACH_, __VA_ARGS__)
#define O_ARY_EACH_2(ary, name) Array_each(ary, O_ARY_ITOR_NAME(name))
#define O_ARY_EACH_3(ary, name, ...) Array_each_with_1(ary, __VA_ARGS__, O_ARY_ITOR_NAME(name))
#define O_ARY_EACH_4(ary, name, ...) Array_each_with_2(ary, __VA_ARGS__, O_ARY_ITOR_NAME(name))
#define O_ARY_EACH_5(ary, name, ...) Array_each_with_3(ary, __VA_ARGS__, O_ARY_ITOR_NAME(name))
#define O_ARY_REVERSE_EACH(...) O_DEFAULT_ARG(O_ARY_REVERSE_EACH_, __VA_ARGS__)
#define O_ARY_REVERSE_EACH_2(ary, name) Array_reverse_each(ary, O_ARY_ITOR_NAME(name))
#define O_ARY_REVERSE_EACH_3(ary, name, ...) Array_reverse_each_with_1(ary, __VA_ARGS__, O_ARY_ITOR_NAME(name))
#define O_ARY_REVERSE_EACH_4(ary, name, ...) Array_reverse_each_with_2(ary, __VA_ARGS__, O_ARY_ITOR_NAME(name))
#define O_ARY_REVERSE_EACH_5(ary, name, ...) Array_reverse_each_with_3(ary, __VA_ARGS__, O_ARY_ITOR_NAME(name))
#define O_ARY_ITEM __o_ary_item
#define O_ARY_INDEX __o_ary_index
#define O_ARY_ANY_P_ITOR(name, ...) bool O_ARY_ANY_P_ITOR_NAME(name)(o_obj O_ARY_ITEM, o_uint O_ARY_INDEX, ## __VA_ARGS__)
#define O_ARY_ANY_P_ITOR_NAME(name) O_STR_CAT(__o_ary_any_p_itor_, name)
#define O_ARY_ANY_P(...) O_DEFAULT_ARG(O_ARY_ANY_P_, __VA_ARGS__)
#define O_ARY_ANY_P_2(ary, name) Array_any_p(ary, O_ARY_ANY_P_ITOR_NAME(name))
#define O_ARY_ANY_P_3(ary, name, ...) Array_any_p_with_1(ary, __VA_ARGS__, O_ARY_ANY_P_ITOR_NAME(name))
#define O_ARY_ANY_P_4(ary, name, ...) Array_any_p_with_2(ary, __VA_ARGS__, O_ARY_ANY_P_ITOR_NAME(name))
#define O_ARY_ANY_P_5(ary, name, ...) Array_any_p_with_3(ary, __VA_ARGS__, O_ARY_ANY_P_ITOR_NAME(name))
#define O_ARY_LEN(...) Array_len(__VA_ARGS__)
#define O_ARY_GET(...) Array_get(__VA_ARGS__)
#define O_ARY_PUSH(...) Array_push(__VA_ARGS__)

typedef void (* o_ary_each_with_0_itor)(o_obj item, o_uint index);
typedef void (* o_ary_each_with_1_itor)(o_obj item, o_uint index, o_obj arg);
typedef void (* o_ary_each_with_2_itor)(o_obj item, o_uint index, o_obj arg, o_obj arg2);
typedef void (* o_ary_each_with_3_itor)(o_obj item, o_uint index, o_obj arg, o_obj arg2, o_obj arg3);
typedef bool (* o_ary_any_with_0_itor)(o_obj item, o_uint index);
typedef bool (* o_ary_any_with_1_itor)(o_obj item, o_uint index, o_obj arg);
typedef bool (* o_ary_any_with_2_itor)(o_obj item, o_uint index, o_obj arg, o_obj arg2);
typedef bool (* o_ary_any_with_3_itor)(o_obj item, o_uint index, o_obj arg, o_obj arg2, o_obj arg3);


#undef O_CLASS
#undef O_PARENT
#define O_CLASS Array
#define O_PARENT Object
#define O_Array_OVERRIDE_METHODS_LEN 2
#define O_Array_PUBLIC_METHODS_LEN 20
#define O_Array_PRIVATE_METHODS_LEN 1
#define O_Array_OVERRIDE_METHOD_0 ctor, void, (va_list * args_ptr, args_ptr)
#define O_Array_OVERRIDE_METHOD_1 dtor, void
#define O_Array_PUBLIC_METHOD_0 len, o_uint
#define O_Array_PUBLIC_METHOD_1 get, o_obj, (o_uint i, i)
#define O_Array_PUBLIC_METHOD_2 first, o_obj
#define O_Array_PUBLIC_METHOD_3 last, o_obj
#define O_Array_PUBLIC_METHOD_4 push, void, (o_obj data, data)
#define O_Array_PUBLIC_METHOD_5 pop, o_obj
#define O_Array_PUBLIC_METHOD_6 unshift, void, (o_obj data, data)
#define O_Array_PUBLIC_METHOD_7 shift, o_obj
#define O_Array_PUBLIC_METHOD_8 each, void, (o_ary_each_with_0_itor itor, itor)
#define O_Array_PUBLIC_METHOD_9 each_with_1, void, (o_obj arg0, arg0), (o_ary_each_with_1_itor itor, itor)
#define O_Array_PUBLIC_METHOD_10 each_with_2, void, (o_obj arg0, arg0), (o_obj arg1, arg1), (o_ary_each_with_2_itor itor, itor)
#define O_Array_PUBLIC_METHOD_11 each_with_3, void, (o_obj arg0, arg0), (o_obj arg1, arg1), (o_obj arg2, arg2), (o_ary_each_with_3_itor itor, itor)
#define O_Array_PUBLIC_METHOD_12 reverse_each, void, (o_ary_each_with_0_itor itor, itor)
#define O_Array_PUBLIC_METHOD_13 reverse_each_with_1, void, (o_obj arg0, arg0), (o_ary_each_with_1_itor itor, itor)
#define O_Array_PUBLIC_METHOD_14 reverse_each_with_2, void, (o_obj arg0, arg0), (o_obj arg1, arg1), (o_ary_each_with_2_itor itor, itor)
#define O_Array_PUBLIC_METHOD_15 reverse_each_with_3, void, (o_obj arg0, arg0), (o_obj arg1, arg1), (o_obj arg2, arg2), (o_ary_each_with_3_itor itor, itor)
#define O_Array_PUBLIC_METHOD_16 any_p, bool, (o_ary_any_with_0_itor itor, itor)
#define O_Array_PUBLIC_METHOD_17 any_p_with_1, bool, (o_obj arg0, arg0), (o_ary_any_with_1_itor itor, itor)
#define O_Array_PUBLIC_METHOD_18 any_p_with_2, bool, (o_obj arg0, arg0), (o_obj arg1, arg1), (o_ary_any_with_2_itor itor, itor)
#define O_Array_PUBLIC_METHOD_19 any_p_with_3, bool, (o_obj arg0, arg0), (o_obj arg1, arg1), (o_obj arg2, arg2), (o_ary_any_with_3_itor itor, itor)
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
#define O_Array_each_with_1 O_Array_PUBLIC_METHOD_9
#define O_Array_each_with_2 O_Array_PUBLIC_METHOD_10
#define O_Array_each_with_3 O_Array_PUBLIC_METHOD_11
#define O_Array_reverse_each O_Array_PUBLIC_METHOD_12
#define O_Array_reverse_each_with_1 O_Array_PUBLIC_METHOD_13
#define O_Array_reverse_each_with_2 O_Array_PUBLIC_METHOD_14
#define O_Array_reverse_each_with_3 O_Array_PUBLIC_METHOD_15
#define O_Array_any_p O_Array_PUBLIC_METHOD_16
#define O_Array_any_p_with_1 O_Array_PUBLIC_METHOD_17
#define O_Array_any_p_with_2 O_Array_PUBLIC_METHOD_18
#define O_Array_any_p_with_3 O_Array_PUBLIC_METHOD_19
#define O_Array_double_capa O_Array_PRIVATE_METHOD_0
O_DEF_GLOBAL_METHODS()

#endif
