#ifndef O_HASH_H
#define O_HASH_H

#include <libooc/object.h>

// Please put included files here.


// Please put macros/type declarations here.
#define O_HASH_ITOR(name, ...) void O_HASH_ITOR_NAME(name)(o_obj O_HASH_KEY, o_obj O_HASH_VALUE, ## __VA_ARGS__)
#define O_HASH_ITOR_NAME(name) O_STR_CAT(__o_hash_itor_, name)
#define O_HASH_EACH(...) O_DEFAULT_ARG(O_HASH_EACH_, __VA_ARGS__)
#define O_HASH_EACH_2(hash, name) Hash_each(hash, O_HASH_ITOR_NAME(name))
#define O_HASH_EACH_3(hash, name, ...) Hash_each_with_1(hash, __VA_ARGS__, O_HASH_ITOR_NAME(name))
#define O_HASH_EACH_4(hash, name, ...) Hash_each_with_2(hash, __VA_ARGS__, O_HASH_ITOR_NAME(name))
#define O_HASH_EACH_5(hash, name, ...) Hash_each_with_3(hash, __VA_ARGS__, O_HASH_ITOR_NAME(name))
#define O_HASH_KEY __o_obj_key
#define O_HASH_VALUE __o_obj_value
#define O_HASH_GET(...) Hash_get(__VA_ARGS__)
#define O_HASH_SET(...) Hash_set(__VA_ARGS__)
#define O_HASH_KEYS(...) Hash_keys(__VA_ARGS__)
#define O_HASH_VALUES(...) Hash_values(__VA_ARGS__)

typedef void (* o_hash_each_with_0_itor)(o_obj key, o_obj value);
typedef void (* o_hash_each_with_1_itor)(o_obj key, o_obj value, o_obj arg);
typedef void (* o_hash_each_with_2_itor)(o_obj key, o_obj value, o_obj arg, o_obj arg2);
typedef void (* o_hash_each_with_3_itor)(o_obj key, o_obj value, o_obj arg, o_obj arg2, o_obj arg3);


#undef O_CLASS
#undef O_PARENT
#define O_CLASS Hash
#define O_PARENT Object
#define O_Hash_OVERRIDE_METHODS_LEN 2
#define O_Hash_PUBLIC_METHODS_LEN 10
#define O_Hash_PRIVATE_METHODS_LEN 3
#define O_Hash_OVERRIDE_METHOD_0 ctor, void, (va_list * args_ptr, args_ptr)
#define O_Hash_OVERRIDE_METHOD_1 dtor, void
#define O_Hash_PUBLIC_METHOD_0 len, o_uint
#define O_Hash_PUBLIC_METHOD_1 set, bool, (o_obj key, key), (o_obj data, data)
#define O_Hash_PUBLIC_METHOD_2 get, o_obj, (o_obj key, key)
#define O_Hash_PUBLIC_METHOD_3 intersact_p, bool, (o_obj _set, _set)
#define O_Hash_PUBLIC_METHOD_4 each, void, (o_hash_each_with_0_itor itor, itor)
#define O_Hash_PUBLIC_METHOD_5 each_with_1, void, (o_obj arg0, arg0), (o_hash_each_with_1_itor itor, itor)
#define O_Hash_PUBLIC_METHOD_6 each_with_2, void, (o_obj arg0, arg0), (o_obj arg1, arg1), (o_hash_each_with_2_itor itor, itor)
#define O_Hash_PUBLIC_METHOD_7 each_with_3, void, (o_obj arg0, arg0), (o_obj arg1, arg1), (o_obj arg2, arg2), (o_hash_each_with_3_itor itor, itor)
#define O_Hash_PUBLIC_METHOD_8 keys, o_obj
#define O_Hash_PUBLIC_METHOD_9 values, o_obj
#define O_Hash_PRIVATE_METHOD_0 prime_p, bool, (o_uint n, n)
#define O_Hash_PRIVATE_METHOD_1 search, bool, (o_obj _key, _key), (o_obj data, data), (o_obj * ret, ret), (enum ACTION action, action)
#define O_Hash_PRIVATE_METHOD_2 rehash, void
#define O_Hash_ctor O_Hash_OVERRIDE_METHOD_0
#define O_Hash_dtor O_Hash_OVERRIDE_METHOD_1
#define O_Hash_len O_Hash_PUBLIC_METHOD_0
#define O_Hash_set O_Hash_PUBLIC_METHOD_1
#define O_Hash_get O_Hash_PUBLIC_METHOD_2
#define O_Hash_intersact_p O_Hash_PUBLIC_METHOD_3
#define O_Hash_each O_Hash_PUBLIC_METHOD_4
#define O_Hash_each_with_1 O_Hash_PUBLIC_METHOD_5
#define O_Hash_each_with_2 O_Hash_PUBLIC_METHOD_6
#define O_Hash_each_with_3 O_Hash_PUBLIC_METHOD_7
#define O_Hash_keys O_Hash_PUBLIC_METHOD_8
#define O_Hash_values O_Hash_PUBLIC_METHOD_9
#define O_Hash_prime_p O_Hash_PRIVATE_METHOD_0
#define O_Hash_search O_Hash_PRIVATE_METHOD_1
#define O_Hash_rehash O_Hash_PRIVATE_METHOD_2
O_DEF_GLOBAL_METHODS()

#endif
