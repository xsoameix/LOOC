#include <check.h>
#include <libooc/string.conflict.h>

START_TEST(wrong_method_error) {
    o_obj obj = new(Object);
    char buf[BUFSIZ];
    setbuf(stderr, buf);
    String_strip(obj);
    char * err = "WrongMethodError: calling String#strip on #<Object:0x";
    ck_assert(strncmp(buf, err, strlen(err)) == 0);
    delete(obj);
} END_TEST

Suite *
macro_suite(void) {
    Suite * s = suite_create("Macro");

    TCase * t = tcase_create("Core");
    tcase_add_test(t, wrong_method_error);
    suite_add_tcase(s, t);

    return s;
}
