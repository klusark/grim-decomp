#!/bin/bash
# usage: build/difftest/s2/build.sh [out.exe]     (then: out.exe [cases] [seed])
# Differential test of the iMUSE fade engine (agent s2, fade_test.c): Im_FadeParamImpl / Im_FadesClearSound /
# Im_FadesHeartbeat as compiled into the rebuilt imuse.dll (build/obj/IMUSE.DLL/imuse.o; OBJ=<file> for another object)
# against the original machine code, sliced from the all-assembly IMUSE.DLL of commit 68b8b5b^ with
# build/mixdiff/slice_orig.py (orig_<name>).  Links the original data image (build/obj/IMUSE.DLL/data_s.o); int3 stubs
# for everything else imuse.o references.
set -e
cd "$(dirname "$0")/../../.."
PROG=IMUSE.DLL
D=build/difftest/s2/out
OUT=${1:-$D/fade_test.exe}
W=$D/$(basename $OUT .exe); mkdir -p $W; rm -f $W/*.o
[ -f $D/allasm_funcs.s ] || git show 68b8b5b^:src/IMUSE.DLL/asm_funcs.s > $D/allasm_funcs.s
python -I build/mixdiff/slice_orig.py $D/allasm_funcs.s $W/orig.s Im_FadeParamImpl Im_FadesClearSound Im_FadesHeartbeat
if [ -n "$MUTSED" ]; then   # a mutant of the original slice (mutate.sh)
  cp $W/orig.s $W/orig0.s; sed -i -E "$MUTSED" $W/orig.s
  if cmp -s $W/orig0.s $W/orig.s; then echo "mutation $MUTSED matched nothing"; exit 2; fi
fi
/ucrt64/bin/gcc -m32 -c $W/orig.s -o $W/orig.o
export PATH=/mingw32/bin:$PATH
gcc -O1 -w -c build/difftest/s2/fade_test.c -o $W/test.o
: > $W/stubs.s
/ucrt64/bin/gcc -m32 -c $W/stubs.s -o $W/stubs.o
rm -f $OUT
for i in 1 2 3 4 5 6; do
  gcc -o $OUT $W/test.o ${OBJ:-build/obj/$PROG/imuse.o} $W/orig.o build/obj/$PROG/data_s.o $W/stubs.o -Wl,--allow-multiple-definition 2> $W/link.log && break
  python -I build/difftest/asm_s5/stubgen.py $W/link.log $W/stubs.s
  /ucrt64/bin/gcc -m32 -c $W/stubs.s -o $W/stubs.o
done
test -f $OUT || { head -20 $W/link.log; exit 1; }
echo "built $OUT"
