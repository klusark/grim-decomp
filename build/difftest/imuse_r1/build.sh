#!/bin/bash
# usage: build/difftest/imuse_r1/build.sh [out.exe]     (then: out.exe [cases] [seed])
# Differential test of build/overrides_imuse_r1.c against the original machine code (agent r1): FUN_10006560, FUN_10006620,
# FUN_100068b0 sliced from the base assembly of commit 85dd22f (where they are still assembled) with
# build/mixdiff/slice_orig.py, renamed orig_<name>; their return addresses after the calls of FUN_100068b0 are exported as
# _orig_ret_<original address> so the test can map them; FUN_100064d0 transcribed in thunks.s.  The C is compiled with
# the flags build/link.py uses for override files (EXTRA_CFLAGS=-O2 for an optimised variant, OVR=<file> for a mutant).
# Links the original data image of IMUSE.DLL (build/obj/IMUSE.DLL/data_s.o); int3 stubs for anything else.
set -e
cd "$(dirname "$0")/../../.."
PROG=IMUSE.DLL
OUT=${1:-build/difftest/imuse_r1/out/r1_test.exe}
W=build/difftest/imuse_r1/out/$(basename $OUT .exe); mkdir -p $W; rm -f $W/*.o
[ -f build/difftest/imuse_r1/out/base_asm_funcs.s ] || git show 85dd22f:src/IMUSE.DLL/asm_funcs.s > build/difftest/imuse_r1/out/base_asm_funcs.s
python -I build/mixdiff/slice_orig.py build/difftest/imuse_r1/out/base_asm_funcs.s $W/orig.s FUN_10006560 FUN_10006620 FUN_100068b0
sed -i -E 's/^(\.L1000(6560|6620)_(100065f3|100066eb|1000672c|10006778):)/\t.globl _orig_ret_\3\n_orig_ret_\3:\n\1/' $W/orig.s
test $(grep -c "^_orig_ret_" $W/orig.s) = 4
/ucrt64/bin/gcc -m32 -c $W/orig.s -o $W/orig.o
/ucrt64/bin/gcc -m32 -c build/difftest/imuse_r1/thunks.s -o $W/thunks.o
export PATH=/mingw32/bin:$PATH
gcc -std=gnu11 -fpermissive -w -fno-builtin -ffreestanding -fno-common -include build/compat.h -Isrc/$PROG -DGRIM_IMUSE $EXTRA_CFLAGS \
    -c ${OVR:-build/overrides_imuse_r1.c} -o $W/mine.o
gcc -O1 -w -c build/difftest/imuse_r1/r1_test.c -o $W/test.o
: > $W/stubs.s
/ucrt64/bin/gcc -m32 -c $W/stubs.s -o $W/stubs.o
rm -f $OUT
for i in 1 2 3 4 5; do
  gcc -o $OUT $W/test.o $W/mine.o $W/orig.o $W/thunks.o build/obj/$PROG/data_s.o $W/stubs.o -Wl,--allow-multiple-definition 2> $W/link.log && break
  python -I build/difftest/asm_s5/stubgen.py $W/link.log $W/stubs.s
  /ucrt64/bin/gcc -m32 -c $W/stubs.s -o $W/stubs.o
done
test -f $OUT || { head -20 $W/link.log; exit 1; }
