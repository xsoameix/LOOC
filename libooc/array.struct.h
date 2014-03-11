#ifndef ARRAY_STRUCT_H
#define ARRAY_STRUCT_H

#include <libooc/class.struct.h>
#include <libooc/array.h>

struct Array {
    const struct Class * class;
    size_t len;
    size_t capa;
    void ** values;
};

def_class_struct()

#endif
