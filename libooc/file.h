#ifndef FILE_H
#define FILE_H

#include <libooc/class.h>

#undef CLASS
#undef PUBLIC_METHODS_PREFIX
#define CLASS File
#define PUBLIC_METHODS_PREFIX FILE
#define FILE_OVERRIDE_METHODS \
    (FILE_ctor), \
    (FILE_dtor)
#define FILE_METHODS \
    (FILE_read)
#define FILE_ctor    ctor, void,   (va_list * args_ptr, args_ptr)
#define FILE_dtor    dtor, void
#define FILE_read    read, void *
def_public_methods()

#endif
