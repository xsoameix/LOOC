#ifndef FILE_H
#define FILE_H

#include <libooc/class.h>

extern const void * File;

void   file_init(void);
void * file_read(void * self);

#endif
