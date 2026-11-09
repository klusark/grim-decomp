#!/bin/bash
# usage: build/difftest/r2/build.sh [ftol cases] [chkstk cases] [chkstk traced cases] [chkstk thread sizes]
# Differential tests of round r2 (docs/notes/r2.md):
#   ftol_test   the original _ftol (sliced from the asm_funcs.s of $BASE_REV, default 85dd22f, renamed orig__ftol)
#               against msvcrt.dll's _ftol through libmsvcrt.a (`__ftol`), which is what the rebuilt exe's symbol is now
#   chkstk_test the original __chkstk FUN_004addf0 against _FUN_004addf0 of build/overrides_r2.c compiled the way
#               build/link.py compiles overrides (a jump to libgcc's ___chkstk)
# BASE_ASM=<file> slices another copy; MUT=1 compares the original with itself; NORUN=1 only builds.
set -e
cd "$(dirname "$0")/../../.."
D=build/difftest/r2; W=$D/out; mkdir -p $W; rm -f $W/*.o
if [ -z "$BASE_ASM" ]; then BASE_ASM=$W/base_asm_funcs.s; git show ${BASE_REV:-85dd22f}:src/GRIMFANDANGO.EXE/asm_funcs.s > $BASE_ASM; fi
python -I build/mixdiff/slice_orig.py $BASE_ASM $W/orig.s _ftol FUN_004addf0 >/dev/null
[ -n "$ORIG_SED" ] && sed -i -e "$ORIG_SED" $W/orig.s     # mutation checks (mutate.sh)
export PATH=/mingw32/bin:$PATH
gcc -m32 -c $W/orig.s -o $W/orig.o
gcc -c $D/harness.S -o $W/harness.o
gcc -std=gnu11 -fpermissive -w -fno-builtin -ffreestanding -fno-common -include build/compat.h -Isrc/GRIMFANDANGO.EXE \
    -DGRIM_EXE -c build/overrides_r2.c -o $W/mine.o
gcc -O1 -w -c $D/ftol_test.c -o $W/ftol_test.o
gcc -O1 -w -c $D/chkstk_test.c -o $W/chkstk_test.o
gcc -o $W/ftol_test.exe $W/ftol_test.o $W/harness.o $W/orig.o
gcc -o $W/chkstk_test.exe $W/chkstk_test.o $W/harness.o $W/orig.o $W/mine.o
[ -n "$NORUN" ] && exit 0
rc=0
$W/ftol_test.exe ${1:-1000000} || rc=1
$W/chkstk_test.exe ${2:-1000000} ${3:-20000} ${4:-300} || rc=1
exit $rc
