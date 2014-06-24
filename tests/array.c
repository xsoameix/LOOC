#include <check.h>
#include <stdlib.h>
#include <libooc/string.conflict.h>
#include <libooc/array.h>

START_TEST(get) {
    o_obj a = new(String, "a");
    o_obj b = new(String, "b");
    o_obj c = new(String, "c");
    o_obj ary = new(Array);
    Array_push(ary, a);
    Array_push(ary, b);
    Array_push(ary, c);
    ck_assert(Array_get(ary, 0) == a);
    ck_assert(Array_get(ary, 1) == b);
    ck_assert(Array_get(ary, 2) == c);
    ck_assert(Array_get(ary, 3) == NULL);
    ck_assert(Array_get(ary, -1) == c);
    ck_assert(Array_get(ary, -2) == b);
    ck_assert(Array_get(ary, -3) == a);
    ck_assert(Array_get(ary, -4) == NULL);
    delete(ary);
    delete(a);
} END_TEST

Suite *
array_suite(void) {
    Suite * s = suite_create("Array");

    TCase * t = tcase_create("Core");
    tcase_add_test(t, get);
    suite_add_tcase(s, t);

    return s;
}
