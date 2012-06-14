lib_LTLIBRARIES = libmplib.la

libmplib_la_SOURCES = u1.c  u2.c potentials_f.c dft-u1.c dft-u2.c ddft-W.c ddft-Wx.c
libmplib_la_LDFLAGS = -version-info @MPLIB_LT_VERSION@

pkginclude_HEADERS = mplib.h mplib_f.h

INCLUDES = -I$(top_srcdir)/src   @GSL_INCLUDES@

AM_CFLAGS= -Wall -DMPLIB_MAINTAINER=\"@MPLIB_MAINTAINER@\" 
AM_LDFLAGS = @GSL_LIBS@ -pedantic -ansi -fwritable-strings



EXTRA_DIST = defines.h
