#!/bin/bash
# Task 2 of agent q6: the span fillers of build/overrides_asm_o2.c (rdRaster_Span16_TexLitZw, _2 .. _8, _15 .. _22,
# _24 .. _30) against their original machine code, with the C compiled exactly as build/link.py compiles override files
# (so the file's own pragmas decide the optimisation level).  The test program is build/difftest/asm_s5/span_test.c
# (random spans, z-buffer, texture, palette, tables, control words, precision 24 / 53 / 64 bits; colour surface,
# z-buffer and the span state globals compared); the originals are sliced from the asm_funcs.s of 9a56b04^ (before
# round 4 converted them).
# usage: build/difftest/asm_q6/o2span.sh [cases (all functions together; default 23000000)] [overrides file]
# TIME=1: build o2span_time.c instead (cycles per call, original vs the C); OUTEXE=name: the exe name
set -e
cd "$(dirname "$0")/../../.."
N=${1:-23000000}
OV=${2:-build/overrides_asm_o2.c}
D=build/difftest/asm_q6; O=$D/out; W=$O/o2span; mkdir -p $W; rm -f $W/*.o
[ -s $O/base_o2span.s ] || git show 9a56b04^:src/GRIMFANDANGO.EXE/asm_funcs.s > $O/base_o2span.s
NAMES="rdRaster_Span16_TexLitZw"; for k in 2 3 4 5 6 7 8 15 16 17 18 19 20 21 22 24 25 26 27 28 29 30; do NAMES="$NAMES rdRaster_Span16_TexLitZw_$k"; done
python -I build/mixdiff/slice_orig.py $O/base_o2span.s $W/orig.s $NAMES >/dev/null
/ucrt64/bin/gcc -m32 -c $W/orig.s -o $W/orig.o
export PATH=/mingw32/bin:$PATH
gcc -std=gnu11 -fpermissive -w -fno-builtin -ffreestanding -fno-common -include build/compat.h -Isrc/GRIMFANDANGO.EXE \
    -DGRIM_EXE -c $OV -o $W/mine.o
if [ -n "$TIME" ]; then gcc -O2 -w -c $D/o2span_time.c -o $W/test.o; else gcc -O1 -w -Ibuild/mixdiff -c build/difftest/asm_s5/span_test.c -o $W/test.o; fi
gcc -O2 -w -Ibuild/mixdiff -c build/mixdiff/fx.c -o $W/fx.o
: > $W/stubs.s
OUT=$O/${OUTEXE:-o2span}.exe; rm -f $OUT
for i in 1 2 3 4 5 6; do
  /ucrt64/bin/gcc -m32 -c $W/stubs.s -o $W/stubs.o
  gcc -o $OUT $W/test.o $W/fx.o $W/mine.o $W/orig.o build/obj/GRIMFANDANGO.EXE/data_s.o $W/stubs.o \
      -Wl,--allow-multiple-definition -lkernel32 -lwinmm 2> $W/link.log && break
  python -I build/difftest/asm_s5/stubgen.py $W/link.log $W/stubs.s >/dev/null
done
test -f $OUT || { head -20 $W/link.log; exit 1; }
if grep -E "^\s*\.globl _(UINT_|DAT_|PTR_|g_)" $W/stubs.s; then echo "data symbols stubbed"; rm -f $OUT; exit 1; fi
[ -n "$BUILD_ONLY" ] && exit 0
$OUT $N
