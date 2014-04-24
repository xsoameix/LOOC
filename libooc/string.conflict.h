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
#define _String_PUBLIC_METHODS \
    (_String_set), \
    (_String_index), \
    (_String_rindex), \
    (_String_strip)
#define _String_PRIVATE_METHODS
#define _String_ctor      ctor,      void,   (va_list * args_ptr, args_ptr)
#define _String_dtor      dtor,      void
#define _String_equals    equals,    bool,   (void * _obj, _obj)
#define _String_hash_code hash_code, size_t
#define _String_inspect   inspect,   char *
#define _String_set set, void, (char * chars, chars)
#define _String_index index, size_t, (bool (* func)(void * _self_, char c), func), (void * _self_, _self_)
#define _String_rindex rindex, size_t, (bool (* func)(void * _self_, char c), func), (void * _self_, _self_)
#define _String_strip strip, void
def_public_methods()

#endif
