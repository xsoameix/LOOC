#ifndef ARRAY_H
#define ARRAY_H

#include <libooc/object.h>


#undef CLASS
#define CLASS Array
#define _Array_PUBLIC_OVERRIDE_METHODS \
    (_Array_ctor), \
    (_Array_dtor)
#define _Array_PUBLIC_METHODS \
    (_Array_len), \
    (_Array_get), \
    (_Array_last), \
    (_Array_push), \
    (_Array_pop), \
    (_Array_unshift), \
    (_Array_shift), \
    (_Array_each), \
    (_Array_any_p)
#define _Array_PRIVATE_METHODS \
    (_Array_double_capa)
#define _Array_ctor ctor, void, (va_list * args_ptr, args_ptr)
#define _Array_dtor dtor, void
#define _Array_len len, size_t
#define _Array_get get, void *, (size_t index, index)
#define _Array_last last, void *
#define _Array_push push, void, (void * data, data)
#define _Array_pop pop, void *
#define _Array_unshift unshift, void, (void * data, data)
#define _Array_shift shift, void *
#define _Array_each each, void, (void (* iter)(void * _self_, void * obj, size_t index), iter), (void * _self_, _self_)
#define _Array_any_p any_p, bool, (bool (* iter)(void * _self_, void * obj, size_t index), iter), (void * _self_, _self_)
#define _Array_double_capa double_capa, void, (size_t offset, offset)
def_public_methods()

#endif
