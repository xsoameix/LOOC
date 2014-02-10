#ifndef CLASS_H
#define CLASS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <string.h>

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

extern const void * Class;
extern const void * ObjectClass;

size_t size_of(const void * obj);
void * ctor(void * self, va_list * args);
void * new(const void * klass, ...);

#endif
