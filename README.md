#   What's libooc

libooc is library with object oriented written in c.

#   Examples

*   String

        String_init();
        void * a = new(String, "a");
        delete(a);

*   Static String

        Value_init();
        Value a;
        Value_type(&a, StaticString);
        Value_set_str(&a, "a");
        Value_get_str(&a);

*   Hash

        String_init();
        void * a = new(String, "a");
        void * b = new(String, "b");

        Hash_init();
        void * hash = new(Hash);
        Hash_set(hash, a, b);
        Hash_get(hash, a);
        delete(hash);

*   Array

        Array_init();
        void * ary = new(Array);
        Array_push(ary, a);
        Array_push(ary, b);
        Array_each(ary, Array_print);
        delete(ary);

#   How to get libooc

Use following command:

    $ git clone git@github.com:xsoameix/libooc.git

#   How to compile and install

1.  If `./configure` does not exist or is older than configure.in,
    run autoconf to (re)generate configure.

2.  Run `./configure`, which will generate config.h and Makefile.

3.  Run `make`.

4.  Run `make install`.

#   Usage

*   Hash

        #include <libooc/hash.h>

*   Array

        #include <libooc/array.h>

*   String

        #include <libooc/string.conflict.h>

*   Static String

        #include <libooc/value.h>

#   Copying

See the file `COPYING`.
