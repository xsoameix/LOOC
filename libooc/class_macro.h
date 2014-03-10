#ifndef CLASS_MACRO_H
#define CLASS_MACRO_H

// ARGS macro usage:
// 1.  ARG_SIZE()
//     =>  0
//
// 2.  ARG_SIZE(A, B, C)
//     =>  3
#define ARG_SIZE(...) ARG_EXPAND(0, ## __VA_ARGS__, \
    19, 18, 17, 16, 15, 14, 13, 12, 11, 10, \
     9,  8,  7,  6,  5,  4,  3,  2,  1,  0)
#define ARG_EXPAND(...) ARG_BUFFER(__VA_ARGS__)
#define ARG_BUFFER( \
        _1,   _2,  _3,  _4,  _5,  _6,  _7,  _8,  _9, _10, \
        _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, \
        n, ...) n
#define ARG_TYPE(type, ...) , type
#define ARG_NAME_SPREAD(void, type, name) , name
#define ARG_NAME(void, args) ARG_NAME_SPREAD(void, args)
#define ARG_SELF_() _self
#define ARG_SELF() self

// LOOP macro usage:
// 1.  #define FUNC(arg1, arg2) [arg1, arg2]
//       LOOP_SINGLE(FUNC, var, ((A), (B), (C), (D), (E), (F)))
//     = LOOP_MULTIPLE(FUNC, var, (A), (B), (C), (D), (E), (F))
//     = [var, A][var, B][var, C][var, D][var, E][var, F]
#define LOOP_SPREAD(...) __VA_ARGS__
#define LOOP_ITER_(func, n) func ## n
#define LOOP_ITER(func, n) LOOP_ITER_(func, n)
#define LOOP_0(func, var, ...)
#define LOOP_1(func, var, _1) func(var, LOOP_SPREAD _1)
#define LOOP_2(func, var, _1, _2) \
        LOOP_1(func, var, _1)LOOP_1(func, var, _2)
#define LOOP_3(func, var, _1, _2, _3) \
        LOOP_1(func, var, _1)LOOP_2(func, var, _2, _3)
#define LOOP_4(func, var, _1, _2, _3, _4) \
        LOOP_2(func, var, _1, _2)LOOP_2(func, var, _3, _4)
#define LOOP_5(func, var, _1, _2, _3, _4, _5) \
        LOOP_2(func, var, _1, _2)LOOP_3(func, var, _3, _4, _5)
#define LOOP_6(func, var, _1, _2, _3, _4, _5, _6) \
        LOOP_3(func, var, _1, _2, _3)LOOP_3(func, var, _4, _5, _6)
#define LOOP_7(func, var, _1, _2, _3, _4, _5, _6, _7) \
        LOOP_3(func, var, _1, _2, _3)LOOP_4(func, var, _4, _5, _6, _7)
#define LOOP_8(func, var, _1, _2, _3, _4, _5, _6, _7, _8) \
        LOOP_4(func, var, _1, _2, _3, _4)LOOP_4(func, var, _5, _6, _7, _8)
#define LOOP_9(func, var, _1, _2, _3, _4, _5, _6, _7, _8, _9) \
        LOOP_4(func, var, _1, _2, _3, _4)LOOP_5(func, var, _5, _6, _7, _8, _9)
#define LOOP_10(func, var, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10) \
        LOOP_5(func, var, _1, _2, _3, _4, _5)LOOP_5(func, var, _6, _7, _8, _9, _10)
#define LOOP_11(func, var, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11) \
        LOOP_5(func, var, _1, _2, _3, _4, _5)LOOP_6(func, var, _6, _7, _8, _9, _10, _11)
#define LOOP_12(func, var, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12) \
        LOOP_6(func, var, _1, _2, _3, _4, _5, _6)LOOP_6(func, var, _7, _8, _9, _10, _11, _12)
