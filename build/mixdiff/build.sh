#!/bin/bash
# usage: build/mixdiff/build.sh <test.c> <out.exe> <orig function names...>
# Builds a differential test: the original machine code (sliced from the baseline assembly $BASE_ASM) as orig_<name>,
# the hand-written C of build/overrides_*.c ($OVERRIDES) as <name>, the original data image (data_s.o of the baseline build).
# Symbols the data image points at (function pointers) and that nobody defines get int3 stubs.
set -e
cd "$(dirname "$0")/../.."
BASE_ASM=${BASE_ASM:-/c/Users/Joel/grimO_base/asm_funcs_base.s}
DATA_O=${DATA_O:-build/obj/GRIMFANDANGO.EXE/data_s.o}
T=$1; OUT=$2; shift 2
W=build/mixdiff/out; mkdir -p $W; rm -f $W/mine_*.o $W/extra_*.o
python -I build/mixdiff/slice_orig.py $BASE_ASM $W/orig.s "$@"
/ucrt64/bin/gcc -m32 -c $W/orig.s -o $W/orig.o
for ov in ${OVERRIDES:-build/overrides_mixer.c build/overrides_mixer_drv.c}; do
  /ucrt64/bin/gcc -m32 -std=gnu11 -fpermissive -w -fno-builtin -ffreestanding -fno-common -include build/compat.h -Isrc/GRIMFANDANGO.EXE -DGRIM_EXE $EXTRA_CFLAGS -c $ov -o $W/mine_$(basename $ov .c).o
done
export PATH=/mingw32/bin:$PATH
gcc -O2 -w $TEST_CFLAGS -Ibuild/mixdiff -c $T -o $W/test.o
gcc -O2 -w -Ibuild/mixdiff -c build/mixdiff/fx.c -o $W/fx.o
: > $W/stubs.s; : > $W/extra_none.s; /ucrt64/bin/gcc -m32 -c $W/extra_none.s -o $W/extra_none.o
/ucrt64/bin/gcc -m32 -c $W/stubs.s -o $W/stubs.o
for i in 1 2 3 4; do
  for a in $EXTRA_ASM; do /ucrt64/bin/gcc -m32 -c $a -o $W/extra_$(basename $a .s).o; done
  gcc -o $OUT $W/test.o $W/fx.o $W/extra_*.o $W/mine_*.o $W/orig.o $DATA_O $W/stubs.o -Wl,--allow-multiple-definition -lkernel32 -lwinmm 2> $W/link.log && break
  python -I build/mixdiff/stubgen.py $W/link.log $W/stubs.s
  /ucrt64/bin/gcc -m32 -c $W/stubs.s -o $W/stubs.o
done
test -f $OUT || { head -20 $W/link.log; exit 1; }
# a stub that stands in for a data symbol would silently corrupt the code: refuse
if grep -E '^_(g_|DAT_|UINT_|PTR_|s_|_DAT|_g_)' $W/stubs.s | grep -v '\.globl'; then echo "data symbols were stubbed (stale data_s.o?)"; rm -f $OUT; exit 1; fi
