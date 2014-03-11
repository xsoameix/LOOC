#ifndef FILE_STRUCT_H
#define FILE_STRUCT_H

#include <libooc/class.struct.h>
#include <libooc/file.h>

struct File {
    const struct Class * class;
    char * filename;
    void * content;
};

def_class_struct()

#endif
