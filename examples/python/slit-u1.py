import sys
def printf(format, *args):
    sys.stdout.write(format % args)

import mplib_ctypes as mplib

#
# parameters
#
diel=2.5
T=300
conv = 332.0636 * 503.2166 / diel / T
# pore width
L=10.

# ion radius in A
r=0.5
# distance across the slit
z = r
step = 0.01*L

# output
printf("# Temperature %g \n", T); 
printf("# Dielectric constant %e \n", diel); 
printf("# Slit width %g) \n", L); 
printf("# z (A)    U1 (1/A)    U1 (kBT)\n"); 

while z < L - r + step:
    val = mplib.slit_u1 (z, L)
    printf(" %e  % e   % e \n", z, val, conv * val); 

    z=z+step; 