#define LOOP_MULTIPLE(func, var, ...) LOOP_ITER(LOOP_, ARG_SIZE(__VA_ARGS__))(func, var, __VA_ARGS__)
#define LOOP_SINGLE(func, var, args) LOOP_MULTIPLE(func, var, LOOP_SPREAD args)
#define LOOP_L2_0(func, ...)
#define LOOP_L2_1(func, _1) func _1
#define LOOP_L2_2(func, _1, _2) \
        LOOP_L2_1(func, _1)LOOP_L2_1(func, _2)
#define LOOP_L2_3(func, _1, _2, _3) \
        LOOP_L2_1(func, _1)LOOP_L2_2(func, _2, _3)
#define LOOP_L2_4(func, _1, _2, _3, _4) \
        LOOP_L2_2(func, _1, _2)LOOP_L2_2(func, _3, _4)
#define LOOP_L2_5(func, _1, _2, _3, _4, _5) \
        LOOP_L2_2(func, _1, _2)LOOP_L2_3(func, _3, _4, _5)
#define LOOP_L2_6(func, _1, _2, _3, _4, _5, _6) \
        LOOP_L2_3(func, _1, _2, _3)LOOP_L2_3(func, _4, _5, _6)
#define LOOP_L2_7(func, _1, _2, _3, _4, _5, _6, _7) \
        LOOP_L2_3(func, _1, _2, _3)LOOP_L2_4(func, _4, _5, _6, _7)
#define LOOP_L2_8(func, _1, _2, _3, _4, _5, _6, _7, _8) \
        LOOP_L2_4(func, _1, _2, _3, _4)LOOP_L2_4(func, _5, _6, _7, _8)
#define LOOP_L2_9(func, _1, _2, _3, _4, _5, _6, _7, _8, _9) \
        LOOP_L2_4(func, _1, _2, _3, _4)LOOP_L2_5(func, _5, _6, _7, _8, _9)
#define LOOP_L2_10(func, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10) \
        LOOP_L2_5(func, _1, _2, _3, _4, _5)LOOP_L2_5(func, _6, _7, _8, _9, _10)
#define LOOP_L2_11(func, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11) \
        LOOP_L2_5(func, _1, _2, _3, _4, _5)LOOP_L2_6(func, _6, _7, _8, _9, _10, _11)
#define LOOP_L2_12(func, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12) \
        LOOP_L2_6(func, _1, _2, _3, _4, _5, _6)LOOP_L2_6(func, _7, _8, _9, _10, _11, _12)
#define LOOP_L2_MULTIPLE(func, ...) LOOP_ITER(LOOP_L2_, ARG_SIZE(__VA_ARGS__))(func, __VA_ARGS__)

// macros usage:
//
// `foo.struct.h`
//
//     #ifndef FOO_STRUCT_H
//     #define FOO_STRUCT_H
//     
//     #include <libooc/class.struct.h>
//
//     struct Foo {
//         const struct Class * class;
//         size_t bar;
//     };
//
//     #endif
//
// `foo.h`
//
//     #ifndef FOO_H
//     #define FOO_H
//     
//     #include <libooc/class.h>
//
//     #undef CLASS
//     #undef CLASS_UNDERSCORE()
//     #define CLASS Foo
//     #define CLASS_MACRO_NAME FOO
//     #define FOO_OVERRIDE_METHODS \
//         (FOO_ctor)
//     #define FOO_METHODS \
//         (FOO_len)
//     #define FOO_ctor ctor, void, (va_list * args_ptr, args_ptr)
//     //                v     v                       v
//     //                1.    2.                      3.
//     // 1:   The method name is 'ctor', and override parent's method.
//     // 2:   No return.
//     // 3:   The first argument.
//     //      The type is 'va_list * args_ptr', and the variable name is 'args_ptr'
//
//     #define FOO_bar bar, size_t, (size_t a, a), (size_t b, b)
//     //               v     v           v              v
//     //               1.    2.          3.             4.
//     // 1:   The method name is 'bar'.
//     // 2:   The return type is 'size_t'.
//     // 3:   The first argument.
//     //      The type is 'size_t a', and the variable name is 'a'
//     // 4:   The second argument.
//     //      The type is 'size_t b', and the variable name is 'b'
//
//     def_methods()
//
//     #endif
//
// `foo.c`
//
//     def_class(Object, CLASS_SIZE_FIXED)
//     //           ^
//     //       superclass
//
//     def_override(ctor) {
//         self->bar = 10;
//     }
//
//     def(bar) {
//         return self->bar + a + b;
//     }

