import sys
def printf(format, *args):
    sys.stdout.write(format % args)

import mplib_ctypes as mplib
import numpy as np
from scipy import interpolate

def cyl_u1_calc_array (R, rmax, n):
    r=np.linspace (0,rmax, n)
    U1 = []
    for ri in r:
        U1.append(mplib.cyl_u1 (ri, R))
    return r,U1 

#
# parameters
#
r1 = 0.;
R = 6.4/ 2.;
idx = 0.1;

# dielectric constant and temperature
diel=2.5
T = 300 # in K

r,U1 = cyl_u1_calc_array (R, 0.5 * R, 100)
cyl_u1_interp = interpolate.interp1d(r, U1)

# output
printf("# Dielectric constant %e \n", diel); 
printf("# Temperature %e \n", T); 

printf("# Tube radius %g (diameter %g) \n", R, 2. * R); 
printf("# r (A)     U1 (1/A)        U1 (KBT)        U1_approx (1/A)     U1_approx (KBT)\n"); 

#while r1 < R-5.0/2.+2.*idx:
while r1 < 0.5 * R:
    val = mplib.cyl_u1 (r1, R)
    val_interp = cyl_u1_interp (r1)
    printf(" %e  ", r1)
    printf(" % e   % e ", val, 332.0636 * 503.2166 * val / diel / T)
    printf(" % e   % e\n", val_interp, 332.0636 * 503.2166 * val_interp / diel / T); 

    r1=r1+idx; 

