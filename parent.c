#include "include/parent.h"

const void * ParentClass;
static const void * ParentMetaClass;

struct ParentClass {
    const struct Class class;
    void (* parent_method)(void * self);
};

void parent_method(void * self) {
    struct Parent * parent = self;
    const struct ParentClass * class = (struct ParentClass *) parent->class;
    class->parent_method(parent);
}

static void ParentClass_method(void * self) {
    struct Parent * parent = self;
    printf("%d\n", parent->variable);
}

static void * ParentMetaClass_ctor(void * self, va_list * args_ptr) {
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

static void * ParentClass_ctor(void * self, va_list * args_ptr) {
    struct Parent * parent = self;
    parent->variable = va_arg(* args_ptr, int);
    return parent;
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
