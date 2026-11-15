#!/bin/bash
# usage: build/mixdiff/twin.sh <test.c> <out.exe> <orig function names...>
# Differential test of GENERATED code against the original machine code: the test (one of build/mixdiff/*_test.c or
# build/difftest/*), build/mixdiff/fx.c, the generated twins of hand-written functions (src/<prog>/<module>.c with their
# `#if 0` blocks switched on by twinsrc.py), the original machine code of the named functions (orig_<name>, sliced from
# $BASE_ASM), then every object of the current build (make -C build link): with --allow-multiple-definition the first
# definition wins, so the twins replace the hand-written versions and everything else is today's code.
#   MODULE="video videobitmap"   modules whose twins are switched on
#   TWINS="name ..."             only these twins (default: every twin of the modules)
#   PROG                         default GRIMFANDANGO.EXE
#   BASE_ASM                     baseline assembly (default: src/<prog>/asm_funcs.s of 223e097, written to build/mixdiff/out)
#   TWIN_SED / ORIG_SED          sed expressions applied to the twin sources / the sliced original (sanity checks)
# Run the result with the DLL directories on PATH: PATH=build/obj/LUA.DLL:build/obj/IMUSE.DLL:build/obj/CHORE.DLL:$PATH
set -e
cd "$(dirname "$0")/../.."
P=${PROG:-GRIMFANDANGO.EXE}; O=build/obj/$P; W=build/mixdiff/out/twin_$(basename $2 .exe); mkdir -p $W; rm -f $W/*.o
T=$1; OUT=$2; shift 2
if [ -z "$BASE_ASM" ]; then
  BASE_ASM=build/mixdiff/out/asm_funcs_223e097.s
  [ -s $BASE_ASM ] || git show 223e097:src/$P/asm_funcs.s > $BASE_ASM
fi
python -I build/mixdiff/slice_orig.py $BASE_ASM $W/orig.s "$@" >/dev/null
[ -n "$ORIG_SED" ] && sed -i -E "$ORIG_SED" $W/orig.s
/ucrt64/bin/gcc -m32 -c $W/orig.s -o $W/orig.o
EXCL="cleanroom_[a-z0-9_]*|cov_export"
for M in $MODULE; do
  python -I build/mixdiff/twinsrc.py src/$P/$M.c $W/twin_$M.c $TWINS
  [ -n "$TWIN_SED" ] && sed -i -E "$TWIN_SED" $W/twin_$M.c
  FL=$(sed "s|-include compat.h -I\.|-include build/compat.h -Ibuild|" $O/$M.flags)
  gcc $FL -Isrc/$P $EXTRA_CFLAGS -c $W/twin_$M.c -o $W/twin_$M.o
  EXCL="$EXCL|$M"
done
export PATH=/mingw32/bin:$PATH
gcc -O2 -w $TEST_CFLAGS -Ibuild/mixdiff -c $T -o $W/test.o
gcc -O2 -w -Ibuild/mixdiff -c build/mixdiff/fx.c -o $W/fx.o
REST=$(ls $O/*.o | grep -vE "/($EXCL)\.o$")
if [ "$P" = GRIMFANDANGO.EXE ]; then
  LIBS="$O/../LUA.DLL/liblua.a $O/../IMUSE.DLL/libimuse.a $O/../CHORE.DLL/libchore.a -lmingwex -lgcc -Wl,-Bstatic -lz -Wl,-Bdynamic"
else
  LIBS="-lmingwex -lgcc"
fi
LIBS="$LIBS -lkernel32 -luser32 -lgdi32 -lwinmm -lddraw -ldinput -ldsound -ladvapi32 -lcomdlg32 -lole32 -lshell32 -lcomctl32"
: > $W/stubs.s
for i in 1 2 3 4; do
  /ucrt64/bin/gcc -m32 -c $W/stubs.s -o $W/stubs.o
  gcc -o $OUT $W/test.o $W/fx.o $(ls $W/twin_*.o 2>/dev/null) $W/orig.o $REST $W/stubs.o -Wl,--allow-multiple-definition \
      -Wl,--enable-stdcall-fixup -Wl,--disable-dynamicbase $LIBS 2> $W/link.log && break
  python -I build/mixdiff/stubgen.py $W/link.log $W/stubs.s >/dev/null
done
test -f $OUT || { grep -v warning $W/link.log | head -20; exit 1; }
echo "built $OUT ($(grep -c globl $W/stubs.s) stubs)"
