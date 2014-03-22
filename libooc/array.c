#include <stdlib.h>
#include <string.h>

#include "array.struct.h"

#define DEFAULT_SIZE 2

def_class(Array, Object)

override
def(ctor, void : va_list * @args_ptr) {
    self->len = 0;
    self->capa = DEFAULT_SIZE;
    self->values = malloc(DEFAULT_SIZE * sizeof(void *));
}

override
def(dtor, void) {
    free(self->values);
    free(self);
}

def(len, size_t) {
    return self->len;
}

def(get, void * : size_t @index) {
    return self->len > index ? self->values[index] : NULL;
}

def(last, void *) {
    size_t len = self->len;
    return len > 0 ? self->values[len - 1] : NULL;
}

def(push, void : void * @data) {
    if(self->len == self->capa) {
        double_capa(self, 0);
    }
    self->values[self->len++] = data;
}

def(pop, void *) {
    if(self->len == 0) return NULL;
    return self->values[--self->len];
}

def(unshift, void : void * @data) {
    if(self->len == self->capa) {
        double_capa(self, 1);
    }
    self->values[0] = data;
}

def(shift, void *) {
    if(self->len == 0) return NULL;
    void ** values = self->values;
    void * element = values[0];
    memmove(values, &values[1], --self->len * sizeof(void *));
    return element;
}

def(each, void : void (* @iter)(void * _self_, void * obj, size_t index) . void * @_self_) {
    void ** values = self->values;
    for(size_t i = 0, len = self->len; i < len; i++) {
        iter(_self_, values[i], i);
    }
}

def(any_p, bool : bool (* @iter)(void * _self_, void * obj, size_t index) . void * @_self_) {
    void ** values = self->values;
    for(size_t i = 0, len = self->len; i < len; i++) {
        if(iter(_self_, values[i], i)) {
            return true;
        }
    }
    return false;
}

private
def(double_capa, void : size_t @offset) {
    size_t capa = self->len * 2;
    void ** values = malloc(capa * sizeof(void *));
    memcpy(&values[offset], self->values, self->len * sizeof(void *));
    free(self->values);
    self->values = values;
    self->capa = capa;
}
