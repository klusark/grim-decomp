#!/bin/bash
# usage: build/difftest/asm_q5/build.sh <test.c> <out.exe> <orig function names...>
# Differential test build for the rasteriser port (agent q5), modelled on build/difftest/asm_p2/build.sh:
#   - the original machine code of the named functions, sliced from $BASE_ASM (default: the asm_funcs.s of 2df265d,
#     where they are still assembled; run_all.sh makes out/base_asm_funcs.s) and renamed orig_<name>;
#   - build/overrides_asm_q5.c ($OVR) compiled exactly as build/link.py compiles override files (i686 gcc, no -O on the
#     command line, same flags; the file's own pragmas select -O2 / SSE4.1), plus $EXTRA_CFLAGS;
#   - the original data image (build/obj/GRIMFANDANGO.EXE/data_s.o) for the globals and tables;
#   - $EXTRA_OBJS (e.g. the compiled C span fillers of rdraster.o) and int3 stubs for anything else.
set -e
cd "$(dirname "$0")/../../.."
PROG=GRIMFANDANGO.EXE
D=build/difftest/asm_q5
BASE_ASM=${BASE_ASM:-$D/out/base_asm_funcs.s}
DATA_O=${DATA_O:-build/obj/$PROG/data_s.o}
[ -f "$DATA_O" ] || DATA_O=/c/Users/Joel/grim-decomp/build/obj/$PROG/data_s.o
T=$1; OUT=$2; shift 2
W=$D/out/$(basename $OUT .exe); mkdir -p $W; rm -f $W/*.o
if [ -n "$PEEP" ]; then   # the assembly as the game links it: build/peephole.py ($PEEPHOLE: another version) turns the fldcw floor / ceil sequences into SSE4.1
  python -I ${PEEPHOLE:-build/peephole.py} $BASE_ASM $W/base_peep.s >/dev/null; BASE_ASM=$W/base_peep.s
fi
python -I build/mixdiff/slice_orig.py $BASE_ASM $W/orig.s "$@" >/dev/null
/ucrt64/bin/gcc -m32 -c $W/orig.s -o $W/orig.o
export PATH=/mingw32/bin:$PATH
gcc -std=gnu11 -fpermissive -w -fno-builtin -ffreestanding -fno-common -include build/compat.h -Isrc/$PROG -DGRIM_EXE \
    $EXTRA_CFLAGS -c ${OVR:-build/overrides_asm_q5.c} -o $W/mine.o
gcc -O2 -w -msse4.1 -c $T -o $W/test.o
: > $W/stubs.s
rm -f $OUT
for i in 1 2 3 4 5 6; do
  /ucrt64/bin/gcc -m32 -c $W/stubs.s -o $W/stubs.o
  gcc -o $OUT $W/test.o $W/mine.o $W/orig.o $EXTRA_OBJS $DATA_O $W/stubs.o -Wl,--allow-multiple-definition 2> $W/link.log && break
  python -I build/difftest/asm_s5/stubgen.py $W/link.log $W/stubs.s >/dev/null
done
test -f $OUT || { head -20 $W/link.log; exit 1; }
