#ifndef ARRAY_STRUCT_H
#define ARRAY_STRUCT_H

#include <libooc/object.struct.h>
#include <libooc/array.h>

struct Array {
    struct Object super;
    size_t len;
    size_t capa;
    void ** values;
};

def_class_struct()

#endif
