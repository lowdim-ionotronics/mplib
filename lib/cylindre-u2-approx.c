/*  cylindre-u2-approx.c  2015-02-27  2body potential energy (up to a coeff)
 *
 * Copyright (C) 2015 S Kondrat aka Valiska
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

static inline double Km (double r1, double r2, double z, double R, int m);
static inline double fm (int m, void * params);
static inline double kron(int m, int n); 

#define EPS_SUM    1.e-016

double mplib_cylinder_u2_approx (double rho1, double rho2, double phi, double z, double R) 
{

	int M = 2, i;
	double result, error;
	double s[M];	

	void * p[] = {&rho1, &rho2, &z, &R,&phi};

	// fprintf (stderr, "mplib_cylinder_u2_approx(): using only two terms\n");
	
	for (i = 0; i < M; i++)
	{
		
		s[i] = (kron(i,0)+1)*fm(i, p);
		DPRINT ("cylindre(): s[%i]=%1.10e\n", i, s[i]);

/* reinstate this break clause? Alpha 18/09/2012 */
/*
		 if (fabs(s[i]) < EPS_SUM)
			break;
*/			
	}
	result = s[0] + s[1]; /* take only the first term in approximation */
	/*
	M=i + 1; 
	DPRINT ("M=%i\n", M);	

	gsl_sum_levin_u_workspace * w = gsl_sum_levin_u_alloc (M);
	MPLIB_CRITICAL (w, "Cannot allocate the workspace for the sum");

	gsl_sum_levin_u_accel (s, M, w, &result, &error);

	DPRINT ("results=%g (term-by-term=%g), error=%g\n", result, w->sum_plain, error);

	gsl_sum_levin_u_free (w);
*/
        result = 2.*result/R; 

	return result;
}

static inline double fm (int m, void * params) {

	void ** p = (void*) params;
	
	double r1 = *((double *) p[0]);
	double r2 = *((double *) p[1]);
	double z = *( (double*) p[2]);
	double R = *( (double*) p[3]);
	double phi = *( (double*) p[4]);
	
	double km = Km(r1,r2,z,R,m); 
	double cosval = cos((double)m*phi) ;
	double fun_m =  cosval * km;
	DPRINT ("fm(): fm[%i]= cos * Km = %g * %g = %1.10e\n", m, cosval, km, fun_m);
	return fun_m; 

}

#define BLOCK_SIZE   1
static inline double Km(double r1, double r2, double z, double R, int m) {

	double result, error;
	int N = 2;
	double S[N];	

	int j, k, n = 0;
	for (j = 0; j < N;j++) 
	{

		S[j]=0; 

		for (k = 0; k < BLOCK_SIZE; k++)
		{
			n++;
			double k_nm = gsl_sf_bessel_zero_Jnu (m, n);
			DPRINT ("k_nm = %g \n", k_nm);

			DPRINT ("k_nm*r1/R = %e", k_nm*r1/R);
			DPRINT ("J=%e\n", gsl_sf_bessel_Jn (m, k_nm*r1/R));

			DPRINT ("k_nm*r2/R = %e", k_nm*r2/R);
			DPRINT ("J=%e\n", gsl_sf_bessel_Jn (m, k_nm*r2/R));

			double a = gsl_sf_bessel_Jn (m, k_nm*r1/R) * gsl_sf_bessel_Jn(m, k_nm*r2/R)*exp(-k_nm*z/R);
			DPRINT ("a = %g\n",a);			
			double b = k_nm * pow2(gsl_sf_bessel_Jn(m+1, k_nm));
			DPRINT ("b = %g\n", b);	
			S[j] += a/b;
			
			//DPRINT ("Km(): k_nm = %g, n = %i, a = %g, b = %g, s = %1.10e\n", k_nm, n, a, b, S[j]);
		}
		//DPRINT ("Km(): S[%i] = %1.10e\n", j, S[j]);
/*
		if (S[j] < EPS_SUM)
			break;
*/
	}
	result = S[0] + S[1]; /* take only first term */
	/*
	N = j + 1;
	DPRINT ("N=%i\n", N);
	gsl_sum_levin_u_workspace * w = gsl_sum_levin_u_alloc (N);
	MPLIB_CRITICAL (w, "Cannot allocate the workspace for the sum");

	gsl_sum_levin_u_accel (S, N, w, &result, &error);

	DPRINT ("results=%g (term-by-term=%g), error=%g\n", result, w->sum_plain, error);

	gsl_sum_levin_u_free (w);
	*/
	return result;
}

static inline double kron(int m, int n) {

	if (m==n){
		return 1; 
	}
	else { 
		return 0; 
	}	
}

