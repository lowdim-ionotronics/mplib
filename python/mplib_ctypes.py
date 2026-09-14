#
# mplib binding via ctypes
#
import ctypes
from ctypes import *
import numpy as np

# libmplib.so must be on the OS dynamic loader's search path (e.g.
# LD_LIBRARY_PATH set to the install prefix's lib/, or `ldconfig` re-run
# after installing to a standard location). We don't consume the
# mplib-config/mplib.pc that `./configure` also generates -- those are
# meant for other autotools/pkg-config *build* systems to find mplib's
# headers/libs at compile time, not for a plain `ctypes.CDLL` runtime
# lookup, so they wouldn't help here anyway.
so_file = "libmplib.so"
try:
    mplib = CDLL(so_file, mode=1)
except OSError as e:
    raise OSError(
        f"Could not load {so_file}: {e}\n"
        "Build it first (./configure && make in the mplib repo root), then "
        "make sure its lib/ directory is on LD_LIBRARY_PATH (or run `make "
        "install` and point LD_LIBRARY_PATH at the install prefix's lib/)."
    ) from e

#
# ions in a metallic cylinder 
#
mplib.mplib_cylinder_u1.restype = ctypes.c_double
mplib.mplib_cylinder_u1_approx.restype = ctypes.c_double
mplib.mplib_cylinder_u2.restype = ctypes.c_double
mplib.mplib_cylinder_u2_approx.restype = ctypes.c_double

def cyl_u1 (r1, R):
    return mplib.mplib_cylinder_u1 (ctypes.c_double(r1), ctypes.c_double(R))

def cyl_u1_calc_array (R, rmax, n):
    r=np.linspace (0,rmax, n)
    U1 = []
    for ri in r:
        U1.append(cyl_u1 (ri, R))
    return r,U1 

def cyl_u1_app (r1, R):
    return mplib.mplib_cylinder_u1_approx (ctypes.c_double(r1), ctypes.c_double(R))

def cyl_u2 (r0, r1, phi, z, R):
    return mplib.mplib_cylinder_u2 (ctypes.c_double(r0),ctypes.c_double(r1),ctypes.c_double(phi), ctypes.c_double(z), ctypes.c_double(R))

def cyl_u2_app (r0, r1, phi, z, R):
    return mplib.mplib_cylinder_u2_approx (ctypes.c_double(r0),ctypes.c_double(r1),ctypes.c_double(phi), ctypes.c_double(z), ctypes.c_double(R))

#
# ions in a metallic slit
#
mplib.mplib_potential_unary.restype = ctypes.c_double
mplib.mplib_potential_binary.restype = ctypes.c_double
mplib.mplib_potential_binary_approx.restype = ctypes.c_double

def slit_u1 (z, L):
    return mplib.mplib_potential_unary (ctypes.c_double(z), ctypes.c_double(L) );

def slit_u1_calc_array (L, eps, n):
    z=np.linspace (eps,L-eps, n)
    U1 = []
    for zi in z:
        U1.append(slit_u1 (zi, L))
    return z,U1 

def slit_u2 (z1, z2, R, L):
    return mplib.mplib_potential_binary (ctypes.c_double(z1), ctypes.c_double(z2), ctypes.c_double(R), ctypes.c_double(L) );

def slit_u2_app (z1, z2, R, L):
    return mplib.mplib_potential_binary_approx (ctypes.c_double(z1), ctypes.c_double(z2), ctypes.c_double(R), ctypes.c_double(L) );

