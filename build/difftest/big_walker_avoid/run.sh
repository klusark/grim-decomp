#!/bin/bash
# usage: build/difftest/big_walker_avoid/run.sh [cases]
# Builds and runs the differential test twice: the port compiled with the Makefile's GHIDRA_CFLAGS and with the flags
# build/link.py uses for overrides_*.c.
cd "$(dirname "$0")/../../.." || exit 1
n=${1:-1000000}; rc=0
bash build/difftest/big_walker_avoid/build.sh >/dev/null && build/difftest/big_walker_avoid/out/wav_test.exe $n | grep -v "calls per case" || rc=1
LINKPY=1 bash build/difftest/big_walker_avoid/build.sh >/dev/null && build/difftest/big_walker_avoid/out/wav_test.exe $n | tail -1 || rc=1
exit $rc
