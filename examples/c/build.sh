#!/bin/sh
# Compile the C examples against an already-built mplib (run
# "./configure && make" in the repo root first). Usage:
#   cd examples/c && ./build.sh
set -e

cd "$(dirname "$0")"
LIBDIR=../../lib/.libs
INCDIR=../../lib

if [ ! -f "$LIBDIR/libmplib.so" ] && [ ! -f "$LIBDIR/libmplib.a" ]; then
    echo "error: $LIBDIR/libmplib.* not found -- build mplib first (./configure && make in the repo root)" >&2
    exit 1
fi

for src in slit-u1.c slit-u2.c cylindre-u1.c cylindre-u2.c; do
    out=${src%.c}
    echo "compiling $src -> $out"
    gcc -o "$out" "$src" -I "$INCDIR" $(gsl-config --cflags --libs) \
        -L "$LIBDIR" -lmplib -Wl,-rpath,"$LIBDIR"
done

echo "done -- run e.g. ./slit-u1"
