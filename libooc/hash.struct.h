#ifndef O_HASH_STRUCT_H
#define O_HASH_STRUCT_H

#include <libooc/object.struct.h>
#include <libooc/hash.h>

struct HashEntry {
    o_uint used;
    void * key;
    void * data;
};

struct Hash {
    struct Object super;
    o_uint capa;
    o_uint len;
    struct HashEntry * entries;
};

O_DEF_CLASS_STRUCT()

#endif
