import sys
def printf(format, *args):
    sys.stdout.write(format % args)

import ctypes
from ctypes import *

# mplib must be installed in a searchable dir
so_file = "libmplib.so"
mplib = CDLL(so_file, mode=1)
mplib.mplib_cylinder_u2.restype = ctypes.c_double
mplib.mplib_cylinder_u2_approx.restype = ctypes.c_double

#
# parameters
#
R = 5.2 / 2.; # pore radius
r0 = 0; # p1's radial position
phi = 0.; # p2's radial position
r1=0.; # p1's angle (wrt p2)

# ion diameter
d = 5.
# separation along cylinder's axis
z = d;
dz = 0.1*d
zmax = 3. * d

# dielectric constant and T
diel=2.5
T=300

# output
printf("# Dielectric constant %e \n", diel); 
printf("# Temperature %e \n", T); 

printf("# Tube radius %g (diameter %g) \n", R, 2. * R);
printf("# Particles' radial positions: %g, %g\n", r0, r1);
printf("# Particles' orientation: %g\n", phi);

printf("# z (A)         U (1/A)         U (kBT)        U_approx (1/A)  U_approx (kBT)\n"); 

while z < zmax:
    val = mplib.mplib_cylinder_u2 (ctypes.c_double(r0),ctypes.c_double(r1),ctypes.c_double(phi), ctypes.c_double(z), ctypes.c_double(R))
    val_app = mplib.mplib_cylinder_u2_approx (ctypes.c_double(r0),ctypes.c_double(r1),ctypes.c_double(phi), ctypes.c_double(z), ctypes.c_double(R))
    printf(" %e  % e   % e  % e   % e\n", z, val, 332.0636 * 503.2166 * val / diel / T,  val_app, 332.0636 * 503.2166 * val_app / diel / T); 

    z=z+dz; 

