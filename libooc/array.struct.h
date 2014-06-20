#ifndef O_ARRAY_STRUCT_H
#define O_ARRAY_STRUCT_H

#include <libooc/object.struct.h>
#include <libooc/array.h>

struct Array {
    struct Object super;
    ooc_uint len;
    ooc_uint capa;
    void ** values;
};

O_DEF_CLASS_STRUCT()

#endif
