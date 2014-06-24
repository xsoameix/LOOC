#include <stdlib.h>
#include <stdio.h>

#include "array.h"
#include "hash.struct.h"
#include "inttype.h"
#include "object_type.h"
#include "hash_macro.h"

#define DEFAULT_SIZE 5
#define CAPA self->capa
#define LEN self->len
#define ENTRIES self->entries

enum ACTION {
    Set,
    Get
};

O_DEF_CLASS(Hash, Object)

override
def(ctor, void : va_list * @args_ptr) {
    CAPA = DEFAULT_SIZE;
    LEN = 0;
    ENTRIES = calloc(1, DEFAULT_SIZE * (sizeof(struct Hash)));
}

override
def(dtor, void) {
    free(ENTRIES);
    free(self);
}

def(len, uint_t) {
    return LEN;
}

def(set, bool : o @key . o @data) {
    return search(self, key, data, NULL, Set);
}

def(get, o : o @key) {
    o result;
    if(search(self, key, NULL, &result, Get)) {
        return result;
    }
    return NULL;
}

def(intersact_p, bool : o @_set) {
    if(LEN == 0 || len(_set) == 0) return false;
    o union_set = new(Hash);

    H_ITOR(merge) {
        set(union_set, KEY, VALUE);
    }

    H_EACH(self, merge);
    H_EACH(_set, merge);
    uint_t union_len = len(union_set);
    delete(union_set);
    return union_len < LEN + len(_set);
}

#define EACH_WITH_N(n) EACH_WITH_N_(n, O_ARR_UPTO(n, O_VA_ARG))
#define EACH_WITH_N_(n, ...) \
    for(uint_t i = 0, capa = CAPA; i < capa; i++) { \
        struct HashEntry entry = ENTRIES[i]; \
        if(entry.used) itor(entry.key, O_NOP(entry.data)__VA_ARGS__); \
    }

def(each, void : o_hash_each_with_0_itor @itor) {
    EACH_WITH_N(0)
}

def(each_with_1, void : o @arg0 . o_hash_each_with_1_itor @itor) {
    EACH_WITH_N(1)
}

def(each_with_2, void : o @arg0 . o @arg1 . o_hash_each_with_2_itor @itor) {
    EACH_WITH_N(2)
}

def(each_with_3, void : o @arg0 . o @arg1 . o @arg2 . o_hash_each_with_3_itor @itor) {
    EACH_WITH_N(3)
}

def(keys, o) {
    o ary = new(Array);

    H_ITOR(to_ary) {
        O_ARY_PUSH(ary, KEY);
    }

    H_EACH(self, to_ary);
    return ary;
}

def(values, o) {
    o ary = new(Array);

    H_ITOR(to_ary) {
        O_ARY_PUSH(ary, VALUE);
    }

    H_EACH(self, to_ary);
    return ary;
}

private
def(prime_p, bool : uint_t @n) {
    uint_t div = 3;
    while(div * div < n && n % div != 0) {
        div += 2;
    }
    return n % div != 0;
}

private
def(search, bool : o @_key . o @data . o * @ret . enum ACTION @action) {
    struct Object * key = _key;
    uint_t hval = hash_code(key);
    uint_t i = hval % CAPA; // First hash function.

    // There are 3 possibilities:
    // 1. The slot is used, same key.
    // 2. The slot is used, different key.
    // 3. The slot is not used.

    // Possibility 1.
    if(ENTRIES[i].used == hval &&
            equals(key, ENTRIES[i].key)) {
        // Possibility 2.
    } else if(ENTRIES[i].used) {
        // The second hash function can't be 0.
        uint_t hval2 = 1 + hval % (CAPA - 1);
        uint_t first = i;
        do {
            i = (i + hval2) % CAPA;
            if(i == first) {
                // If all of slots are Possibility 2. The end is here.
                return false;
            }

            // Possibility 1.
            if(ENTRIES[i].used == hval &&
                    equals(key, ENTRIES[i].key)) {
                break;
            }
            // Possibility 2.
        } while(ENTRIES[i].used);
    }
    // Possibility 1, 3.
    struct HashEntry * select = &ENTRIES[i];
    switch(action) {
    case Set:
        // Possibility 3.
        if(!select->used) {
            LEN++;
        }
        select->used = hval;
        select->key  = key;
        select->data = data;
        float ratio = 0.8;
        if(((float) LEN) / CAPA > ratio) {
            rehash(self);
        }
        break;
    case Get:
        // Possibility 3.
        if(!select->used) {
            return false;
        }
        // Possibility 1.
        * ret = select->data;
        break;
    }
    return true;
}

private
def(rehash, void) {
    // Make the new capa is double and odd.
    uint_t old_capa = CAPA;
    uint_t capa = old_capa * 2 + 1;
    while(!prime_p(self, capa)) capa += 2;
    CAPA = capa;
    LEN = 0;

    // Create the new entry array.
    struct HashEntry * entries = ENTRIES;
    ENTRIES = calloc(1, capa * (sizeof(struct Hash)));
    for(uint_t i = 0; i < old_capa; i++) {
        struct HashEntry entry = entries[i];
        if(entry.used) set(self, entry.key, entry.data);
    }
    free(entries);
}
