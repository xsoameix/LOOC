#ifndef ARRAY_STRUCT_H
#define ARRAY_STRUCT_H

#include <libooc/class.struct.h>

struct ArrayValues {
    const struct Class * class;
    void ** values;
};

struct Array {
    const struct Class * class;
    size_t len;
    size_t capa;
    struct ArrayValues * values;
};

#endif
