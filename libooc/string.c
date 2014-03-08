#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "string.struct.h"
#include "string.conflict.h"

struct StringClass {
    const struct Class class;
    void   (* string_puts)(void * self);
};

static const void * StringClass;
       const void * String;

static void   StringClass_ctor(void * self, va_list * args_ptr);
static void   String_ctor(void * self, va_list * args_ptr);
static void   String_dtor(void * self);
static bool   String_equals(void * _self, void * _obj);
static size_t String_hash_code(void * self);
static char * String_inspect(void * self);
static void   String_puts(void * self);

void
string_init(void) {
    if(!StringClass) {
        StringClass = new(
                Class,
                Class,
                "StringClass",
                sizeof(struct StringClass),
                false,
                ctor,        StringClass_ctor,
                0);
    }
    if(!String) {
        String = new(
                StringClass,
                Object,
                "String",
                sizeof(struct String),
                false,
                ctor,        String_ctor,
                dtor,        String_dtor,
                equals,      String_equals,
                hash_code,   String_hash_code,
                inspect,     String_inspect,
                string_puts, String_puts,
                0);
    }
}

static void
StringClass_ctor(void * self, va_list * args_ptr) {
    struct StringClass * class = self;

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
        if(select == (func) string_puts) {
            *(func *) &class->string_puts = method;
        }
    }
}

static void
String_ctor(void * self, va_list * args_ptr) {
    struct String * string = self;
    string->self = va_arg(* args_ptr, char *);
}

static void
String_dtor(void * self) {
    free(self);
}

static bool
String_equals(void * _self, void * _obj) {
    struct String * self = _self;
    struct String * obj = _obj;
    return (obj->class == String &&
            strcmp(self->self, obj->self) == 0);
}

static size_t
String_hash_code(void * self) {
    struct String * string = self;
    size_t len = strlen(string->self);
    size_t hval = len;
    for(size_t i = 0; i < len; i++) {
        hval <<= 4;
        hval += string->self[i];
    }
    return hval;
}

static char *
String_inspect(void * self) {
    struct String * string = self;
    return string->self;
}

void
string_puts(void * self) {
    struct String * string = self;
    const struct StringClass * class = (struct StringClass *) string->class;
    class->string_puts(string);
}

static void
String_puts(void * self) {
    struct String * string = self;
    puts(string->self);
}
