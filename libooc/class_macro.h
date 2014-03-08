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
#define ARG_SEPERATOR() ,
#define ARG_NO_SEPERATOR()
#define ARG_TYPE(type, ...) , type
#define ARG_NAME(type, name) , name
#define ARG_SELF_() _self
#define ARG_SELF() self

// LOOP macro usage:
// 1.  #define FUNC(arg1) arg1
//     LOOP(FUNC, ARG_SEPERATOR, ((A), (B), (C), (D), (E), (F)))
//     = LOOP__(FUNC, ARG_SEPERATOR, (A), (B), (C), (D), (E), (F))
//     = LOOP___(FUNC, ARG_SEPERATOR, A, B, C, D, E, F)
//     => A, B, C, D, E, F
//
// 2.  #define FUNC(arg1, ...) arg1
//     LOOP__(FUNC, ARG_SEPERATOR, (A, B), (B), (C), (D), (E), (F))
//     => A, B, C, D, E, F
#define LOOP_ITER_(func, n) func ## n
#define LOOP_ITER(func, n) LOOP_ITER_(func, n)
#define LOOP1__(func, _1) func(_1)
#define LOOP1_(func, _1) func _1
#define L1_LOOP0(loop, func, ...)
#define L1_LOOP1(loop, func, _1) loop(func, _1)
#define L1_LOOP2(loop, func, _1, _2) \
        L1_LOOP1(loop, func, _1)L1_LOOP1(loop, func, _2)
#define L1_LOOP3(loop, func, _1, _2, _3) \
        L1_LOOP1(loop, func, _1)L1_LOOP2(loop, func, _2, _3)
#define L1_LOOP4(loop, func, _1, _2, _3, _4) \
        L1_LOOP2(loop, func, _1, _2)L1_LOOP2(loop, func, _3, _4)
#define L1_LOOP5(loop, func, _1, _2, _3, _4, _5) \
        L1_LOOP2(loop, func, _1, _2)L1_LOOP3(loop, func, _3, _4, _5)
#define L1_LOOP6(loop, func, _1, _2, _3, _4, _5, _6) \
        L1_LOOP3(loop, func, _1, _2, _3)L1_LOOP3(loop, func, _4, _5, _6)
#define L1_LOOP7(loop, func, _1, _2, _3, _4, _5, _6, _7) \
        L1_LOOP3(loop, func, _1, _2, _3)L1_LOOP4(loop, func, _4, _5, _6, _7)
#define L1_LOOP8(loop, func, _1, _2, _3, _4, _5, _6, _7, _8) \
        L1_LOOP4(loop, func, _1, _2, _3, _4)L1_LOOP4(loop, func, _5, _6, _7, _8)
#define L1_LOOP9(loop, func, _1, _2, _3, _4, _5, _6, _7, _8, _9) \
        L1_LOOP4(loop, func, _1, _2, _3, _4)L1_LOOP5(loop, func, _5, _6, _7, _8, _9)
#define L1_LOOP10(loop, func, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10) \
        L1_LOOP5(loop, func, _1, _2, _3, _4, _5)L1_LOOP5(loop, func, _6, _7, _8, _9, _10)
#define L1_LOOP11(loop, func, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11) \
        L1_LOOP5(loop, func, _1, _2, _3, _4, _5)L1_LOOP6(loop, func, _6, _7, _8, _9, _10, _11)
#define L1_LOOP12(loop, func, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12) \
        L1_LOOP6(loop, func, _1, _2, _3, _4, _5, _6)L1_LOOP6(loop, func, _7, _8, _9, _10, _11, _12)
#define LOOP____(loop, func, ...) LOOP_ITER(L1_LOOP, ARG_SIZE(__VA_ARGS__))(loop, func, __VA_ARGS__)
#define LOOP___(...) LOOP____(LOOP1__, __VA_ARGS__)
#define LOOP__(...) LOOP____(LOOP1_, __VA_ARGS__)
#define LOOP_(...) __VA_ARGS__
#define LOOP(func, args) LOOP__(func, LOOP_ args)
#define L2_LOOP1__(func, _1) func(_1)
#define L2_LOOP1_(func, _1) func _1
#define L2_LOOP0(loop, func, ...)
#define L2_LOOP1(loop, func, _1) loop(func, _1)
#define L2_LOOP2(loop, func, _1, _2) \
        L2_LOOP1(loop, func, _1)L2_LOOP1(loop, func, _2)
#define L2_LOOP3(loop, func, _1, _2, _3) \
        L2_LOOP1(loop, func, _1)L2_LOOP2(loop, func, _2, _3)
