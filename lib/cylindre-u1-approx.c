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

//#define DEBUG
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

double mplib_cylinder_u1_approx (double r, double R) 
{

	double x = r/R;
	MPLIB_CRITICAL (x <= 0.75, "Too close to the surface (%1.10e)< 0.75", x);

	double x2 = pow2(x);
	double x3 = x * x2;
	double x4 = pow2 (x2);
	
	double result = 8.650738495182575 - 3.509006980758725 * x + 
			41.56937034835524 * x2 - 92.40059159564377 * x3  + 97.05413438801448 * x4;
	/*return -result/(4 * M_PI * M_PI * R);*/
        result = - result / (2. * M_PI * M_PI * R);
        return result; 
}

