#ifndef HASH_H
#define HASH_H

#include <libooc/class.h>

#undef CLASS
#undef PUBLIC_METHODS_PREFIX
#define CLASS Hash
#define PUBLIC_METHODS_PREFIX HASH
#define HASH_PUBLIC_OVERRIDE_METHODS \
    (HASH_ctor), \
    (HASH_dtor)
#define HASH_PUBLIC_METHODS \
    (HASH_set),     \
    (HASH_get),     \
    (HASH_each)
#define HASH_PRIVATE_METHODS \
    (HASH_prime_p),     \
    (HASH_search),     \
    (HASH_rehash)
#define HASH_ctor    ctor,    void,   (va_list * args_ptr, args_ptr)
#define HASH_dtor    dtor,    void
#define HASH_set     set,     bool,   (void * key, key), (void * data, data)
#define HASH_get     get,     void *, (void * key, key)
#define HASH_each    each,    void,   (void (* iter)(void * key, void * data), iter)
#define HASH_prime_p prime_p, bool,   (size_t n, n)
#define HASH_search  search,  bool,   (void * _key, _key), (void * data, data), (void ** ret, ret), (enum ACTION action, action)
#define HASH_rehash  rehash,  void
def_public_methods()

#endif
