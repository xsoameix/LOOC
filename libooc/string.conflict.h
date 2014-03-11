#ifndef STRING_H
#define STRING_H

#include <libooc/class.h>

#undef CLASS
#undef PUBLIC_METHODS_PREFIX
#define CLASS String
#define PUBLIC_METHODS_PREFIX STRING
#define STRING_OVERRIDE_METHODS \
    (STRING_ctor),      \
    (STRING_dtor),      \
    (STRING_equals),    \
    (STRING_hash_code), \
    (STRING_inspect)
#define STRING_METHODS \
    (STRING_puts)
#define STRING_ctor      ctor,      void,   (va_list * args_ptr, args_ptr)
#define STRING_dtor      dtor,      void
#define STRING_equals    equals,    bool,   (struct String * obj, obj)
#define STRING_hash_code hash_code, size_t
#define STRING_inspect   inspect,   char *
#define STRING_puts      puts,      void
def_public_methods()

#endif
