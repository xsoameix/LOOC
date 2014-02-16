#ifndef HASH_STRUCT_H
#define HASH_STRUCT_H

#include <stdarg.h>

#include "include/class.struct.h"

struct HashEntry {
    size_t used;
    void * key;
    void * data;
};

struct HashEntries {
    const struct Class * class;
    struct HashEntry * entries;
};

struct Hash {
    const struct Class * class;
    size_t size;
    size_t filled;
    struct HashEntries * entries;
};

#endif
