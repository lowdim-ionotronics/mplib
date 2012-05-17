/*  dft-u1.c  2011-10-16  The unary potential function (self energy) to be used in the DFT.
a *  It is up to a copnstant (-LB, note the sign) as in u1.c
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

#include <stdio.h>
#include <math.h>
	
#include <gsl/gsl_integration.h>
#define EPS          2.e-5

/* Integrand */
static double f (double Q, void * params);
/* 
 * The unary function up to a constant: the integral f(x) (as in Kondrat & Kornyshev) 
 */
double mplib_dft_u1 (double z, double L, double LB) {

	z /= L;
	DPRINT ("z=%g\n", z);
	MPLIB_CRITICAL ( (z >= EPS) && ((1. - z) >= EPS), "argument z=%g out of bound (0,1)", z);

	gsl_integration_workspace * w 
		= gsl_integration_workspace_alloc (10000);
	MPLIB_CRITICAL (w, "Cannot allocate the integration workspace");

	double result, error;

	gsl_function F;
	F.function = &f;
	F.params = &z;

	gsl_integration_qagiu (&F, 0.0, 1.e-7, 1e-7, 10000, w, &result, &error); 

	DPRINT ("%g   % .18f\n", z, result);
	DPRINT ("estimated error = % .18f\n", error);
	DPRINT ("intervals =  %d\n", w->size);

	gsl_integration_workspace_free (w);

	return 0.5 * result *LB / L;
}
/* 
 * Privat function
 */
static double inline f (double Q, void * params) {

	double z = *((double *) params);

//	double f = 1. / tanh(Q) - 1.;
	double f = 1. - 1. / tanh(Q);

	double a = exp( -2.* Q * z) + exp (- 2. * Q * (1 - z));
	double b  = 1. - exp (-2. * Q);

	f += a / b;

	return f;
}
