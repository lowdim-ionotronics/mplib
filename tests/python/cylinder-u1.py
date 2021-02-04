import sys
def printf(format, *args):
    sys.stdout.write(format % args)

import mplib_ctypes as mplib

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
    val = mplib.cyl_u1 (r1, R)
    val_app = mplib.cyl_u1_app (r1, R)
    printf(" %e  % e   % e  % e   % e\n", r1, val, 332.0636 * 503.2166 * val / diel,  val_app, 332.0636 * 503.2166 * val_app / diel); 

    r1=r1+idx; 

