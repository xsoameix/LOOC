lib_LIBRARIES = libooc-0.0.1.a
libooc_0_0_1_a_SOURCES = \
    object.c             \
    hash.c               \
    string.c             \
    array.c              \
    value.c              \
    file.c

liboocincludedir=$(includedir)/libooc-0.0.1/libooc
liboocinclude_HEADERS = \
    macro.h             \
    object.struct.h     \
    object.h            \
    hash.struct.h       \
    hash.h              \
    hash_macro.h        \
    string.struct.h     \
    string.conflict.h   \
    array.struct.h      \
    array.h             \
    array_macro.h       \
    value.h             \
    file.h              \
    inttype.h           \
    object_type.h

# libooc
bin_PROGRAMS = bin/example
bin_example_SOURCES = example.c \
				 $(top_builddir)/libooc/array.h \
				 $(top_builddir)/libooc/hash.h  \
				 $(top_builddir)/libooc/value.h \
				 $(top_builddir)/libooc/string.conflict.h
bin_example_LDADD = $(top_builddir)/libooc/libooc-0.0.1.a
