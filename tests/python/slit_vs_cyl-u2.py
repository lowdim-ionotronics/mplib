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
conv = 332.0636 * 503.2166 / diel / T

#
d=5.0; # ion diameter in A
L= d
Lmax = 3. * d
dL = 0.01 * d

# separation between the iopns
sep=d

# output
printf("# Temperature %g \n", T); 
printf("# Dielectric constant %g \n", diel); 
printf("# Ion diameter %g\n", d);
printf("# Separation between the ions: %g\n", sep);
printf("# Ions are on teh symmetry axis/plane of the pore\n");
printf("# L (A)         Uslit (kBT)         Ucyl (kBT) \n"); 

while L < Lmax:
    z1 = L/2.
    z2 = z1
    slit = mplib.slit_u2 (z1, z2, sep, L)

    cyl = mplib.cyl_u2 (0, 0, 0, sep, L/2.)

    printf(" %e  % e   % e \n", L, conv * slit, conv * cyl); 

    L=L+dL; 


