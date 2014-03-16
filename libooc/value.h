#ifndef VALUE_H
#define VALUE_H

#include <libooc/object.struct.h>

typedef struct {
    struct Object super;
    union {
        int                v_int;
        unsigned int       v_uint;
        long               v_long;
        unsigned long      v_ulong;
        long long          v_int64;
        unsigned long long v_uint64;
        float              v_float;
        double             v_double;
        void *             v_pointer;
    };
} Value;

extern const void * StaticString;

void   Value_init(void);
void   Value_type(Value * value, const void * class);
void   Value_set_str(Value * value, char * str);
char * Value_get_str(Value * value);

#endif
