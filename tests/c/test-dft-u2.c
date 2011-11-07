/*  test-dft-u2.c 2011-10-17 test (effective) binary potential
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


	/* In nanometers*/
	double L = 2.;
	double LB = 10.;
	double b = 0.7;

	double z0 = EPS, z1 = L - EPS;
	int iz, Nz = 200;

	double stepz = (z1 - z0) / ((double) Nz );

	// Charge location	
	double Z = 0.5 * L;
	double z = z0;

	fprintf (stderr, "# Pore width L=%g\n", L);
	fprintf (stderr, "# Charge is at z=%g\n", Z);

	for (iz = 0; iz < Nz + 1; iz++) 
	{
		double pot = mplib_dft_u2 (z, Z, L, LB, b);
		printf (" % e \t  % e \n", z, pot);
		z += stepz;
	}

	return 1;
}

