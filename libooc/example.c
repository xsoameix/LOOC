#include <stdio.h>

#include "value.h"
#include "string.conflict.h"
#include "hash.h"
#include "array.h"
#include "file.h"
#include "inttype.h"

static void
Array_print(void * value, uint_t index) {
    printf("%zu: %s\n", index, Value_get_str(value));
}

static void
write_file(void * null, void * file) {
    File_puts(file, "hello");
    File_printf(file, " w%drld", 0);
}

int main(void) {
    // static string
    Value_init();
    Value a;
    Value_type(&a, StaticString);
    Value_set_str(&a, "a");
    Value_get_str(&a);

    // string
    String_init();
    void * b = new(String, "b");

    // hash
    Hash_init();
    void * hash = new(Hash);
    Hash_set(hash, &a, b);
    void * c = Hash_get(hash, &a);
    puts(Object_inspect(c));
    delete(hash);

    // array
    Array_init();
    void * ary = new(Array);
    Array_push(ary, &a);
    Array_unshift(ary, b);
    void * d = Array_shift(ary);
    puts(Object_inspect(d));
    delete(ary);

    delete(b);

    // file
    File_init();
    void * file = new(File, "libooc/example");
    void * content = File_read(file);
    puts(Object_inspect(content));
    delete(file);

    file = new(File, "libooc/example-2");
    File_open(file, "w", write_file, NULL);
    delete(file);
}
