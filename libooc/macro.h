#ifndef O__MACRO_H
#define O__MACRO_H

#define O_DEF_GLOBAL_METHODS() O_DEF_GLOBAL_METHODS_(O_CLASS)
#define O_DEF_GLOBAL_METHODS_(class) O_DEF_GLOBAL_METHODS__(class)
#define O_DEF_GLOBAL_METHODS__(_class) \
        extern const void * _class; \
        \
        void _class ## _init(void); \
        O_DECL_OVERRIDE_METHODS \
        O_DECL_PUBLIC_METHODS

#define O_DECL_OVERRIDE_METHODS O_OVERRIDE_METHODS(O_DECL_GLOBAL_FUNC)
#define O_DECL_PUBLIC_METHODS   O_PUBLIC_METHODS(O_DECL_GLOBAL_FUNC)
#define O_DECL_GLOBAL_FUNC(...) O_DEF_GLOBAL_FUNC(__VA_ARGS__);
#define O_DEF_GLOBAL_FUNC(class, parent, name, ret, ...) \
        ret class ## _ ## name(void * O_DECL_ARG_FIRST()O_DECL_ARGS_TAIL(__VA_ARGS__))

#define O_DEF_CLASS_STRUCT() O_DEF_CLASS_STRUCT_(O_CLASS, O_PARENT)
#define O_DEF_CLASS_STRUCT_(...) O_DEF_CLASS_STRUCT__(__VA_ARGS__)
#define O_DEF_CLASS_STRUCT__(_class, parent) \
        struct _class ## Class { \
            const struct parent ## Class class; \
            O_DEF_METHODS_PTR \
        }; \
        \
        O_DEF_ALIAS_PUBLIC_METHODS

#define O_DEF_CLASS_STRUCT_WITHOUT_ALIAS() O_DEF_CLASS_STRUCT_WITHOUT_ALIAS_(O_CLASS, O_PARENT)
#define O_DEF_CLASS_STRUCT_WITHOUT_ALIAS_(...) O_DEF_CLASS_STRUCT_WITHOUT_ALIAS__(__VA_ARGS__)
#define O_DEF_CLASS_STRUCT_WITHOUT_ALIAS__(_class, parent) \
        struct _class ## Class { \
            const struct parent ## Class class; \
            O_DEF_METHODS_PTR \
        };

#define O_DEF_METHODS_PTR O_PUBLIC_METHODS(O_DEF_METHOD_PTR)
#define O_DEF_METHOD_PTR(class, parent, name, ret, ...) \
        ret (* name)(struct class * O_DECL_ARG_FIRST()O_DECL_ARGS_TAIL(__VA_ARGS__));

