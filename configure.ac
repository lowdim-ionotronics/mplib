#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.71])
AC_INIT([mplib],[2.0],[valiska@gmail.com])
AC_CONFIG_SRCDIR([lib/slit-u1.c])
AC_CONFIG_HEADERS([config.h])

AM_PATH_PYTHON([3.4])

PACKAGE=mplib
VERSION=2.0

dnl IFACE_NUMBER (current) : REV : AGE (< IFACE_NUMBER)
MPLIB_LT_VERSION="8:0:8"
AC_SUBST(MPLIB_LT_VERSION)

AC_SUBST(PACKAGE)
AC_SUBST(PACKAGE_STRING)
AC_SUBST(VERSION)

#AM_INIT_AUTOMAKE($PACKAGE, $VERSION)
# 'foreign': don't require GNU-standard files (ChangeLog etc) to exist.
AM_INIT_AUTOMAKE([foreign])


dnl maintainer
AC_SUBST(MPLIB_MAINTAINER)
MPLIB_MAINTAINER="valiska@gmail.com"

# Checks for programs.
AC_PROG_CC
AC_PROG_CXX

# Fortran is optional: only needed for the Towhee-style Fortran-callable
# wrappers' test (tests/fortran/u1.F), not for the C library or Python
# bindings that single-file/mpore-gcmc actually use. Soft-detect gfortran and
# skip that one test directory if it isn't present, rather than forcing
# every user to install a Fortran toolchain.
AC_PROG_F77(gfortran)
AM_CONDITIONAL([HAVE_FORTRAN], [test -n "$F77"])
if test -z "$F77"; then
  AC_MSG_WARN([no Fortran compiler found; skipping tests/fortran (the C library and Python bindings are unaffected)])
fi

#AC_PROG_RANLIB
LT_INIT

# Checks for libraries.
#
# GNU Scientific Library
#
#AM_PATH_GSL(1.3, AC_DEFINE_UNQUOTED([GSL_VERSION],
#                    "`$ac_cv_path_GSL_CONFIG --version`" , [GSL version we use to compile this package]),
#  AC_MSG_ERROR([gsl is missing. You need gsl to compile this package.
#      See http://www.gnu.org/software/gsl/])
#)

AC_ARG_WITH(gsl,
            [  --with-gsl=DIR        Directory where the GSL is installed (optional)],
            GSL_DIR="$withval")

GSL_CONFIG=
AC_PATH_PROG([GSL_CONFIG], [gsl-config],, [$GSL_DIR/bin:$PATH])
                                                                                                                
GSL_INCLUDES=
GSL_LIBS=
                                                                                                                 
if test -x "$GSL_CONFIG"; then
  GSL_INCLUDES=`$GSL_CONFIG --cflags`
  GSL_LIBS=`$GSL_CONFIG --libs`
else
  AC_MSG_ERROR(GSL not found)
fi
AC_SUBST(GSL_INCLUDES)
AC_SUBST(GSL_LIBS)

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

# 'Optimizization' must be beore all the other flags!
AC_ARG_ENABLE([optimize],
    [AS_HELP_STRING([--enable-optimize],[disable debugging (removes -g flags) and set optimization level O3 (disabled)])],
    [CFLAGS="-O3"], [CFLAGS="$CFLAGS_save"])

# Enable/disable assetions
AC_ARG_ENABLE(assertions,
	      AS_HELP_STRING([--disable-assertions],[disable all assertions (enabled)]), 
			     [disable_assertions=yes AC_DEFINE([MPLIB_NO_ASSERT],,[no assertions])],
			      disable_assertions=no)

if test "x$disable_assertions" = "xyes"; then
	CFLAGS="-DMPLIB_NO_ASSERT $CFLAGS"
#	CFLAGS="-DNDEBUG $CFLAGS"
fi

MPLIB_CFLAGS="-I$includedir"
MPLIB_LIBS="-L$libdir -lmplib"

AC_SUBST(MPLIB_CFLAGS)
AC_SUBST(MPLIB_LIBS)

AC_CONFIG_FILES([Makefile
		mplib.pc mplib-config
		lib/Makefile
		python/Makefile
		tests/Makefile
		tests/c/Makefile
		tests/python/Makefile
		tests/fortran/Makefile])
AC_OUTPUT
