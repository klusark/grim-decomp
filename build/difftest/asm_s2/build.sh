#!/bin/bash
# usage: build/difftest/asm_s2/build.sh <test.c> <out.exe> [OPT=-O0]
# Compiles build/overrides_asm_o1.c (and build/overrides_asm_s2.c) as the game build does (Makefile GHIDRA_CFLAGS,
# -m32 -march=i686, compat.h, src/GRIMFANDANGO.EXE headers), defines every game symbol they use as an absolute symbol at its
# 1.01 address (gensyms.py), and links them with the test program and the runtime (rt.c: maps the original image at
# 0x400000).  The test exe is linked at image base 0x400000 with a section that covers the 1.01 range (img.ld, grim_img.s).
set -e
cd "$(dirname "$0")/../../.."
T=$1; OUT=$2; OPTL=${OPT:--O0}
W=build/difftest/asm_s2/out; mkdir -p $W
CF=${CFLAGS_MINE:-"$OPTL -m32 -march=i686 -std=gnu11 -fpermissive -w -fno-builtin -fno-strict-aliasing -fwrapv -fsingle-precision-constant -fno-common -ffreestanding -include build/compat.h -Isrc/GRIMFANDANGO.EXE -DGRIM_EXE"}
# CFLAGS_MINE: flags for the C under test instead (e.g. the exact link.py set: -m32 -std=gnu11 -fpermissive -w
#   -fno-builtin -ffreestanding -fno-common -include build/compat.h -Isrc/GRIMFANDANGO.EXE -DGRIM_EXE)
objs=""
for ov in ${OVERRIDES:-build/overrides_asm_o1.c build/overrides_asm_s2.c}; do
  /ucrt64/bin/gcc $CF -c $ov -o $W/mine_$(basename $ov .c).o
  objs="$objs $W/mine_$(basename $ov .c).o"
done
export PATH=/mingw32/bin:$PATH
nm $objs | awk '$1=="U"{print $2} NF==3 && $2~/[TDBR]/{print "DEF " $3}' > $W/nm.txt
python -I - $W/nm.txt $W/undef.txt <<'PY'
import sys
u=set(); d=set()
for l in open(sys.argv[1]):
    p=l.split()
    if p[0]=="DEF": d.add(p[1])
    else: u.add(p[0])
open(sys.argv[2],"w").write("\n".join(sorted(u-d))+"\n")
PY
python -I build/difftest/asm_s2/gensyms.py $W/undef.txt $W/syms.s
gcc -m32 -c $W/syms.s -o $W/syms.o
gcc -O1 -w -c build/difftest/asm_s2/rt.c -o $W/rt.o
gcc -m32 -c build/difftest/asm_s2/gcall.s -o $W/gcall.o
gcc -m32 -c build/difftest/asm_s2/grim_img.s -o $W/grim_img.o
gcc -O1 -w -Ibuild/difftest/asm_s2 -c $T -o $W/test.o
gcc -o $OUT $W/test.o $W/rt.o $W/gcall.o $objs $W/syms.o $W/grim_img.o -Wl,-T,build/difftest/asm_s2/img.ld -Wl,--image-base=0x400000 -Wl,--disable-dynamicbase
