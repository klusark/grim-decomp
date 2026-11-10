#!/bin/bash
# Builds and runs the differential test of build/overrides_asm_q6.c against the original machine code.
# The original is sliced from the assembly of commit 2df265d (before these functions were converted); the data image and
# the C neighbours the originals call are the objects of a linked build (make -C build link).
# usage: build/difftest/asm_q6/run_all.sh [cases per function] [name filter]   (default 1000000)
cd "$(dirname "$0")/../../.." || exit 1
N=${1:-1000000}
D=build/difftest/asm_q6; O=$D/out; mkdir -p $O
[ -s $O/base_asm_funcs.s ] || git show 2df265d:src/GRIMFANDANGO.EXE/asm_funcs.s > $O/base_asm_funcs.s
F=$(sed -n 's/^FN([A-Z_0-9]*, *\([A-Za-z0-9_]*\)).*/\1/p' $D/q6_funcs.h)
F="$F _ftol $EXTRA_ORIG"
OB=build/obj/GRIMFANDANGO.EXE
EXTRA_OBJS=${EXTRA_OBJS-"$OB/overrides_asm_o1.o $OB/overrides_asm_s1.o"} bash $D/build.sh $D/q6_test.c $O/${OUTEXE:-q6_test}.exe $F || exit 1
[ -n "$BUILD_ONLY" ] && exit 0
$O/${OUTEXE:-q6_test}.exe $N $2
