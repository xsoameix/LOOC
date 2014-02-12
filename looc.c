#include <stdio.h>

#include "include/hash.h"

int main(void) {
    hash_init();
    void * hash = new(Hash, 3);
    hash_set(hash, "key1", "data1");
    hash_set(hash, "key2", "data2");
    hash_set(hash, "key3", "data3");
    hash_set(hash, "key4", "data4");
    hash_set(hash, "key5", "data5");
    hash_set(hash, "key6", "data6");
    puts(hash_get(hash, "key3"));
    delete(hash);
    return 0;
}
