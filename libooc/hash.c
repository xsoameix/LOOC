#include <stdlib.h>
#include <stdio.h>

#include "hash.struct.h"
#include "hash.h"

#define DEFAULT_SIZE 5

enum ACTION {
    Set,
    Get
};

def_class(Object)

def(ctor, override) {
    self->size = DEFAULT_SIZE;
    self->filled = 0;
    self->entries = malloc(DEFAULT_SIZE * (sizeof(struct Hash)));
}

def(dtor, override) {
    free(self->entries);
    free(self);
}

def(set) {
    return Hash_search(self, key, data, NULL, Set);
}

def(get) {
    void * result;
    if(Hash_search(self, key, NULL, &result, Get)) {
        return result;
    }
    return NULL;
}

def(each) {
    struct HashEntry * entries = self->entries;
    for(size_t i = 0, size = self->size; i < size; i++) {
        struct HashEntry entry = entries[i];
        if(entry.used) iter(entry.key, entry.data);
    }
}

def(prime_p, private) {
    size_t div = 3;
    while(div * div < n && n % div != 0) {
        div += 2;
    }
    return n % div != 0;
}

def(search, private) {
    struct Object * key = _key;
    size_t hval = Object_hash_code(key);
    size_t i = hval % self->size; // First hash function.

    // There are 3 possibilities:
    // 1. The slot is used, same key.
    // 2. The slot is used, different key.
    // 3. The slot is not used.
    struct HashEntry * entries = self->entries;

    // Possibility 1.
    if(entries[i].used == hval &&
            Object_equals(key, entries[i].key)) {
        // Possibility 2.
    } else if(entries[i].used) {
        // The second hash function can't be 0.
        size_t hval2 = 1 + hval % (self->size - 1);
        size_t first = i;
        do {
            i = (i + hval2) % self->size;
            if(i == first) {
                // If all of slots are Possibility 2. The end is here.
                return false;
            }

            // Possibility 1.
            if(entries[i].used == hval &&
                    Object_equals(key, entries[i].key)) {
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
            self->filled++;
        }
        select->used = hval;
        select->key  = key;
        select->data = data;
        float ratio = 0.8;
        if(((float) self->filled) / self->size > ratio) {
            Hash_rehash(self);
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

def(rehash, private) {
    // Make the new size is double and odd.
    size_t old_size = self->size;
    size_t size = old_size * 2 + 1;
    while(!Hash_prime_p(self, size)) size += 2;
    self->size = size;
    self->filled = 0;

    // Create the new entry array.
    struct HashEntry * entries = self->entries;
    self->entries = malloc(size * (sizeof(struct Hash)));
    for(size_t i = 0; i < old_size; i++) {
        struct HashEntry entry = entries[i];
        if(entry.used) Hash_set(self, entry.key, entry.data);
    }
    free(entries);
}
