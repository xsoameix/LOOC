#include <stdio.h>

#include "include/string.h"
#include "include/hash.h"

int main(void) {
    // string
    string_init();
    void * a = new(String, "a");
    void * b = new(String, "b");

    // hash
    hash_init();
    void * hash = new(Hash);
    hash_set(hash, a, b);
    void * c = hash_get(hash, a);
    string_puts(c);
    delete(hash);
}
