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
    void   (* dtor)(void * self);
};

struct Object {
    const struct Class * class;
};

void * ctor(void * self, va_list * args);
void   dtor(void * self);
size_t size_of(const void * obj);
const void * super_of(const void * obj);
char * class_name_of(const void * obj);

#endif
