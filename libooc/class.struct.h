#ifndef CLASS_STRUCT_H
#define CLASS_STRUCT_H

#include <stdarg.h>
#include <stddef.h>
#include <stdbool.h>
#include <libooc/class_macro.h>

struct ObjectClass {
    const struct ObjectClass * class;
    const struct ObjectClass * super;
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
    const struct ObjectClass * class;
};

static void   ctor(struct Object * self, va_list * args_ptr) __attribute__((weakref("Object_ctor")));
static void   dtor(struct Object * self) __attribute__((weakref("Object_dtor")));
static bool   equals(struct Object * self, void * obj) __attribute__((weakref("Object_equals")));
static size_t hash_code(struct Object * self) __attribute__((weakref("Object_hash_code")));
static char * inspect(struct Object * self) __attribute__((weakref("Object_inspect")));

#endif
