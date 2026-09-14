import sys
def printf(format, *args):
    sys.stdout.write(format % args)

import mplib_ctypes as mplib
from scipy import interpolate

#
# parameters
#
diel = 2.5
T = 300
conv = 332.0636 * 503.2166 / diel / T
#
# ion radius in A
r = 0.5
r1 = 0.
# tube diameter and radius
L = 10.
R = L / 2.
step = 0.01 * R
# cyl_u1_app() only accepts r/R <= 0.9 (see MAX in cylindre-u1-approx.c);
# stay safely clear of that boundary given the fixed step accumulates
# floating-point error, on top of the physical ion-radius margin (R - r).
rmax = min(R - r, 0.88 * R)

# Build an interpolation table from a coarse grid, exactly like
# mpore-gcmc's code does internally (see cylinder.__init__ in
# mpore_serial_c.py)
# for fast repeated lookups instead of calling cyl_u1() directly on
# every Monte Carlo move. This lets us check how much accuracy that
# shortcut costs.
r_coarse, U1_coarse = mplib.cyl_u1_calc_array(R, rmax, 100)
u1_interp = interpolate.interp1d(r_coarse, U1_coarse)

# output
printf("# Temperature %g \n", T)
printf("# Dielectric constant %e \n", diel)
printf("# Tube radius %g (diameter %g) \n", R, L)
printf("# r (A)    U1 (1/A)    U1 (kBT)  U1_approx (1/A)  U1_approx (kBT)  "
       "U1_interp (1/A)  U1_interp (kBT)\n")
while r1 < rmax + step:
    val = mplib.cyl_u1(r1, R)
    val_app = mplib.cyl_u1_app(r1, R)
    val_interp = u1_interp(r1)
    printf(" %e  % e   % e  % e   % e  % e   % e\n",
           r1, val, conv * val, val_app, conv * val_app,
           val_interp, conv * val_interp)

    r1 = r1 + step
