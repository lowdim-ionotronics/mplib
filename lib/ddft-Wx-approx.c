/*  ddft-Wx.c  2012-05-23  evaluate Wx (x-x', b,..) of Jx due to the pore-screaned elecrostatic pair potential
 *
 *  mplib_ddft_Wx (z1, z2, dx, L, LB, b) calculates the effective modified mean-field interaction potential:
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

/* The sum of the second term in Wx */
static double inline integral (double dx, double yo);

double mplib_ddft_Wx_approx (double z1, double z2, double dx, double L, double LB, double b)
{
	DPRINT ("mplib_ddft_Wx(): z1=%g, z2=%g, dx=%g, L=%g, LB=%g, b=%g\n", z1, z2, dx, L, LB, b);

	MPLIB_CRITICAL ( (z1 > 0.) && (z1 < L), "argument out of bound (z1=%g, z2=%g, L=%g)", z1, z2, L);
	MPLIB_CRITICAL ( (z2 > 0.) && (z2 < L), "argument out of bound (z1=%g, z2=%g, L=%g)", z1, z2, L);
	MPLIB_CRITICAL ( b > 0.0, "argument out of bound, b=%g", b);

	double yo2 = pow2(b) - pow2(dx);
	double yo = 0.;

	double K1 = 0., K2 = 0.;

	if (yo2 > 0.0) 
	{	
		yo = sqrt (yo2);
		/* 4/L is included in potential_binary 
		 * NOTE: z1 and z2 are not normalized to L as we use functions for MC simulation */
		K1 = 4. * LB * dx * mplib_potential_binary_approx (z1, z2, b, L) / yo;
	}

	/* NOTE: z1, z2, dx and yo are normalized, functions are below */
	K2 = - 16. * M_PI * LB * dx * integral (dx/L, yo/L) * sin (M_PI * z1/L) * sin (M_PI * z2 / L) / (pow2(L)) ;

	return K1 + K2;
}

/* declare I_n(dx, y) for n = 1 */
static double inline integral (double dx, double yo);

/*
 * Evaluate the integral
 *
 * 	I_n (dx, yo) = int_y0^\infty dy K1 (pi n sqrt(dx^2 + y^2)) / sqrt(dx^2 + y^2)
 */

/* integrand */
static double f (double y, void * params) 
{

	double dx = *((double *) params);

	double R = sqrt (pow2(dx) + pow2 (y));
	DPRINT ("Wx::f(): n=%g, dx=%g, y=%g, R=%g, ", n, dx, y, R);

	double f = 0;
	
	if ( (R < R_MAX) && (R != 0.0) )
#if defined(_MPLIB_APPROX_USE_BESSEL_)
		f = gsl_sf_bessel_K1 (M_PI * R) / R;
#else
#   error MPLIB_APPROX not chosen or not implemented
#endif

	DPRINT ("f=%g\n", f);

	return f;
}

/* Use GSL integrator */
static double inline integral (double dx, double yo)
{
	gsl_integration_workspace * w 
		= gsl_integration_workspace_alloc (10000);
	MPLIB_CRITICAL (w, "Cannot allocate the workspace for the integration");

	DPRINT ("Wx::integral(): n=%g, dx=%g, yo=%g\n", n, dx, yo);

	double result, error;

	gsl_function F;
	F.function = &f;
	F.params = &dx;

	gsl_integration_qagiu (&F, yo, 1.e-7, 1e-7, 10000, w, &result, &error); 

	DPRINT ("Wx::integral(): % .18f\n", result);
	DPRINT ("\testimated error = % .18f\n", error);
	DPRINT ("\tintervals =  %d\n", w->size);

	gsl_integration_workspace_free (w);

	return result;
}

