#!/bin/bash
# usage: build/difftest/clipface/run.sh [cases]
# Differential test of rdPrimit3_ClipFace (0x0040deb0): the original machine code, sliced from the asm_funcs.s of the last
# commit that still assembled it (1b0b2d2^; BASE_ASM=<file> to use another copy), next to the C block of
# build/overrides_logic.c (OVERRIDE=<file> for another file) compiled the way build/link.py compiles the overrides
# (i686 gcc, -O0, same flags), linked with the original data image (build/obj/GRIMFANDANGO.EXE/data_s.o, or the one of the
# main checkout if this tree has not been built).
set -e
cd "$(dirname "$0")/../../.."
D=build/difftest/clipface; W=$D/out; mkdir -p $W
OVERRIDE=${OVERRIDE:-build/overrides_logic.c}
if [ -z "$BASE_ASM" ]; then BASE_ASM=$W/base_asm_funcs.s; git show 1b0b2d2^:src/GRIMFANDANGO.EXE/asm_funcs.s > $BASE_ASM; fi
DATA=${DATA:-build/obj/GRIMFANDANGO.EXE/data_s.o}
[ -f "$DATA" ] || DATA=/c/Users/Joel/grim-decomp/build/obj/GRIMFANDANGO.EXE/data_s.o
python -I build/mixdiff/slice_orig.py $BASE_ASM $W/orig.s rdPrimit3_ClipFace >/dev/null
/ucrt64/bin/gcc -m32 -c $W/orig.s -o $W/orig.o
# the one C function, with the headers overrides_logic.c uses
{ printf '#include "ghidra_types.h"\n#include "globals.h"\n#include "functions.h"\n'
  awk '/^\/\* ==== rdPrimit3_ClipFace \(/{on=1} on && /^\/\* ==== / && !/rdPrimit3_ClipFace/{exit} on' $OVERRIDE; } > $W/mine.c
export PATH=/mingw32/bin:$PATH
CF="-std=gnu11 -fpermissive -w -fno-builtin -ffreestanding -fno-common -include build/compat.h -Isrc/GRIMFANDANGO.EXE -Ibuild -DGRIM_EXE"
gcc $CF $EXTRA_CFLAGS -c $W/mine.c -o $W/mine.o
gcc -O1 -w -fno-builtin -c $D/clip_test.c -o $W/test.o
# int3 stubs for everything else the data image references
rm -f $W/clip_test.exe; : > $W/stubs.s
for i in 1 2 3 4 5; do
  /ucrt64/bin/gcc -m32 -c $W/stubs.s -o $W/stubs.o
  gcc -o $W/clip_test.exe $W/test.o $W/mine.o $W/orig.o $DATA $W/stubs.o -Wl,--allow-multiple-definition 2> $W/link.log && break
  python -I build/difftest/asm_s5/stubgen.py $W/link.log $W/stubs.s >/dev/null
done
test -f $W/clip_test.exe || { head -20 $W/link.log; exit 1; }
$W/clip_test.exe ${1:-200000}
