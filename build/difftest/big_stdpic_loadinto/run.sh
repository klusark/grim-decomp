#!/bin/bash
# usage: build/difftest/big_stdpic_loadinto/run.sh [cases]
# Builds and runs the differential test of stdPic_LoadEntry: the original machine code (sliced with its _ftol from $BASE_ASM,
# default the current src/GRIMFANDANGO.EXE/asm_funcs.s, where the function is still assembled; after a regeneration use
# BASE_ASM=<copy of an older asm_funcs.s>) next to build/overrides_big_stdpic_loadinto.c compiled with the build's flags,
# linked with the original data image build/obj/GRIMFANDANGO.EXE/data_s.o.  OVERRIDE=<file> tests another C version.
set -e
cd "$(dirname "$0")/../../.."
BASE_ASM=${BASE_ASM:-src/GRIMFANDANGO.EXE/asm_funcs.s}
OVERRIDE=${OVERRIDE:-build/overrides_big_stdpic_loadinto.c}
D=build/difftest/big_stdpic_loadinto; W=$D/out; mkdir -p $W
python -I build/mixdiff/slice_orig.py $BASE_ASM $W/orig.s stdPic_LoadEntry _ftol >/dev/null
/ucrt64/bin/gcc -m32 -c $W/orig.s -o $W/orig.o
CF="-O0 -m32 -march=i686 -std=gnu11 -fpermissive -w -fno-builtin -fno-strict-aliasing -fwrapv -fsingle-precision-constant -fno-common -ffreestanding -include build/compat.h -Ibuild -Isrc/GRIMFANDANGO.EXE -DGRIM_EXE"
/ucrt64/bin/gcc $CF $EXTRA_CFLAGS -c $OVERRIDE -o $W/mine.o
export PATH=/mingw32/bin:$PATH
gcc -O1 -w -fno-builtin -c $D/pic_test.c -o $W/test.o
rm -f $W/pic_test.exe; : > $W/stubs.s
for i in 1 2 3 4 5; do
  /ucrt64/bin/gcc -m32 -c $W/stubs.s -o $W/stubs.o
  gcc -o $W/pic_test.exe $W/test.o $W/mine.o $W/orig.o build/obj/GRIMFANDANGO.EXE/data_s.o $W/stubs.o -Wl,--allow-multiple-definition 2> $W/link.log && break
  python -I build/difftest/asm_s5/stubgen.py $W/link.log $W/stubs.s >/dev/null
done
test -f $W/pic_test.exe || { head -20 $W/link.log; exit 1; }
$W/pic_test.exe ${1:-20000}
