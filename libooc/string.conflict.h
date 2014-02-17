#ifndef STRING_H
#define STRING_H

#include <stdbool.h>

#include <libooc/class.h>

extern const void * String;

void   string_init(void);
void   string_puts(void * self);

#endif
