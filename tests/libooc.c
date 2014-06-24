#include <check.h>
#include <stdlib.h>
#include <libooc/object.h>

Suite * object_suite(void);
Suite * array_suite(void);
Suite * macro_suite(void);

Suite *
libooc_suite(void) {
    return suite_create("libooc");
}

int
main(void) {
    SRunner * r = srunner_create(libooc_suite());
    srunner_add_suite(r, macro_suite());
    srunner_add_suite(r, object_suite());
    srunner_add_suite(r, array_suite());
    srunner_run_all(r, CK_NORMAL);
    o_uint failed = srunner_ntests_failed(r);
    srunner_free(r);
    return (failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
