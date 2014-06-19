#ifndef STRING_STRUCT_H
#define STRING_STRUCT_H

#include <libooc/object.struct.h>
#include <libooc/string.conflict.h>

struct String {
    struct Object super;
    char * chars;
};

O_DEF_CLASS_STRUCT_WITHOUT_ALIAS()

#endif
