#!/bin/bash
# usage: build/difftest/s1/build.sh [out.exe]     (then: out.exe [cases] [seed])
# Differential test of build/overrides_s1_chore.c (FUN_10004e50, FUN_10005090) against the original machine code, sliced
# from CHORE.DLL of the install (GRIM_INSTALL, default C:\GOG Games\GRIMDATA) by slice.py.  The C is compiled with the
# flags build/link.py uses for override files (EXTRA_CFLAGS=-O2 for an optimised variant, OVR=<file> for a mutant).
set -e
cd "$(dirname "$0")/../../.."
OUT=${1:-build/difftest/s1/out/s1_test.exe}
W=build/difftest/s1/out; mkdir -p $W
python -I build/difftest/s1/slice.py "${GRIM_INSTALL:-C:/GOG Games/GRIMDATA}/CHORE.DLL" $W/orig.s
export PATH=/mingw32/bin:$PATH
gcc -c $W/orig.s -o $W/orig.o
gcc -std=gnu11 -fpermissive -w -fno-builtin -ffreestanding -fno-common -include build/compat.h -Isrc/CHORE.DLL -DGRIM_CHORE \
    $EXTRA_CFLAGS -c ${OVR:-build/overrides_s1_chore.c} -o $W/mine.o
gcc -O1 -w -c build/difftest/s1/s1_test.c -o $W/test.o
gcc -o $OUT $W/test.o $W/mine.o $W/orig.o
