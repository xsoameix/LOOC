#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "string.struct.h"
#include "string.conflict.h"

def_class(Object)

def(ctor, override) {
    self->chars = va_arg(* args_ptr, char *);
}

def(dtor, override) {
    free(self);
}

def(equals, override) {
    return (obj->class == String &&
            strcmp(self->chars, obj->chars) == 0);
}

def(hash_code, override) {
    size_t len = strlen(self->chars);
    size_t hval = len;
    for(size_t i = 0; i < len; i++) {
        hval <<= 4;
        hval += self->chars[i];
    }
    return hval;
}

def(inspect, override) {
    return self->chars;
}

def(puts) {
    puts(self->chars);
}
