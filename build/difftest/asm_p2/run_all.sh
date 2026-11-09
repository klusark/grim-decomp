#!/bin/bash
# Builds and runs the differential test of build/overrides_asm_p2.c against the original machine code.
# The original is sliced from the assembly of commit bb04517 (before these functions were converted); the data image is
# build/obj/GRIMFANDANGO.EXE/data_s.o of a linked build of the tree (make -C build link).
# usage: build/difftest/asm_p2/run_all.sh [cases per function]   (default 1000000; also runs the C at -O2 and the
# mutation check)
cd "$(dirname "$0")/../../.." || exit 1
N=${1:-1000000}
O=build/difftest/asm_p2/out; mkdir -p $O
[ -s $O/base_asm_funcs.s ] || git show bb04517:src/GRIMFANDANGO.EXE/asm_funcs.s > $O/base_asm_funcs.s
F="Frustum_TestSphere Polygon_ClipToPlane Angles_ToMatrix Angles_ToMatrixNoPos Matrix_AxisAngle rdLight_CalcVertexIntensities rdCanvas_DrawPoint _ftol"
rc=0
bash build/difftest/asm_p2/build.sh build/difftest/asm_p2/math_test.c $O/math_test.exe $F >/dev/null || exit 1
echo "== C at -O0 (the build's default), all inputs"; $O/math_test.exe $N || rc=1
echo "== C at -O0, no signalling NaN inputs"; P2_NAN=1 $O/math_test.exe $((N / 4)) || rc=1
EXTRA_CFLAGS=-O2 bash build/difftest/asm_p2/build.sh build/difftest/asm_p2/math_test.c $O/math_test_O2.exe $F >/dev/null || exit 1
echo "== C at -O2, all inputs"; $O/math_test_O2.exe $((N / 4)) || rc=1
LINKPY=1 bash build/difftest/asm_p2/build.sh build/difftest/asm_p2/math_test.c $O/math_test_link.exe $F >/dev/null || exit 1
echo "== C with the build/link.py flags (the object that is linked into the game)"; $O/math_test_link.exe $((N / 4)) || rc=1
echo "== mutations"; python -I build/difftest/asm_p2/mutate.py 20000 | tail -1 || rc=1
exit $rc
