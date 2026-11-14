#!/bin/bash
# Line coverage of the four programs under grim_tools' clean-room tests (grim-autorun/cleanroom, `run.py decomp`).
#
#   tools/coverage.sh [grim_tools/cleanroom folder] [run.py options, e.g. --only a,b]
#
# 1. builds the gcov build (make COVERAGE=1 OBJ=obj-cov, then link) and copies the four programs to build/run-cov,
# 2. clears the counters (obj-cov/*/*.gcda), runs `run.py decomp` with GRIM_DECOMP=build/run-cov,
# 3. writes the report (tools/covreport.py): build/coverage/summary.md, functions.tsv, gcov/<prog>/<module>.gcov.
#
# Each program adds its counters to the .gcda files next to its objects when it ends (the four games run.py runs at a
# time lock each file while they add to it). A game run.py kills as hung writes nothing; one that crashes writes them in
# its crash filter (build/startup.c).
#
# Windows (MSYS2 UCRT64, as build/Makefile): CC and CC32LINK as for a normal build.
# Linux: the mingw-w64 i686 cross compiler (gcc-mingw-w64-i686, libz-mingw-w64-dev) and Wine (wine32) with an X display
# (Xvfb) and a sound device (a PulseAudio null sink: without DirectSound the game stops with "could not initialize your
# hardware"). CROSS (default /usr/bin/i686-w64-mingw32-) names the toolchain; a folder with the plain names (gcc, nm) is
# made for link.py, which finds nm next to gcc.
set -e
HERE=$(cd "$(dirname "$0")/.." && pwd)
CR=${1:-${GRIM_TOOLS:-$HERE/../grim-autorun}/cleanroom}
shift || true
cd "$HERE/build"
if [ "$(uname -o 2>/dev/null)" = "GNU/Linux" ]; then
	CROSS=${CROSS:-/usr/bin/i686-w64-mingw32-}
	TC=$HERE/build/obj-cov/toolchain
	mkdir -p "$TC"
	for t in gcc nm as ld ar objdump dlltool gcov; do ln -sf "${CROSS}$t" "$TC/$t"; done
	MK=(CC="$TC/gcc" CC32LINK="$TC/gcc" PYTHON="python3 -I")
	export PATH=$TC:$PATH
	PY=python3
	GCOV=$TC/gcov
else
	MK=()
	PY=python
	GCOV=${GCOV:-gcov}
fi
make -j"$(nproc)" COVERAGE=1 OBJ=obj-cov "${MK[@]}" >/dev/null || true   # (-k: the summary says what did not compile)
make COVERAGE=1 OBJ=obj-cov link "${MK[@]}"
mkdir -p run-cov
for f in GRIMFANDANGO.EXE/grimfandango.exe LUA.DLL/lua.dll IMUSE.DLL/imuse.dll CHORE.DLL/chore.dll; do
	cp "obj-cov/$f" run-cov/
done
find obj-cov -name '*.gcda' -delete
# (the gcov build is slower: more time before a quiet game counts as hung)
(cd "$CR" && GRIM_DECOMP="$HERE/build/run-cov" CR_STALL=${CR_STALL:-60} CR_STARTUP=${CR_STARTUP:-120} $PY run.py decomp "$@") || true
$PY -I "$HERE/tools/covreport.py" --obj "$HERE/build/obj-cov" --gcov "$GCOV" --out "$HERE/build/coverage" --uncovered
