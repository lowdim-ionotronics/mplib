"""
Regression tests for the mplib Python bindings (mplib_ctypes).

Covers the cylinder (1D pore) and slit (2D pore) electrostatic potentials --
the only functions still exposed after the DFT/DDFT code was dropped from
this public release.

Two independent kinds of check, deliberately not requiring hand-derived
"true" reference values:

1. Cross-validation between the exact and polynomial-approximation variants
   of the cylinder functions, which should agree closely within the
   approximation's documented valid range (r/R <= 0.9, see
   lib/cylindre-u1-approx.c). This is a free regression check: it would have
   caught, for example, the stray `#define DEBUG` that was accidentally left
   enabled in cylindre-u1-approx.c.

2. Frozen regression values (tests/python/reference_values.json), generated
   once from this library and checked into git. Any future change to the
   numerics that isn't an intentional physics fix should be caught by these.

The slit u2 exact/approx variants are NOT cross-validated against each
other here: at the parameter points checked during development they
disagreed by more than 100% (e.g. slit_u2(2,3,1,10)=0.53 vs
slit_u2_app(2,3,1,10)=0.25), meaning the approximation's valid regime for
that function isn't the same simple "small x" one used for the cylinder
functions and isn't characterized in this repo. Only frozen-value and
sanity checks are applied to it for now.
"""
import json
import math
import os

import pytest

import mplib_ctypes as mplib

FIXTURE_PATH = os.path.join(os.path.dirname(__file__), "reference_values.json")


def _load_fixtures():
    with open(FIXTURE_PATH) as f:
        return json.load(f)


# ---------------------------------------------------------------------------
# 1. Cross-validation: exact vs. polynomial-approximation cylinder functions
# ---------------------------------------------------------------------------

CYL_APPROX_MAX_X = 0.9  # matches MAX in lib/cylindre-u1-approx.c


@pytest.mark.parametrize("x", [0.1, 0.3, 0.5, 0.7, 0.85])
def test_cyl_u1_approx_matches_exact(x):
    R = 3.0
    r = x * R
    exact = mplib.cyl_u1(r, R)
    approx = mplib.cyl_u1_app(r, R)
    assert approx == pytest.approx(exact, rel=0.02)


@pytest.mark.parametrize(
    "r0_frac,r1_frac,phi,z_frac",
    [
        (0.2, 0.3, 0.3, 0.7),
        (0.4, 0.1, 1.0, 0.2),
        (0.8, 0.85, 2.5, 1.5),
    ],
)
def test_cyl_u2_approx_matches_exact(r0_frac, r1_frac, phi, z_frac):
    R = 3.0
    r0, r1 = r0_frac * R, r1_frac * R
    z = z_frac * R
    exact = mplib.cyl_u2(r0, r1, phi, z, R)
    approx = mplib.cyl_u2_app(r0, r1, phi, z, R)
    assert approx == pytest.approx(exact, rel=0.1, abs=1e-6)


# ---------------------------------------------------------------------------
# 2. Frozen regression values
# ---------------------------------------------------------------------------

@pytest.mark.parametrize("entry", _load_fixtures(), ids=lambda e: f"{e['fn']}{tuple(e['args'])}")
def test_frozen_regression_value(entry):
    fn = getattr(mplib, entry["fn"])
    result = fn(*entry["args"])
    assert result == pytest.approx(entry["value"], rel=1e-9, abs=1e-12)


# ---------------------------------------------------------------------------
# 3. Basic physical sanity checks
# ---------------------------------------------------------------------------

def test_cyl_u1_finite_across_accessible_range():
    R = 3.0
    for i in range(1, 20):
        r = (i / 20.0) * CYL_APPROX_MAX_X * R
        assert math.isfinite(mplib.cyl_u1(r, R))


def test_slit_u1_finite_across_range():
    L = 10.0
    for i in range(1, 20):
        z = (i / 20.0) * L
        assert math.isfinite(mplib.slit_u1(z, L))


def test_slit_u2_decays_with_axial_separation():
    """Interaction magnitude should decrease as the two ions move further
    apart along the slit (z1 fixed, z2 -> further from z1)."""
    R, L = 1.0, 20.0
    z1 = 5.0
    values = [abs(mplib.slit_u2(z1, z1 + dz, R, L)) for dz in (0.5, 2.0, 5.0, 9.0)]
    assert all(a >= b for a, b in zip(values, values[1:])), values


def test_cyl_u2_decays_with_axial_separation():
    R = 3.0
    r0, r1, phi = 0.3 * R, 0.3 * R, 0.0
    values = [abs(mplib.cyl_u2(r0, r1, phi, z, R)) for z in (0.5, 2.0, 5.0, 9.0)]
    assert all(a >= b for a, b in zip(values, values[1:])), values
