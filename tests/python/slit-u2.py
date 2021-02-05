import sys
def printf(format, *args):
    sys.stdout.write(format % args)

import numpy as np
import mplib_ctypes as mplib

#
# parameters
#
# dielectric constant and T
diel=2.5
T=300
#
d=7.0; # ion radius
L2d = 1.5
L = L2d * d; # slit width
# z positions
z1=L/2.;
z2=L/2.
# separation
R = d
Rmax = 3. * d
dR = 0.01 * d

# separations for a square lattice
R4 = np.array([d, d*np.sqrt(2), 2. * d, d * np.sqrt(5), 2. * d * np.sqrt(2)]);
R3 = np.array([d, d*np.sqrt(3)]);

# output
printf("# Temperature %g \n", T); 
printf("# Dielectric constant %g \n", diel); 
printf("# Ion diameter %g\n", d);
printf("# Slit width %g\n", L);
printf("# Particles' perpendicular position (across the slit): %g, %g\n", z1, z2);
printf("# R (A)         U (1/A)         U (kBT) \n"); 

while R < Rmax:
    val = mplib.slit_u2 (z1, z2, R, L)
    printf(" %e  % e   % e \n", R, val, 332.0636 * 503.2166 * val / diel / T); 

    R=R+dR; 

printf ("\n\n")
for R in R4:
    val = mplib.slit_u2 (z1, z2, R, L)
    printf(" %e  % e   % e  \n", R, val, 332.0636 * 503.2166 * val / diel / T); 

printf ("\n\n")
for R in R3:
    val = mplib.slit_u2 (z1, z2, R, L)
    printf(" %e  % e   % e \n", R, val, 332.0636 * 503.2166 * val / diel / T); 


