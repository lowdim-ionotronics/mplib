/*  u2.c  2010-04-28  2body potential energy (up to a coeff)
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

#include <gsl/gsl_sum.h>
#include <gsl/gsl_sf_bessel.h>
#include <gsl/gsl_integration.h>

//
// Some EPS defines
//
// Minimum of a sum element, otherwise zero
#define EPS_SUM  1.e-50

// Minimum R, otherwise treated as zero
#define EPS_R    1.e-50

// Minimum of dz=fabs(z1 -z2)
#define EPS_DZ   1.e-50

// The sum and the integral representation of a potential
static double inline sum (double z1, double z2, double R);
static double inline integral (double z1, double z2);

double mplib_potential_binary (double z1, double z2, double R, double L) 
{
	// rescale arguments
        z1 /= L;
	z2 /= L;
	R /= L;

	DPRINT ("z1=%g, z2=%g, R=%g\n", z1, z2, R);

	MPLIB_CRITICAL ( (z1 > 0.) && (z1 < 1.), "argument out of bound (z1=%g, z2=%g)", z1, z2);
	MPLIB_CRITICAL ( (z2 > 0.) && (z2 < 1.), "argument out of bound");
	MPLIB_CRITICAL ( R >= 0.0, "argument out of bound");

	// Calculate as an integral or as a sum 
	// depending on the aruments
	if (R != 0.0)
//	if (R > EPS_R)
		return (4. / L) * sum (z1, z2, R);
	else 
	{
		MPLIB_WARNING ("R=0.0, using the integral representation");
		return (1. / L) * integral (z1, z2);
	}
}

/*****************************
 * The sum and the integral  *
 * ***************************/

/* undersum function */
static double fn (int n, void * params) {

	void ** p = (void*) params;
	double z1 = *((double *) p[0]);
	double z2 = *((double *) p[1]);

	double R = *( (double*) p[2]);

	DPRINT ("z1=%g, z2=%g, R=%g\n", z1, z2, R);

	double s1 = sin (M_PI * (double) n * z1);
	double s2 = sin (M_PI * (double) n * z2);

	double x = M_PI * (double) n * R;
	double K = gsl_sf_bessel_K0 (x);

	double Sn = K * s1 * s2;
	DPRINT ("n=%i: sin(z1)=%g, sin(z2)=%g, K0=%g, Sn=%g\n", n, s1, s2, K, Sn);

	return Sn;
}
/* The sum (rescaled arguments!) */
static double inline sum (double z1, double z2, double R)
{

	int N = 100, i;
	double result, error;
	double s[N];

	DPRINT ("mplib_potential_binary_sum(): sum(): z1=%g, z2=%g, R=%g\n", z1, z2, R);

	void * p[] = {&z1, &z2, &R};

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

