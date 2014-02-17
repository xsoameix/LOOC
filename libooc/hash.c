#include <stdlib.h>
#include <stdio.h>

#include "hash.struct.h"
#include "hash.h"
#include "string.struct.h"
#include "string.conflict.h"

struct HashClass {
    const struct Class class;
    bool   (* hash_set)(void * self, void * key, void * data);
    void * (* hash_get)(void * self, void * key);
};

enum ACTION {
    Set,
    Get
};

static const void * HashClass;
       const void * Hash;
static const void * HashEntries;

static void * HashClass_ctor(void * self, va_list * args_ptr);
static void * Hash_ctor(void * self, va_list * args_ptr);
static void   Hash_dtor(void * self);
static bool   Hash_set(void * self, void * key, void * data);
static void * Hash_get(void * self, void * key);
static void * HashEntries_ctor(void * self, va_list * args_ptr);
static void   HashEntries_dtor(void * self);

static bool isprime(size_t n);
static bool search(struct Hash * hash, void * key, void * data, void ** retdata, enum ACTION action);
static void rehash(struct Hash * hash);

void
hash_init(void) {
    if(!HashClass) {
        HashClass = new(
                Class,
                Class,
                "HashClass",
                sizeof(struct HashClass),
                ctor,     HashClass_ctor);
    }
    if(!Hash) {
        Hash = new(
                HashClass,
                Object,
                "Hash",
                sizeof(struct Hash),
                ctor,     Hash_ctor,
                dtor,     Hash_dtor,
                hash_set, Hash_set,
                hash_get, Hash_get);
    }
    if(!HashEntries) {
        HashEntries = new(
                Class,
                Object,
                "HashEntries",
                sizeof(struct HashEntries),
                ctor,     HashEntries_ctor,
                dtor,     HashEntries_dtor);
    }
}

static void *
HashClass_ctor(void * self, va_list * args_ptr) {
    struct HashClass * class = self;

    // inherit
    const struct Class * superclass = super_of(class);
    superclass->ctor(class, args_ptr);

    // override
    va_list args;
    va_copy(args, * args_ptr);
    typedef void (* func)(); func select;
    while(select = va_arg(args, func)) {
        func method = va_arg(args, func);
        if(select == (func) hash_set) {
            *(func *) &class->hash_set = method;
        } else if(select == (func) hash_get) {
            *(func *) &class->hash_get = method;
        }
    }
    return class;
}

static void *
Hash_ctor(void * self, va_list * args_ptr) {
    struct Hash * hash = self;
    size_t size = 5;
    size |= 1; // Because most prime is odd, so make it odd.
    if(!isprime(size)) {
        size += 2;
    }
    hash->size = size;
    hash->filled = 0;
    hash->entries = new(HashEntries, size);
    return hash;
}

static void
Hash_dtor(void * self) {
    struct Hash * hash = self;
    delete(hash->entries);
}

bool
hash_set(void * self, void * key, void * data) {
    struct Hash * hash = self;
    const struct HashClass * class = (struct HashClass *) hash->class;
    return class->hash_set(hash, key, data);
}

static bool
Hash_set(void * self, void * key, void * data) {
    struct Hash * hash = self;
    return search(hash, key, data, NULL, Set);
}

void *
hash_get(void * self, void * key) {
    struct Hash * hash = self;
    const struct HashClass * class = (struct HashClass *) hash->class;
    return class->hash_get(hash, key);
}

static void *
Hash_get(void * self, void * key) {
    struct Hash * hash = self;
    void * result;
    if(search(hash, key, NULL, &result, Get)) {
        return result;
    }
    return NULL;
}

static void *
HashEntries_ctor(void * self, va_list * args_ptr) {
    struct HashEntries * entries = self;
    size_t size = va_arg(* args_ptr, size_t);
    entries->entries = malloc(size * sizeof(struct HashEntry));
    return entries;
}

static void
HashEntries_dtor(void * self) {
    struct HashEntries * entries = self;
    free(entries->entries);
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
    size_t hval = hash_code(key);
    size_t idx = hval % hash->size; // First hash function.

    // There are 3 possibilities:
    // 1. The slot is used, same key.
    // 2. The slot is used, different key.
    // 3. The slot is not used.
    struct HashEntry * entries = hash->entries->entries;

    // Possibility 1.
    if(entries[idx].used == hval &&
            equals(key, entries[idx].key)) {
        // Possibility 2.
    } else if(entries[idx].used) {
        // The second hash function can't be 0.
        size_t hval2 = 1 + hval % (hash->size - 1),
               first_idx = idx;
        do {
            idx = (idx + hval2) % hash->size;
            if(idx == first_idx) {
                // If all of slots are Possibility 2. The end is here.
                return false;
            }

            // Possibility 1.
            if(entries[idx].used == hval &&
                    equals(key, entries[idx].key)) {
                break;
            }
            // Possibility 2.
        } while(entries[idx].used);
    }
    // Possibility 1, 3.
    struct HashEntry * select = &entries[idx];
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
        *retdata = select->data;
        break;
    }
    return true;
}

static void
rehash(struct Hash * hash) {
    size_t old_size = hash->size;
    // Make the new size is double and odd.
    size_t new_size = old_size * 2 + 1;
    while(!isprime(new_size)) {
        new_size += 2;
    }
    hash->size = new_size;
    hash->filled = 0;

    // Create the new entry array.
    struct HashEntries * old_entries = hash->entries;
    struct HashEntry * entries = old_entries->entries;
    hash->entries = new(HashEntries, new_size);
    for(size_t i = 0; i < old_size; i++) {
        if(entries[i].used) {
            hash_set(hash, entries[i].key, entries[i].data);
        }
    }
    delete(old_entries);
}
