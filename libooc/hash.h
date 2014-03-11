#ifndef HASH_H
#define HASH_H

#include <libooc/class.h>

#undef CLASS
#undef PUBLIC_METHODS_PREFIX
#define CLASS Hash
#define PUBLIC_METHODS_PREFIX HASH
#define HASH_OVERRIDE_METHODS \
    (HASH_ctor), \
    (HASH_dtor)
#define HASH_METHODS \
    (HASH_set),     \
    (HASH_get),     \
    (HASH_each)
#define HASH_ctor    ctor, void,   (va_list * args_ptr, args_ptr)
#define HASH_dtor    dtor, void
#define HASH_set     set,  bool,   (void * key, key), (void * data, data)
#define HASH_get     get,  void *, (void * key, key)
#define HASH_each    each, void,   (void (* iter)(void * key, void * data), iter)
def_public_methods()

#endif