#define L2_LOOP4(loop, func, _1, _2, _3, _4) \
        L2_LOOP2(loop, func, _1, _2)L2_LOOP2(loop, func, _3, _4)
#define L2_LOOP5(loop, func, _1, _2, _3, _4, _5) \
        L2_LOOP2(loop, func, _1, _2)L2_LOOP3(loop, func, _3, _4, _5)
#define L2_LOOP6(loop, func, _1, _2, _3, _4, _5, _6) \
        L2_LOOP3(loop, func, _1, _2, _3)L2_LOOP3(loop, func, _4, _5, _6)
#define L2_LOOP7(loop, func, _1, _2, _3, _4, _5, _6, _7) \
        L2_LOOP3(loop, func, _1, _2, _3)L2_LOOP4(loop, func, _4, _5, _6, _7)
#define L2_LOOP8(loop, func, _1, _2, _3, _4, _5, _6, _7, _8) \
        L2_LOOP4(loop, func, _1, _2, _3, _4)L2_LOOP4(loop, func, _5, _6, _7, _8)
#define L2_LOOP9(loop, func, _1, _2, _3, _4, _5, _6, _7, _8, _9) \
        L2_LOOP4(loop, func, _1, _2, _3, _4)L2_LOOP5(loop, func, _5, _6, _7, _8, _9)
#define L2_LOOP10(loop, func, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10) \
        L2_LOOP5(loop, func, _1, _2, _3, _4, _5)L2_LOOP5(loop, func, _6, _7, _8, _9, _10)
#define L2_LOOP11(loop, func, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11) \
        L2_LOOP5(loop, func, _1, _2, _3, _4, _5)L2_LOOP6(loop, func, _6, _7, _8, _9, _10, _11)
#define L2_LOOP12(loop, func, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12) \
        L2_LOOP6(loop, func, _1, _2, _3, _4, _5, _6)L2_LOOP6(loop, func, _7, _8, _9, _10, _11, _12)
#define L2_LOOP____(loop, func, ...) LOOP_ITER(L2_LOOP, ARG_SIZE(__VA_ARGS__))(loop, func, __VA_ARGS__)
#define L2_LOOP___(...) L2_LOOP____(L2_LOOP1__, __VA_ARGS__)
#define L2_LOOP__(...) L2_LOOP____(L2_LOOP1_, __VA_ARGS__)
#define L2_LOOP_(...) __VA_ARGS__
#define L2_LOOP(func, args) L2_LOOP__(func, L2_LOOP_ args)

// METHOD macros usage:
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
//     #undef CLASS_UNDERSCORE
//     #define CLASS FOO
//     #define CLASS_UNDERSCORE foo
//     #define FOO_OVERRIDE_METHODS \
//         (FOO_CTOR)
//     #define FOO_METHODS \
//         (FOO_LEN)
//     #define FOO_CTOR ctor, ctor, void, (va_list *, args_ptr)
//     //                v     v     v              v
//     //               arg1  arg2  arg3          arg4-N
//     // arg1:   parent's method name to be overidded
//     // arg2:   method name
//     // arg3:   no return
//     // arg4-N: one argument
//
//     #define FOO_BAR bar,  size_t, (size_t, a), (size_t, b)
//     //               v      v              v   v
//     //              arg1   arg2           arg3-N
//     // arg1:   method name
//     // arg2:   return type
//     // arg3-N: two arguments
//
//     METHODS(FOO_METHODS)
//
//     #endif
//
// `foo.c`
//
//     CLASS_INIT(Object, CLASS_SIZE_FIXED, (FOO_OVERRIDE_METHODS), (FOO_METHODS));
//     //           ^
//     //       superclass
//     
//     METHOD(FOO_BAR) {
//         return self->bar + a + b;
//     }
#define METHOD_CALL__(__class, func, ret, ...) \
    struct __class * _self = self; \
    const struct __class ## Class * _class = (struct __class ## Class *) _self->class; \
    return _class->func(ARG_SELF_()LOOP__(ARG_NAME, __VA_ARGS__));
#define METHOD_CALL_(...) METHOD_CALL__(__VA_ARGS__)
#define METHOD_CALL(...) METHOD_CALL_(CLASS, __VA_ARGS__)
#define METHOD_PUBLIC___(class, name, ret, ...) ret class ## _ ## name(void * ARG_SELF()L2_LOOP__(ARG_TYPE, __VA_ARGS__))
#define METHOD_PUBLIC__(...) METHOD_PUBLIC___(__VA_ARGS__)
#define METHOD_PUBLIC_(...) METHOD_PUBLIC__(CLASS_UNDERSCORE, __VA_ARGS__);
#define METHOD_PUBLIC(...) METHOD_PUBLIC__(CLASS_UNDERSCORE, __VA_ARGS__)
#define METHODS__(class, class_underscore, ...) \
    extern const void * class; \
    \
    void class_underscore ## _init(void); \
    LOOP__(METHOD_PUBLIC_, __VA_ARGS__)
