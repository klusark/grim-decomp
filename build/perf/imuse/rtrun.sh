#!/bin/bash
# atrun.sh <rundir> <tag> <scenario> <symbol> [words]
RUN="$1"; TAG="$2"; SCN="$3"; export RT_SYM="$4"; export RT_ARGS="${5:-2}"; export RT_OUT=C:/Users/Joel/grimN_work/rt_$TAG.txt; export PATH=/ucrt64/bin:$PATH
W=/c/Users/Joel/grimN_work
cd /c/Users/Joel/grimN_data; cat "$SCN" > $W/cmd.lua; : > $W/log.txt
cat > $W/gdbat.txt <<EOF
set pagination off
set breakpoint pending on
set environment _NO_DEBUG_HEAP=1
set environment GRIM_MULTI=agentN
set environment GRIM_ACTIVE=1
set environment GRIM_SIMTIME=17
set environment GRIM_NOMOVIE=1
set environment GRIM_LUA_FILE=C:\Users\Joel\grimN_work\cmd.lua
set environment GRIM_LUA_LOG=C:\Users\Joel\grimN_work\log.txt
source C:/Users/Joel/grimN_work/rettrace.py
run
EOF
( i=0; until grep -aq '^DONE' $W/log.txt || [ $i -ge ${TMO:-250} ]; do sleep 1; i=$((i+1)); done; sleep 2
  powershell -NoProfile -Command "Get-Process grimfandango -ea 0 | ? { \$_.Path -like 'C:\Users\Joel\grim-agentN\*' } | % { Stop-Process -Id \$_.Id -Force }" ) &
timeout 400 gdb -batch -x $W/gdbat.txt --args "$RUN/grimfandango.exe" > $W/at.out 2>&1
wc -l < $W/rt_$TAG.txt
