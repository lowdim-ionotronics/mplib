/*  test-slit.c
 *
 * Minimal automated smoke test for the slit (2D pore) potentials -- part
 * of `make check` (see tests/c/Makefile.am). Unlike examples/c/slit-u1.c
 * and slit-u2.c (illustrative print loops, not assertions), this program
 * aborts (via assert()) if anything looks wrong, so it registers as a
 * real PASS/FAIL in the test harness.
 *
 * Copyright (C) 2026 Svyatoslav Kondrat (Valiska)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at
 * your option) any later version.
 */
#include <assert.h>
#include <math.h>
#include <stdio.h>

#include "mplib.h"

int main(void)
{
    double L = 10.0;

    /* Frozen regression value, computed once from this library. */
    double u1 = mplib_potential_unary(2.0, L);
    assert(isfinite(u1));
    assert(fabs(u1 - (-0.1274904283373799)) < 1e-9);

    /* Finite across the accessible range (0 < z < L). */
    for (int i = 1; i < 20; i++) {
        double z = (i / 20.0) * L;
        assert(isfinite(mplib_potential_unary(z, L)));
    }

    /* Interaction magnitude should decay as the axial separation grows. */
    double R = 1.0, z1 = 3.0;
    double prev = fabs(mplib_potential_binary(z1, z1 + 0.5, R, L));
    for (double dz = 1.0; dz <= 6.0; dz += 1.0) {
        double cur = fabs(mplib_potential_binary(z1, z1 + dz, R, L));
        assert(cur <= prev + 1e-12);
        prev = cur;
    }

    printf("test-slit: OK\n");
    return 0;
}
