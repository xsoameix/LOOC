#include <string.h>

#include "class.struct.h"
#include "class.h"
#include "string.struct.h"
#include "string.conflict.h"
#include "value.h"

const void * StaticString;

static void   StaticString_dtor(void * self);
static bool   StaticString_equals(void * _self, void * _obj);
static size_t StaticString_hash_code(void * self);

void
value_init(void) {
    if(!StaticString) {
        string_init();
        StaticString = new(
                Class,
                Object,
                "StaticString",
                sizeof(Value),
                dtor,        StaticString_dtor,
                equals,      StaticString_equals,
                hash_code,   StaticString_hash_code);
    }
}

void
value_type(Value * value, const void * class) {
    value->class = class;
}

void
value_set_str(Value * value, char * str) {
    value->v_pointer = str;
}

char *
value_get_str(Value * value) {
    return (char *) value->v_pointer;
}

static void
StaticString_dtor(void * self) {
}

static bool
StaticString_equals(void * _self, void * _obj) {
    Value * self = _self;
    Value * obj = _obj;
    return (obj->class == StaticString &&
            strcmp(value_get_str(self), value_get_str(obj)) == 0);
}

static size_t
StaticString_hash_code(void * self) {
    Value * value = self;
    char * string = value_get_str(value);
    size_t len = strlen(string);
    size_t hval = len;
    for(size_t i = 0; i < len; i++) {
        hval <<= 4;
        hval += string[i];
    }
    return hval;
}
