#include <stdlib.h>
#include <string.h>

#include "array.struct.h"
#include "inttype.h"
#include "object_type.h"

#define DEFAULT_SIZE 2
#define _LEN self->len
#define _CAPA self->capa
#define _VALUES self->values

O_DEF_CLASS(Array, Object)

override
def(ctor, void : va_list * @args_ptr) {
    _LEN = 0;
    _CAPA = DEFAULT_SIZE;
    _VALUES = malloc(DEFAULT_SIZE * sizeof(o));
}

override
def(dtor, void) {
    free(_VALUES);
    free(self);
}

def(len, uint_t) {
    return _LEN;
}

def(get, o : uint_t @i) {
    if(i <= INTPTR_MAX) {
        return i < _LEN ? _VALUES[i] : NULL;
    } else {
        i = ~ i + 1;
        return i <= _LEN ? _VALUES[_LEN - i] : NULL;
    }
}

def(first, o) {
    return _LEN > 0 ? _VALUES[0] : NULL;
}

def(last, o) {
    return _LEN > 0 ? _VALUES[_LEN - 1] : NULL;
}

def(push, void : o @data) {
    if(_LEN == _CAPA) {
        double_capa(self, 0);
    }
    _VALUES[_LEN++] = data;
}

def(pop, o) {
    if(_LEN == 0) return NULL;
    return _VALUES[--_LEN];
}

def(unshift, void : o @data) {
    if(_LEN == _CAPA) {
        double_capa(self, 1);
    }
    _VALUES[0] = data;
}

def(shift, o) {
    if(_LEN == 0) return NULL;
    o first = _VALUES[0];
    memmove(_VALUES, &_VALUES[1], --_LEN * sizeof(o));
    return first;
}

#define EACH_WITH_N(n) EACH_WITH_N_(n, O_ARR_UPTO(n, O_VA_ARG))
#define EACH_WITH_N_(n, ...) \
    for(uint_t i = 0, len = _LEN; i < len; i++) { \
        itor(_VALUES[i], O_NOP(i)__VA_ARGS__); \
    }

def(each, void : o_ary_each_with_0_itor @itor) {
    EACH_WITH_N(0)
}

def(each_with_1, void : o @arg0 . o_ary_each_with_1_itor @itor) {
    EACH_WITH_N(1)
}

def(each_with_2, void : o @arg0 . o @arg1 . o_ary_each_with_2_itor @itor) {
    EACH_WITH_N(2)
}

def(each_with_3, void : o @arg0 . o @arg1 . o @arg2 . o_ary_each_with_3_itor @itor) {
    EACH_WITH_N(3)
}

#define REVERSE_EACH_WITH_N(n) REVERSE_EACH_WITH_N_(n, O_ARR_UPTO(n, O_VA_ARG))
#define REVERSE_EACH_WITH_N_(n, ...) \
    uint_t i = _LEN; \
    while(i > 0) { \
        i -= 1; \
        itor(_VALUES[i], O_NOP(_LEN - i - 1)__VA_ARGS__); \
    }

def(reverse_each, void : o_ary_each_with_0_itor @itor) {
    REVERSE_EACH_WITH_N(0)
}

def(reverse_each_with_1, void : o @arg0 . o_ary_each_with_1_itor @itor) {
    REVERSE_EACH_WITH_N(1)
}

def(reverse_each_with_2, void : o @arg0 . o @arg1 . o_ary_each_with_2_itor @itor) {
    REVERSE_EACH_WITH_N(2)
}

def(reverse_each_with_3, void : o @arg0 . o @arg1 . o @arg2 . o_ary_each_with_3_itor @itor) {
    REVERSE_EACH_WITH_N(3)
}

#define ANY_P_WITH_N(n) ANY_P_WITH_N_(n, O_ARR_UPTO(n, O_VA_ARG))
#define ANY_P_WITH_N_(n, ...) \
    for(uint_t i = 0, len = _LEN; i < len; i++) { \
        if(itor(_VALUES[i], O_NOP(i)__VA_ARGS__)) return true; \
    } \
    return false;

def(any_p, bool : o_ary_any_with_0_itor @itor) {
    ANY_P_WITH_N(0)
}

def(any_p_with_1, bool : o @arg0 . o_ary_any_with_1_itor @itor) {
    ANY_P_WITH_N(1)
}

def(any_p_with_2, bool : o @arg0 . o @arg1 . o_ary_any_with_2_itor @itor) {
    ANY_P_WITH_N(2)
}

def(any_p_with_3, bool : o @arg0 . o @arg1 . o @arg2 . o_ary_any_with_3_itor @itor) {
    ANY_P_WITH_N(3)
}

private
def(double_capa, void : uint_t @offset) {
    uint_t capa = _LEN * 2;
    o * values = malloc(capa * sizeof(o));
    memcpy(&values[offset], _VALUES, _LEN * sizeof(o));
    free(_VALUES);
    _VALUES = values;
    _CAPA = capa;
}
