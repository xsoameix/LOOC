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
    return (((struct Object *) obj)->class == String &&
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

def(set, void : char * @chars) {
    self->chars = chars;
}

def(index, size_t : bool (* @func)(void * _self_, char c) . void * @_self_) {
    char * chars = self->chars;
    size_t len = strlen(chars);
    for(size_t i = 0; i < len; i++) {
        if(func(_self_, chars[i])) {
            return i;
        }
    }
    return -1;
}

def(rindex, size_t : bool (* @func)(void * _self_, char c) . void * @_self_) {
    char * chars = self->chars;
    size_t i = strlen(chars);
    while(i > 0) {
        i -= 1;
        if(func(_self_, chars[i])) {
            return i;
        }
    }
    return -1;
}

static bool
not_whitespace_p(void * null, char c) {
    return !(c == ' ' || c == '\t' ||
            c == 0x0A || c == 0x0D);
}

def(strip, void) {
    char * chars = self->chars;
    size_t start = String_index(self, not_whitespace_p, NULL);
    if(start == -1) start = 0;
    size_t end = String_rindex(self, not_whitespace_p, NULL);
    if(end == -1) end = strlen(chars) - 1;
    size_t len = end - start + 1;
    if(start > 0) {
        memmove(chars, chars + start, len);
    }
    chars[len] = '\0';
}
