#!/bin/bash
# usage: build/difftest/big_collision_others/build.sh [overrides.c]
# Builds coll_test.exe: the original machine code of Collision_TestActorAgainstOthers (sliced from $BASE_ASM, default the
# current src/GRIMFANDANGO.EXE/asm_funcs.s, where it is still assembled; renamed orig_...), the C of
# build/overrides_big_collision_others.c (or $1) with the build's GHIDRA_CFLAGS, the original data image and the test.
set -e
cd "$(dirname "$0")/../../.."
BASE_ASM=${BASE_ASM:-src/GRIMFANDANGO.EXE/asm_funcs.s}
DATA_O=${DATA_O:-build/obj/GRIMFANDANGO.EXE/data_s.o}
OV=${1:-build/overrides_big_collision_others.c}
D=build/difftest/big_collision_others; W=$D/out; mkdir -p $W; rm -f $W/*.o
python -I build/mixdiff/slice_orig.py $BASE_ASM $W/orig.s Collision_TestActorAgainstOthers
/ucrt64/bin/gcc -m32 -c $W/orig.s -o $W/orig.o
CF="-O0 -m32 -march=i686 -std=gnu11 -fpermissive -w -fno-builtin -fno-strict-aliasing -fwrapv -fsingle-precision-constant -fno-common -ffreestanding -include build/compat.h -Ibuild -Isrc/GRIMFANDANGO.EXE -DGRIM_EXE"
/ucrt64/bin/gcc $CF $EXTRA_CFLAGS -c $OV -o $W/mine.o
export PATH=/mingw32/bin:$PATH
gcc -O1 -w -c $D/coll_test.c -o $W/test.o
: > $W/stubs.s; /ucrt64/bin/gcc -m32 -c $W/stubs.s -o $W/stubs.o; rm -f $W/coll_test.exe
for i in 1 2 3 4 5; do   # int3 stubs for whatever the data image references (code addresses in tables)
  gcc -o $W/coll_test.exe $W/test.o $W/mine.o $W/orig.o $DATA_O $W/stubs.o -Wl,--allow-multiple-definition -lkernel32 2> $W/link.log && break
  python -I build/difftest/asm_s5/stubgen.py $W/link.log $W/stubs.s >/dev/null
  /ucrt64/bin/gcc -m32 -c $W/stubs.s -o $W/stubs.o
done
test -f $W/coll_test.exe || { head -20 $W/link.log; exit 1; }
# the callees must be the models of coll_test.c, never stubs
if grep -E '^_(Actor_|Vec3_|Collision_|Walker_|Sector_|g_|DAT_)' $W/stubs.s; then echo "callee or data stubbed"; rm -f $W/coll_test.exe; exit 1; fi
