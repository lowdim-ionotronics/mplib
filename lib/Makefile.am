noinst_LIBRARIES = libmplib.a
libmplib_a_SOURCES = u1.c  u2.c potentials_f.c dft-u1.c dft-u2.c

INCLUDES = -I$(top_srcdir)/src   @GSL_INCLUDES@

AM_CFLAGS= -Wall -DMPLIB_MAINTAINER=\"@MPLIB_MAINTAINER@\" 
AM_LDFLAGS = @GSL_LIBS@ -pedantic -ansi -fwritable-strings

EXTRA_DIST = defines.h potentials.h potentials_f.h
