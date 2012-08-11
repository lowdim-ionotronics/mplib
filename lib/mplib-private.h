/*  mplib-private.h 2012-05-17  header file for some 'private' definitions
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

#if !defined (_HAVE_MPLIB_PRIVATE_H_)
#define _HAVE_MPLIB_PRIVATE_H_

#include "mplib.h"

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

#define pow2(x)         ( (x) * (x) )

/*
 * Some EPS defines
*/
/* Minimum of a sum element, otherwise zero */
#define EPS_SUM  1.e-50

/* Minimum R, otherwise treated as zero */
#define EPS_R    1.e-50

/* Minimum of dz=fabs(z1 -z2) */
#define EPS_DZ   1.e-50

/* maximum value of R above which Kn(piR/L) is zero */
#define R_MAX     50.0


__END_DECLS

#endif 

