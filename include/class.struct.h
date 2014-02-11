#ifndef CLASS_STRUCT_H
#define CLASS_STRUCT_H

#include <stdarg.h>
#include <stddef.h>

struct Class {
    const struct Class * class;
    const struct Class * super;
    char * name;
    size_t size;
    void * (* ctor)(void * self, va_list * args);
    void (* dtor)(void * self);
};

struct Object {
    const struct Class * class;
};

#endif
