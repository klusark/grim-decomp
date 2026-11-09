#!/bin/bash
# The full differential test: every function of q5_funcs.h with N cases (default 1000000), P processes in parallel
# (default 8), against the original assembly (and, with PEEP=1, against the assembly after build/peephole.py, as the
# game links it).  One line per function; the totals at the end.
# usage: build/difftest/asm_q5/run_par.sh [cases] [processes]
cd "$(dirname "$0")/../../.." || exit 1
N=${1:-1000000}; P=${2:-8}
D=build/difftest/asm_q5; O=$D/out
EXE=${OUTEXE:-raster_test}
BUILD_ONLY=1 bash $D/run_all.sh || exit 1
mkdir -p $O/par_$EXE; rm -f $O/par_$EXE/*.txt
sed -n 's/^FN([A-Z_]*, *\([A-Za-z0-9_]*\)).*/\1/p' $D/q5_funcs.h |
  xargs -P $P -I{} sh -c "$O/$EXE.exe $N ={} > $O/par_$EXE/{}.txt 2>&1 || echo 'FAILED (exit '\$?')' >> $O/par_$EXE/{}.txt"
cat $O/par_$EXE/*.txt | grep -v "^[0-9]* cases" | sort
grep -h "cases, " $O/par_$EXE/*.txt | awk '{c += $1; d += $3} END {print c " cases, " d " differences"}'
grep -l "FAILED\|DIFF" $O/par_$EXE/*.txt && exit 1
exit 0
