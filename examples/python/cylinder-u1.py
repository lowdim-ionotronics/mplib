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
#
# ion radius in A
r=0.5
r1 = 0.;
# tube diameter and radius
L=10.
R = L/ 2.;
step = 0.01* R;

# output
printf("# Temperature %g \n", T); 
printf("# Dielectric constant %e \n", diel); 
printf("# Tube radius %g (diameter %g) \n", R, L); 
printf("# r (A)    U1 (1/A)    U1 (kBT)  U1_approx (1/A)    U1_approx (KBT)\n"); 
while r1 < R - r + step:
    val = mplib.cyl_u1 (r1, R)
   # val_app = mplib.cyl_u1_app (r1, R)
    printf(" %e  % e   % e \n", r1, val, conv * val); 
#    printf(" %e  % e   % e  % e   % e\n", r1, val, conv * val,  val_app, conv * val_app); 

    r1=r1+step; 

