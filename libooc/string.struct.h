#ifndef STRING_STRUCT_H
#define STRING_STRUCT_H

#include <libooc/class.struct.h>
#include <libooc/string.conflict.h>

struct String {
    const struct Class * class;
    char * chars;
};

def_class_struct()

#endif
