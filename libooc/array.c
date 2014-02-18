#include <stdlib.h>
#include <string.h>

#include "array.struct.h"
#include "array.h"

struct ArrayClass {
    const struct Class class;
    void (* array_push)(void * self, void * data);
    void (* array_each)(void * self, void (* iter)(void * obj, size_t index));
};

static const void * ArrayClass;
       const void * Array;
static const void * ArrayValues;

static void * ArrayClass_ctor(void * self, va_list * args_ptr);
static void * Array_ctor(void * self, va_list * args_ptr);
static void   Array_dtor(void * self);
static void   Array_push(void * self, void * data);
static void   Array_each(void * self, void (* iter)(void * obj, size_t index));
static void * ArrayValues_ctor(void * _self, va_list * args_ptr);
static void   ArrayValues_dtor(void * self);

void
array_init(void) {
    if(!ArrayClass) {
        ArrayClass = new(
                Class,
                Class,
                "ArrayClass",
                sizeof(struct ArrayClass),
                ctor,       ArrayClass_ctor);
    }
    if(!Array) {
        Array = new(
                ArrayClass,
                Object,
                "Array",
                sizeof(struct Array),
                ctor,       Array_ctor,
                dtor,       Array_dtor,
                array_push, Array_push,
                array_each, Array_each);
    }
    if(!ArrayValues) {
        ArrayValues = new(
                Class,
                Object,
                "ArrayValues",
                sizeof(struct ArrayValues),
                ctor,       ArrayValues_ctor,
                dtor,       ArrayValues_dtor);
    }
}

static void *
ArrayClass_ctor(void * self, va_list * args_ptr) {
    struct ArrayClass * class = self;

    // inherit
    const struct Class * superclass = super_of(class);
    superclass->ctor(class, args_ptr);

    // override
    va_list args;
    va_copy(args, * args_ptr);
    typedef void (* func)();
    func select;
    while(select = va_arg(args, func)) {
        func method = va_arg(args, func);
        if(select == (func) array_push) {
            *(func *) &class->array_push = method;
        } else if(select == (func) array_each) {
            *(func *) &class->array_each = method;
        }
    }
    return class;
}

static void *
Array_ctor(void * self, va_list * args_ptr) {
    struct Array * ary = self;
    ary->len = 0;
    ary->capa = 3;
    ary->values = new(ArrayValues, ary->capa);
    return ary;
}

static void
Array_dtor(void * self) {
    struct Array * ary = self;
    delete(ary->values);
}

void
array_push(void * self, void * data) {
    struct Array * ary = self;
    const struct ArrayClass * class = (struct ArrayClass *) ary->class;
    return class->array_push(ary, data);
}

static void
Array_push(void * self, void * data) {
    struct Array * ary = self;
    if(ary->len == ary->capa) {
        size_t len = ary->len * 2;
        struct ArrayValues * values = new(ArrayValues, len);
        memcpy(values->values, ary->values, ary->len * sizeof(void *));
        delete(ary->values);
        ary->values = values;
        ary->len = len;
    }
    ary->values->values[ary->len++] = data;
}

void
array_each(void * self, void (* iter)(void * obj, size_t index)) {
    struct Array * ary = self;
    const struct ArrayClass * class = (struct ArrayClass *) ary->class;
    return class->array_each(ary, iter);
}

static void
Array_each(void * self, void (* iter)(void * obj, size_t index)) {
    struct Array * ary = self;
    void ** values = ary->values->values;
    for(size_t i = 0; i < ary->len; i++) {
        iter(values[i], i);
    }
}

static void *
ArrayValues_ctor(void * _self, va_list * args_ptr) {
    struct ArrayValues * self = _self;
    size_t len = va_arg(* args_ptr, size_t);
    self->values = malloc(len * sizeof(void *));
    return self;
}

static void
ArrayValues_dtor(void * self) {
    struct ArrayValues * values = self;
    free(values->values);
}
