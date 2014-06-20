#ifndef O_HASH_H
#define O_HASH_H

#include <libooc/object.h>
// Please put included files here.
// Please put macros/type declarations here.


#undef O_CLASS
#undef O_PARENT
#define O_CLASS Hash
#define O_PARENT Object
#define O_Hash_OVERRIDE_METHODS_LEN 2
#define O_Hash_PUBLIC_METHODS_LEN 5
#define O_Hash_PRIVATE_METHODS_LEN 3
#define O_Hash_OVERRIDE_METHOD_0 ctor, void, (va_list * args_ptr, args_ptr)
#define O_Hash_OVERRIDE_METHOD_1 dtor, void
#define O_Hash_PUBLIC_METHOD_0 len, ooc_uint
#define O_Hash_PUBLIC_METHOD_1 set, bool, (void * key, key), (void * data, data)
#define O_Hash_PUBLIC_METHOD_2 get, void *, (void * key, key)
#define O_Hash_PUBLIC_METHOD_3 intersact_p, bool, (void * set, set)
#define O_Hash_PUBLIC_METHOD_4 each, void, (void (* iter)(void * _self_, void * key, void * data), iter), (void * _self_, _self_)
#define O_Hash_PRIVATE_METHOD_0 prime_p, bool, (ooc_uint n, n)
#define O_Hash_PRIVATE_METHOD_1 search, bool, (void * _key, _key), (void * data, data), (void ** ret, ret), (enum ACTION action, action)
#define O_Hash_PRIVATE_METHOD_2 rehash, void
#define O_Hash_ctor O_Hash_OVERRIDE_METHOD_0
#define O_Hash_dtor O_Hash_OVERRIDE_METHOD_1
#define O_Hash_len O_Hash_PUBLIC_METHOD_0
#define O_Hash_set O_Hash_PUBLIC_METHOD_1
#define O_Hash_get O_Hash_PUBLIC_METHOD_2
#define O_Hash_intersact_p O_Hash_PUBLIC_METHOD_3
#define O_Hash_each O_Hash_PUBLIC_METHOD_4
#define O_Hash_prime_p O_Hash_PRIVATE_METHOD_0
#define O_Hash_search O_Hash_PRIVATE_METHOD_1
#define O_Hash_rehash O_Hash_PRIVATE_METHOD_2
O_DEF_GLOBAL_METHODS()

#endif