// === *.h ===
// public macros:
//     def_methods(...)
#define METHOD_PUBLIC_DEFINE__(class, _void, name, ret, ...) ret class ## _ ## name(void * ARG_SELF()LOOP_L2_MULTIPLE(ARG_TYPE, __VA_ARGS__))
#define METHOD_PUBLIC_DEFINE_(...) METHOD_PUBLIC_DEFINE__(__VA_ARGS__)
#define METHOD_PUBLIC_DEFINE(...) METHOD_PUBLIC_DEFINE_(CLASS, __VA_ARGS__)
#define METHOD_PUBLIC_DECLARE(...) METHOD_PUBLIC_DEFINE(__VA_ARGS__);
#define METHODS__(class, ...) \
    extern const void * class; \
    \
    void class ## _init(void); \
    LOOP_MULTIPLE(METHOD_PUBLIC_DECLARE, void, __VA_ARGS__)
#define METHODS_(...) METHODS__(__VA_ARGS__)
#define def_public_methods() METHODS_(CLASS, CLASS_MACRO(METHODS))

// === *.c ===
// public macros:
//     def_class(...),
//     def_override(...),
//     def(...)
#define METHOD_STATIC_DEFINE__(class, class_underscore, void, name, ret, ...) static ret class_underscore ## _ ## name(struct class * ARG_SELF()LOOP_L2_MULTIPLE(ARG_TYPE, __VA_ARGS__))
#define METHOD_STATIC_DEFINE_(...) METHOD_STATIC_DEFINE__(__VA_ARGS__)
#define METHOD_STATIC_DEFINE(...) METHOD_STATIC_DEFINE_(CLASS, CLASS_UNDERSCORE(), __VA_ARGS__)
#define METHOD_STATIC_DECLARE(...) METHOD_STATIC_DEFINE(__VA_ARGS__);
#define METHOD_CALL__(__class, func, ret, ...) \
    struct __class * _self = self; \
    const struct __class ## Class * _class = (struct __class ## Class *) _self->class; \
    return _class->func(ARG_SELF_()LOOP_MULTIPLE(ARG_NAME, void, __VA_ARGS__));
#define METHOD_CALL_(...) METHOD_CALL__(__VA_ARGS__)
#define METHOD_CALL(...) METHOD_CALL_(CLASS, __VA_ARGS__)
#define def_SELECT_(name, n) name ## n
#define def_SELECT(name, n) def_SELECT_(name, n)
#define def_0(method, ...) \
    METHOD_PUBLIC_DEFINE(void, CLASS_MACRO(method)) { METHOD_CALL(CLASS_MACRO(method)) } \
    METHOD_STATIC_DEFINE(void, CLASS_MACRO(method))
