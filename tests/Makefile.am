TESTS = check_libooc
check_PROGRAMS = check_libooc
check_libooc_SOURCES = \
    libooc.c \
    macro.c  \
    object.c \
    array.c
check_libooc_CFLAGS = @CHECK_CFLAGS@
check_libooc_LDADD = $(top_builddir)/libooc/libooc-0.0.1.a @CHECK_LIBS@
