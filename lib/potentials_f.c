/*  potentials_f.c  2010-07-28  wrappers for towhee fortran code.
 *
 * Copyright (C) 2010 Svyatoslav Kondrat (Valiska)
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
//#define DEBUG
#include "defines.h"

#include "mplib.h"

double mplib_potential_unary_ (double * z, double *L) 
{
	DPRINT ("unary_f(): z=%g\n", *z);
	double u1 = mplib_potential_unary (*z, *L);
	DPRINT ("unary_f(): pot=%e\n", u1);
	return u1;
}

double mplib_potential_binary_ (double * z1, double * z2, double * R, double *L)
{
	return mplib_potential_binary (*z1, *z2, *R, *L);
}

double mplib_cylinder_u1_ (double * r, double * R) 
{
	return mplib_cylinder_u1 (*r, *R);
}

double mplib_cylinder_u2_ (double * rho1, double * rho2, double * phi, double * z, double * R) 
{
	return mplib_cylinder_u2 (*rho1, *rho2, *phi, *z,*R);
}
