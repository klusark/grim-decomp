#!/bin/bash
# A/B frame times for task 2 (agent q6): bench_q6.py on two exe directories, interleaved, N rounds (default 2).
# usage: build/difftest/asm_q6/bench_ab.sh <dir A> <dir B> [rounds] [dwell s]
cd "$(dirname "$0")"
A=$1; B=$2; N=${3:-2}; DW=${4:-4}
for i in $(seq 1 $N); do
  echo "== A $A (round $i)"; ~/venv/bin/python.exe -I bench_q6.py "$(cygpath -w "$A")" $DW
  echo "== B $B (round $i)"; ~/venv/bin/python.exe -I bench_q6.py "$(cygpath -w "$B")" $DW
done
