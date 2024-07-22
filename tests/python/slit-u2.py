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
T=298
#
d=5.0; # ion diameter in A
#L2d = 1.
#L = L2d * d; # slit width in A
L=d+3.37
# z positions
z1=L/2.;
z2=L/2.
# separation
#d=0.1
R = d
Rmax = 50.
dR = 0.1

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
printf("# R (A)         U (1/A)         U (kBT) 	Coulomb (KBT)       \n"); 

#K2H = 0.0000031667908523699422
K2H=1
conv1 = 332.0636 * 503.2166
conv2 = 0.5922 # kBt to kcal/mole at T=298
E_kcalmol =[]
R_A = []
while R < Rmax:
    val = mplib.slit_u2 (z1, z2, R, L)
    U_kBT = conv1 * val / diel / T
    UC_kBT = conv1 / diel / T / R

    U_kcalmol= U_kBT * conv2
    UC_kcalmol= UC_kBT * conv2
    E_kcalmol.append(U_kcalmol)
    R_A.append (R)

#   printf(" %e  % e   % e  % e   %e  %e\n", R, val, U_kBT,  UC_kBT,  U_kcalmol, UC_kcalmol); 
#   printf(" %e  % e   % e  % e\n", R, val, 332.0636 * 503.2166 * val * K2H, 332.0636 * 503.2166 * K2H / R); 

    R=R+dR; 

#print (E_kcalmol)
F_kcalmolA = - np.gradient (E_kcalmol, R_A)
#print (F_kcalmolA)

for r,u,f in zip (R_A, E_kcalmol, F_kcalmolA):
	printf(" %e  % e   %e\n", r, u, f)

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


