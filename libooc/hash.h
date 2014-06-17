#ifndef HASH_H
#define HASH_H

#include <libooc/object.h>


#undef CLASS
#define CLASS Hash
#define _Hash_PUBLIC_OVERRIDE_METHODS \
    (_Hash_ctor), \
    (_Hash_dtor)
#define _Hash_PUBLIC_METHODS \
    (_Hash_len), \
    (_Hash_set), \
    (_Hash_get), \
    (_Hash_intersact_p), \
    (_Hash_each)
#define _Hash_PRIVATE_METHODS \
    (_Hash_prime_p), \
    (_Hash_search), \
    (_Hash_rehash)
#define _Hash_ctor ctor, void, (va_list * args_ptr, args_ptr)
#define _Hash_dtor dtor, void
#define _Hash_len len, size_t
#define _Hash_set set, bool, (void * key, key), (void * data, data)
#define _Hash_get get, void *, (void * key, key)
#define _Hash_intersact_p intersact_p, bool, (void * set, set)
#define _Hash_each each, void, (void (* iter)(void * _self_, void * key, void * data), iter), (void * _self_, _self_)
#define _Hash_prime_p prime_p, bool, (size_t n, n)
#define _Hash_search search, bool, (void * _key, _key), (void * data, data), (void ** ret, ret), (enum ACTION action, action)
#define _Hash_rehash rehash, void
def_public_methods()

#endif
