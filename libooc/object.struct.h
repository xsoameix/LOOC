#ifndef O_OBJECT_STRUCT_H
#define O_OBJECT_STRUCT_H

#include "object.h"

struct ObjectClass {
    const struct ObjectClass * class;
    const struct ObjectClass * super;
    char *   name;
    ooc_uint size;
    ooc_uint is_variable_size;
    void     (* ctor)(void * self, va_list * args);
    void     (* dtor)(void * self);
    bool     (* equals)(void * self, void * obj);
    ooc_uint (* hash_code)(void * self);
    char *   (* inspect)(void * self);
};

struct Object {
    const struct ObjectClass * class;
};

extern const void * Class;
extern const void * Object;

void     Object_ctor(void * self, va_list * args);
void     Object_dtor(void * self);
bool     Object_equals(void * self, void * obj);
ooc_uint Object_hash_code(void * self);
char *   Object_inspect(void * self);

static void     ctor(struct Object * self, va_list * args_ptr) __attribute__((weakref("Object_ctor")));
static void     dtor(struct Object * self) __attribute__((weakref("Object_dtor")));
static bool     equals(struct Object * self, void * obj) __attribute__((weakref("Object_equals")));
static ooc_uint hash_code(struct Object * self) __attribute__((weakref("Object_hash_code")));
static char *   inspect(struct Object * self) __attribute__((weakref("Object_inspect")));

#endif
