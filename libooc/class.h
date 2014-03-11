#ifndef CLASS_H
#define CLASS_H

#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <libooc/class_macro.h>

#undef CLASS
#define CLASS Object
#define _Object_PUBLIC_OVERRIDE_METHODS
#define _Object_PUBLIC_METHODS \
    (_Object_ctor),      \
    (_Object_dtor),      \
    (_Object_equals),    \
    (_Object_hash_code), \
    (_Object_inspect)
#define _Object_PRIVATE_METHODS
#define _Object_ctor      ctor,       void,   (va_list * args_ptr, args_ptr)
#define _Object_dtor      dtor,       void
#define _Object_equals    equals,     bool,   (void * obj, obj)
#define _Object_hash_code hash_code,  size_t
#define _Object_inspect   inspect,    char *

extern const void * Class;
extern const void * Object;

void * new(const void * klass, ...);
void   delete(void * obj);
void   Object_ctor(void * self, va_list * args);
void   Object_dtor(void * self);
bool   Object_equals(void * self, void * obj);
size_t Object_hash_code(void * self);
char * Object_inspect(void * self);

#endif
