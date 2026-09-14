/*  u1.cc 2010-07-27 test binary potential
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

#include "mplib.h"

#define EPS    2.e-2

int main (int argc, char ** argv) {

#if 0

	double T = 333.;
	double diel = 2.42;
	double factor = 332.0636 * 503.2166 / (T * diel);

	double L = 5.5;

	//double z_0 = EPS;
	double d = 5.; // diameter (A)
	double z_0 = d/2.;
	double z_1 = L - z_0;

	int i, N = 50;

	double step = (z_1 - z_0) / ((double) N );
	double z = z_0;
	for (i = 0; i < N + 1; i++) 
	{
	        double val_c = mplib_potential_unary (z, L);
		/*double val_f = mplib_potential_unary_ (&z, &L);
		double val_dft = mplib_dft_u1 (z, L, 1.); 
		printf (" % g \t % e  \t % e  \t  % e\n",
			z, val_c, val_f, val_dft); */
		printf (" %e  % e  %e \n",z, val_c, factor * val_c);
		z += step;
	}

#endif
#if 1
	double T = 300.;
	double diel = 2.5;

	double factor = 332.0636 * 503.2166 /  (T * diel);

	printf ("# temperature: T = %g\n", T);
	printf ("# dielectric constant: e = %g\n", diel);
	printf ("# self energy is calculated in the slit center\n");

	printf ("# slit width L (A)  \t self energy (kBT)\n");

	// d is ion diameter in A
	double L= 3.;
	double dL = 0.1;
	for (; L < 12.;)
	{
		double z = L /2.;
		double val = mplib_potential_unary (z, L);
		printf (" % e \t %e\n", L, factor * val);
		L += dL;
	}
#endif


	return 0;
}
