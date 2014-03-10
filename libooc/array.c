#include <stdlib.h>
#include <string.h>

#include "array.struct.h"
#include "array.h"

#define DEFAULT_SIZE 2

static void double_capa(struct Array * self, size_t offset);

def_class(Object, CLASS_SIZE_FIXED)

def_override(ctor) {
    self->len = 0;
    self->capa = DEFAULT_SIZE;
    self->values = malloc(DEFAULT_SIZE * sizeof(void *));
}

def_override(dtor) {
    free(self->values);
    free(self);
}

def(len) {
    return self->len;
}

def(get) {
    return self->len > index ? self->values[index] : NULL;
}

def(last) {
    size_t len = self->len;
    return len > 0 ? self->values[len - 1] : NULL;
}

def(push) {
    if(self->len == self->capa) {
        double_capa(self, 0);
    }
    self->values[self->len++] = data;
}

def(pop) {
    if(self->len == 0) return NULL;
    return self->values[--self->len];
}

def(unshift) {
    if(self->len == self->capa) {
        double_capa(self, 1);
    }
    self->values[0] = data;
}

def(shift) {
    if(self->len == 0) return NULL;
    void ** values = self->values;
    void * element = values[0];
    memmove(values, &values[1], --self->len * sizeof(void *));
    return element;
}

def(each) {
    void ** values = self->values;
    for(size_t i = 0, len = self->len; i < len; i++) {
        iter(values[i], i);
    }
}

static void
double_capa(struct Array * self, size_t offset) {
    size_t len = self->len * 2;
    void ** values = malloc(len * sizeof(void *));
    memcpy(&values[offset], self->values, self->len * sizeof(void *));
    free(self->values);
    self->values = values;
    self->len = len;
}