#define def_1(method, ...) METHOD_STATIC_DEFINE(void, CLASS_MACRO(method))
#define def(method, ...) def_SELECT(def_, ARG_SIZE(__VA_ARGS__))(method, __VA_ARGS__)
#define METHOD_POINTER_DEFINE__(class, void, name, ret, ...) ret (* name)(struct class * ARG_SELF()LOOP_L2_MULTIPLE(ARG_TYPE, __VA_ARGS__));
#define METHOD_POINTER_DEFINE_(...) METHOD_POINTER_DEFINE__(__VA_ARGS__)
#define METHOD_POINTER_DEFINE(...) METHOD_POINTER_DEFINE_(CLASS, __VA_ARGS__)
#define CLASS_UNDERSCORE__(class) _ ## class
#define CLASS_UNDERSCORE_(class) CLASS_UNDERSCORE__(class)
#define CLASS_UNDERSCORE() CLASS_UNDERSCORE_(CLASS)
#define CLASS_MACRO__(class, name) class ## _ ## name
#define CLASS_MACRO_(class, name) CLASS_MACRO__(class, name)
#define CLASS_MACRO(name) CLASS_MACRO_(CLASS_MACRO_NAME, name)
#define CLASS_INIT__(class, class_underscore, void, name, ret, ...) , class ## _ ## name, class_underscore ## _ ## name
#define CLASS_INIT_(...) CLASS_INIT__(__VA_ARGS__)
#define CLASS_INIT(...) CLASS_INIT_(CLASS, CLASS_UNDERSCORE(), __VA_ARGS__)
#define CLASS_INIT_OVERRIDE__(class, super, name, ret, ...) , super ## _ ## name, class ## _ ## name
#define CLASS_INIT_OVERRIDE_(...) CLASS_INIT_OVERRIDE__(__VA_ARGS__)
#define CLASS_INIT_OVERRIDE(...) CLASS_INIT_OVERRIDE_(CLASS_UNDERSCORE(), __VA_ARGS__)
#define CLASS_CTOR__(_class, void, name, ...) \
    if(select == (func) _class ## _ ## name) { \
        * (func *) &class->name = method; \
    } else
#define CLASS_CTOR_(...) CLASS_CTOR__(__VA_ARGS__)
#define CLASS_CTOR(...) CLASS_CTOR_(CLASS, __VA_ARGS__)
#define CLASS_SIZE(size) size
#define CLASS_SIZE_FIXED 0
#define CLASS_SIZE_VARIABLE 1
#define CLASS_DEFINE__(_class, _super, is_variable_size, override_methods, methods) \
    struct _class ## Class { \
        const struct Class class; \
        LOOP_SINGLE(METHOD_POINTER_DEFINE, void, methods) \
    }; \
    \
    static const void * _class ## Class; \
           const void * _class; \
    \
    static void \
    _class ## Class_ctor(struct _class ## Class * class, va_list * args_ptr) { \
        /* inherit */ \
        const struct Class * superclass = ((const struct Class *) class)->class->super; \
        superclass->ctor(class, args_ptr); \
        \
        /* override */ \
        va_list args; \
        va_copy(args, * args_ptr); \
        typedef void (* func)(); \
        func select, method; \
        while(select = va_arg(args, func)) { \
            method = va_arg(args, func); \
            LOOP_SINGLE(CLASS_CTOR, void, methods) {} \
        } \
    } \
    \
    LOOP_SINGLE(METHOD_STATIC_DECLARE, void, override_methods) \
    LOOP_SINGLE(METHOD_STATIC_DECLARE, void, methods) \
    \
    void \
    _class ## _init(void) { \
        if(!_class ## Class) { \
            _class ## Class = new(Class, \
                    Class, #_class "Class", \
                    sizeof(struct _class ## Class), \
                    0, \
                    Object_ctor, _class ## Class_ctor, \
                    0); \
        } \
        if(!_class) { \
            _class = new(_class ## Class, \
                    _super, #_class, \
                    sizeof(struct _class), \
                    CLASS_SIZE(is_variable_size)LOOP_SINGLE(CLASS_INIT_OVERRIDE, _super, override_methods)LOOP_SINGLE(CLASS_INIT, temp, methods), \
                    0); \
        } \
    }
#define CLASS_DEFINE_(...) CLASS_DEFINE__(__VA_ARGS__)
#define def_class(...) CLASS_DEFINE_(CLASS, __VA_ARGS__, (CLASS_MACRO(OVERRIDE_METHODS)), (CLASS_MACRO(METHODS)))

#endif
