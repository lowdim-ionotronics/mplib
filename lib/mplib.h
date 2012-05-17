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

/* 'raw' electrostatic potentials due to pore screening
   (see S Kondrat & A kornyshev, J Phys: Cond. Matt. 23 022201 (2011))*/
double mplib_potential_unary (double z, double L);
double mplib_potential_binary (double z1, double z2, double R, double L);

/** Fortran wrappers **/
double mplib_potential_unary_ (double * z, double * L); 
double mplib_potenial_binary_ (double * z1, double * z2, double * R, double * L);

/* Potentials for DFT calculations */
double mplib_dft_u1 (double z, double L, double LB);
double mplib_dft_u2 (double z1, double z2, double L, double LB, double b);

__END_DECLS

#endif 
