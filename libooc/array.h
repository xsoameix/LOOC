#ifndef ARRAY_H
#define ARRAY_H

#include <libooc/class.h>

#undef CLASS
#undef CLASS_UNDERSCORE
#define CLASS Array
#define CLASS_UNDERSCORE array
#define ARRAY_OVERRIDE_METHODS \
    (ARRAY_CTOR), \
    (ARRAY_DTOR)
#define ARRAY_METHODS \
    (ARRAY_LEN),     \
    (ARRAY_GET),     \
    (ARRAY_LAST),    \
    (ARRAY_PUSH),    \
    (ARRAY_POP),     \
    (ARRAY_UNSHIFT), \
    (ARRAY_SHIFT),   \
    (ARRAY_EACH)
#define ARRAY_CTOR ctor, ctor,    void,   (va_list * args_ptr, args_ptr)
#define ARRAY_DTOR dtor, dtor,    void
#define ARRAY_LEN        len,     size_t
#define ARRAY_GET        get,     void *, (size_t index, index)
#define ARRAY_LAST       last,    void *
#define ARRAY_PUSH       push,    void,   (void * data, data)
#define ARRAY_POP        pop,     void *
#define ARRAY_UNSHIFT    unshift, void,   (void * data, data)
#define ARRAY_SHIFT      shift,   void *
#define ARRAY_EACH       each,    void,   (void (* iter)(void * obj, size_t index), iter)
METHODS(ARRAY_METHODS)

#endif
