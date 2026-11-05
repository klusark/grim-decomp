#!/bin/bash
# usage: build/difftest/asm_p1/build.sh <test.c> <out.exe>      (env: OPT=-O0, CFLAGS_MINE, OVERRIDES)
# Compiles build/overrides_asm_p1.c as the game build does (Makefile GHIDRA_CFLAGS, -m32 -march=i686, compat.h,
# src/GRIMFANDANGO.EXE headers), defines every game symbol it uses as an absolute symbol at its 1.01 address
# (gensyms.py), and links it with the test program and the runtime (rt.c maps the original image at 0x400000, so the
# original bytes run at their own address).  Copy of build/difftest/asm_s2/build.sh with its own output directory.
set -e
cd "$(dirname "$0")/../../.."
T=$1; OUT=$2; OPTL=${OPT:--O0}
W=build/difftest/asm_p1/out/$(basename $OUT .exe); mkdir -p $W
CF=${CFLAGS_MINE:-"$OPTL -m32 -march=i686 -std=gnu11 -fpermissive -w -fno-builtin -fno-strict-aliasing -fwrapv -fsingle-precision-constant -fno-common -ffreestanding -include build/compat.h -Isrc/GRIMFANDANGO.EXE -DGRIM_EXE"}
objs=""
for ov in ${OVERRIDES:-build/overrides_asm_p1.c}; do
  /ucrt64/bin/gcc $CF -c $ov -o $W/mine_$(basename $ov .c).o
  objs="$objs $W/mine_$(basename $ov .c).o"
done
export PATH=/mingw32/bin:$PATH
nm $objs | awk '$1=="U"{print $2} NF==3 && $2~/[TDBR]/{print "DEF " $3}' > $W/nm.txt
python -I build/difftest/asm_p1/undef.py $W/nm.txt $W/undef.txt
python -I build/difftest/asm_p1/gensyms.py $W/undef.txt $W/syms.s
gcc -m32 -c $W/syms.s -o $W/syms.o
gcc -O1 -w -c build/difftest/asm_p1/rt.c -o $W/rt.o
gcc -m32 -c build/difftest/asm_p1/gcall.s -o $W/gcall.o
gcc -m32 -c build/difftest/asm_p1/grim_img.s -o $W/grim_img.o
gcc -O1 -w -Ibuild/difftest/asm_p1 $TEST_CFLAGS -c $T -o $W/test.o
gcc -o $OUT $W/test.o $W/rt.o $W/gcall.o $objs $W/syms.o $W/grim_img.o -Wl,-T,build/difftest/asm_p1/img.ld -Wl,--image-base=0x400000 -Wl,--disable-dynamicbase
