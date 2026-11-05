#!/bin/bash
# Builds and runs the rasteriser differential tests in three compilations of the C under test: the Makefile flags at
# -O0 (default), the exact link.py flags (_lk) and -O2 (_o2).  Usage: build/difftest/asm_s2/run_all.sh [span] [edge] [draw]
cd "$(dirname "$0")/../../.."
D=build/difftest/asm_s2; O=$D/out
LF="-m32 -std=gnu11 -fpermissive -w -fno-builtin -ffreestanding -fno-common -include build/compat.h -Isrc/GRIMFANDANGO.EXE -DGRIM_EXE"
NS=${1:-2000}; NE=${2:-4000}; ND=${3:-400}
for t in span edge draw; do
  bash $D/build.sh $D/test_$t.c $O/test_$t.exe
  CFLAGS_MINE="$LF" bash $D/build.sh $D/test_$t.c $O/test_${t}_lk.exe
  OPT=-O2 bash $D/build.sh $D/test_$t.c $O/test_${t}_o2.exe
done
# full counts for the Makefile compilation, a quarter for the other two
echo "#### span"; $O/test_span.exe $NS
echo "#### edge"; $O/test_edge.exe $NE
echo "#### draw"; $O/test_draw.exe $ND
for v in _lk _o2; do
  echo "#### span$v"; $O/test_span$v.exe $((NS / 4))
  echo "#### edge$v"; $O/test_edge$v.exe $((NE / 4))
  echo "#### draw$v"; $O/test_draw$v.exe $((ND / 4))
done
