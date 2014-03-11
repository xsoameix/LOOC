#include <check.h>
#include "../libooc/string.conflict.h"
#include "../libooc/array.h"

START_TEST(test_array_get) {
    string_init();
    void * a = new(String, "a");
    void * b = new(String, "b");
    void * c = new(String, "c");
    array_init();
    void * ary = new(Array);
    array_push(ary, a);
    array_push(ary, b);
    array_push(ary, c);
    ck_assert_int_eq(array_get(ary, 0), a);
    ck_assert_int_eq(array_get(ary, 1), b);
    ck_assert_int_eq(array_get(ary, 2), c);
    delete(ary);
    delete(a);
} END_TEST

int
main(void) {
    return 0;
}
