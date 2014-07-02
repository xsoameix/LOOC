#   What's libooc

libooc is library with object oriented written in c.

#   How to install

1.  Download this repository.

        $ git clone https://github.com/xsoameix/libooc -b develop

2.  Compile.

        $ cd libooc
        $ ./autogen.sh
        $ make

3.  Install

        $ sudo make install

#   Define your class

##  Example: Circle

*   Interface: `main.c`

        #include <stdio.h>
        #include <libooc/object_type.h>
        #include "circle.h"
        
        int
        main(void) {
            o circle = new(Circle, 2);
            int area = Circle_area(circle);
            printf("circle area: %d\n", area);
            delete(circle);
            return 0;
        }

Compile:
(make sure your have installed libooc)

    $ cc -o main main.c circle.c -I/usr/local/include/libooc-0.0.1 -L/usr/local/lib -looc-0.0.1

Run:

    $ ./main
    circle area: 4

*   Implementation: `circle.c`

        #include <stdlib.h>
        
        // struct definition of Circle
        #include "circle.struct.h"
        
        // inherit form Object
        O_DEF_CLASS(Circle, Object)
        
        // constructor
        override
        def(ctor, void : va_list * @args) {
            self->radius = va_arg(* args, int);
        }
        
        // destructor
        override
        def(dtor, void) {
            free(self);
        }
        
        // public method
        
        def(area, int) {
            // call private method
            return my_pow(self, self->radius, 2);
        }
        
        // private method
        private
        def(my_pow, int : int @base . int @exponent) {
            int result = 1;
            while(exponent > 0) {
                result *= base;
                exponent -= 1;
            }
            return result;
        }

*   Struct definition: `circle.struct.h`

        #ifndef CIRCLE_STRCUT_H
        #define CIRCLE_STRCUT_H
        
        // get the parent's struct definition
        #include <libooc/object.struct.h>
        // declare the methods
        #include "circle.h"
        
        struct Circle {
            struct Object super;
            int radius;
        };
        
        // declare virtual table(like C++) of Circle
        O_DEF_CLASS_STRUCT()
        
        #endif

*   Public methods declaration: `circle.h`

    (I create a script for vim, the script can auto create/update this file according to `circle.c`)

        #ifndef O_CIRCLE_H
        #define O_CIRCLE_H
        
        #include <libooc/object.h>
        
        // Please put included files here.
        
        
        // Please put macros/type declarations here.
        
        
        #undef O_CLASS
        #undef O_PARENT
        #define O_CLASS Circle
        #define O_PARENT Object
        #define O_Circle_OVERRIDE_METHODS_LEN 2
        #define O_Circle_PUBLIC_METHODS_LEN 1
        #define O_Circle_PRIVATE_METHODS_LEN 1
        #define O_Circle_OVERRIDE_METHOD_0 ctor, void, (va_list * args, args)
        #define O_Circle_OVERRIDE_METHOD_1 dtor, void
        #define O_Circle_PUBLIC_METHOD_0 area, int
        #define O_Circle_PRIVATE_METHOD_0 my_pow, int, (int base, base), (int exponent, exponent)
        #define O_Circle_ctor O_Circle_OVERRIDE_METHOD_0
        #define O_Circle_dtor O_Circle_OVERRIDE_METHOD_1
        #define O_Circle_area O_Circle_PUBLIC_METHOD_0
        #define O_Circle_my_pow O_Circle_PRIVATE_METHOD_0
        O_DEF_GLOBAL_METHODS()
        
        #endif

#   Available Classes in libooc

*   Object

        o obj = new(Object);
        Object_class(obj); // => Object
        Object_is_a(obj, Object); // => true
        Object_class_name(obj); // => "Object"
        String_strip(obj); // stderr => "WrongMethodError: calling String#strip on #<Object:0xdeadbeaf>"
        delete(obj);

*   String

        o a = new(String, "a");
        Object_class(a); // => String
        Object_is_a(a, Object); // => true
        Object_class_name(a); // => "String"
        delete(a);

*   Static String

        Value a;
        Value_type(&a, StaticString);
        Value_set_str(&a, "a");
        Value_get_str(&a);

*   Hash

        o a = new(String, "a");
        o b = new(String, "b");

        o hash = new(Hash);
        H_SET(hash, a, b);
        H_GET(hash, a); // => b

        // nested function (gcc extension)
        H_ITOR(print) {
            printf("key: %s, value: %s\n", KEY, VALUE);
        }

        H_EACH(hash, print);
        delete(hash);

    If you have name conflict problem:

        o_obj hash = new(Hash);
        Hash_set(hash, a, b);
        Hash_get(hash, a);

        void print(o_obj key, o_obj value) {
            printf("key: %s, value: %s\n", key, value);
        }

        Hash_each(hash, print);

*   Array

        o ary = new(Array);
        PUSH(ary, a);
        PUSH(ary, b);

        ITOR(print) {
            printf("%zu: %s\n", INDEX, Object_inspect(ITEM));
        }

        EACH(ary, print);
        delete(ary);

    If you have name conflict problem:

        o_obj ary = new(Array);
        Array_push(ary, a);
        Array_push(ary, b);

        void print(o_obj item, o_uint index) {
            printf("%zu: %s\n", index, Object_inspect(item));
        }

        Array_each(ary, print);

#   Copying

See the file `COPYING`.
