/*  dft-u2.c  2011-10-17  effective elecrostatic pair potential for DFT calculations
 *
 *  mplib_dft_u2 (z1, z2, L, LB, b) calculates the effective modified mean-field interaction potential:
 *
 *  	u2 (z1, z2) = 4 LB R0 sum_1^\infty (1/n) sin (pi n z1/L) sin (pi n z2/L) K1 (pi n Rc / L)

 *  for R0 > 0, and
 *						
 * 	u2 (z1, z2) = pi LB [ z + z' - |z - z'| - 2 z1 z2 /L),
 *
 *  for R0 = 0, where R0 = H(b - |z1-z2]) sqrt[b^2 - (z1-z2)^2], 
 *  H(x) being the Heaviside step function and b(=d) the 'cut-off radius'.
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

// The sum and the integral representation of a potential
static double inline sum (double z1, double z2, double R);

double mplib_dft_u2 (double z1, double z2, double L, double LB, double b)
{

	DPRINT ("z1=%g, z2=%g, L=%g, LB=%g, b=%g\n", z1, z2, L, LB, b);

	MPLIB_CRITICAL ( (z1 > 0.) && (z1 < L), "argument out of bound (z1=%g, z2=%g, L=%g)", z1, z2, L);
	MPLIB_CRITICAL ( (z2 > 0.) && (z2 < L), "argument out of bound (z1=%g, z2=%g, L=%g)", z1, z2, L);
	MPLIB_CRITICAL ( b > 0.0, "argument out of bound, b=%g", b);

	double Ro2 = pow2(b) - pow2(z1 - z2);

	if (Ro2 > 0.0) 
	{	
		double Ro = sqrt (Ro2);
		DPRINT("Using summation for z1=%g, z2=%g, Ro = %g\n", z1, z2, Ro);
		return 4. * LB * Ro * sum (z1/L, z2/L, Ro/L);
	}
	else
	{
		DPRINT(stderr, "Using FUNC for z1=%g, z2=%g, Ro2 = %g\n", z1, z2, Ro2);
		return M_PI * LB * ( z1 + z2 - fabs(z1- z2) - 2. * z1 * z2 / L);
	}
}

/*****************************
 * The sum  *
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
	double K = gsl_sf_bessel_K1 (x);

	double Sn = K * s1 * s2 / (double) n;
	DPRINT ("n=%i: sin(z1)=%g, sin(z2)=%g, K0=%g, Sn=%g\n", n, s1, s2, K, Sn);

	return Sn;
}
/* The sum (rescaled arguments!) */
static double inline sum (double z1, double z2, double R)
{

	int N = 100, i;
	double result, error;
	double s[N];

	DPRINT ("mplib_dft_u2(): sum(): z1=%g, z2=%g, R=%g\n", z1, z2, R);

	void * p[] = {&z1, &z2, &R};

	DPRINT("R=%e vs Rmax=%e\n", R, R_MAX);
	if (R >= R_MAX)
	    return 0.0;

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

