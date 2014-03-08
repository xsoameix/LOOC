#include <stdlib.h>
#include <string.h>

#include "array.struct.h"
#include "array.h"

#define ARRAY_DEFAULT_SIZE 2

static void double_capa(struct Array * self, size_t offset);

CLASS_INIT(Object, CLASS_SIZE_FIXED, (ARRAY_OVERRIDE_METHODS), (ARRAY_METHODS));

METHOD_OVERRIDE(ARRAY_CTOR) {
    self->len = 0;
    self->capa = ARRAY_DEFAULT_SIZE;
    self->values = malloc(ARRAY_DEFAULT_SIZE * sizeof(void *));
}

METHOD_OVERRIDE(ARRAY_DTOR) {
    free(self->values);
    free(self);
}

METHOD(ARRAY_LEN) {
    return self->len;
}

METHOD(ARRAY_GET) {
    return self->len > index ? self->values[index] : NULL;
}

METHOD(ARRAY_LAST) {
    size_t len = self->len;
    return len > 0 ? self->values[len - 1] : NULL;
}

METHOD(ARRAY_PUSH) {
    if(self->len == self->capa) {
        double_capa(self, 0);
    }
    self->values[self->len++] = data;
}

METHOD(ARRAY_POP) {
    if(self->len == 0) return NULL;
    return self->values[--self->len];
}

METHOD(ARRAY_UNSHIFT) {
    if(self->len == self->capa) {
        double_capa(self, 1);
    }
    self->values[0] = data;
}

METHOD(ARRAY_SHIFT) {
    if(self->len == 0) return NULL;
    void ** values = self->values;
    void * element = values[0];
    memmove(values, &values[1], --self->len * sizeof(void *));
    return element;
}

METHOD(ARRAY_EACH) {
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
