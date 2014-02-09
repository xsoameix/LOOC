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

struct ParentClass {
    const struct Class class;
    void (* parent_method)(void * self);
};

struct Parent {
    const struct Class * class;
    int variable;
};

size_t size_of(const void * obj) {
    const struct Class * class = obj;
    return class->class->size;
}

void * ctor(void * self, va_list * args) {
    struct Class * class = self;
    return class->class->ctor(class, args);
}

void * Class_ctor(void * self, va_list * args_ptr) {
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

void Class_dtor(void * self) {
}

void * ObjectClass_ctor(void * self, va_list * args_ptr) {
    puts("ObjectClass_ctor");
    return self;
}

const void * ParentMetaClass;
const void * ParentClass;

void parent_method(void * self) {
    struct Parent * parent = self;
    const struct ParentClass * class = (struct ParentClass *) parent->class;
    class->parent_method(parent);
}

void ParentClass_method(void * self) {
    struct Parent * parent = self;
    printf("%d", parent->variable);
}

void * ParentMetaClass_ctor(void * self, va_list * args_ptr) {
    struct ParentClass * class = self;
    const struct Class * metaclass = ParentMetaClass;
    metaclass->super->ctor(class, args_ptr);

    // override
    va_list args;
    va_copy(args, * args_ptr);
    typedef void (* func)();
    func select;
    while(select = va_arg(args, func)) {
        func method = va_arg(args, func);
        if(select == (func) parent_method) {
            *(func *) &class->parent_method = method;
        }
    }
    return class;
}

void * ParentClass_ctor(void * self, va_list * args_ptr) {
    struct Parent * parent = self;
    parent->variable = va_arg(* args_ptr, int);
    return parent;
}

struct Class classes[2] = {
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

void init_Parent(void) {
    if(!ParentMetaClass) {
        ParentMetaClass = new(
                Class,
                Class,
                "ParentMetaClass",
                sizeof(struct ParentClass),
                ctor, ParentMetaClass_ctor);
    }
    if(!ParentClass) {
        ParentClass = new(
                ParentMetaClass,
                ObjectClass,
                "ParentClass",
                sizeof(struct Parent),
                ctor, ParentClass_ctor,
                parent_method, ParentClass_method);
    }
}

int main(void) {
    init_Parent();
    struct Parent * parent = new(ParentClass, 2);
    parent_method(parent);
    return 0;
}
