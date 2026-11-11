#!/bin/bash
# usage: build/difftest/big_walker_avoid/build.sh [extra C flags for the port]
# Builds wav_test.exe: the original Walker_AvoidActorPath (sliced from $BASE_ASM, default the current
# src/GRIMFANDANGO.EXE/asm_funcs.s, where it is still assembled; after a regeneration point BASE_ASM at an older copy),
# renamed orig_Walker_AvoidActorPath, the C of $OVERRIDES (default build/overrides_big_walker_avoid.c) compiled with the
# build's GHIDRA_CFLAGS (LINKPY=1: the flags of build/link.py), the original data image and the recorders of wav_test.c.  Same scheme as build/difftest/asm_s5/build.sh.
set -e
cd "$(dirname "$0")/../../.."
PROG=GRIMFANDANGO.EXE
BASE_ASM=${BASE_ASM:-src/$PROG/asm_funcs.s}
DATA_O=${DATA_O:-build/obj/$PROG/data_s.o}
OV=${OVERRIDES:-build/overrides_big_walker_avoid.c}
W=build/difftest/big_walker_avoid/out; mkdir -p $W; rm -f $W/*.o $W/wav_test.exe
python -I build/mixdiff/slice_orig.py $BASE_ASM $W/orig.s Walker_AvoidActorPath
/ucrt64/bin/gcc -m32 -c $W/orig.s -o $W/orig.o
CF="-O0 -m32 -march=i686 -std=gnu11 -fpermissive -w -fno-builtin -fno-strict-aliasing -fwrapv -fsingle-precision-constant -fno-common -ffreestanding -include build/compat.h -Ibuild -Isrc/$PROG -DGRIM_EXE"
if [ -n "$LINKPY" ]; then
  # the flags build/link.py really compiles overrides_*.c with (mingw32 gcc, -O0, no -fwrapv / -fno-strict-aliasing)
  PATH=/mingw32/bin:$PATH gcc -std=gnu11 -fpermissive -w -fno-builtin -ffreestanding -fno-common -include build/compat.h -Isrc/$PROG -DGRIM_EXE "$@" -c $OV -o $W/mine.o
else
  /ucrt64/bin/gcc $CF "$@" -c $OV -o $W/mine.o
fi
export PATH=/mingw32/bin:$PATH
gcc -O1 -w -Ibuild/mixdiff -c build/difftest/big_walker_avoid/wav_test.c -o $W/test.o
gcc -O2 -w -Ibuild/mixdiff -c build/mixdiff/fx.c -o $W/fx.o
: > $W/stubs.s
/ucrt64/bin/gcc -m32 -c $W/stubs.s -o $W/stubs.o
for i in 1 2 3 4 5; do
  gcc -o $W/wav_test.exe $W/test.o $W/fx.o $W/mine.o $W/orig.o $DATA_O $W/stubs.o -Wl,--allow-multiple-definition -lkernel32 2> $W/link.log && break
  python -I build/difftest/asm_s5/stubgen.py $W/link.log $W/stubs.s
  /ucrt64/bin/gcc -m32 -c $W/stubs.s -o $W/stubs.o
done
test -f $W/wav_test.exe || { head -20 $W/link.log; exit 1; }
if grep -E '^_(g_|DAT_|UINT_|PTR_|s_|_DAT|_g_)' $W/stubs.s | grep -v '\.globl'; then echo "data symbols were stubbed (stale data_s.o?)"; rm -f $W/wav_test.exe; exit 1; fi
# the recorders must be the ones the two versions call
for s in sputActor_GetOrientMatrix rdMatrix_TransformVector34 Vec3_Sub GetOuttaTheBox WalkPlane_PlaneAt TestCollision WalkPlane_PlaneClosest WalkPlane_SnapTo FindObjectCorners BuildPath Collision_PickDetour GetPath Collision_PointInBox; do
  grep -q "^_$s:" $W/stubs.s && { echo "recorder $s not linked"; rm -f $W/wav_test.exe; exit 1; }
done
true
