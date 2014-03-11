#ifndef FILE_STRUCT_H
#define FILE_STRUCT_H

#include <libooc/class.struct.h>

struct File {
    const struct Class * class;
    char * filename;
    void * content;
};

#endif
