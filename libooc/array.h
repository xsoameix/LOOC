#ifndef ARRAY_H
#define ARRAY_H

#include <libooc/class.h>

#undef CLASS
#undef PUBLIC_METHODS_PREFIX
#define CLASS Array
#define PUBLIC_METHODS_PREFIX ARRAY
#define ARRAY_PUBLIC_OVERRIDE_METHODS \
    (ARRAY_ctor), \
    (ARRAY_dtor)
#define ARRAY_PUBLIC_METHODS \
    (ARRAY_len),     \
    (ARRAY_get),     \
    (ARRAY_last),    \
    (ARRAY_push),    \
    (ARRAY_pop),     \
    (ARRAY_unshift), \
    (ARRAY_shift),   \
    (ARRAY_each)
#define ARRAY_PRIVATE_METHODS \
    (ARRAY_double_capa)
#define ARRAY_ctor        ctor,        void,   (va_list * args_ptr, args_ptr)
#define ARRAY_dtor        dtor,        void
#define ARRAY_len         len,         size_t
#define ARRAY_get         get,         void *, (size_t index, index)
#define ARRAY_last        last,        void *
#define ARRAY_push        push,        void,   (void * data, data)
#define ARRAY_pop         pop,         void *
#define ARRAY_unshift     unshift,     void,   (void * data, data)
#define ARRAY_shift       shift,       void *
#define ARRAY_each        each,        void,   (void (* iter)(void * obj, size_t index), iter)
#define ARRAY_double_capa double_capa, void,   (size_t offset, offset)
def_public_methods()

#endif
