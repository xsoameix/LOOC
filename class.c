#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "include/class.struct.h"
#include "include/class.h"

static void * Class_ctor(void * self, va_list * args_ptr);
static void   Class_dtor(void * self);
static void * ObjectClass_ctor(void * self, va_list * args_ptr);
static void   ObjectClass_dtor(void * self);

static struct Class classes[2] = {
    {
        classes,
        classes + 1,
        "Class",
        sizeof(struct Class),
        Class_ctor,
        Class_dtor
    }, {
        classes,
        0,
        "ObjectClass",
        sizeof(struct Object),
        ObjectClass_ctor,
        ObjectClass_dtor
    }
};

const void * Class = classes;
const void * ObjectClass = classes + 1;

void * new(const void * klass, ...) {
    const struct Class * class = klass;
    va_list args;
    va_start(args, klass);
    struct Class * obj = malloc(class->size);
    obj->class = class;
    ctor(obj, &args);
    va_end(args);
    return obj;
}

void delete(void * obj) {
    const struct Object * object = obj;
    dtor(obj);
    free(obj);
}

void * ctor(void * self, va_list * args) {
    struct Class * class = self;
    return class->class->ctor(class, args);
}

void dtor(void * self) {
    struct Class * class = self;
    return class->class->dtor(class);
}

size_t size_of(const void * obj) {
    const struct Object * object = obj;
    return object->class->size;
}

const void * super_of(const void * obj) {
    const struct Object * object = obj;
    return object->class->super;
}

char * class_name_of(const void * obj) {
    const struct Object * object = obj;
    return object->class->name;
}

static
void * Class_ctor(void * self, va_list * args_ptr) {
    struct Class * class = self;
    class->super = va_arg(* args_ptr, struct Class *);
    class->name = va_arg(* args_ptr, char *);
    class->size = va_arg(* args_ptr, size_t);
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
        }
    }
    return class;
}

static
void Class_dtor(void * self) {
}

static
void * ObjectClass_ctor(void * self, va_list * args_ptr) {
    return self;
}

static
void ObjectClass_dtor(void * self) {
}
