#!/bin/bash
# Builds and runs the differential tests of build/overrides_asm_q3.c against the original machine code.
# The original is sliced from the assembly of commit 2df265d (before these functions were converted); the data image is
# build/obj/GRIMFANDANGO.EXE/data_s.o of a linked build of the tree (make -C build link).
# model_test needs the text .3do files of the game data in build/difftest/asm_q3/out/3do (made here from the LABs in
# $GRIMDATA, default C:/GOG Games/GRIMDATA, with tools/lab.py's reader).
# usage: build/difftest/asm_q3/run_all.sh [cases per function] [model cases]   (default 1000000 and 1000000; also the C
# at -O2, with the build/link.py flags, and the mutation check)
cd "$(dirname "$0")/../../.." || exit 1
N=${1:-1000000}
NM=${2:-1000000}
O=build/difftest/asm_q3/out; mkdir -p $O/3do
[ -s $O/base_asm_funcs.s ] || git show 2df265d:src/GRIMFANDANGO.EXE/asm_funcs.s > $O/base_asm_funcs.s
if ! ls $O/3do/*.3do >/dev/null 2>&1; then
  python -I - "${GRIMDATA:-C:/GOG Games/GRIMDATA}" $O/3do <<'EOF'
import glob, os, sys
exec(open("tools/lab.py").read().split("if __name__")[0])
for lab in sorted(glob.glob(os.path.join(sys.argv[1], "*.LAB"))):
    d, ents = read_lab(lab)
    for name, off, size in ents:
        if name.lower().endswith(".3do") and d[off:off + 4] != b"LDOM":
            open(os.path.join(sys.argv[2], name), "wb").write(d[off:off + size])
EOF
fi
P="rdPuppet_AdvanceTrack rdPuppet_UpdateFrame"
M="rdModel3_LoadText FUN_004addf0"
C="rdCache_SendFaceListToHardware _ftol"
rc=0
B=build/difftest/asm_q3/build.sh
bash $B build/difftest/asm_q3/puppet_test.c $O/puppet_test.exe $P >/dev/null || exit 1
bash $B build/difftest/asm_q3/model_test.c $O/model_test.exe $M >/dev/null || exit 1
bash $B build/difftest/asm_q3/cache_test.c $O/cache_test.exe $C >/dev/null || exit 1
echo "== C at -O0 (the build's default)"
$O/puppet_test.exe $N || rc=1
P3_NAN=1 $O/puppet_test.exe $((N / 4)) || rc=1
$O/model_test.exe $NM $O/3do || rc=1
$O/cache_test.exe $N || rc=1
P3_NAN=1 $O/cache_test.exe $((N / 4)) || rc=1
LINKPY=1 bash $B build/difftest/asm_q3/puppet_test.c $O/puppet_test_link.exe $P >/dev/null || exit 1
LINKPY=1 bash $B build/difftest/asm_q3/model_test.c $O/model_test_link.exe $M >/dev/null || exit 1
LINKPY=1 bash $B build/difftest/asm_q3/cache_test.c $O/cache_test_link.exe $C >/dev/null || exit 1
echo "== C with the build/link.py flags (the object that is linked into the game)"
$O/puppet_test_link.exe $N || rc=1
$O/model_test_link.exe $NM $O/3do || rc=1
$O/cache_test_link.exe $N || rc=1
EXTRA_CFLAGS=-O2 bash $B build/difftest/asm_q3/puppet_test.c $O/puppet_test_O2.exe $P >/dev/null || exit 1
EXTRA_CFLAGS=-O2 bash $B build/difftest/asm_q3/model_test.c $O/model_test_O2.exe $M >/dev/null || exit 1
EXTRA_CFLAGS=-O2 bash $B build/difftest/asm_q3/cache_test.c $O/cache_test_O2.exe $C >/dev/null || exit 1
echo "== C at -O2"
$O/puppet_test_O2.exe $((N / 4)) || rc=1
$O/model_test_O2.exe $((NM / 4)) $O/3do || rc=1
$O/cache_test_O2.exe $((N / 4)) || rc=1
echo "== mutations"
python -I build/difftest/asm_q3/mutate.py 20000 puppet | tail -1 || rc=1
python -I build/difftest/asm_q3/mutate.py 5000 model | tail -1 || rc=1
python -I build/difftest/asm_q3/mutate.py 20000 cache | tail -1 || rc=1
exit $rc
