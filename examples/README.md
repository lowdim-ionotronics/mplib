# mplib examples

Illustrative scripts showing how to call mplib's slit/cylinder potential
functions directly. These are **not** part of the automated build/test
suite (see `tests/` for that) -- they print/plot values for a human to
inspect, not assertions.

## C (`examples/c/`)

Build the library first (`./configure && make` in the repo root), then run
the build script to compile all four examples:

    cd examples/c && ./build.sh
    ./slit-u1

## Python (`examples/python/`)

    LD_LIBRARY_PATH=../../lib/.libs PYTHONPATH=../../python python3 cylinder-u1.py

(run from `examples/python/`; adjust the paths if running from elsewhere).
