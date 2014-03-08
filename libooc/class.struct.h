#ifndef CLASS_STRUCT_H
#define CLASS_STRUCT_H

#include <stdarg.h>
#include <stddef.h>
#include <stdbool.h>

struct Class {
    const struct Class * class;
    const struct Class * super;
    char * name;
    size_t size;
    size_t is_variable_size;
    void   (* ctor)(void * self, va_list * args);
    void   (* dtor)(void * self);
    bool   (* equals)(void * self, void * obj);
    size_t (* hash_code)(void * self);
    char * (* inspect)(void * self);
};

struct Object {
    const struct Class * class;
};

#endif
