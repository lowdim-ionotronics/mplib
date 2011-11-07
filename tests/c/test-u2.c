/*  u2.c 2010-07-27 test binary potential
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

#include <stdio.h>
#include <math.h>

#include "potentials.h"

#define EPS    1.e-8
#define pow2(x)     ( (x) * (x) )

int main (int argc, char ** argv) {


	double L = 10.0;

// Box to tabulate
	double z0 = EPS, z1 = L - EPS;
//	double z0 = 0.4 * L, z1 = 0.6 * L;
	double x0 = -1. * L, x1 = 1. * L;

	int ix, iz, Nx = 50, Nz = 50;

	double stepz = (z1 - z0) / ((double) Nz );
	double stepx = (x1 - x0) / ((double) Nx );

	// Charge location	
	double Z = 0.5 * L , X = 0.;

	double z = z0, x = x0;

	printf ("# Charge is at z=%g, x=%g\n", Z, X);

#if    0
	for (iz = 0; iz < Nz; iz++) 
	{
		x = x0;
		for (ix = 0; ix < Nx; ix++) 
		{
			x += stepx;
			double R = fabs(X-x);
			printf ("  % e  \t  % e ", z, x);

			if ( (fabs(z - Z) < EPS) && ( R < EPS) )
				printf (" \t NaN \n");
			else
			{
				double r = sqrt (pow2 (R) + pow2 (z-Z));
				double pot = mplib_potential_binary (z, Z, R, L);
				printf (" \t  % e \t  % e\n", pot, 1. / r);
			}
		}
		z += stepz;
		printf ("\n");
	}
#else
#  if 0
	x = X;
	double R = fabs(X-x);
	for (iz = 0; iz < Nz; iz++) 
	{
		if ( !((fabs(z - Z) < EPS) && ( R < EPS)) )
		{
			double r = sqrt (pow2 (R) + pow2 (z-Z));
			double pot = mplib_potential_binary (z, Z, R, L);
			printf (" % e \t  % e \t  % e\n", z, pot, 1. / r);
		}
		z += stepz;
	}
#  else
	z = Z;
	x = x0;
	for (ix = 0; ix < Nx; ix++) 
	{
		x += stepx;
		double R = fabs(X-x);

		if ( ! ((fabs(z - Z) < EPS) && ( R < EPS) ) )
		{
			double r = sqrt (pow2 (R) + pow2 (z-Z));
			double pot = mplib_potential_binary (z, Z, R, L);
			printf (" %e  \t  % e \t  % e\n", R, pot, 1. / r);
		}
	}

#  endif
#endif

// Check what is zero
/*
	double R = 1.e-40;
	z = 0.975 * L, Z = .5 * L;
	fprintf (stderr, "z1=%g, z2=%g, R=%g, pot=%g vs %g\n", 
		z, Z,  R, mplib_potential_binary (z, Z, R, L), 
		mplib_potential_binary (z, Z, 0.0, L));

	R = 1.e-300;
	fprintf (stderr, "z1=%g, z2=%g, R=%g, pot=%g vs %g\n", 
		z, Z,  R, mplib_potential_binary (z, Z, R, L), 
		mplib_potential_binary (z, Z, 0.0, L));
*/
	return 1;
}
