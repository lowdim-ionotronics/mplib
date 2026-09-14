/*  u2.c 2012-08-24 test binary potential
 *
 * Copyright (C) 2012 Alpha 
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

#include <stdio.h>
#include <math.h>

#include "mplib.h"

#define EPS    1.e-8
#define pow2(x)     ( (x) * (x) )

int main (int argc, char ** argv) {

// pore diameter in A
double D = 10;
double R = D/2.;
/*double r0=0; */
double r0 = 0;
double phi = 0.; 
double r1=0.; 

#if 0
double z = 10;
int Nr = 5;
int Nphi = 5;  
double idxPHI = 2*M_PI/ (double)Nphi; 
double idxRHO = R/ (double) Nr; 
double ir, iphi ;
 
	for (ir = 0; ir < Nr; ir++ ) 
	{
		for(iphi = 0; iphi < Nphi; iphi++)  
		{
			
			double var = mplib_cylinder_u2 (r0, r1, phi, z, R); 
			double var_approx = mplib_cylinder_u2_approx (r0, r1, phi, z, R); 

			printf("%e   %e  % e   % e   % e\n", r1, phi, var, var_approx, (var - var_approx) / var); 
			phi  += idxPHI; 
	

		}
		r1 += idxRHO;
		phi = 0.;
		printf("\n"); 
	}
#endif

#if 1
	
	double d = 5.; // ion diameter
	double z = d;
	double dz = 0.1*d;
	double zmax = 3*d;
	for (z = d; z < zmax;) 
	{
		double var = mplib_cylinder_u2 (r0, r1, phi, z, R); 
		double var_approx = mplib_cylinder_u2_approx (r0, r1, phi, z, R); 

		printf("%e   %e  % e   % e\n", z, var, var_approx, (var - var_approx) / var); 
		z  += dz; 
	}

#endif

	return 1;
}

