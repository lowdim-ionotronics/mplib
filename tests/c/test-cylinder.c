/*  test-cylinder.c
 *
 * Minimal automated smoke test for the cylinder (1D pore) potentials --
 * part of `make check` (see tests/c/Makefile.am). Unlike
 * examples/c/cylindre-u1.c and cylindre-u2.c (illustrative print loops,
 * not assertions), this program aborts (via assert()) if anything looks
 * wrong, so it registers as a real PASS/FAIL in the test harness. Mirrors
 * tests/python/test_mplib.py's cross-validation + frozen-value approach.
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
    double R = 3.0;

    /* Frozen regression value, computed once from this library. */
    double u1 = mplib_cylinder_u1(1.0, R);
    assert(isfinite(u1));
    assert(fabs(u1 - (-0.15345337399145023)) < 1e-9);

    /* Exact vs. polynomial-approximation should agree closely within the
     * approximation's documented valid range (r/R <= 0.9, see
     * lib/cylindre-u1-approx.c's MAX). */
    for (int i = 1; i <= 8; i++) {
        double x = i / 10.0; /* 0.1 .. 0.8 */
        double r = x * R;
        double exact = mplib_cylinder_u1(r, R);
        double approx = mplib_cylinder_u1_approx(r, R);
        double rel_err = fabs(approx - exact) / fabs(exact);
        assert(rel_err < 0.02);
    }

    /* Pairwise interaction should decay with axial separation. */
    double r0 = 0.3 * R, r1 = 0.3 * R, phi = 0.0;
    double prev = fabs(mplib_cylinder_u2(r0, r1, phi, 0.5, R));
    for (double z = 2.0; z <= 9.0; z += 3.5) {
        double cur = fabs(mplib_cylinder_u2(r0, r1, phi, z, R));
        assert(cur <= prev + 1e-12);
        prev = cur;
    }

    printf("test-cylinder: OK\n");
    return 0;
}
