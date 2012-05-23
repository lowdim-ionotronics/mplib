/*  ddft-Kx.c  2012-05-23  evaluate Kx (x-x', b,..) of Jx due to the pore-screaned elecrostatic pair potential
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

#include "mplib.h"

#include <stdio.h>
#include <math.h>

#include <gsl/gsl_sum.h>
#include <gsl/gsl_sf_bessel.h>
#include <gsl/gsl_integration.h>

#define EPS_SUM   1.e-20
#define R_MAX     50.0
#define pow2(x)         ( (x) * (x) )

/* The sum of the second term in Kx */
static double inline sum (double z1, double z2, double dx, double yo);

double mplib_ddft_Kx (double z1, double z2, double dx, double L, double LB, double b)
{

	DPRINT ("z1=%g, z2=%g, L=%g, LB=%g, b=%g\n", z1, z2, L, LB, b);

	MPLIB_CRITICAL ( (z1 > 0.) && (z1 < L), "argument out of bound (z1=%g, z2=%g, L=%g)", z1, z2, L);
	MPLIB_CRITICAL ( (z2 > 0.) && (z2 < L), "argument out of bound (z1=%g, z2=%g, L=%g)", z1, z2, L);
	MPLIB_CRITICAL ( b > 0.0, "argument out of bound, b=%g", b);

	double yo2 = pow2(b) - pow2(dx);
	double yo = 0.;

	double K1 = 0., K2 = 0.;

	if (yo2 > 0.0) 
	{	
		yo = sqrt (yo2);
		/* 1/L is included in potential_binary 
		 * NOTE: z1 and z2 are not normalized to L as we use functions for MC simulation */
		K1 = 16. * LB * dx * mplib_potential_binary (z1, z2, b, L);
	}

	/* NOTE: z1, z2, dx and yo are normalized, functions are below */
	K2 = - 16. * M_PI * LB * dx / pow2(L) * sum (z1/L, z2/L, dx/L, yo/L);

	return K1 + K2;
}

/*****************************
 * The sum  *
 * ***************************/

/* declare I_n(dx, y)*/
static double inline integral (double n, double dx, double yo);

/* undersum function */
static double fn (int n, void * params) {

	void ** p = (void*) params;
	double z1 = *((double *) p[0]);
	double z2 = *((double *) p[1]);

	double dx = *( (double*) p[2]);
	double yo = *( (double*) p[3]);

	DPRINT ("z1=%g, z2=%g, dx=%g, yo=%g\n", z1, z2, dx, yo);

	double s1 = sin (M_PI * (double) n * z1);
	double s2 = sin (M_PI * (double) n * z2);
	double In = integral ((double) n, dx, yo);

	double Sn = In * s1 * s2 * (double) n;
	DPRINT ("n=%i: sin(z1)=%g, sin(z2)=%g, K0=%g, Sn=%g\n", n, s1, s2, In, Sn);

	return Sn;
}
/* The sum (rescaled arguments!) */
static double inline sum (double z1, double z2, double dx, double yo)
{

	int N = 100, i;
	double result, error;
	double s[N];

	DPRINT ("mplib_ddft_Kx(): sum(): z1=%g, z2=%g, dx=%g yo=%g\n", z1, z2, dx, yo);

	void * p[] = {&z1, &z2, &dx, &yo};

	for (i = 0; i < N; i++)
	{
		s[i] = fn (i + 1, p);
		if (fabs(s[i]) < EPS_SUM)
			break;
	}
	N = i;

	if (N < 2) 
	{
		N = 2;
		s[0] =  fn (1, p);
		s[1] =  fn (2, p);

	}

	gsl_sum_levin_u_workspace * w = gsl_sum_levin_u_alloc (N);
	MPLIB_CRITICAL (w, "Cannot allocate the workspace for the sum");

	gsl_sum_levin_u_accel (s, N, w, &result, &error);

	DPRINT ("results=%g (term-by-term=%g), error=%g\n", result, w->sum_plain, error);

	gsl_sum_levin_u_free (w);

	return result;
}

/*
 * Evaluate the integral
 *
 * 	I_n (dx, yo) = int_y0^\infty dy K1 (pi n sqrt(dx^2 + y^2)) / sqrt(dx^2 + y^2)
 */

/* integrand */
static double f (double y, void * params) {

	void ** p = (void*) params;

	double n = *((double *) p[0]);
	double dx = *((double *) p[1]);

	DPRINT ("f(): n=%g, dx = %g", n, dx);

	double R = sqrt (pow2(dx) + pow2 (y));
	double f = gsl_sf_bessel_K1 (M_PI * n * R) / R;

	DPRINT ("%g\n", f);

	return f;
}

/* Use GSL integrator */
static double inline integral (double n, double dx, double yo)
{
	gsl_integration_workspace * w 
		= gsl_integration_workspace_alloc (10000);
	MPLIB_CRITICAL (w, "Cannot allocate the workspace for the integration");

	DPRINT ("integral(): n=%g, dx=%g, yo=%g\n", n, dx, yo);

	double result, error;

	gsl_function F;
	F.function = &f;

	void * p[] = {&n, &dx};
	F.params = (void*) p;

	gsl_integration_qagiu (&F, yo, 1.e-7, 1e-7, 10000, w, &result, &error); 

	DPRINT ("integral(): % .18f\n", result);
	DPRINT ("\testimated error = % .18f\n", error);
	DPRINT ("\tintervals =  %d\n", w->size);

	gsl_integration_workspace_free (w);

	return result;
}

