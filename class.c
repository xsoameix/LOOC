#include "include/class.h"

size_t size_of(const void * obj) {
    const struct Class * class = obj;
    return class->class->size;
}

void * ctor(void * self, va_list * args) {
    struct Class * class = self;
    return class->class->ctor(class, args);
}

static void * Class_ctor(void * self, va_list * args_ptr) {
    struct Class * class = self;
    class->super = va_arg(* args_ptr, struct Class *);
    class->name = va_arg(* args_ptr, char *);
    class->size = va_arg(* args_ptr, int);
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
        }
    }
    return class;
}

static void Class_dtor(void * self) {
}

static void * ObjectClass_ctor(void * self, va_list * args_ptr) {
    puts("ObjectClass_ctor");
    return self;
}

static const struct Class classes[2] = {
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
        0
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