#define O_DEF_ALIAS_PUBLIC_METHODS O_PUBLIC_METHODS(O_DEF_ALIAS_PUBLIC_METHOD)
#define O_DEF_ALIAS_PUBLIC_METHOD(class, parent, name, ret, ...) \
        static ret name(struct class * O_DECL_ARG_FIRST()O_DECL_ARGS_TAIL(__VA_ARGS__)) \
        __attribute__((alias(#class "_" #name)));

#define O_DEF_CLASS(class, parent, ...) O_DEF_CLASS_(class, parent, O_ARY_LEN(__VA_ARGS__), __VA_ARGS__)
#define O_DEF_CLASS_(class, parent, n, ...) O_STR_CAT(O_DEF_CLASS_TYPE_, n)(class, parent, __VA_ARGS__)
#define O_DEF_CLASS_TYPE_0(class, parent, ...) O_DEF_CLASS__(class, parent, O_CLASS_SIZE_FIXED)
#define O_DEF_CLASS_TYPE_1(class, parent, ...) O_DEF_CLASS__(class, parent, __VA_ARGS__)
#define O_DEF_CLASS__(_class, parent, is_variable_size) \
        static const void * _class ## Class; \
               const void * _class; \
        \
        static void \
        _class ## Class_ctor(struct _class ## Class * class, va_list * args_ptr) { \
            /* inherit */ \
            const struct ObjectClass * superclass = ((const struct ObjectClass *) class)->class->super; \
            superclass->ctor(class, args_ptr); \
            \
            /* override */ \
            va_list args; \
            va_copy(args, * args_ptr); \
            typedef void (* func)(void); \
            func select, method; \
            while(select = va_arg(args, func)) { \
                method = va_arg(args, func); \
                O_PUBLIC_METHODS_IN_CTOR {} \
            } \
        } \
        \
        O_DEF_OVERRIDE_METHODS \
        O_DEF_PUBLIC_METHODS \
        O_DECL_HIDDEN_OVERRIDE_METHODS \
        O_DECL_HIDDEN_PUBLIC_METHODS \
        O_DECL_HIDDEN_PRIVATE_METHODS \
        O_DEF_ALIAS_PRIVATE_METHODS \
        \
        void \
        _class ## _init(void) { \
            if(!_class ## Class) { \
                ooc_uint name = (ooc_uint) #_class "Class"; \
                ooc_uint size = sizeof(struct _class ## Class); \
                _class ## Class = new(Class, Class, name, size, O_CLASS_SIZE_FIXED, \
                        Object_ctor, _class ## Class_ctor, O_CLASS_OVERRIDE_EOF); \
            } \
            if(!_class) { \
                ooc_uint name = (ooc_uint) #_class; \
                ooc_uint size = sizeof(struct _class); \
                _class = new(_class ## Class, parent, name, size, \
                        O_STR_COPY(is_variable_size)O_OVERRIDE_METHODS_IN_INIT()O_PUBLIC_METHODS_IN_INIT, O_CLASS_OVERRIDE_EOF); \
            } \
        }
#define O_CLASS_SIZE_FIXED (ooc_uint) 0
#define O_CLASS_SIZE_VARIABLE (ooc_uint) 1
#define O_CLASS_OVERRIDE_EOF (ooc_uint) 0

#define O_PUBLIC_METHODS_IN_CTOR O_PUBLIC_METHODS(O_PUBLIC_METHOD_IN_CTOR)
#define O_PUBLIC_METHOD_IN_CTOR(_class, parent, name, ...) \
        if(select == (func) _class ## _ ## name) { \
            * (func *) &class->name = method; \
        } else

#define O_DEF_OVERRIDE_METHODS O_OVERRIDE_METHODS(O_DEF_OVERRIDE_METHOD)
#define O_DEF_PUBLIC_METHODS   O_PUBLIC_METHODS(O_DEF_PUBLIC_METHOD)
#define O_DEF_OVERRIDE_METHOD(class, parent, ...) O_DEF_METHOD(parent, class, parent, __VA_ARGS__)
#define O_DEF_PUBLIC_METHOD(class, parent, ...)   O_DEF_METHOD(class, class, parent, __VA_ARGS__)
#define O_DEF_METHOD(metaclass, __class, parent, name, ret, ...) \
        O_DEF_GLOBAL_FUNC(__class, parent, name, ret, __VA_ARGS__) { \
            struct __class * _self = self; \
            const struct metaclass ## Class * _class = (struct metaclass ## Class *) ((struct Object *) _self)->class; \
            return _class->name(O_DEF_ARG_FIRST()O_DEF_ARGS_TAIL(__VA_ARGS__)); \
        }

#define O_DECL_HIDDEN_OVERRIDE_METHODS O_OVERRIDE_METHODS(O_DECL_HIDDEN_METHOD)
#define O_DECL_HIDDEN_PUBLIC_METHODS   O_PUBLIC_METHODS(O_DECL_HIDDEN_METHOD)
#define O_DECL_HIDDEN_PRIVATE_METHODS  O_PRIVATE_METHODS(O_DECL_HIDDEN_METHOD)
#define O_DECL_HIDDEN_METHOD(...) O_DEF_HIDDEN_METHOD(__VA_ARGS__);
#define O_DEF_HIDDEN_METHOD(class, parent, name, ret, ...) \
        static ret O_CLASS_HIDE(class ## _ ## name)(struct class * O_DECL_ARG_FIRST()O_DECL_ARGS_TAIL(__VA_ARGS__))

#define O_DEF_ALIAS_PRIVATE_METHODS O_PRIVATE_METHODS(O_DEF_ALIAS_PRIVATE_METHOD)
#define O_DEF_ALIAS_PRIVATE_METHOD(class, parent, name, ret, ...) \
        static ret name(struct class * O_DECL_ARG_FIRST()O_DECL_ARGS_TAIL(__VA_ARGS__)) \
        __attribute__((alias("__" #class "_" #name)));

#define O_OVERRIDE_METHODS_IN_INIT() O_OVERRIDE_METHODS(O_OVERRIDE_METHOD_IN_INIT)
#define O_OVERRIDE_METHOD_IN_INIT(class, parent, name, ret, ...) \
        , parent ## _ ## name, O_CLASS_HIDE(class ## _ ## name)

#define O_PUBLIC_METHODS_IN_INIT O_PUBLIC_METHODS(O_PUBLIC_METHOD_IN_INIT)
#define O_PUBLIC_METHOD_IN_INIT(class, parent, name, ret, ...) \
        , class ## _ ## name, O_CLASS_HIDE(class ## _ ## name)

#define O_CLASS_HIDE(class) __ ## class

#define override
#define private
#define def(name, ...) def_(O_CLASS, O_PARENT, name)
#define def_(class, parent, name) \
        def__(class, parent, O_STR_CAT4(O_, class, _, name))
#define def__(class, parent, ary) \
        O_DEF_HIDDEN_METHOD(class, parent, ary)

#define O_DECL_ARGS_TAIL(...) O_ARY_MAP(O_DECL_ARG_SPREAD, __VA_ARGS__)
#define O_DECL_ARG_SPREAD(ary, ...) O_DECL_ARG ary
#define O_DECL_ARG(type, name) , type
#define O_DECL_ARG_FIRST() self
#define O_DEF_ARGS_TAIL(...) O_ARY_MAP(O_DEF_ARG_SPREAD, __VA_ARGS__)
#define O_DEF_ARG_SPREAD(ary, ...) O_DEF_ARG ary
#define O_DEF_ARG(type, name) , name
#define O_DEF_ARG_FIRST() _self

#define O_OVERRIDE_METHODS(func) O_METHODS(OVERRIDE, func, O_OVERRIDE_METHOD)
#define O_PUBLIC_METHODS(func)   O_METHODS(PUBLIC, func, O_PUBLIC_METHOD)
#define O_PRIVATE_METHODS(func)  O_METHODS(PRIVATE, func, O_PRIVATE_METHOD)
#define O_METHODS(prefix, func, func2) O_METHODS_(O_CLASS, prefix, func, func2)
#define O_METHODS_(...) O_METHODS__(__VA_ARGS__)
#define O_METHODS__(class, prefix, func, func2) \
        O_ARY_UPTO(O_STR_CAT5(O_, class, _, prefix, _METHODS_LEN), func, func2)
#define O_OVERRIDE_METHOD(n) O_DECL_USE(OVERRIDE, n)
#define O_PUBLIC_METHOD(n)   O_DECL_USE(PUBLIC, n)
#define O_PRIVATE_METHOD(n)  O_DECL_USE(PRIVATE, n)
#define O_DECL_USE(prefix, n) O_DECL_USE_(O_CLASS, O_PARENT, prefix, n)
#define O_DECL_USE_(...) O_DECL_USE__(__VA_ARGS__)
#define O_DECL_USE__(class, parent, prefix, n) \
        class, parent, O_STR_CAT6(O_, class, _, prefix, _METHOD_, n)
#define O_STR_CAT(a, b) a ## b
#define O_STR_CAT3(a, b, c) a ## b ## c
#define O_STR_CAT4(a, b, c, d) a ## b ## c ## d
#define O_STR_CAT5(a, b, c, d, e) a ## b ## c ## d ## e
#define O_STR_CAT6(a, b, c, d, e, f) a ## b ## c ## d ## e ## f
#define O_STR_COPY(a) a
#define O_ARY_MAP(func, ...) O_ARY_MAP_(O_ARY_LEN(__VA_ARGS__), func, __VA_ARGS__)
#define O_ARY_MAP_(n, func, ...)   O_STR_CAT(O_ARY2_, n)(func, __VA_ARGS__)
#define O_ARY_UPTO(n, func, func2) O_STR_CAT(O_ARY_, n)(func, func2)
#define O_ARY_LEN(...) O_ARY_BUF_SPREAD(padding, ## __VA_ARGS__, O_ARY_NEW)
#define O_ARY_BUF_SPREAD(...) O_ARY_BUF(__VA_ARGS__)
#define O_ARY_BUF(padding, \
        _99, _98, _97, _96, _95, _94, _93, _92, _91, _90, \
        _89, _88, _87, _86, _85, _84, _83, _82, _81, _80, \
        _79, _78, _77, _76, _75, _74, _73, _72, _71, _70, \
        _69, _68, _67, _66, _65, _64, _63, _62, _61, _60, \
        _59, _58, _57, _56, _55, _54, _53, _52, _51, _50, \
        _49, _48, _47, _46, _45, _44, _43, _42, _41, _40, \
        _39, _38, _37, _36, _35, _34, _33, _32, _31, _30, \
        _29, _28, _27, _26, _25, _24, _23, _22, _21, _20, \
        _19, _18, _17, _16, _15, _14, _13, _12, _11, _10, \
         _9,  _8,  _7,  _6,  _5,  _4,  _3,  _2,  _1,  _0, ...) _0
#define O_ARY_NEW \
        99, 98, 97, 96, 95, 94, 93, 92, 91, 90, \
        89, 88, 87, 86, 85, 84, 83, 82, 81, 80, \
        79, 78, 77, 76, 75, 74, 73, 72, 71, 70, \
        69, 68, 67, 66, 65, 64, 63, 62, 61, 60, \
        59, 58, 57, 56, 55, 54, 53, 52, 51, 50, \
        49, 48, 47, 46, 45, 44, 43, 42, 41, 40, \
        39, 38, 37, 36, 35, 34, 33, 32, 31, 30, \
        29, 28, 27, 26, 25, 24, 23, 22, 21, 20, \
        19, 18, 17, 16, 15, 14, 13, 12, 11, 10, \
         9,  8,  7,  6,  5,  4,  3,  2,  1,  0
#define O_ARY_SPREAD(func, func2, n) O_ARY_SPREAD_(func, func2(n))
#define O_ARY_SPREAD_(func, val) func(val)
#define O_ARY_0(func, func2)
#define O_ARY_1(func, func2) O_ARY_SPREAD(func, func2, 0)
#define O_ARY_2(func, func2) O_ARY_1(func, func2) O_ARY_SPREAD(func, func2, 1)
#define O_ARY_3(func, func2) O_ARY_2(func, func2) O_ARY_SPREAD(func, func2, 2)
#define O_ARY_4(func, func2) O_ARY_3(func, func2) O_ARY_SPREAD(func, func2, 3)
#define O_ARY_5(func, func2) O_ARY_4(func, func2) O_ARY_SPREAD(func, func2, 4)
#define O_ARY_6(func, func2) O_ARY_5(func, func2) O_ARY_SPREAD(func, func2, 5)
#define O_ARY_7(func, func2) O_ARY_6(func, func2) O_ARY_SPREAD(func, func2, 6)
#define O_ARY_8(func, func2) O_ARY_7(func, func2) O_ARY_SPREAD(func, func2, 7)
#define O_ARY_9(func, func2) O_ARY_8(func, func2) O_ARY_SPREAD(func, func2, 8)
#define O_ARY_10(func, func2) O_ARY_9(func, func2) O_ARY_SPREAD(func, func2, 9)
#define O_ARY_11(func, func2) O_ARY_10(func, func2) O_ARY_SPREAD(func, func2, 10)
#define O_ARY_12(func, func2) O_ARY_11(func, func2) O_ARY_SPREAD(func, func2, 11)
#define O_ARY_13(func, func2) O_ARY_12(func, func2) O_ARY_SPREAD(func, func2, 12)
#define O_ARY_14(func, func2) O_ARY_13(func, func2) O_ARY_SPREAD(func, func2, 13)
#define O_ARY_15(func, func2) O_ARY_14(func, func2) O_ARY_SPREAD(func, func2, 14)
#define O_ARY_16(func, func2) O_ARY_15(func, func2) O_ARY_SPREAD(func, func2, 15)
#define O_ARY_17(func, func2) O_ARY_16(func, func2) O_ARY_SPREAD(func, func2, 16)
#define O_ARY_18(func, func2) O_ARY_17(func, func2) O_ARY_SPREAD(func, func2, 17)
#define O_ARY_19(func, func2) O_ARY_18(func, func2) O_ARY_SPREAD(func, func2, 18)
#define O_ARY_20(func, func2) O_ARY_19(func, func2) O_ARY_SPREAD(func, func2, 19)
#define O_ARY_21(func, func2) O_ARY_20(func, func2) O_ARY_SPREAD(func, func2, 20)
#define O_ARY_22(func, func2) O_ARY_21(func, func2) O_ARY_SPREAD(func, func2, 21)
#define O_ARY_23(func, func2) O_ARY_22(func, func2) O_ARY_SPREAD(func, func2, 22)
#define O_ARY_24(func, func2) O_ARY_23(func, func2) O_ARY_SPREAD(func, func2, 23)
#define O_ARY_25(func, func2) O_ARY_24(func, func2) O_ARY_SPREAD(func, func2, 24)
#define O_ARY_26(func, func2) O_ARY_25(func, func2) O_ARY_SPREAD(func, func2, 25)
#define O_ARY_27(func, func2) O_ARY_26(func, func2) O_ARY_SPREAD(func, func2, 26)
#define O_ARY_28(func, func2) O_ARY_27(func, func2) O_ARY_SPREAD(func, func2, 27)
#define O_ARY_29(func, func2) O_ARY_28(func, func2) O_ARY_SPREAD(func, func2, 28)
#define O_ARY_30(func, func2) O_ARY_29(func, func2) O_ARY_SPREAD(func, func2, 29)
#define O_ARY_31(func, func2) O_ARY_30(func, func2) O_ARY_SPREAD(func, func2, 30)
#define O_ARY_32(func, func2) O_ARY_31(func, func2) O_ARY_SPREAD(func, func2, 31)
#define O_ARY_33(func, func2) O_ARY_32(func, func2) O_ARY_SPREAD(func, func2, 32)
#define O_ARY_34(func, func2) O_ARY_33(func, func2) O_ARY_SPREAD(func, func2, 33)
#define O_ARY_35(func, func2) O_ARY_34(func, func2) O_ARY_SPREAD(func, func2, 34)
#define O_ARY_36(func, func2) O_ARY_35(func, func2) O_ARY_SPREAD(func, func2, 35)
#define O_ARY_37(func, func2) O_ARY_36(func, func2) O_ARY_SPREAD(func, func2, 36)
#define O_ARY_38(func, func2) O_ARY_37(func, func2) O_ARY_SPREAD(func, func2, 37)
#define O_ARY_39(func, func2) O_ARY_38(func, func2) O_ARY_SPREAD(func, func2, 38)
#define O_ARY_40(func, func2) O_ARY_39(func, func2) O_ARY_SPREAD(func, func2, 39)
#define O_ARY_41(func, func2) O_ARY_40(func, func2) O_ARY_SPREAD(func, func2, 40)
#define O_ARY_42(func, func2) O_ARY_41(func, func2) O_ARY_SPREAD(func, func2, 41)
#define O_ARY_43(func, func2) O_ARY_42(func, func2) O_ARY_SPREAD(func, func2, 42)
#define O_ARY_44(func, func2) O_ARY_43(func, func2) O_ARY_SPREAD(func, func2, 43)
#define O_ARY_45(func, func2) O_ARY_44(func, func2) O_ARY_SPREAD(func, func2, 44)
#define O_ARY_46(func, func2) O_ARY_45(func, func2) O_ARY_SPREAD(func, func2, 45)
#define O_ARY_47(func, func2) O_ARY_46(func, func2) O_ARY_SPREAD(func, func2, 46)
#define O_ARY_48(func, func2) O_ARY_47(func, func2) O_ARY_SPREAD(func, func2, 47)
#define O_ARY_49(func, func2) O_ARY_48(func, func2) O_ARY_SPREAD(func, func2, 48)
#define O_ARY_50(func, func2) O_ARY_49(func, func2) O_ARY_SPREAD(func, func2, 49)

#define O_ARY2_0(func, a)
#define O_ARY2_1(func, a) func(a)
#define O_ARY2_2(func, a, ...) func(a) O_ARY2_1(func, __VA_ARGS__)
#define O_ARY2_3(func, a, ...) func(a) O_ARY2_2(func, __VA_ARGS__)
#define O_ARY2_4(func, a, ...) func(a) O_ARY2_3(func, __VA_ARGS__)
#define O_ARY2_5(func, a, ...) func(a) O_ARY2_4(func, __VA_ARGS__)
#define O_ARY2_6(func, a, ...) func(a) O_ARY2_5(func, __VA_ARGS__)
#define O_ARY2_7(func, a, ...) func(a) O_ARY2_6(func, __VA_ARGS__)
#define O_ARY2_8(func, a, ...) func(a) O_ARY2_7(func, __VA_ARGS__)
#define O_ARY2_9(func, a, ...) func(a) O_ARY2_8(func, __VA_ARGS__)
#define O_ARY2_10(func, a, ...) func(a) O_ARY2_9(func, __VA_ARGS__)
#define O_ARY2_11(func, a, ...) func(a) O_ARY2_10(func, __VA_ARGS__)
#define O_ARY2_12(func, a, ...) func(a) O_ARY2_11(func, __VA_ARGS__)
#define O_ARY2_13(func, a, ...) func(a) O_ARY2_12(func, __VA_ARGS__)
#define O_ARY2_14(func, a, ...) func(a) O_ARY2_13(func, __VA_ARGS__)
#define O_ARY2_15(func, a, ...) func(a) O_ARY2_14(func, __VA_ARGS__)
#define O_ARY2_16(func, a, ...) func(a) O_ARY2_15(func, __VA_ARGS__)
#define O_ARY2_17(func, a, ...) func(a) O_ARY2_16(func, __VA_ARGS__)
#define O_ARY2_18(func, a, ...) func(a) O_ARY2_17(func, __VA_ARGS__)
#define O_ARY2_19(func, a, ...) func(a) O_ARY2_18(func, __VA_ARGS__)
#define O_ARY2_20(func, a, ...) func(a) O_ARY2_19(func, __VA_ARGS__)
#define O_ARY2_21(func, a, ...) func(a) O_ARY2_20(func, __VA_ARGS__)
#define O_ARY2_22(func, a, ...) func(a) O_ARY2_21(func, __VA_ARGS__)
#define O_ARY2_23(func, a, ...) func(a) O_ARY2_22(func, __VA_ARGS__)
#define O_ARY2_24(func, a, ...) func(a) O_ARY2_23(func, __VA_ARGS__)
#define O_ARY2_25(func, a, ...) func(a) O_ARY2_24(func, __VA_ARGS__)
#define O_ARY2_26(func, a, ...) func(a) O_ARY2_25(func, __VA_ARGS__)
#define O_ARY2_27(func, a, ...) func(a) O_ARY2_26(func, __VA_ARGS__)
#define O_ARY2_28(func, a, ...) func(a) O_ARY2_27(func, __VA_ARGS__)
#define O_ARY2_29(func, a, ...) func(a) O_ARY2_28(func, __VA_ARGS__)
#define O_ARY2_30(func, a, ...) func(a) O_ARY2_29(func, __VA_ARGS__)
#define O_ARY2_31(func, a, ...) func(a) O_ARY2_30(func, __VA_ARGS__)
#define O_ARY2_32(func, a, ...) func(a) O_ARY2_31(func, __VA_ARGS__)
#define O_ARY2_33(func, a, ...) func(a) O_ARY2_32(func, __VA_ARGS__)
#define O_ARY2_34(func, a, ...) func(a) O_ARY2_33(func, __VA_ARGS__)
#define O_ARY2_35(func, a, ...) func(a) O_ARY2_34(func, __VA_ARGS__)
#define O_ARY2_36(func, a, ...) func(a) O_ARY2_35(func, __VA_ARGS__)
#define O_ARY2_37(func, a, ...) func(a) O_ARY2_36(func, __VA_ARGS__)
#define O_ARY2_38(func, a, ...) func(a) O_ARY2_37(func, __VA_ARGS__)
#define O_ARY2_39(func, a, ...) func(a) O_ARY2_38(func, __VA_ARGS__)
#define O_ARY2_40(func, a, ...) func(a) O_ARY2_39(func, __VA_ARGS__)
#define O_ARY2_41(func, a, ...) func(a) O_ARY2_40(func, __VA_ARGS__)
#define O_ARY2_42(func, a, ...) func(a) O_ARY2_41(func, __VA_ARGS__)
#define O_ARY2_43(func, a, ...) func(a) O_ARY2_42(func, __VA_ARGS__)
#define O_ARY2_44(func, a, ...) func(a) O_ARY2_43(func, __VA_ARGS__)
#define O_ARY2_45(func, a, ...) func(a) O_ARY2_44(func, __VA_ARGS__)
#define O_ARY2_46(func, a, ...) func(a) O_ARY2_45(func, __VA_ARGS__)
#define O_ARY2_47(func, a, ...) func(a) O_ARY2_46(func, __VA_ARGS__)
#define O_ARY2_48(func, a, ...) func(a) O_ARY2_47(func, __VA_ARGS__)
#define O_ARY2_49(func, a, ...) func(a) O_ARY2_48(func, __VA_ARGS__)
#define O_ARY2_50(func, a, ...) func(a) O_ARY2_49(func, __VA_ARGS__)

#endif
