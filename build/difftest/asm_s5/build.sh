#!/bin/bash
# usage: build/difftest/asm_s5/build.sh <test.c> <out.exe> <orig function names...>
# Differential test build (copy of build/mixdiff/build.sh with its own output directory): the original machine code of the
# named functions, sliced from $BASE_ASM (default: the current src/<PROG>/asm_funcs.s, where they are still assembled) and
# renamed orig_<name>; the C of $OVERRIDES compiled with the build's GHIDRA_CFLAGS; the original data image ($DATA_O);
# $EXTRA_OBJ (compiled modules of the current build that provide callees); int3 stubs for anything else.
set -e
cd "$(dirname "$0")/../../.."
PROG=${PROG:-GRIMFANDANGO.EXE}
DEF=${DEF:-GRIM_EXE}
BASE_ASM=${BASE_ASM:-src/$PROG/asm_funcs.s}
DATA_O=${DATA_O:-build/obj/$PROG/data_s.o}
T=$1; OUT=$2; shift 2
W=build/difftest/asm_s5/out/$(basename $OUT .exe); mkdir -p $W; rm -f $W/*.o
python -I build/mixdiff/slice_orig.py $BASE_ASM $W/orig.s "$@"
[ -n "$ORIG_SED" ] && sed -i -E "$ORIG_SED" $W/orig.s
/ucrt64/bin/gcc -m32 -c $W/orig.s -o $W/orig.o
CF="-O0 -m32 -march=i686 -std=gnu11 -fpermissive -w -fno-builtin -fno-strict-aliasing -fwrapv -fsingle-precision-constant -fno-common -ffreestanding -include build/compat.h -Ibuild -Isrc/$PROG -D$DEF"
for ov in ${OVERRIDES:-build/overrides_asm_o2.c}; do
  /ucrt64/bin/gcc $CF $EXTRA_CFLAGS -c $ov -o $W/mine_$(basename $ov .c).o
done
export PATH=/mingw32/bin:$PATH
gcc -O1 -w $TEST_CFLAGS -Ibuild/mixdiff -c $T -o $W/test.o
gcc -O2 -w -Ibuild/mixdiff -c build/mixdiff/fx.c -o $W/fx.o
: > $W/stubs.s
/ucrt64/bin/gcc -m32 -c $W/stubs.s -o $W/stubs.o
for i in 1 2 3 4 5; do
  gcc -o $OUT $W/test.o $W/fx.o $W/mine_*.o $W/orig.o $EXTRA_OBJ $DATA_O $W/stubs.o -Wl,--allow-multiple-definition -lkernel32 -lwinmm 2> $W/link.log && break
  python -I build/difftest/asm_s5/stubgen.py $W/link.log $W/stubs.s
  /ucrt64/bin/gcc -m32 -c $W/stubs.s -o $W/stubs.o
done
test -f $OUT || { head -20 $W/link.log; exit 1; }
if grep -E '^_(g_|DAT_|UINT_|PTR_|s_|_DAT|_g_)' $W/stubs.s | grep -v '\.globl'; then echo "data symbols were stubbed (stale data_s.o?)"; rm -f $OUT; exit 1; fi
