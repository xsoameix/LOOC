#ifndef O_FILE_H
#define O_FILE_H

#include <libooc/object.h>
void File_puts(void * _self, const char * string);
void File_printf(void * _self, const char * format, ...);


#undef O_CLASS
#undef O_PARENT
#define O_CLASS File
#define O_PARENT Object
#define O_File_OVERRIDE_METHODS_LEN 2
#define O_File_PUBLIC_METHODS_LEN 2
#define O_File_PRIVATE_METHODS_LEN 0
#define O_File_OVERRIDE_METHOD_0 ctor, void, (va_list * args_ptr, args_ptr)
#define O_File_OVERRIDE_METHOD_1 dtor, void
#define O_File_PUBLIC_METHOD_0 read, void *
#define O_File_PUBLIC_METHOD_1 open, void, (const char * mode, mode), (void (* func)(void * self, void * file), func), (void * _self_, _self_)
#define O_File_ctor O_File_OVERRIDE_METHOD_0
#define O_File_dtor O_File_OVERRIDE_METHOD_1
#define O_File_read O_File_PUBLIC_METHOD_0
#define O_File_open O_File_PUBLIC_METHOD_1
O_DEF_GLOBAL_METHODS()

#endif
