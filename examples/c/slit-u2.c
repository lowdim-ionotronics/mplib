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
#include <stdlib.h>

#include <math.h>

#include "mplib.h"

#define EPS    1.e-8
#define pow2(x)     ( (x) * (x) )

int main (int argc, char ** argv) {

#if 0
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
#endif
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
#endif
# if 0
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
			printf (" %e  \t  % e \t  % e\n", R, factor * pot, factor * 1. / r);
		}
	}

#  endif
#endif
#if 0
	double T = 400.;
	double factor = 332.0636 * 503.2166 / T;

	// Ion diameter in A
	double R = 5.;
	double l = R;
	double dl = 0.1;
	printf ("# pore width  \t  energy, kBT \t  Coulomb energy\n");

	for (; l < 1.9 * R;)
	{
		double z = l /2.;
		{
			double r = sqrt (pow2 (R) + pow2 (z-z));
			double pot = mplib_potential_binary (z, z, R, l);
			printf (" %e  \t  % e \t  % e\n", l, factor * pot, factor * 1. / r);
		}
		l += dl;
	}
#endif
#if 0
//	double T = 400.;
	double T = 298.;
	double factor = 332.0636 * 503.2166 / T;

	// Ion diameter in A
	// double L = 6.;
	double L = 10.;

	if (argc > 1)
		L = atof (argv[1]);

	double R = 1.;
	double r = 1.;
	double dr = 0.1;

	printf ("# R=%g, L=%g\n", R, L);
	printf ("# r  \t  energy, kBT \t  Coulomb energy\n");

	for (; r < 10 * R;)
	{
		double z = L /2.;
		{
			double pot = mplib_potential_binary (z, z, r, L);
			printf (" %e  \t  % e \t  % e\n", r, factor * pot, factor * 1. / r);
		}
		r += dr;
	}

#endif
	// Calculate as a function of diameter for a fixed L/d, in the slit center, 
	// at a separation r=d
#if 1
	double T = 300.;
	double diel = 5.;

	double factor = 332.0636 * 503.2166 /  (T * diel);

	// pore width to ion diameter
	double L2d = 1.;

	if (argc > 1)
		L2d = atof (argv[1]);

	printf ("# temperature: T = %g\n", T);
	printf ("# dielectric constant: e = %g\n", diel);
	printf ("# slit width to ion diameter: L/d = %g\n", L2d);
	printf ("# energy is calculated in the slit center for ion separation r=d\n");

	printf ("# d (ion diameter, A)  \t  slit width L (A)  \t energy (kBT)\n");

	// d is ion diameter in A
	double d= 4.;
	double dd = 0.1;
	for (; d < 12.;)
	{
		double L = L2d * d;
		double r = d;
		double z = L /2.;
		double pot = mplib_potential_binary (z, z, r, L);
		printf (" %e  \t  % e \t %e\n", d, L, factor * pot);
		d += dd;
	}
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
