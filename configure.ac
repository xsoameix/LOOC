#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.68])
AC_INIT([libooc], [0.0.1], [xsoameix@gmail.com])
AM_INIT_AUTOMAKE
AC_CONFIG_SRCDIR([libooc/object.c])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC

AC_PROG_RANLIB

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h string.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_PROG_CC_C99

# Checks for library functions.
AC_FUNC_MALLOC

AC_CONFIG_FILES([
libooc-0.0.1.pc
Makefile
libooc/Makefile
tests/Makefile
])

AC_OUTPUT
