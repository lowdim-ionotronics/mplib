/*  u2-approx.c  2012-10-12  2body potential energy (up to a coeff): approximation
 *
 * Copyright (C) 2012 Svyatoslav Kondrat (Valiska)
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

#include "mplib-private.h"

#include <stdio.h>
#include <math.h>

#include <gsl/gsl_integration.h>

static double inline integral (double z1, double z2);

double mplib_potential_binary_approx (double z1, double z2, double R, double L) 
{
	// rescale arguments
        z1 /= L;
	z2 /= L;
	R /= L;

	DPRINT ("z1=%g, z2=%g, R=%g\n", z1, z2, R);

	MPLIB_CRITICAL ( (z1 > 0.) && (z1 < 1.), "argument out of bound (z1=%g, z2=%g)", z1, z2);
	MPLIB_CRITICAL ( (z2 > 0.) && (z2 < 1.), "argument out of bound");
	MPLIB_CRITICAL ( R >= 0.0, "argument out of bound");

	/* Use integral _only_ when R = 0
	 * FIXME: use approximation for R=0 as well? */
	if (R != 0.0)
//	if (R > EPS_R)

#ifdef _MPLIB_APPROX_USE_EXPANSION_
		return (1. / L * sqrt(2. * R)) * exp (- M_PI * R) * sin (M_PI * z1) * sin (M_PI * z2);
#elif defined(_MPLIB_APPROX_USE_BESSEL_)
		return (4. / L ) * gsl_sf_bessel_K0 ( M_PI * R) * sin (M_PI * z1) * sin (M_PI * z2);
#else
#  error MPLIB_APPROX not chosen
#endif

	else 
	{
		MPLIB_WARNING ("R=0.0, using the integral representation");
		return (1. / L) * integral (z1, z2);
	}
}

/*********************
 * The the integral  *
 * *******************/

/* integrand */
static double f (double Q, void * params) {

	void ** p = (void*) params;

	double zp = *((double *) p[0]);
	double zm = *( (double*) p[1]);

	DPRINT ("zp=%g, zm=%g\n", zp, zm);

	double c1 = 1. - exp (-2. * Q);
   	double c2 = 1. / tanh(Q) + 1.;
   
	double Ap = exp( - Q * (2. - zp) ) / c1 + 0.5 * exp ( - Q * zp) * c2;
	double Am = exp( - Q * (2. - zm) ) / c1 + 0.5 * exp ( - Q * zm) * c2;

	DPRINT ("Q=%g: A= %g - %g = %g\n", Q, Ap, Am, Ap - Am);

	return Am - Ap;
}

/* The integral (arguments are rescaled (by L)) */
static double inline integral (double z1, double z2) 
{

	DPRINT ("z1=%g, z2=%g\n", z1, z2);

	double Zp = z1 + z2;
	double Zm = fabs (z1 - z2);

	MPLIB_CRITICAL (Zm > EPS_DZ, "the difference dz = |z1-z2| = %g is too small", Zm);

	gsl_integration_workspace * w 
		= gsl_integration_workspace_alloc (10000);
	MPLIB_CRITICAL (w, "Cannot allocate the workspace for the integration");

	double result, error;

	gsl_function F;
	F.function = &f;

	void * p[] = {&Zp, &Zm};
	F.params = (void*) p;

	DPRINT ("integral(): zp=%g, zm=%g\n", Zp, Zm);

	gsl_integration_qagiu (&F, 0.0, 1.e-7, 1e-7, 10000, w, &result, &error); 

	DPRINT ("%g  %g: % .18f\n", z1, z2, result);
	DPRINT ("estimated error = % .18f\n", error);
	DPRINT ("intervals =  %d\n", w->size);

	gsl_integration_workspace_free (w);

	return result;
}

