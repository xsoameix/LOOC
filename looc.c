#include <stdio.h>

#include "include/hash.h"

int main(void) {
    hash_init();
    void * hash = new(Hash, 1);
    hash_set(hash, "a", "b");
    hash_get(hash, "a");
    delete(hash);
}
