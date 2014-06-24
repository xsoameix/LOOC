#ifndef O_OBJECT_STRUCT_H
#define O_OBJECT_STRUCT_H

#include "object.h"

struct Object;

struct ObjectClass {
    const struct ObjectClass * metaclass;
    const struct ObjectClass * super;
    char * name;
    o_uint size;
    o_uint is_variable_size;
    void         (* ctor)      (struct Object * self, va_list * args);
    void         (* dtor)      (struct Object * self);
    bool         (* equals)    (struct Object * self, o_obj obj);
    o_uint       (* hash_code) (struct Object * self);
    char *       (* inspect)   (struct Object * self);
    const void * (* class)     (struct Object * self);
    char *       (* class_name)(struct Object * self);
    bool         (* is_a)      (struct Object * self, const void * class);
};

struct Object {
    const struct ObjectClass * class;
};

extern const void * Class;
extern const void * Object;

void         Object_ctor      (o_obj self, va_list * args);
void         Object_dtor      (o_obj self);
bool         Object_equals    (o_obj self, o_obj obj);
o_uint       Object_hash_code (o_obj self);
char *       Object_inspect   (o_obj self);
const void * Object_class     (o_obj self);
char *       Object_class_name(o_obj self);
bool         Object_is_a      (o_obj self, const void * class);

static void         ctor      (struct Object * self, va_list * args_ptr) __attribute__((weakref("Object_ctor")));
static void         dtor      (struct Object * self)                     __attribute__((weakref("Object_dtor")));
static bool         equals    (struct Object * self, o_obj obj)          __attribute__((weakref("Object_equals")));
static o_uint       hash_code (struct Object * self)                     __attribute__((weakref("Object_hash_code")));
static char *       inspect   (struct Object * self)                     __attribute__((weakref("Object_inspect")));
static const void * class     (struct Object * self)                     __attribute__((weakref("Object_class")));
static char *       class_name(struct Object * self)                     __attribute__((weakref("Object_class_name")));
static bool         is_a      (struct Object * self, const void * class) __attribute__((weakref("Object_is_a")));

#endif
