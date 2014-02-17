#include <stdio.h>

#include "include/string.h"
#include "include/hash.h"
#include "include/array.h"

static void
array_print(void * string, size_t index) {
    string_puts(string);
    printf("%zd\n", index);
}

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

    // array
    array_init();
    void * ary = new(Array);
    array_push(ary, a);
    array_push(ary, b);
    array_each(ary, array_print);
    delete(ary);
}
