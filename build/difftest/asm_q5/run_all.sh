#!/bin/bash
# Builds and runs the differential test of build/overrides_asm_q5.c against the original machine code.
# The original is sliced from the assembly of commit 2df265d (before these functions were converted); the data image is
# build/obj/GRIMFANDANGO.EXE/data_s.o of a linked build (make -C build link).
# usage: build/difftest/asm_q5/run_all.sh [cases per function] [name filter]   (default 1000000)
cd "$(dirname "$0")/../../.." || exit 1
N=${1:-1000000}
D=build/difftest/asm_q5; O=$D/out; mkdir -p $O
[ -s $O/base_asm_funcs.s ] || git show 2df265d:src/GRIMFANDANGO.EXE/asm_funcs.s > $O/base_asm_funcs.s
F=$(sed -n 's/^FN([A-Z_]*, *\([A-Za-z0-9_]*\)).*/\1/p' $D/q5_funcs.h)
# EXTRA_OBJS: more objects to link (none needed: the drivers call only functions of overrides_asm_q5.c)
F="$F $EXTRA_ORIG"
EXTRA_OBJS=${EXTRA_OBJS-} bash $D/build.sh $D/raster_test.c $O/${OUTEXE:-raster_test}.exe $F || exit 1
[ -n "$BUILD_ONLY" ] && exit 0
$O/${OUTEXE:-raster_test}.exe $N $2
