#include <stdlib.h>
#include <stdio.h>

#include "hash.struct.h"
#include "hash.h"

#define HASH_DEFAULT_SIZE 5

struct HashClass {
    const struct Class class;
    bool   (* hash_set)(void * self, void * key, void * data);
    void * (* hash_get)(void * self, void * key);
    void   (* hash_each)(void * self, void (* iter)(void * key, void * data));
};

enum ACTION {
    Set,
    Get
};

static const void * HashClass;
       const void * Hash;

static void   HashClass_ctor(void * self, va_list * args_ptr);
static void   Hash_ctor(void * self, va_list * args_ptr);
static void   Hash_dtor(void * self);
static bool   Hash_set(void * self, void * key, void * data);
static void * Hash_get(void * self, void * key);
static void   Hash_each(void * self, void (* iter)(void * key, void * data));

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
                false,
                Object_ctor, HashClass_ctor,
                0);
    }
    if(!Hash) {
        Hash = new(
                HashClass,
                Object,
                "Hash",
                sizeof(struct Hash),
                false,
                Object_ctor, Hash_ctor,
                Object_dtor, Hash_dtor,
                hash_set,    Hash_set,
                hash_get,    Hash_get,
                hash_each,   Hash_each,
                0);
    }
}

static void
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
        } else if(select == (func) hash_each) {
            *(func *) &class->hash_each = method;
        }
    }
}

static void
Hash_ctor(void * self, va_list * args_ptr) {
    struct Hash * hash = self;
    hash->size = HASH_DEFAULT_SIZE;
    hash->filled = 0;
    hash->entries = malloc(HASH_DEFAULT_SIZE * (sizeof(struct Hash)));
}

static void
Hash_dtor(void * self) {
    struct Hash * hash = self;
    free(hash->entries);
    free(hash);
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

void
hash_each(void * self, void (* iter)(void * key, void * data)) {
    struct Hash * hash = self;
    const struct HashClass * class = (struct HashClass *) hash->class;
    class->hash_each(hash, iter);
}

static void
Hash_each(void * self, void (* iter)(void * key, void * data)) {
    struct Hash * hash = self;
    struct HashEntry * entries = hash->entries;
    for(size_t i = 0, size = hash->size; i < size; i++) {
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
        if(entry.used) hash_set(hash, entry.key, entry.data);
    }
    free(entries);
}
