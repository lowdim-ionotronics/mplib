import sys
def printf(format, *args):
    sys.stdout.write(format % args)

import mplib_ctypes as mplib

#
# parameters
#
D=10. # pore diameter in A
R = 10. / 2.; # pore radius
r0 = 0; # p1's radial position
r1=0. # p2's radial position
phi = 0.;  # p1's angle (wrt p2)

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
printf("# Dielectric constant %g \n", diel); 
printf("# Temperature %g \n", T); 

printf("# Tube radius %g (diameter %g) \n", R, 2. * R);
printf("# Particles' radial positions: %g, %g\n", r0, r1);
printf("# Particles' orientation: %g\n", phi);

printf("# z (A)         U (1/A)         U (kBT)        U_approx (1/A)  U_approx (kBT)\n"); 

while z < zmax:
    val = mplib.cyl_u2 (r0, r1, phi, z, R)
    val_app = mplib.cyl_u2_app (r0, r1, phi, z, R)
    printf(" %e  % e   % e  % e   % e\n", z, val, 332.0636 * 503.2166 * val / diel / T,  val_app, 332.0636 * 503.2166 * val_app / diel / T); 

    z=z+dz; 

