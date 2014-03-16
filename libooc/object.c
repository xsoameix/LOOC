#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "object.struct.h"

static void   class_ctor(void * self, va_list * args_ptr);
static void   class_dtor(void * self);
static void   object_ctor(void * self, va_list * args_ptr);
static void   object_dtor(void * self);
static bool   object_equals(void * self, void * obj);
static size_t object_hash_code(void * self);
static char * object_inspect(void * self);
static size_t size_of(const void * obj);

static struct ObjectClass classes[2] = {
    {
        classes,
        classes + 1,
        "Class",
        sizeof(struct ObjectClass),
        false,
        class_ctor,
        class_dtor,
        object_equals,
        object_hash_code,
        object_inspect
    }, {
        classes,
        0,
        "Object",
        sizeof(struct Object),
        false,
        object_ctor,
        object_dtor,
        object_equals,
        object_hash_code,
        object_inspect
    }
};

const void * Class = classes;
const void * Object = classes + 1;

void *
new(const void * klass, ...) {
    const struct ObjectClass * class = klass;
    va_list args;
    va_start(args, klass);
    struct ObjectClass * obj;
    if(class->is_variable_size) {
        class->ctor(&obj, &args);
        obj->class = class;
    } else {
        obj = malloc(class->size);
        obj->class = class;
        class->ctor(obj, &args);
    }
    va_end(args);
    return obj;
}

void
delete(void * obj) {
    const struct Object * object = obj;
    object->class->dtor(obj);
}

void
Object_ctor(void * self, va_list * args_ptr) {
    struct ObjectClass * class = self;
    class->class->ctor(class, args_ptr);
}

static void
object_ctor(void * self, va_list * args_ptr) {
}

static void
class_ctor(void * self, va_list * args_ptr) {
    struct ObjectClass * class = self;
    class->super = va_arg(* args_ptr, struct ObjectClass *);
    class->name = va_arg(* args_ptr, char *);
    class->size = va_arg(* args_ptr, size_t);
    class->is_variable_size = va_arg(* args_ptr, size_t);
    size_t offset = offsetof(struct ObjectClass, ctor);

    // inherit
    memcpy((char *) class + offset,
            (char *) class->super + offset,
            size_of(class->super) - offset);

    // override
    va_list args;
    va_copy(args, * args_ptr);
    typedef void (* func)();
    func select, method;
    while(select = va_arg(args, func)) {
        method = va_arg(args, func);
        if(select == (func) Object_ctor) {
            *(func *) &class->ctor = method;
        } else if(select == (func) Object_dtor) {
            *(func *) &class->dtor = method;
        } else if(select == (func) Object_equals) {
            *(func *) &class->equals = method;
        } else if(select == (func) Object_hash_code) {
            *(func *) &class->hash_code = method;
        } else if(select == (func) Object_inspect) {
            *(func *) &class->inspect = method;
        }
    }
}

void
Object_dtor(void * self) {
    // Please use delete() instead.
}

static void
object_dtor(void * self) {
    free(self);
}

static void
class_dtor(void * self) {
}

bool
Object_equals(void * self, void * obj) {
    struct ObjectClass * class = self;
    return class->class->equals(class, obj);
}

static bool
object_equals(void * self, void * obj) {
    return self == obj;
}

size_t
Object_hash_code(void * self) {
    struct ObjectClass * class = self;
    return class->class->hash_code(class);
}

static size_t
object_hash_code(void * self) {
    return (size_t) self;
}

char *
Object_inspect(void * self) {
    struct ObjectClass * class = self;
    return class->class->inspect(class);
}

static char *
object_inspect(void * self) {
    struct Object * object = self;
    return object->class->name;
}

static size_t
size_of(const void * obj) {
    const struct Object * object = obj;
    return object->class->size;
}
