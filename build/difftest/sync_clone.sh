#!/bin/bash
# copy the working tree (without .git, scratch and build outputs of the harness) into a bisect clone
SRC="$(cd "$(dirname "$0")/../.." && pwd)"; DST="$1"
mkdir -p "$DST"
cd "$SRC" && for d in raw src names tools build/overrides.c build/overrides_exe.c build/link.py build/fastpaths.c build/compat.h build/opt.mk build/Makefile build/peephole.py build/gendata.py build/difftest build/obj; do rm -rf "$DST/$d"; done
tar cf - --exclude=.git --exclude=.scratch --exclude=build/difftest/out raw src names tools build/overrides.c build/overrides_exe.c build/link.py build/fastpaths.c build/compat.h build/opt.mk build/Makefile build/peephole.py build/gendata.py build/difftest build/obj docs 2>/dev/null | (cd "$DST" && tar xf -)
mkdir -p "$DST/build/difftest/out" "$DST/build/run_t"
[ -d "$SRC/build/difftest/out/probe_ref" ] && cp -r "$SRC/build/difftest/out/probe_ref" "$DST/build/difftest/out/"
cp "$SRC/build/difftest/out/"t*_ref.log "$DST/build/difftest/out/" 2>/dev/null
echo synced
