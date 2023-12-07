import sys
def printf(format, *args):
    sys.stdout.write(format % args)

import numpy as np
import mplib_ctypes as mplib

#
# parameters
#
# dielectric constant and T
diel=2
T=400
#
d=7.0; # ion diameter in A
L2d = 1.1
L = L2d * d; # slit width in A
L=10.
# z positions
z1=L/2.;
z2=L/2.
# separation
#d=0.1
R = d
Rmax = 20.
dR = 0.01

# separations for a square lattice
#R4 = np.array([d, d*np.sqrt(2), 2. * d, d * np.sqrt(5), 2. * d * np.sqrt(2)]);
#R3 = np.array([d, d*np.sqrt(3)]);

# output
#printf("# Temperature %g \n", T); 
#printf("# Dielectric constant %g \n", diel); 
#printf("# Ion diameter %g\n", d);
printf("# Slit width %g\n", L);
printf("# Temperature %g \n", T); 
printf("# Dielectric constant %g \n", diel); 
printf("# Particles' perpendicular position (across the slit): %g, %g\n", z1, z2);
#printf("# R (A)         U (1/A)         U (Hartree) 	Coulomb (Hartree)\n"); 
printf("# R (A)         U (1/A)         U (kBT) 	Coulomb (KBT)\n"); 

#K2H = 0.0000031667908523699422
K2H=1
while R < Rmax:
    val = mplib.slit_u2 (z1, z2, R, L)
    printf(" %e  % e   % e  % e\n", R, val, 332.0636 * 503.2166 * val / diel / T,
	332.0636 * 503.2166  / diel / T / R); 
#   printf(" %e  % e   % e  % e\n", R, val, 332.0636 * 503.2166 * val * K2H, 332.0636 * 503.2166 * K2H / R); 

    R=R+dR; 

exit()
printf ("\n\n")
for R in R4:
    val = mplib.slit_u2 (z1, z2, R, L)
#    printf(" %e  % e   % e  \n", R, val, 332.0636 * 503.2166 * val / diel / T); 
    printf(" %e  % e  \n", R, 332.0636 * 503.2166 * val / diel / T); 


printf ("\n\n")
for R in R3:
    val = mplib.slit_u2 (z1, z2, R, L)
    printf(" %e  % e   % e \n", R, val, 332.0636 * 503.2166 * val / diel / T); 


