#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "object.struct.h"
#include "object_type.h"
#include "inttype.h"

static void         class_ctor       (struct Object * self, va_list * args_ptr);
static void         class_dtor       (struct Object * self);
static void         object_ctor      (struct Object * self, va_list * args_ptr);
static void         object_dtor      (struct Object * self);
static bool         object_equals    (struct Object * self, o obj);
static uint_t       object_hash_code (struct Object * self);
static char *       object_inspect   (struct Object * self);
static const void * object_class     (struct Object * self);
static char *       object_class_name(struct Object * self);
static bool         object_is_a      (struct Object * self, const void * class);

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
        object_inspect,
        object_class,
        object_class_name,
        object_is_a
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
        object_inspect,
        object_class,
        object_class_name,
        object_is_a
    }
};

const void * Class = classes;
const void * Object = classes + 1;

o
new(const void * klass, ...) {
    const struct ObjectClass * class = klass;
    va_list args;
    va_start(args, klass);
    struct Object * obj;
    if(class->is_variable_size) {
        class->ctor((o) &obj, &args);
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
delete(o obj) {
    const struct Object * object = obj;
    object->class->dtor(obj);
}

// #constructor

void
Object_ctor(o self, va_list * args_ptr) {
    struct Object * class = self;
    class->class->ctor(class, args_ptr);
}

static void
object_ctor(struct Object * self, va_list * args_ptr) {
}

static void
class_ctor(struct Object * self, va_list * args_ptr) {

    struct ObjectClass * class = (struct ObjectClass *) self;
    class->super = va_arg(* args_ptr, struct ObjectClass *);
    class->name = va_arg(* args_ptr, char *);
    class->size = va_arg(* args_ptr, uint_t);
    class->is_variable_size = va_arg(* args_ptr, uint_t);
    uint_t offset = offsetof(struct ObjectClass, ctor);

    uint_t size_of(const void * obj) {
        const struct Object * object = obj;
        return object->class->size;
    }

    // inherit
    memcpy((char *) class + offset,
            (char *) class->super + offset,
            size_of(class->super) - offset);

    // override
    va_list args;
    va_copy(args, * args_ptr);
    typedef void (* func)(void);
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
        } else if(select == (func) Object_class) {
            *(func *) &class->class = method;
        } else if(select == (func) Object_class_name) {
            *(func *) &class->class_name = method;
        } else if(select == (func) Object_is_a) {
            *(func *) &class->is_a = method;
        }
    }
}

// #destructor

void
Object_dtor(o self) {
    // Please use delete() instead.
}

static void
object_dtor(struct Object * self) {
    free(self);
}

static void
class_dtor(struct Object * self) {
}

// #equals

bool
Object_equals(o self, o obj) {
    struct Object * class = self;
    return class->class->equals(class, obj);
}

static bool
object_equals(struct Object * self, o obj) {
    return self == obj;
}

// #hash_code

uint_t
Object_hash_code(o self) {
    struct Object * class = self;
    return class->class->hash_code(class);
}

static uint_t
object_hash_code(struct Object * self) {
    return (uint_t) self;
}

// #inspect

char *
Object_inspect(o self) {
    struct Object * class = self;
    return class->class->inspect(class);
}

static char *
object_inspect(struct Object * self) {
    return self->class->name;
}

// #class

const void *
Object_class(o self) {
    struct Object * class = self;
    return class->class->class(class);
}

static const void *
object_class(struct Object * self) {
    return self->class;
}

// #class_name

char *
Object_class_name(o self) {
    struct Object * class = self;
    return class->class->class_name(class);
}

static char *
object_class_name(struct Object * self) {
    return self->class->name;
}

// #is_a

bool
Object_is_a(o self, const void * class) {
    struct Object * klass = self;
    return klass->class->is_a(klass, class);
}

static bool
object_is_a(struct Object * self, const void * class) {
    struct ObjectClass * klass = (o) self->class;
    while(klass != class && klass->super) {
        klass = (o) klass->super;
    }
    return klass == class;
}
