#!/bin/bash
# usage: build/difftest/asm_q2/build.sh <test.c> <out.exe> <orig function names...>
# Differential test build (as build/difftest/asm_s5/build.sh): the original machine code of the named functions, sliced
# from $BASE_ASM and renamed orig_<name>; the C of build/overrides_asm_q2.c compiled with the build's GHIDRA_CFLAGS
# (plus $EXTRA_CFLAGS, e.g. -O2); the original data image ($DATA_O); int3 stubs for anything else.
# BASE_ASM defaults to build/difftest/asm_q2/out/base_asm_funcs.s, the assembly of commit 2df265d (made by run_all.sh
# with `git show 2df265d:src/GRIMFANDANGO.EXE/asm_funcs.s`), where these functions are still assembled.
set -e
cd "$(dirname "$0")/../../.."
PROG=GRIMFANDANGO.EXE
BASE_ASM=${BASE_ASM:-build/difftest/asm_q2/out/base_asm_funcs.s}
DATA_O=${DATA_O:-build/obj/$PROG/data_s.o}
T=$1; OUT=$2; shift 2
W=build/difftest/asm_q2/out/$(basename $OUT .exe); mkdir -p $W; rm -f $W/*.o
python -I build/mixdiff/slice_orig.py $BASE_ASM $W/orig.s "$@"
/ucrt64/bin/gcc -m32 -c $W/orig.s -o $W/orig.o
CF="-O0 -m32 -march=i686 -std=gnu11 -fpermissive -w -fno-builtin -fno-strict-aliasing -fwrapv -fsingle-precision-constant -fno-common -ffreestanding -include build/compat.h -Ibuild -Isrc/$PROG -DGRIM_EXE"
if [ -n "$LINKPY" ]; then   # the flags build/link.py compiles the override files with (the C actually linked)
  PATH=/mingw32/bin:$PATH /mingw32/bin/gcc -std=gnu11 -fpermissive -w -fno-builtin -ffreestanding -fno-common -include build/compat.h -Isrc/$PROG -DGRIM_EXE $EXTRA_CFLAGS -c ${OVR:-build/overrides_asm_q2.c} -o $W/mine.o
else
  /ucrt64/bin/gcc $CF $EXTRA_CFLAGS -c ${OVR:-build/overrides_asm_q2.c} -o $W/mine.o
fi
export PATH=/mingw32/bin:$PATH
gcc -O1 -w -Ibuild/mixdiff -c $T -o $W/test.o
gcc -O2 -w -Ibuild/mixdiff -c build/mixdiff/fx.c -o $W/fx.o
: > $W/stubs.s
/ucrt64/bin/gcc -m32 -c $W/stubs.s -o $W/stubs.o
for i in 1 2 3 4 5; do
  gcc -o $OUT $W/test.o $W/fx.o $W/mine.o $W/orig.o $DATA_O $W/stubs.o -Wl,--allow-multiple-definition -lkernel32 2> $W/link.log && break
  python -I build/difftest/asm_s5/stubgen.py $W/link.log $W/stubs.s
  /ucrt64/bin/gcc -m32 -c $W/stubs.s -o $W/stubs.o
done
test -f $OUT || { head -20 $W/link.log; exit 1; }
