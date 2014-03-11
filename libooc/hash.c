#include <stdlib.h>
#include <stdio.h>

#include "hash.struct.h"
#include "hash.h"

#define DEFAULT_SIZE 5

enum ACTION {
    Set,
    Get
};

static bool isprime(size_t n);
static bool search(struct Hash * hash, void * key, void * data, void ** retdata, enum ACTION action);
static void rehash(struct Hash * hash);

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
    return search(self, key, data, NULL, Set);
}

def(get) {
    void * result;
    if(search(self, key, NULL, &result, Get)) {
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

static bool
isprime(size_t n) {
    size_t div = 3;
    while(div * div < n && n % div != 0) {
        div += 2;
    }
    return n % div != 0;
}

static bool
search(struct Hash * hash, void * _key, void * data, void ** retdata, enum ACTION action) {
    struct Object * key = _key;
    size_t hval = Object_hash_code(key);
    size_t i = hval % hash->size; // First hash function.

    // There are 3 possibilities:
    // 1. The slot is used, same key.
    // 2. The slot is used, different key.
    // 3. The slot is not used.
    struct HashEntry * entries = hash->entries;

    // Possibility 1.
    if(entries[i].used == hval &&
            Object_equals(key, entries[i].key)) {
        // Possibility 2.
    } else if(entries[i].used) {
        // The second hash function can't be 0.
        size_t hval2 = 1 + hval % (hash->size - 1);
        size_t first = i;
        do {
            i = (i + hval2) % hash->size;
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
            hash->filled++;
        }
        select->used = hval;
        select->key  = key;
        select->data = data;
        float ratio = 0.8;
        if(((float) hash->filled) / hash->size > ratio) {
            rehash(hash);
        }
        break;
    case Get:
        // Possibility 3.
        if(!select->used) {
            return false;
        }
        // Possibility 1.
        * retdata = select->data;
        break;
    }
    return true;
}

static void
rehash(struct Hash * hash) {
    // Make the new size is double and odd.
    size_t old_size = hash->size;
    size_t size = old_size * 2 + 1;
    while(!isprime(size)) size += 2;
    hash->size = size;
    hash->filled = 0;

    // Create the new entry array.
    struct HashEntry * entries = hash->entries;
    hash->entries = malloc(size * (sizeof(struct Hash)));
    for(size_t i = 0; i < old_size; i++) {
        struct HashEntry entry = entries[i];
        if(entry.used) Hash_set(hash, entry.key, entry.data);
    }
    free(entries);
}
