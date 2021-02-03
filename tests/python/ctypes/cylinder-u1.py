import sys
def printf(format, *args):
    sys.stdout.write(format % args)

import ctypes
from ctypes import *

# mplib must be installed in a searchable dir
so_file = "libmplib.so"
mplib = CDLL(so_file, mode=1)
mplib.mplib_cylinder_u1.restype = ctypes.c_double
mplib.mplib_cylinder_u1_approx.restype = ctypes.c_double

#
# parameters
#
r1 = 0.;
R = 6.4/ 2.;
idx = 0.01;
diel=2.5

# output
printf("# Dielectric constant %e \n", diel); 
printf("# Tube radius %g (diameter %g) \n", R, 2. * R); 
printf("# r (A)    U1 (1/A)    U1 (K)    U1_approx (1/A)    U1_approx (K)\n"); 

while r1 < R-5.0/2.+2.*idx:
    val = mplib.mplib_cylinder_u1 (ctypes.c_double(r1), ctypes.c_double(R))
    val_app = mplib.mplib_cylinder_u1_approx (ctypes.c_double(r1), ctypes.c_double(R))
    printf(" %e  % e   % e  % e   % e\n", r1, val, 332.0636 * 503.2166 * val / diel,  val_app, 332.0636 * 503.2166 * val_app / diel); 

    r1=r1+idx; 

