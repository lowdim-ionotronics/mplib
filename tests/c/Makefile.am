noinst_PROGRAMS = test-u1 test-u2 test-dft-u2 test-ddft-Kx test-ddft-W test-cylindre-u2 test-cylindre-u1

AM_CFLAGS = -I$(top_srcdir)/lib/  @GSL_INCLUDES@  -Wall -DMPLIB_MAINTAINER=\"@MPLIB_MAINTAINER@\"  -g
AM_LDFLAGS = @GSL_LIBS@ -pedantic -ansi  -Wall

test_u1_SOURCES = test-u1.c
test_u1_LDADD = $(top_srcdir)/lib/libmplib.la

test_u2_SOURCES = test-u2.c
test_u2_LDADD = $(top_srcdir)/lib/libmplib.la

test_dft_u2_SOURCES = test-dft-u2.c
test_dft_u2_LDADD = $(top_srcdir)/lib/libmplib.la

test_ddft_Kx_SOURCES = test-ddft-Kx.c
test_ddft_Kx_LDADD = $(top_srcdir)/lib/libmplib.la

test_ddft_W_SOURCES = test-ddft-W.c
test_ddft_W_LDADD = $(top_srcdir)/lib/libmplib.la

test_cylindre_u2_SOURCES = test-cylindre-u2.c
test_cylindre_u2_LDADD = $(top_srcdir)/lib/libmplib.la

test_cylindre_u1_SOURCES = test-cylindre-u1.c
test_cylindre_u1_LDADD = $(top_srcdir)/lib/libmplib.la
