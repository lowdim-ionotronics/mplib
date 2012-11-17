/*  dft-u2-approx.c  2011-10-17  effective elecrostatic pair potential for DFT calculations
 *  the sum is approximated by the first term only (implying _MPLIB_APPROX_USE_BESSEL_)
 *
 *  mplib_dft_u2 (z1, z2, L, LB, b) calculates the effective modified mean-field interaction potential:
 *
 *  	u2 (z1, z2) = 4 LB R0 sum_1^\infty (1/n) sin (pi n z1/L) sin (pi n z2/L) K1 (pi n Rc / L)

 *  for R0 > 0, and
 *						
 * 	u2 (z1, z2) = pi LB [ z + z' - |z - z'| - 2 z1 z2 /L),
 *
 *  for R0 = 0, where R0 = H(b - |z1-z2]) sqrt[b^2 - (z1-z2)^2], 
 *  H(x) being the Heaviside step function and b(=d) the 'cut-off radius'.
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

#include "mplib-private.h"

#include <stdio.h>
#include <math.h>

#include <gsl/gsl_sf_bessel.h>

double mplib_dft_u2_approx (double z1, double z2, double L, double LB, double b)
{

	DPRINT ("z1=%g, z2=%g, L=%g, LB=%g, b=%g\n", z1, z2, L, LB, b);

	MPLIB_CRITICAL ( (z1 > 0.) && (z1 < L), "argument out of bound (z1=%g, z2=%g, L=%g)", z1, z2, L);
	MPLIB_CRITICAL ( (z2 > 0.) && (z2 < L), "argument out of bound (z1=%g, z2=%g, L=%g)", z1, z2, L);
	MPLIB_CRITICAL ( b > 0.0, "argument out of bound, b=%g", b);

	double Ro2 = pow2(b) - pow2(z1 - z2);

/* FIXME: add _MPLIB_APPROX_USE_EXPANSION_ */

	if (Ro2 > 0.0) 
	{	
		double Ro = sqrt (Ro2) / L;
		DPRINT("R=%e vs Rmax=%e\n", Ro, R_MAX);
		if (Ro >= R_MAX)
			return 0.0;

#if defined(_MPLIB_APPROX_USE_BESSEL_)
		DPRINT("Using first term in the sum: z1=%g, z2=%g, Ro = %g\n", z1, z2, Ro);
		return 4. * LB * Ro * gsl_sf_bessel_K1 (M_PI * Ro) * sin (M_PI * z1 / L) * sin (M_PI * z2 / L);
#else
#   error MPLIB_APPROX not chosen or not implemented
#endif

	}
	else
	{
		DPRINT(stderr, "Using FUNC for z1=%g, z2=%g, Ro2 = %g\n", z1, z2, Ro2);
		return M_PI * LB * ( z1 + z2 - fabs(z1- z2) - 2. * z1 * z2 / L);
	}
}

