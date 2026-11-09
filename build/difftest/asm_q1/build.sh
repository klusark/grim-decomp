#!/bin/bash
# usage: build/difftest/asm_q1/build.sh <out.exe>
# Differential test build of build/overrides_asm_q1.c (as build/difftest/asm_p2/build.sh): the original machine code of
# rdClip_Line2D, rdClip_Face3_Pos / PosB / Pos_2 / PosB_2 / PosUv and _ftol, sliced from $BASE_ASM and renamed orig_<name>;
# the C of $OVR (default build/overrides_asm_q1.c) compiled with the build's GHIDRA_CFLAGS plus $EXTRA_CFLAGS (e.g. -O2),
# or with LINKPY=1 the flags build/link.py compiles override files with (the C actually linked); the original data image
# ($DATA_O); int3 stubs for anything else.
# BASE_ASM defaults to build/difftest/asm_q1/out/base_asm_funcs.s = `git show 2df265d:src/GRIMFANDANGO.EXE/asm_funcs.s`
# (made by run_all.sh), where these functions are still assembled.
set -e
cd "$(dirname "$0")/../../.."
PROG=GRIMFANDANGO.EXE
D=build/difftest/asm_q1
BASE_ASM=${BASE_ASM:-$D/out/base_asm_funcs.s}
DATA_O=${DATA_O:-build/obj/$PROG/data_s.o}
[ -f "$DATA_O" ] || DATA_O=/c/Users/Joel/grim-decomp/build/obj/$PROG/data_s.o
OUT=$1
W=$D/out/$(basename $OUT .exe); mkdir -p $W; rm -f $W/*.o
python -I build/mixdiff/slice_orig.py $BASE_ASM $W/orig.s rdClip_Line2D rdClip_Face3_Pos rdClip_Face3_PosB \
    rdClip_Face3_Pos_2 rdClip_Face3_PosB_2 rdClip_Face3_PosUv _ftol > /dev/null
/ucrt64/bin/gcc -m32 -c $W/orig.s -o $W/orig.o
CF="-O0 -m32 -march=i686 -std=gnu11 -fpermissive -w -fno-builtin -fno-strict-aliasing -fwrapv -fsingle-precision-constant -fno-common -ffreestanding -include build/compat.h -Ibuild -Isrc/$PROG -DGRIM_EXE"
if [ -n "$LINKPY" ]; then
  PATH=/mingw32/bin:$PATH /mingw32/bin/gcc -std=gnu11 -fpermissive -w -fno-builtin -ffreestanding -fno-common -include build/compat.h -Isrc/$PROG -DGRIM_EXE $EXTRA_CFLAGS -c ${OVR:-build/overrides_asm_q1.c} -o $W/mine.o
else
  /ucrt64/bin/gcc $CF $EXTRA_CFLAGS -c ${OVR:-build/overrides_asm_q1.c} -o $W/mine.o
fi
export PATH=/mingw32/bin:$PATH
gcc -O1 -w -c ${T:-$D/q1_test.c} -o $W/test.o
: > $W/stubs.s
/ucrt64/bin/gcc -m32 -c $W/stubs.s -o $W/stubs.o
rm -f $OUT
for i in 1 2 3 4 5; do
  gcc -o $OUT $W/test.o $W/mine.o $W/orig.o $DATA_O $W/stubs.o -Wl,--allow-multiple-definition -lkernel32 2> $W/link.log && break
  python -I build/difftest/asm_s5/stubgen.py $W/link.log $W/stubs.s > /dev/null
  /ucrt64/bin/gcc -m32 -c $W/stubs.s -o $W/stubs.o
done
test -f $OUT || { head -20 $W/link.log; exit 1; }
