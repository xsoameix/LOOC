#ifndef FILE_H
#define FILE_H

#include <libooc/object.h>


#undef CLASS
#define CLASS File
#define _File_PUBLIC_OVERRIDE_METHODS \
    (_File_ctor), \
    (_File_dtor)
#define _File_PUBLIC_METHODS \
    (_File_read)
#define _File_PRIVATE_METHODS
#define _File_ctor ctor, void, (va_list * args_ptr, args_ptr)
#define _File_dtor dtor, void
#define _File_read read, void *
def_public_methods()

#endif
