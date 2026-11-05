#!/bin/bash
# usage: build/difftest/asm_p1/variant.sh <outdir> <name>...
# Links the game with build/overrides_asm_p1.c minus the named functions (each renamed p1_off_<name>, so the
# assembled original is linked instead) and copies the four binaries to <outdir>.  The override file is restored.
set -e
cd "$(dirname "$0")/../../.."
OUT=$1; shift
cp build/overrides_asm_p1.c build/difftest/asm_p1/out/ov_keep.c
python -I build/difftest/asm_p1/variant.py build/overrides_asm_p1.c "$@"
make -C build link > build/difftest/asm_p1/out/variant_link.log 2>&1 || { cp build/difftest/asm_p1/out/ov_keep.c build/overrides_asm_p1.c; tail -20 build/difftest/asm_p1/out/variant_link.log; exit 1; }
cp build/difftest/asm_p1/out/ov_keep.c build/overrides_asm_p1.c
mkdir -p "$OUT"
cp build/obj/GRIMFANDANGO.EXE/grimfandango.exe build/obj/LUA.DLL/lua.dll build/obj/IMUSE.DLL/imuse.dll build/obj/CHORE.DLL/chore.dll "$OUT/"
echo "variant without: $*"
