#ifndef CLASS_H
#define CLASS_H

#include <stdarg.h>
#include <stddef.h>

extern const void * Class;
extern const void * Object;

void * new(const void * klass, ...);
void   delete(void * obj);

#endif
