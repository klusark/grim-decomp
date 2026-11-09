#!/bin/bash
# usage: build/difftest/lua_core/build.sh [cases]
# Differential test of build/overrides_lua_core.c (lua_updatetasks, luaD_protectedrun, luaD_protectedparser) against the
# original LUA.DLL machine code, sliced from the asm_funcs.s of the last commit that still assembled them
# (BASE_ASM=<file> for another copy), with stand-in callees (core_test.c) and the LUA.DLL data image.
set -e
cd "$(dirname "$0")/../../.."
D=build/difftest/lua_core; W=$D/out; mkdir -p $W; rm -f $W/*.o
if [ -z "$BASE_ASM" ]; then BASE_ASM=$W/base_asm_funcs.s; git show ${BASE_REV:-ea3c1a6}:src/LUA.DLL/asm_funcs.s > $BASE_ASM; fi
python -I build/mixdiff/slice_orig.py $BASE_ASM $W/orig.s lua_updatetasks luaD_protectedrun luaD_protectedparser >/dev/null
/ucrt64/bin/gcc -m32 -c $W/orig.s -o $W/orig.o
export PATH=/mingw32/bin:$PATH
CF="-std=gnu11 -fpermissive -w -fno-builtin -ffreestanding -fno-common -include build/compat.h -Isrc/LUA.DLL -DGRIM_LUA"
gcc $CF $EXTRA_CFLAGS -c ${OVR:-build/overrides_lua_core.c} -o $W/mine.o
gcc -O1 -w -fno-builtin -c $D/core_test.c -o $W/test.o
: > $W/stubs.s
for i in 1 2 3 4 5; do
  /ucrt64/bin/gcc -m32 -c $W/stubs.s -o $W/stubs.o
  gcc -o $W/core_test.exe $W/test.o $W/mine.o $W/orig.o build/obj/LUA.DLL/data_s.o $W/stubs.o -Wl,--allow-multiple-definition 2> $W/link.log && break
  python -I build/difftest/asm_s5/stubgen.py $W/link.log $W/stubs.s >/dev/null
done
test -f $W/core_test.exe || { head -20 $W/link.log; exit 1; }
timeout ${TEST_TIMEOUT:-0} $W/core_test.exe ${1:-100000}
