      program u1
c
c     S Kondrat aka Valiska valiska@gmail.com  27/07/2010
c     Test unary potential (libmplib.a) called by a fortran program
c
       implicit none
#define MPLIB_HAVE_UNARY
#include "potentials_f.h"
       double precision eps, L, z0, z1, z, step
       double precision pot
      integer i, N
c
      L= 1.0
      N = 100
      eps = 2.d-05
      z0 = eps
      z1 = L - eps;
      step = (z1 - z0) / DBLE(N)
c
c     Now calculate the potential and
c     print out the results in a loop
      z = z0
      do i = 1,N+1
        pot = mplib_potential_unary (z,L)
        print *, z, '   ', pot
        z = z + step
      enddo
c
      stop
      end

