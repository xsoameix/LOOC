#ifndef CLASS_H
#define CLASS_H

#include <stdarg.h>
#include <stddef.h>

extern const void * Class;
extern const void * Object;

void * new(const void * klass, ...);
void   delete(void * obj);
void * ctor(void * self, va_list * args);
void   dtor(void * self);
size_t size_of(const void * obj);
const void * super_of(const void * obj);
char * class_name_of(const void * obj);

#endif
