#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "string.struct.h"

def_class(String, Object)

override
def(ctor, void : va_list * @args_ptr) {
    self->chars = va_arg(* args_ptr, char *);
}

override
def(dtor, void) {
    free(self);
}

override
def(equals, bool : void * @_obj) {
    struct String * obj = _obj;
    return (obj->class == String &&
            strcmp(self->chars, obj->chars) == 0);
}

override
def(hash_code, size_t) {
    size_t len = strlen(self->chars);
    size_t hval = len;
    for(size_t i = 0; i < len; i++) {
        hval <<= 4;
        hval += self->chars[i];
    }
    return hval;
}

override
def(inspect, char *) {
    return self->chars;
}
