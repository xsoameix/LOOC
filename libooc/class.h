#ifndef CLASS_H
#define CLASS_H

#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <libooc/class_macro.h>

extern const void * Class;
extern const void * Object;

      void * new(const void * klass, ...);
      void   delete(void * obj);
      void   Object_ctor(void * self, va_list * args);
      void   Object_dtor(void * self);
      bool   Object_equals(void * self, void * obj);
      size_t Object_hash_code(void * self);
      char * Object_inspect(void * self);
const void * super_of(const void * obj);

#endif
