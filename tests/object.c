#include <check.h>
#include <stdio.h>
#include <libooc/string.conflict.h>

START_TEST(class) {
    o_obj obj = new(Object);
    o_obj str = new(String, "a");
    ck_assert(Object_class(obj) == Object);
    ck_assert(Object_class(str) == String);
    delete(str);
    delete(obj);
} END_TEST

START_TEST(class_name) {
    o_obj obj = new(Object);
    o_obj str = new(String, "a");
    ck_assert(Object_class_name(obj) == "Object");
    ck_assert(Object_class_name(str) == "String");
    delete(str);
    delete(obj);
} END_TEST

START_TEST(is_a) {
    o_obj obj = new(Object);
    o_obj str = new(String, "a");
    ck_assert(Object_is_a(obj, Object));
    ck_assert(!Object_is_a(obj, String));
    ck_assert(Object_is_a(str, Object));
    ck_assert(Object_is_a(str, String));
    delete(str);
    delete(obj);
} END_TEST

Suite *
object_suite(void) {
    Suite * s = suite_create("Object");

    TCase * t = tcase_create("Core");
    tcase_add_test(t, is_a);
    suite_add_tcase(s, t);

    return s;
}
