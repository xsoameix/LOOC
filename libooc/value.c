#include <string.h>

#include "object.struct.h"
#include "object.h"
#include "string.struct.h"
#include "string.conflict.h"
#include "value.h"
#include "inttype.h"

const void * StaticString;

static void   StaticString_dtor(void * self);
static bool   StaticString_equals(void * _self, void * _obj);
static uint_t StaticString_hash_code(void * self);

void
Value_init(void) {
    if(!StaticString) {
        String_init();
        StaticString = new(
                Class,
                Object,
                "StaticString",
                sizeof(Value),
                false,
                Object_dtor,      StaticString_dtor,
                Object_equals,    StaticString_equals,
                Object_hash_code, StaticString_hash_code,
                0);
    }
}

void
Value_type(Value * value, const void * class) {
    ((struct Object *) value)->class = class;
}

void
Value_set_str(Value * value, char * str) {
    value->v_pointer = str;
}

char *
Value_get_str(Value * value) {
    return (char *) value->v_pointer;
}

static void
StaticString_dtor(void * self) {
}

static bool
StaticString_equals(void * _self, void * _obj) {
    Value * self = _self;
    Value * obj = _obj;
    return (((struct Object *) obj)->class == StaticString &&
            strcmp(Value_get_str(self), Value_get_str(obj)) == 0);
}

static uint_t
StaticString_hash_code(void * self) {
    Value * value = self;
    char * string = Value_get_str(value);
    uint_t len = strlen(string);
    uint_t hval = len;
    for(uint_t i = 0; i < len; i++) {
        hval <<= 4;
        hval += string[i];
    }
    return hval;
}
