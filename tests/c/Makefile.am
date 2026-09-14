noinst_PROGRAMS = test-slit test-cylinder

# Real assert()-based smoke tests (see the files for what they check).
# Illustrative print-loop versions of these now live in examples/c/.
TESTS = $(noinst_PROGRAMS)

AM_CFLAGS = -I$(top_srcdir)/lib/  @GSL_INCLUDES@  -Wall -DMPLIB_MAINTAINER=\"@MPLIB_MAINTAINER@\"  -g
AM_LDFLAGS = @GSL_LIBS@ -pedantic -ansi  -Wall

test_slit_SOURCES = test-slit.c
test_slit_LDADD = $(top_srcdir)/lib/libmplib.la

test_cylinder_SOURCES = test-cylinder.c
test_cylinder_LDADD = $(top_srcdir)/lib/libmplib.la
