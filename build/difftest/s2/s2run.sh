#!/bin/bash
# s2run.sh <rundir> <tag> <scenario.lua> <orig|sym|aud>
# Like build/difftest/imuse_r1/ftrun.sh, with build/difftest/s2/s2trace.py and a selectable time base:
#   SIMTIME=17 (default; SIMTIME= (empty) leaves GRIM_SIMTIME unset: frames and iMUSE on real time),
#   ENVX="GRIM_IMUSE_REALTIME=1 ..." more environment for the game.
# Output: $W/s2_<tag>.txt (aud: $W/aud_<tag>.txt), $W/log_<tag>.txt.  W / DATA: scratch and data folders (hard links of
# the game's LAB / TAB / HMI files).
RUN="$(cd "$1" && pwd)"; TAG="$2"; SCN="$(cd "$(dirname "$3")" && pwd)/$(basename "$3")"; MODE="$4"
W=${W:-/c/Users/Joel/grimS2_data/work}; DATA=${DATA:-/c/Users/Joel/grimS2_data}
HERE="$(cd "$(dirname "$0")" && pwd)"
export PATH=/ucrt64/bin:$PATH
mkdir -p $W; cd $DATA || exit 1
WW=$(cygpath -m $W); export S2_OUT=$WW/s2_$TAG.txt S2_MODE=$MODE AUD_OUT=$WW/aud_$TAG.txt
SCRIPT=$(cygpath -m $HERE/s2trace.py); [ "$MODE" = aud ] && SCRIPT=$(cygpath -m $HERE/../../perf/imuse/audtrace.py)
cat "$SCN" > $W/cmd.lua; : > $W/log.txt
ST=${SIMTIME-17}
{
echo "set pagination off"
echo "set breakpoint pending on"
echo "set environment _NO_DEBUG_HEAP=1"
echo "set environment GRIM_MULTI=agentS2"
echo "set environment GRIM_ACTIVE=1"
[ -n "$ST" ] && echo "set environment GRIM_SIMTIME=$ST"
echo "set environment GRIM_NOMOVIE=1"
for e in $ENVX; do echo "set environment $e"; done
echo "set environment GRIM_LUA_FILE=$(cygpath -w $W/cmd.lua)"
echo "set environment GRIM_LUA_LOG=$(cygpath -w $W/log.txt)"
echo "source $SCRIPT"
echo "run"
echo "bt 10"
} > $W/gdb_$TAG.cmd
( i=0; until grep -aq '^DONE' $W/log.txt || [ $i -ge ${TMO:-300} ]; do sleep 1; i=$((i+1)); done; sleep 2
  powershell -NoProfile -Command "Get-Process grimfandango -ea 0 | ? { \$_.Path -like '$(cygpath -w $RUN)\*' } | % { Stop-Process -Id \$_.Id -Force }" ) &
timeout $(( ${TMO:-300} + 100 )) gdb -batch -x $W/gdb_$TAG.cmd --args "$RUN/grimfandango.exe" > $W/gdb_$TAG.out 2>&1
cp $W/log.txt $W/log_$TAG.txt
if [ "$MODE" = aud ]; then wc -l < $W/aud_$TAG.txt; else grep -c "^FUN_1000656" $W/s2_$TAG.txt; fi
