#ifndef O_FILE_STRUCT_H
#define O_FILE_STRUCT_H

#include <libooc/object.struct.h>
#include <libooc/file.h>

struct File {
    struct Object super;
    char * filename;
    o_obj content;
    FILE * file;
};

O_DEF_CLASS_STRUCT()

#endif
