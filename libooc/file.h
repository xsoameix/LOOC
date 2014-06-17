#ifndef FILE_H
#define FILE_H

#include <libooc/object.h>

void File_puts(void * _self, const char * string);
void File_printf(void * _self, const char * format, ...);

#undef CLASS
#define CLASS File
#define _File_PUBLIC_OVERRIDE_METHODS \
    (_File_ctor), \
    (_File_dtor)
#define _File_PUBLIC_METHODS \
    (_File_read), \
    (_File_open)
#define _File_PRIVATE_METHODS
#define _File_ctor ctor, void, (va_list * args_ptr, args_ptr)
#define _File_dtor dtor, void
#define _File_read read, void *
#define _File_open open, void, (const char * mode, mode), (void (* func)(void * self, void * file), func), (void * _self_, _self_)
def_public_methods()

#endif
