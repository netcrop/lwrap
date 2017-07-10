dnl Process this file with autoconf to produce a configure script.
AC_INIT(lwrap,1.0)
AC_CONFIG_SRCDIR(lwrap.c)
AC_CONFIG_HEADERS(config.h)
AM_INIT_AUTOMAKE

dnl Checks for programs.
AC_PROG_CC
AC_PROG_INSTALL
AC_PROG_MAKE_SET

dnl Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS(sys/ioctl.h unistd.h)

dnl Checks for typedefs, structures, and compiler characteristics.

dnl Checks for library functions.
AC_TYPE_SIGNAL
AC_CHECK_FUNCS(putenv)

dnl Only change gcc options if we are using gcc.  
if test "$ac_cv_prog_CC" = gcc -o "$ac_cv_prog_CC" = g++; then
  CFLAGS="$CFLAGS -Wall -Wno-comment"
fi
AC_OUTPUT(Makefile lwrap.spec)
