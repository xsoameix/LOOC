#ifndef ARRAY_STRUCT_H
#define ARRAY_STRUCT_H

#include <libooc/class.struct.h>

struct Array {
    const struct Class * class;
    size_t len;
    size_t capa;
    void ** values;
};

#endif
