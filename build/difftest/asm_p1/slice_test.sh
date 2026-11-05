#!/bin/bash
# usage: build/difftest/asm_p1/slice_test.sh <asm_funcs(.s|_fast.s)> <test.c> <out.exe> <function>...
# Builds <test.c> with -DSLICE: the named function of the given reassembled asm (as the game build links it) runs as
# "mine" next to the 1.01 bytes.  _sect_data and the callees the slice names are absolute symbols at 1.01 addresses.
set -e
cd "$(dirname "$0")/../../.."
W=build/difftest/asm_p1/out/slice; mkdir -p $W
A=$1; T=$2; OUT=$3; shift 3
python -I build/mixdiff/slice_orig.py $A $W/slice.s "$@"
grep -o -E "\b_[A-Za-z][A-Za-z0-9_@]*" $W/slice.s | sort -u | grep -v -E "^_(orig_|mnemonic|syntax)" > $W/undef.txt || true
python -I build/difftest/asm_p1/gensyms.py $W/undef.txt $W/syms.s
printf '\t.globl _sect_data\n\t.set _sect_data, 0x4dd000\n\t.globl _sect_rdata\n\t.set _sect_rdata, 0x4d7000\n\t.globl _sect_text\n\t.set _sect_text, 0x401000\n' >> $W/syms.s
export PATH=/mingw32/bin:$PATH
gcc -m32 -c $W/slice.s -o $W/slice.o
gcc -m32 -c $W/syms.s -o $W/syms.o
gcc -O1 -w -c build/difftest/asm_p1/rt.c -o $W/rt.o
gcc -m32 -c build/difftest/asm_p1/gcall.s -o $W/gcall.o
gcc -m32 -c build/difftest/asm_p1/grim_img.s -o $W/grim_img.o
gcc -O1 -w -DSLICE -Ibuild/difftest/asm_p1 -c $T -o $W/test.o
gcc -o $OUT $W/test.o $W/rt.o $W/gcall.o $W/slice.o $W/syms.o $W/grim_img.o -Wl,-T,build/difftest/asm_p1/img.ld -Wl,--image-base=0x400000 -Wl,--disable-dynamicbase
