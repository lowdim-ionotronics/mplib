noinst_PROGRAMS = test-u1-fortran

INCLUDES = -I$(top_srcdir)/lib/  @GSL_INCLUDES@

AM_FFLAGS = -Wall -DMPLIB_MAINTAINER=\"@MPLIB_MAINTAINER@\" 
AM_LDFLAGS = @GSL_LIBS@ -pedantic -ansi -fwritable-strings -Wall

test_u1_fortran_SOURCES = u1.F
test_u1_fortran_LDADD = $(top_srcdir)/lib/libmplib.a
