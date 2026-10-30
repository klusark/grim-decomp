#!/bin/bash
# lists the functions that are compiled from C (not assembled): csyms_<PROG>.txt, used by sampler.py
cd "$(dirname "$0")/.."
for p in GRIMFANDANGO.EXE LUA.DLL IMUSE.DLL CHORE.DLL; do
  ls obj/$p/*.o | grep -v "asm_funcs\|data\|stubs" | xargs nm --defined-only -g 2>/dev/null | awk '$2=="T"{print $3}' | sed 's/^_//' > perf/csyms_$p.txt
done
