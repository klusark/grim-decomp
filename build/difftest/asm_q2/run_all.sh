#!/bin/bash
# Builds and runs the differential test of build/overrides_asm_q2.c (the five rdClip_Face3_* clippers) against the
# original machine code, sliced from the assembly of commit 2df265d (before these functions were converted); the data
# image is build/obj/GRIMFANDANGO.EXE/data_s.o of a linked build of the tree (make -C build link).
# usage: build/difftest/asm_q2/run_all.sh [cases per function]   (default 1000000; also runs the C at -O2, the C with
# the build/link.py flags, and the mutation check)
cd "$(dirname "$0")/../../.." || exit 1
N=${1:-1000000}
O=build/difftest/asm_q2/out; mkdir -p $O
[ -s $O/base_asm_funcs.s ] || git show 2df265d:src/GRIMFANDANGO.EXE/asm_funcs.s > $O/base_asm_funcs.s
F="rdClip_Face3GS rdClip_Face3T rdClip_Face3TOrtho rdClip_Face3GT rdClip_Face3GTOrtho"
T=build/difftest/asm_q2/clip_test.c
rc=0
LINKPY=1 bash build/difftest/asm_q2/build.sh $T $O/clip_test_link.exe $F >/dev/null || exit 1
echo "== C with the build/link.py flags (the object that is linked into the game), all inputs"; $O/clip_test_link.exe $N || rc=1
echo "== same, no signalling NaN inputs, other seed"; Q2_NOSNAN=1 Q2_SEED=7 $O/clip_test_link.exe $((N / 4)) || rc=1
bash build/difftest/asm_q2/build.sh $T $O/clip_test.exe $F >/dev/null || exit 1
echo "== C at -O0 with the Makefile flags"; Q2_SEED=11 $O/clip_test.exe $((N / 4)) || rc=1
EXTRA_CFLAGS=-O2 bash build/difftest/asm_q2/build.sh $T $O/clip_test_O2.exe $F >/dev/null || exit 1
echo "== C at -O2"; Q2_SEED=13 $O/clip_test_O2.exe $((N / 4)) || rc=1
echo "== mutations"; python -I build/difftest/asm_q2/mutate.py 20000 | tail -1 || rc=1
exit $rc
