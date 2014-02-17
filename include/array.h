#ifndef ARRAY_H
#define ARRAY_H

#include "include/class.h"

extern const void * Array;

void array_init(void);
void array_push(void * self, void * data);
void array_each(void * self, void (* iter)(void * obj, size_t index));

#endif
