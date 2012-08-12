/*  test-ddft-W.c 2012-05-23 test DDFT's W(x) for the jx current due to 
 *  pore-screened electrostatic potential 9with b const)
 *
 * Copyright (C) 2012 Svyatoslav Kondrat (Valiska)
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

#include <mplib.h>

int main (int argc, char ** argv) 
{

	/* In nanometers*/
	double L = 0.8;
	double LB = 10.;
	double b = 0.5;
	double z = L / 2.;

	double Xo = 0., Xmax = 1.;
	double x0 = 0.0, x1 = Xmax;

	int ix, Nx = 1000;
	double x = x0;

	double stepx = (x1 - x0) / ((double) Nx );

	for (ix = 0; ix < Nx + 1; ix++) 
	{
		double dx = Xo - x;
		//double W = mplib_ddft_W (z, z, dx, L, LB, b);
		double W = 0.;
		//double Wapp = mplib_ddft_W_approx (z, z, dx, L, LB, b);
		double Wapp = 0.;

		//double Wx = mplib_ddft_Wx (z, z, dx, L, LB, b);
		double Wx = 0.;

		printf (" % e \t % e \t  % e \t  % e \n", x, W, Wapp, Wx);
		x += stepx;
	}

	return 1;
}

