#!/bin/bash
# usage: build/difftest/big_engine_renderframe/run.sh [cases]
# Differential test of Engine_RenderFrame (build/overrides_big_engine_renderframe.c) against the original 1.01 code.
# The original is sliced from $BASE_ASM (default src/GRIMFANDANGO.EXE/asm_funcs.s, where the function is still assembled;
# after the port is applied by the build, point BASE_ASM at an older copy), corrected with fix_orig.sed (the export
# mis-decoded 0x0048483d), and its instruction sequence is checked against the real bytes (orig_bytes.hex, read from the
# Ghidra program /v101/GRIMFANDANGO.EXE) by check_slice.py before the test is built.
# Same tool chain as build/difftest/asm_s5/build.sh; outputs in build/difftest/big_engine_renderframe/out/.
set -e
cd "$(dirname "$0")/../../.."
T=build/difftest/big_engine_renderframe; W=$T/out; mkdir -p $W; rm -f $W/*.o
BASE_ASM=${BASE_ASM:-src/GRIMFANDANGO.EXE/asm_funcs.s}
DATA_O=${DATA_O:-build/obj/GRIMFANDANGO.EXE/data_s.o}
python -I build/mixdiff/slice_orig.py $BASE_ASM $W/orig_raw.s Engine_RenderFrame >/dev/null
sed -E -f $T/fix_orig.sed $W/orig_raw.s > $W/orig.s
/ucrt64/bin/gcc -m32 -c $W/orig.s -o $W/orig.o
python3 -c "import binascii,sys; open(sys.argv[2],'wb').write(binascii.unhexlify(open(sys.argv[1]).read().strip()))" $T/orig_bytes.hex $W/orig.bin
python3 $T/check_slice.py $W/orig.bin $W/orig.o | tee $W/check_slice.txt
grep -q '^same instruction sequence' $W/check_slice.txt || { echo "slice differs from the 1.01 bytes"; exit 1; }
CF="-O0 -m32 -march=i686 -std=gnu11 -fpermissive -w -fno-builtin -fno-strict-aliasing -fwrapv -fsingle-precision-constant -fno-common -ffreestanding -include build/compat.h -Ibuild -Isrc/GRIMFANDANGO.EXE -DGRIM_EXE"
/ucrt64/bin/gcc $CF $EXTRA_CFLAGS -c ${OVERRIDE:-build/overrides_big_engine_renderframe.c} -o $W/mine.o
export PATH=/mingw32/bin:$PATH
gcc -O1 -w -Ibuild/mixdiff -c $T/renderframe_test.c -o $W/test.o
gcc -O2 -w -Ibuild/mixdiff -c build/mixdiff/fx.c -o $W/fx.o
: > $W/stubs.s
/ucrt64/bin/gcc -m32 -c $W/stubs.s -o $W/stubs.o
for i in 1 2 3; do
  gcc -o $W/renderframe_test.exe $W/test.o $W/fx.o $W/mine.o $W/orig.o $DATA_O $W/stubs.o -Wl,--allow-multiple-definition -lkernel32 2> $W/link.log && break
  python -I build/difftest/asm_s5/stubgen.py $W/link.log $W/stubs.s
  /ucrt64/bin/gcc -m32 -c $W/stubs.s -o $W/stubs.o
done
test -f $W/renderframe_test.exe || { head -20 $W/link.log; exit 1; }
# the data image references many functions (stubbed); none of the callees of Engine_RenderFrame may be a stub
for c in $(grep -oE 'call _[A-Za-z_0-9]+' $W/orig.s | cut -c7- | sort -u) _ObjectState_Draw _lua_printstack; do
  if grep -q "^$c:" $W/stubs.s; then echo "callee $c was stubbed"; exit 1; fi
done
$W/renderframe_test.exe ${1:-200000}
