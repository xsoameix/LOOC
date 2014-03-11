#ifndef HASH_STRUCT_H
#define HASH_STRUCT_H

#include <libooc/class.struct.h>
#include <libooc/hash.h>

struct HashEntry {
    size_t used;
    void * key;
    void * data;
};

struct Hash {
    const struct Class * class;
    size_t size;
    size_t filled;
    struct HashEntry * entries;
};

def_class_struct()

#endif
