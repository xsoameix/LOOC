#include <check.h>
#include "../libooc/string.conflict.h"
#include "../libooc/array.h"

START_TEST(test_array_get) {
    string_init();
    void * a = new(String, "a");
    array_init();
    void * ary = new(Array);
    array_push(ary, a);
    ck_assert_int_eq(array_get(ary, 0), a);
    delete(ary);
    delete(a);
} END_TEST

int
main(void) {
    return 0;
}
