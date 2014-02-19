#ifndef ARRAY_H
#define ARRAY_H

#include <libooc/class.h>

extern const void * Array;

void   array_init(void);
void * array_get(void * self, size_t index);
void   array_push(void * self, void * data);
void   array_each(void * self, void (* iter)(void * obj, size_t index));

#endif
