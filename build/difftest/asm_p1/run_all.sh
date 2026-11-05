#!/bin/bash
# Builds and runs every differential test of build/overrides_asm_p1.c against the original 1.01 machine code (mapped at its
# own address from raw/GRIMFANDANGO.EXE/sections, rt.c), in three compilations of the C under test: the Makefile
# GHIDRA_CFLAGS at -O0 (full case counts), the exact link.py flags (_lk) and -O2 (_o2) (a quarter of the cases each).
# usage: build/difftest/asm_p1/run_all.sh [scale]   (scale divides the case counts, default 1)
cd "$(dirname "$0")/../../.."
D=build/difftest/asm_p1; O=$D/out; mkdir -p $O
S=${1:-1}
LF="-m32 -std=gnu11 -fpermissive -w -fno-builtin -ffreestanding -fno-common -include build/compat.h -Isrc/GRIMFANDANGO.EXE -DGRIM_EXE"
# test  cases
T="drv:3000 prim:20000 mesh:20000 canvas:20000 light:20000 lbin:5000 prep:20000"
for tc in $T; do
  t=${tc%%:*}
  bash $D/build.sh $D/test_$t.c $O/test_$t.exe || exit 1
  CFLAGS_MINE="$LF" bash $D/build.sh $D/test_$t.c $O/test_${t}_lk.exe || exit 1
  OPT=-O2 bash $D/build.sh $D/test_$t.c $O/test_${t}_o2.exe || exit 1
done
for tc in $T; do
  t=${tc%%:*}; n=$(( ${tc##*:} / S ))
  echo "#### $t (-O0, $n cases)"; $O/test_$t.exe $n
  echo "#### ${t}_lk ($((n / 4)) cases)"; $O/test_${t}_lk.exe $((n / 4))
  echo "#### ${t}_o2 ($((n / 4)) cases)"; $O/test_${t}_o2.exe $((n / 4))
done
