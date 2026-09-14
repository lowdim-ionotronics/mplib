/*  mplib.h 2012-05-17  header file for various screened electrostatic 
 * potentials of point charges confined between two metalic walls
 *
 * Copyright (C) 2010 2012 Svyatoslav Kondrat (Valiska)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at
 * your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#if !defined (_HAVE_MPLIB_H_)
#define _HAVE_MPLIB_H_

#undef __BEGIN_DECLS
#undef __END_DECLS
#ifdef __cplusplus
# define __BEGIN_DECLS extern "C" {
# define __END_DECLS }
#else
# define __BEGIN_DECLS /* empty */
# define __END_DECLS /* empty */
#endif

__BEGIN_DECLS

/* Use the first term in the series only, that is the Bessel (MacDonald function) 
 * an alternative (not fully functioning) is to use a large distance expansion _MPLIB_APPROX_USE_EXPANSION_ */
#define _MPLIB_APPROX_USE_BESSEL_


/* 
 * 'raw' electrostatic potentials due to pore screening (its approx version
   (see S Kondrat & A kornyshev, J Phys: Cond. Matt. 23 022201 (2011)) 
 * 
 */
double mplib_potential_unary (double z, double L);
double mplib_potential_binary_approx (double z1, double z2, double R, double L);

#ifdef MPLIB_USE_APPROX
#  define mplib_potential_binary(z1,z2,R,L)      mplib_potential_binary_approx(z1,z2,R,L)
#else
   double mplib_potential_binary (double z1, double z2, double R, double L);
#endif /* MPLIB_USE_APPROX */

/* 
 * Fortran wrappers 
 */
double mplib_potential_unary_ (double * z, double * L); 
double mplib_potenial_binary_approx_ (double * z1, double * z2, double * R, double * L);

#ifdef MPLIB_USE_APPROX
#  define mplib_potenial_binary_(z1, z2, R, L)   mplib_potenial_binary_approx_(z1, z2, R, L)
#else
   double mplib_potenial_binary_ (double * z1, double * z2, double * R, double * L);
#endif

/*
 * Electrostatic potentials for ions confined in a cylindrical metallic pore.
 * See:
 *   10.1103/PhysRevLett.113.048701
 *   10.1002/cphc.201300834
 */
double mplib_cylinder_u2 (double rho1, double rho2, double phi, double z, double R);
double mplib_cylinder_u2_approx (double rho1, double rho2, double phi, double z, double R);

double mplib_cylinder_u1 (double r1, double R); 
double mplib_cylinder_u1_approx (double r, double R);
__END_DECLS

#endif 

