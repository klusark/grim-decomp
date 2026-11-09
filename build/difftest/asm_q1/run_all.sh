#!/bin/bash
# usage: build/difftest/asm_q1/run_all.sh [cases per function]
# All runs of the asm_q1 differential test (see q1_test.c and docs/notes/asm_q1.md): the C compiled the way build/link.py
# compiles override files (LINKPY=1), with the Makefile flags at -O0 and at -O2, and the link.py build again with every
# signalling NaN input made quiet (Q1_NAN=1; must show 0 NaN-payload-only cases).
set -e
cd "$(dirname "$0")/../../.."
D=build/difftest/asm_q1
N=${1:-1000000}
mkdir -p $D/out
[ -f $D/out/base_asm_funcs.s ] || git show 2df265d:src/GRIMFANDANGO.EXE/asm_funcs.s > $D/out/base_asm_funcs.s
LINKPY=1 bash $D/build.sh $D/out/q1_linkpy.exe
bash $D/build.sh $D/out/q1_o0.exe
EXTRA_CFLAGS=-O2 bash $D/build.sh $D/out/q1_o2.exe
rc=0
echo "== link.py flags"; $D/out/q1_linkpy.exe $N || rc=1
echo "== link.py flags, quiet NaNs only"; Q1_NAN=1 $D/out/q1_linkpy.exe $N || rc=1
echo "== Makefile flags -O0"; $D/out/q1_o0.exe $N || rc=1
echo "== Makefile flags -O2"; $D/out/q1_o2.exe $((N / 4)) || rc=1
exit $rc
