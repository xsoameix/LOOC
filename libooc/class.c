#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "class.struct.h"
#include "class.h"

static void   Class_ctor(void * self, va_list * args_ptr);
static void   Class_dtor(void * self);
static void   Object_ctor(void * self, va_list * args_ptr);
static void   Object_dtor(void * self);
static bool   Object_equals(void * self, void * obj);
static size_t Object_hash_code(void * self);
static char * Object_inspect(void * self);
static size_t size_of(const void * obj);

static struct Class classes[2] = {
    {
        classes,
        classes + 1,
        "Class",
        sizeof(struct Class),
        false,
        Class_ctor,
        Class_dtor,
        Object_equals,
        Object_hash_code,
        Object_inspect
    }, {
        classes,
        0,
        "Object",
        sizeof(struct Object),
        false,
        Object_ctor,
        Object_dtor,
        Object_equals,
        Object_hash_code,
        Object_inspect
    }
};

const void * Class = classes;
const void * Object = classes + 1;

void *
new(const void * klass, ...) {
    const struct Class * class = klass;
    va_list args;
    va_start(args, klass);
    struct Class * obj;
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
ctor(void * self, va_list * args_ptr) {
    struct Class * class = self;
    class->class->ctor(class, args_ptr);
}

static void
Class_ctor(void * self, va_list * args_ptr) {
    struct Class * class = self;
    class->super = va_arg(* args_ptr, struct Class *);
    class->name = va_arg(* args_ptr, char *);
    class->size = va_arg(* args_ptr, size_t);
    class->is_variable_size = va_arg(* args_ptr, size_t);
    size_t offset = offsetof(struct Class, ctor);

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
        if(select == (func) ctor) {
            *(func *) &class->ctor = method;
        } else if(select == (func) dtor) {
            *(func *) &class->dtor = method;
        } else if(select == (func) equals) {
            *(func *) &class->equals = method;
        } else if(select == (func) hash_code) {
            *(func *) &class->hash_code = method;
        } else if(select == (func) inspect) {
            *(func *) &class->inspect = method;
        }
    }
}

void
dtor(void * self) {
}

static void
Class_dtor(void * self) {
}

static void
Object_ctor(void * self, va_list * args_ptr) {
}

static void
Object_dtor(void * self) {
    free(self);
}

bool
equals(void * self, void * obj) {
    struct Class * class = self;
    return class->class->equals(class, obj);
}

static bool
Object_equals(void * self, void * obj) {
    return self == obj;
}

size_t
hash_code(void * self) {
    struct Class * class = self;
    return class->class->hash_code(class);
}

static size_t
Object_hash_code(void * self) {
    return (size_t) self;
}

char *
inspect(void * self) {
    struct Class * class = self;
    return class->class->inspect(class);
}

static char *
Object_inspect(void * self) {
    struct Object * object = self;
    return object->class->name;
}

static size_t
size_of(const void * obj) {
    const struct Object * object = obj;
    return object->class->size;
}

const void *
super_of(const void * obj) {
    const struct Object * object = obj;
    return object->class->super;
}
