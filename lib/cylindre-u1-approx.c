/*  cylindre-u1-approx.c  2015-02-27  self energy (up to a coeff)
 *
 * Copyright (C) 2012 Alpha Lee
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

#define DEBUG
#include "defines.h"

#ifdef MPLIB_USE_APPROX
#  undef MPLIB_USE_APPROX
#endif
#include "mplib-private.h"

#include <stdio.h>
#include <math.h>

#include <gsl/gsl_sum.h>
#include <gsl/gsl_sf_bessel.h>
#include <gsl/gsl_integration.h>
#define pow2(x)     ( (x) * (x) )

static double fm (double t, void * params);/*the t integrand*/
static double integral_t(double phi,void * params); /*the t integral*/

static double fun_phi (double t, void * params); /*the phi integrand*/
static double integral_phi (void * params); /*the phi integral*/
#define MAX 0.9
double mplib_cylinder_u1_approx (double r, double R) 
{

	DPRINT("r=%f, R=%f\n", r, R);
	double x = r/R;
	MPLIB_CRITICAL (x <= MAX, "Too close to the surface (%1.10e)< %g", x, MAX);

	double x2 = pow2(x);
	double x3 = x * x2;
	double x4 = pow2 (x2);
	

	/* double result = 8.650738495182575 - 3.509006980758725 * x + 
			41.56937034835524 * x2 - 92.40059159564377 * x3  + 97.05413438801448 * x4;
        result = - result / (2. * M_PI * M_PI * R); */

	double x5 = x4 * x;
	double x6 = pow2(x3);
	double x7 = x6 * x;
	double x8 = pow2 (x4);
	double x9 = x8 * x;
	double x10 = pow2(x5);

	//fprintf (stderr, "using 10 power approx\n");

	double result = -0.43673 + 0.0420915 * x - 1.8557 * x2 + 25.456 * x3 -201.168 * x4
		+ 917.508 * x5 - 2561.13 * x6 + 4438.71 * x7 + -4662.53 * x8 
		+ 2719.51 * x9 - 676.906 * x10;
        return result / R; 
}

