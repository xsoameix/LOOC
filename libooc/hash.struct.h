#ifndef O_HASH_STRUCT_H
#define O_HASH_STRUCT_H

#include <libooc/object.struct.h>
#include <libooc/hash.h>

struct HashEntry {
    ooc_uint used;
    void *     key;
    void *     data;
};

struct Hash {
    struct Object super;
    ooc_uint capa;
    ooc_uint len;
    struct HashEntry * entries;
};

O_DEF_CLASS_STRUCT()

#endif
