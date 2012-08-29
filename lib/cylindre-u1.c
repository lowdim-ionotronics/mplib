/*  cylindre-u1.c  2012-08-26  self energy (up to a coeff)
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


double mplib_cylinder_u1 (double r, double R) 
{

	int M = 100, i;
	double result, error;
	double s[M];	

	gsl_integration_workspace * wphi
		= gsl_integration_workspace_alloc (10000);
	MPLIB_CRITICAL (wphi, "Cannot allocate the integration workspace");

	gsl_integration_workspace * wt
		= gsl_integration_workspace_alloc (10000);
	MPLIB_CRITICAL (wt, "Cannot allocate the integration workspace");

	for (i = 0; i < M; i++)
	{	
		int table_length = (i == 0 ? 5 : 5 * i);
		DPRINT ("table length = %i\n", table_length);
		gsl_integration_qawo_table * table = gsl_integration_qawo_table_alloc ((double) i, 2*M_PI, GSL_INTEG_COSINE, table_length);

		void * p[] = {&r, &R, &i, wphi, wt, table};
		s[i] = (i == 0 ? 2 : 1) * integral_phi(p);
		DPRINT ("cylindre(): s[%i]=%1.10e\n", i, s[i]);

		gsl_integration_qawo_table_free (table);

		if (s[i] < 1.e-6)
			break;
	}
	M=i; 
	
	gsl_sum_levin_u_workspace * w = gsl_sum_levin_u_alloc (M);
	MPLIB_CRITICAL (w, "Cannot allocate the workspace for the sum");

	gsl_sum_levin_u_accel (s, M, w, &result, &error);

	DPRINT ("results=%g (term-by-term=%g), error=%g\n", result, w->sum_plain, error);

	gsl_sum_levin_u_free (w);

	gsl_integration_workspace_free (wt);
	gsl_integration_workspace_free (wphi);

	return result;
}
/* the t integrand */

static double fm (double t, void * params) 
{

	void ** p = (void*) params;
	
	double r1 = *((double *) p[0]);
	double R = *( (double*) p[1]);
	int m = *( (int*) p[2]);	
	double phi = *( (double*) p[3]);
	
	double tR = t /R;
	
	double alpha = sqrt(pow2(R)- 2*R*r1*cos(phi) + pow2(r1)); 	
	DPRINT ("m=%i, t=%e, t*alpha/R =  %e, tr1/R=%e\n", m, t, t*alpha/R, t*r1/R);
	double fun_m = 0.;
	if (t < 1.e+2)
		fun_m = gsl_sf_bessel_In(m, tR*r1) * gsl_sf_bessel_K0(tR*alpha) / gsl_sf_bessel_In(m, t); 

	DPRINT ("fun_m =  %e\n", fun_m);
	return fun_m; 

}

/*the t intergral*/ 

static double integral_t(double phi,void * params) 
{

	void ** p = (void**) params; 
	void * par[] = {p[0], p[1], p[2], &phi}; 

	double m = (double) *((int*) p[2]);
	DPRINT ("integral_t(): m=%e\n", m);

	gsl_integration_workspace * wt = p[4];

	double result, error;

	gsl_function F;
	F.function = &fm;
	F.params = par;

	gsl_integration_qagiu (&F, 0.0, 1.e-7, 1e-7, 10000, wt, &result, &error); 

	DPRINT ("%g   % .18f\n", phi, result);
	DPRINT ("estimated error = % .18f\n", error);
	DPRINT ("intervals =  %d\n", wt->size);

	return result; 
}  

/*the phi integrand */

static double fun_phi (double phi, void * params) 
{
	return integral_t (phi, params); 
} 

/*the phi integral */ 

static double integral_phi (void * params) 
{

	void ** p = (void*) params; 
	double result, error;
	double m = (double) *((int*) p[2]);
	DPRINT ("integral_phi(): m=%e\n", m);

	gsl_integration_workspace * wphi = (gsl_integration_workspace *) p[3];
	gsl_integration_qawo_table * table = (gsl_integration_qawo_table *) p[5];

	gsl_function F;
	F.function = &fun_phi;
	F.params = params;
	
	gsl_integration_qawo (&F, 0.0, 1.e-7, 1e-7, 10000, wphi, table, &result, &error); 

	DPRINT (" % .18f\n", result);
	DPRINT ("estimated error = % .18f\n", error);
	DPRINT ("intervals =  %d\n", wphi->size);

	return result; 
}

