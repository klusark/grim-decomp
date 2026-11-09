#!/bin/bash
# usage: build/difftest/asm_p1/mut.sh <mutations.txt> <test.c> [cases]
# Sensitivity check: builds the test once per mutation of build/overrides_asm_p1.c and runs it; every mutation
# should report differences.
cd "$(dirname "$0")/../../.."
D=build/difftest/asm_p1; O=$D/out; mkdir -p $O
n=$(python -I $D/mut.py $1 -1 x x)
for ((i = 0; i < n; i++)); do
  python -I $D/mut.py $1 $i build/overrides_asm_p1.c $O/mut.c || continue
  OVERRIDES=$O/mut.c bash $D/build.sh $2 $O/test_mut.exe > /dev/null && $O/test_mut.exe ${3:-2000} | tail -1
done