#define METHODS_(...) METHODS__(__VA_ARGS__)
#define METHODS(...) METHODS_(CLASS, CLASS_UNDERSCORE, __VA_ARGS__)
#define METHOD____(class, name, ret, ...) static ret class ## _ ## name(struct class * ARG_SELF()L2_LOOP__(ARG_TYPE, __VA_ARGS__))
#define METHOD___(...) METHOD____(__VA_ARGS__)
#define METHOD__(...) METHOD___(CLASS, __VA_ARGS__)
#define METHOD_(...) METHOD___(CLASS, __VA_ARGS__);
#define METHOD(method) \
    METHOD_PUBLIC(method) { METHOD_CALL(method) } \
    METHOD__(method)
#define METHOD_OVERRIDE____(class, super, name, ret, ...)  METHOD___(class, name, ret, __VA_ARGS__)
#define METHOD_OVERRIDE___(...) METHOD_OVERRIDE____(__VA_ARGS__)
#define METHOD_OVERRIDE__(super, ...) METHOD__(__VA_ARGS__)
#define METHOD_OVERRIDE_(...) METHOD_OVERRIDE___(CLASS, __VA_ARGS__);
#define METHOD_OVERRIDE(method) METHOD_OVERRIDE__(method)
#define METHOD_IN_STRUCT__(class, name, ret, ...) ret (* name)(struct class * ARG_SELF()L2_LOOP__(ARG_TYPE, __VA_ARGS__));
#define METHOD_IN_STRUCT_(...) METHOD_IN_STRUCT__(__VA_ARGS__)
#define METHOD_IN_STRUCT(...) METHOD_IN_STRUCT_(CLASS, __VA_ARGS__)
#define METHODS_SET__(class, class_underscore, name, ret, ...) , class_underscore ## _ ## name, class ## _ ## name
#define METHODS_SET_(...) METHODS_SET__(__VA_ARGS__)
#define METHODS_SET(...) METHODS_SET_(CLASS, CLASS_UNDERSCORE, __VA_ARGS__)
#define METHODS_SET_OVERRIDE__(class, super, name, ret, ...) , super, class ## _ ## name
#define METHODS_SET_OVERRIDE_(...) METHODS_SET_OVERRIDE__(__VA_ARGS__)
#define METHODS_SET_OVERRIDE(...) METHODS_SET_OVERRIDE_(CLASS, __VA_ARGS__)
#define METHOD_INIT__(_class, name, ...) \
    if(select == (func) _class ## _ ## name) { \
        * (func *) &class->name = method; \
    } else
#define METHOD_INIT_(...) METHOD_INIT__(__VA_ARGS__)
#define METHOD_INIT(...) METHOD_INIT_(CLASS_UNDERSCORE, __VA_ARGS__)
#define CLASS_SIZE(size) size
#define CLASS_INIT__(_class, class_underscore, _super, is_variable_size, override_methods, methods) \
    struct _class ## Class { \
        const struct Class class; \
        LOOP(METHOD_IN_STRUCT, methods) \
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
            LOOP(METHOD_INIT, methods) {} \
        } \
    } \
    \
    LOOP(METHOD_OVERRIDE_, override_methods) \
    LOOP(METHOD_, methods) \
    \
    void \
    class_underscore ## _init(void) { \
        if(!_class ## Class) { \
            _class ## Class = new(Class, \
                    Class, #_class "Class", \
                    sizeof(struct _class ## Class), \
                    0, \
                    ctor, _class ## Class_ctor, \
                    0); \
        } \
        if(!_class) { \
            _class = new(_class ## Class, \
                    _super, #_class, \
                    sizeof(struct _class), \
                    CLASS_SIZE(is_variable_size)LOOP(METHODS_SET_OVERRIDE, override_methods)LOOP(METHODS_SET, methods), \
                    0); \
        } \
    }
#define CLASS_INIT_(...) CLASS_INIT__(__VA_ARGS__)
#define CLASS_INIT(...) CLASS_INIT_(CLASS, CLASS_UNDERSCORE, __VA_ARGS__)
#define CLASS_SIZE_FIXED 0
#define CLASS_SIZE_VARIABLE 1

#endif
