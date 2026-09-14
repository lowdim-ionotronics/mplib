lib_LTLIBRARIES = libmplib.la

libmplib_la_SOURCES = slit-u1.c slit-u2.c slit-u2-approx.c potentials_f.c \
	cylindre-u2.c cylindre-u1.c \
	cylindre-u2-approx.c cylindre-u1-approx.c

libmplib_la_LDFLAGS = -version-info @MPLIB_LT_VERSION@  @GSL_LIBS@ -pedantic -ansi -fwritable-strings -lm -g


pkginclude_HEADERS = mplib.h mplib_f.h

AM_CFLAGS= -Wall -DMPLIB_MAINTAINER=\"@MPLIB_MAINTAINER@\" -I$(top_srcdir)/src   @GSL_INCLUDES@
AM_LDFLAGS = @GSL_LIBS@ -pedantic -ansi -fwritable-strings -lm -g

EXTRA_DIST = defines.h mplib-private.h
