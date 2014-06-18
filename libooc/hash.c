#include <stdlib.h>
#include <stdio.h>

#include "hash.struct.h"
#include "inttype.h"

#define DEFAULT_SIZE 5

enum ACTION {
    Set,
    Get
};

def_class(Hash, Object)

override
def(ctor, void : va_list * @args_ptr) {
    self->capa = DEFAULT_SIZE;
    self->len = 0;
    self->entries = calloc(1, DEFAULT_SIZE * (sizeof(struct Hash)));
}

override
def(dtor, void) {
    free(self->entries);
    free(self);
}

def(len, uint_t) {
    return self->len;
}

def(set, bool : void * @key . void * @data) {
    return search(self, key, data, NULL, Set);
}

def(get, void * : void * @key) {
    void * result;
    if(search(self, key, NULL, &result, Get)) {
        return result;
    }
    return NULL;
}

static void
intersact_p_iter(void * union_set, void * key, void * data) {
    set(union_set, key, data);
}

def(intersact_p, bool : void * @set) {
    if(self->len == 0 || len(set) == 0) return false;
    void * union_set = new(Hash);
    each(self, intersact_p_iter, union_set);
    each(set, intersact_p_iter, union_set);
    uint_t union_len = len(union_set);
    delete(union_set);
    return union_len < self->len + len(set);
}

def(each, void : void (* @iter)(void * _self_, void * key, void * data) . void * @_self_) {
    struct HashEntry * entries = self->entries;
    for(uint_t i = 0, capa = self->capa; i < capa; i++) {
        struct HashEntry entry = entries[i];
        if(entry.used) iter(_self_, entry.key, entry.data);
    }
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
def(search, bool : void * @_key . void * @data . void ** @ret . enum ACTION @action) {
    struct Object * key = _key;
    uint_t hval = hash_code(key);
    uint_t i = hval % self->capa; // First hash function.

    // There are 3 possibilities:
    // 1. The slot is used, same key.
    // 2. The slot is used, different key.
    // 3. The slot is not used.
    struct HashEntry * entries = self->entries;

    // Possibility 1.
    if(entries[i].used == hval &&
            equals(key, entries[i].key)) {
        // Possibility 2.
    } else if(entries[i].used) {
        // The second hash function can't be 0.
        uint_t hval2 = 1 + hval % (self->capa - 1);
        uint_t first = i;
        do {
            i = (i + hval2) % self->capa;
            if(i == first) {
                // If all of slots are Possibility 2. The end is here.
                return false;
            }

            // Possibility 1.
            if(entries[i].used == hval &&
                    equals(key, entries[i].key)) {
                break;
            }
            // Possibility 2.
        } while(entries[i].used);
    }
    // Possibility 1, 3.
    struct HashEntry * select = &entries[i];
    switch(action) {
    case Set:
        // Possibility 3.
        if(!select->used) {
            self->len++;
        }
        select->used = hval;
        select->key  = key;
        select->data = data;
        float ratio = 0.8;
        if(((float) self->len) / self->capa > ratio) {
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
    uint_t old_capa = self->capa;
    uint_t capa = old_capa * 2 + 1;
    while(!prime_p(self, capa)) capa += 2;
    self->capa = capa;
    self->len = 0;

    // Create the new entry array.
    struct HashEntry * entries = self->entries;
    self->entries = calloc(1, capa * (sizeof(struct Hash)));
    for(uint_t i = 0; i < old_capa; i++) {
        struct HashEntry entry = entries[i];
        if(entry.used) set(self, entry.key, entry.data);
    }
    free(entries);
}
