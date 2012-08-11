/*  ddft-W-approx.c  2012-08-11  evaluate W (x-x', b,..) of in Wx = grad W() using approximate potential
 *
 *  mplib_ddft_Kx (z1, z2, dx, L, LB, b) calculates the effective modified mean-field interaction potential:
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

#include <gsl/gsl_sum.h>
#include <gsl/gsl_sf_bessel.h>
#include <gsl/gsl_integration.h>

/* declare I_n(dx, yo) for n = 1 */
static double inline integral (double dx, double yo);

double mplib_ddft_W_approx (double z1, double z2, double dx, double L, double LB, double b)
{
	DPRINT ("mplib_ddft_W(): z1=%g, z2=%g, dx=%g, L=%g, LB=%g, b=%g\n", z1, z2, dx, L, LB, b);

	MPLIB_CRITICAL ( (z1 > 0.) && (z1 < L), "argument out of bound (z1=%g, z2=%g, L=%g)", z1, z2, L);
	MPLIB_CRITICAL ( (z2 > 0.) && (z2 < L), "argument out of bound (z1=%g, z2=%g, L=%g)", z1, z2, L);
	//MPLIB_CRITICAL ( b > 0.0, "argument out of bound, b=%g", b);

	double yo2 = pow2(b) - pow2(dx);
	double yo = 0.;

	double W = 0.;

	if (yo2 > 0.0) 
		yo = sqrt (yo2);

	/* NOTE: z1, z2, dx and yo are normalized, functions are below */
	W = 16. * LB * integral (dx/L, yo/L) * sin (M_PI * z1/L) * sin (M_PI * z2/L);

	return W;
}

/*
 * Evaluate the integral
 *
 * 	I_n (dx, yo) = int_y0^\infty dy K0 (pi n sqrt(dx^2 + y^2))
 */

/* integrand */
static double f (double y, void * params) {

	double dx = *((double *) params);

	double R = sqrt (pow2(dx) + pow2 (y));
	DPRINT ("W::f(): dx=%g, y=%g, R=%g, ", dx, y, R);

	double f = 0.;
	
	if ( (R < R_MAX) && (R != 0.0) )
		f = gsl_sf_bessel_K0 (M_PI *  R);

	DPRINT ("f=%g\n", f);

	return f;
}

/* Use GSL integrator */
static double inline integral (double dx, double yo)
{
	gsl_integration_workspace * w 
		= gsl_integration_workspace_alloc (10000);
	MPLIB_CRITICAL (w, "Cannot allocate the workspace for the integration");

	DPRINT ("W::integral(): n=%g, dx=%g, yo=%g\n", n, dx, yo);

	double result, error;

	gsl_function F;
	F.function = &f;
	F.params = (void*) &dx;

	gsl_integration_qagiu (&F, yo, 1.e-7, 1e-7, 10000, w, &result, &error); 

	DPRINT ("W::integral(): % .18f\n", result);
	DPRINT ("\testimated error = % .18f\n", error);
	DPRINT ("\tintervals =  %d\n", w->size);

	gsl_integration_workspace_free (w);

	return result;
}

