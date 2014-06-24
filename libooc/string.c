#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "string.struct.h"
#include "inttype.h"
#include "object_type.h"

#define CHARS self->chars

O_DEF_CLASS(String, Object)

override
def(ctor, void : va_list * @args_ptr) {
    CHARS = va_arg(* args_ptr, char *);
}

override
def(dtor, void) {
    free(self);
}

override
def(equals, bool : o @_obj) {
    struct String * obj = _obj;
    return (((struct Object *) obj)->class == String &&
            strcmp(CHARS, obj->chars) == 0);
}

override
def(hash_code, uint_t) {
    uint_t len = strlen(CHARS);
    uint_t hval = len;
    for(uint_t i = 0; i < len; i++) {
        hval <<= 4;
        hval += CHARS[i];
    }
    return hval;
}

override
def(inspect, char *) {
    return CHARS;
}

def(set, void : char * @chars) {
    CHARS = chars;
}

def(index, uint_t : bool (* @func)(o _self_, char c) . o @_self_) {
    uint_t len = strlen(CHARS);
    for(uint_t i = 0; i < len; i++) {
        if(func(_self_, CHARS[i])) {
            return i;
        }
    }
    return -1;
}

def(rindex, uint_t : bool (* @func)(o _self_, char c) . o @_self_) {
    uint_t i = strlen(CHARS);
    while(i > 0) {
        i -= 1;
        if(func(_self_, CHARS[i])) {
            return i;
        }
    }
    return -1;
}

def(strip, void) {

    bool not_whitespace_p(o unused, char c) {
        return !(c == ' ' || c == '\t' ||
                c == 0x0A || c == 0x0D);
    }

    char * chars = CHARS;
    uint_t start = String_index(self, not_whitespace_p, NULL);
    if(start == -1) start = 0;
    uint_t end = String_rindex(self, not_whitespace_p, NULL);
    if(end == -1) end = strlen(chars) - 1;
    uint_t len = end - start + 1;
    if(start > 0) {
        memmove(chars, chars + start, len);
    }
    chars[len] = '\0';
}
