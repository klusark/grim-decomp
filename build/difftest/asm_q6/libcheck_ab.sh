#!/bin/bash
# build/perf/libcheck.py on two exe directories (agent q6, task 2): A then B, then the shot / probe diff.
# usage: build/difftest/asm_q6/libcheck_ab.sh <dir A> <dir B> <mod data dir> <out dir> [sets]
cd "$(dirname "$0")/../../.."
A=$1; B=$2; DATA=$3; OUT=$4; SETS=${5:-8}
~/venv/bin/python.exe -I build/perf/libcheck.py "$(cygpath -w "$A")" q6A --data "$(cygpath -w "$DATA")" --out "$(cygpath -w "$OUT")" --sets $SETS
~/venv/bin/python.exe -I build/perf/libcheck.py "$(cygpath -w "$B")" q6B --data "$(cygpath -w "$DATA")" --out "$(cygpath -w "$OUT")" --sets $SETS
~/venv/bin/python.exe -I build/perf/libcheck.py --diff "$(cygpath -w "$OUT/q6A")" "$(cygpath -w "$OUT/q6B")"
