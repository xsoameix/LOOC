#ifndef O_VALUE_H
#define O_VALUE_H

#include <libooc/object.struct.h>

typedef struct {
    struct Object super;
    union {
        o_int  v_int;
        o_uint v_uint;
        float  v_float;
        double v_double;
        void * v_pointer;
    };
} Value;

extern const void * StaticString;

void   Value_init(void);
void   Value_type(Value * value, const void * class);
void   Value_set_str(Value * value, char * str);
char * Value_get_str(Value * value);

#endif
