#ifndef FILE_STRUCT_H
#define FILE_STRUCT_H

#include <libooc/object.struct.h>
#include <libooc/file.h>

struct File {
    struct Object super;
    char * filename;
    void * content;
};

def_class_struct()

#endif
