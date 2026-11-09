#!/bin/bash
# ftrun.sh <rundir> <tag> <scenario.lua> <orig|sym|aud> [FT_LEN hex]  -> $W/ft_<tag>.txt (aud: $W/aud_<tag>.txt), $W/log_<tag>.txt
# Runs the game of <rundir> under gdb with frametrace.py (orig / sym) or the PCM oracle build/perf/imuse/audtrace.py (aud, a
# rebuilt imuse.dll with symbols) and a Lua scenario (build/perf/imuse/scn_*.lua) until it logs DONE.
# W = scratch folder, DATA = data folder (hard links of the game's LAB/TAB/HMI files); edit for another setup.
RUN="$(cd "$1" && pwd)"; TAG="$2"; SCN="$(cd "$(dirname "$3")" && pwd)/$(basename "$3")"; MODE="$4"; LEN="${5:-7f0}"
W=${W:-/c/Users/Joel/grimR1_data/work}; DATA=${DATA:-/c/Users/Joel/grimR1_data}
HERE="$(cd "$(dirname "$0")" && pwd)"
export PATH=/ucrt64/bin:$PATH
mkdir -p $W; cd $DATA || exit 1
WW=$(cygpath -m $W); export FT_OUT=$WW/ft_$TAG.txt FT_MODE=$MODE FT_LEN=$LEN AUD_OUT=$WW/aud_$TAG.txt   # read by the gdb scripts
SCRIPT=$(cygpath -m $HERE/frametrace.py); [ "$MODE" = aud ] && SCRIPT=$(cygpath -m $HERE/../../perf/imuse/audtrace.py)
cat "$SCN" > $W/cmd.lua; : > $W/log.txt
cat > $W/gdbft.txt <<EOF
set pagination off
set breakpoint pending on
set environment _NO_DEBUG_HEAP=1
set environment GRIM_MULTI=agentR1
set environment GRIM_ACTIVE=1
set environment GRIM_SIMTIME=17
set environment GRIM_NOMOVIE=1
set environment GRIM_LUA_FILE=$(cygpath -w $W/cmd.lua)
set environment GRIM_LUA_LOG=$(cygpath -w $W/log.txt)
source $SCRIPT
run
bt 10
EOF
( i=0; until grep -aq '^DONE' $W/log.txt || [ $i -ge ${TMO:-300} ]; do sleep 1; i=$((i+1)); done; sleep 2
  powershell -NoProfile -Command "Get-Process grimfandango -ea 0 | ? { \$_.Path -like '$(cygpath -w $RUN)\*' } | % { Stop-Process -Id \$_.Id -Force }" ) &
timeout $(( ${TMO:-300} + 100 )) gdb -batch -x $W/gdbft.txt --args "$RUN/grimfandango.exe" > $W/gdb_$TAG.out 2>&1
cp $W/log.txt $W/log_$TAG.txt
[ "$MODE" = aud ] && wc -l < $W/aud_$TAG.txt || grep -c ENTRY $W/ft_$TAG.txt
