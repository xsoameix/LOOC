#ifndef STRING_H
#define STRING_H

#include <libooc/object.h>

#undef CLASS
#define CLASS String
#define _String_PUBLIC_OVERRIDE_METHODS \
    (_String_ctor),      \
    (_String_dtor),      \
    (_String_equals),    \
    (_String_hash_code), \
    (_String_inspect)
#define _String_PUBLIC_METHODS
#define _String_PRIVATE_METHODS
#define _String_ctor      ctor,      void,   (va_list * args_ptr, args_ptr)
#define _String_dtor      dtor,      void
#define _String_equals    equals,    bool,   (void * _obj, _obj)
#define _String_hash_code hash_code, size_t
#define _String_inspect   inspect,   char *
def_public_methods()

#endif
