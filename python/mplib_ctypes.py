#
# mplib binding via ctypes
#
import ctypes
from ctypes import *

# mplib must be installed in a searchable dir
so_file = "libmplib.so"
mplib = CDLL(so_file, mode=1)

#
# ions in a metallic cylinder 
#
mplib.mplib_cylinder_u1.restype = ctypes.c_double
mplib.mplib_cylinder_u1_approx.restype = ctypes.c_double
mplib.mplib_cylinder_u2.restype = ctypes.c_double
mplib.mplib_cylinder_u2_approx.restype = ctypes.c_double

def cyl_u1 (r1, R):
    return mplib.mplib_cylinder_u1 (ctypes.c_double(r1), ctypes.c_double(R))

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

def slit_u2 (z1, z2, R, L):
    return mplib.mplib_potential_binary (ctypes.c_double(z1), ctypes.c_double(z2), ctypes.c_double(R), ctypes.c_double(L) );

def slit_u2_app (z1, z2, R, L):
    return mplib.mplib_potential_binary_approx (ctypes.c_double(z1), ctypes.c_double(z2), ctypes.c_double(R), ctypes.c_double(L) );
