/*  u2.c 2012-08-24 test self energy
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

#define EPS    1.e-10
#define pow2(x)     ( (x) * (x) )

int main (int argc, char ** argv) {

	double diel = 2.5;
	double idx = 0.01;
	int i ; 	
	double r1 = 0.;
	double R = 6.4 / 2.;
	printf("# Dielectric constant %e \n", diel); 
	printf("# Tube radius %g (diameter %g) \n", R, 2. * R); 
	printf("# r (A)    U1 (1/A)    U1 (K)\n"); 

	while (r1<R-5.0/2.+2.*idx)
	{ 
		double var = mplib_cylinder_u1 (r1, R); 
		double var_app = mplib_cylinder_u1_approx (r1, R); 

		printf(" %e  % e   % e  % e   % e\n", r1, var, 332.0636 * 503.2166 * var / diel,  var_app, 332.0636 * 503.2166 * var_app / diel); 
		r1=r1+idx; 
	}

	return 1;
}

