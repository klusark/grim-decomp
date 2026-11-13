#!/bin/bash
# audrun.sh <rundir> <tag> <scenario.lua> [movies=0]  -> aud_<tag>.txt, log_<tag>.txt
RUN="$1"; TAG="$2"; SCN="$3"; export AUD_OUT=C:/Users/Joel/grimN_work/aud_$TAG.txt; export PATH=/ucrt64/bin:$PATH
W=/c/Users/Joel/grimN_work
cd /c/Users/Joel/grimN_data
cat "$SCN" > $W/cmd.lua; : > $W/log.txt
cat > $W/gdbaud.txt <<EOF
set pagination off
set breakpoint pending on
set environment _NO_DEBUG_HEAP=1
set environment GRIM_MULTI=agentN
set environment GRIM_SIMTIME=17
$( [ "${4:-0}" = 1 ] || echo "set environment GRIM_NOMOVIE=1" )
set environment GRIM_LUA_FILE=C:\Users\Joel\grimN_work\cmd.lua
set environment GRIM_LUA_LOG=C:\Users\Joel\grimN_work\log.txt
set environment AUD_OUT=C:/Users/Joel/grimN_work/aud_$TAG.txt
source C:/Users/Joel/grimN_work/audtrace.py
run
bt 10
EOF
( i=0; until grep -aq 'lua hook active' $W/log.txt || [ $i -ge 90 ]; do sleep 1; i=$((i+1)); done
  # wait for Manny's office, then run the scenario
  i=0; until grep -aq '^DONE' $W/log.txt || [ $i -ge ${TMO:-240} ]; do sleep 1; i=$((i+1)); done
  sleep 2
  powershell -NoProfile -Command "Get-Process grimfandango -ea 0 | ? { \$_.Path -like 'C:\Users\Joel\grim-agentN\*' } | % { Stop-Process -Id \$_.Id -Force }" ) &
timeout $(( ${TMO:-240} + 150 )) gdb -batch -x $W/gdbaud.txt --args "$RUN/grimfandango.exe" 2>&1 | grep -v "^\[New\|^\[Thread" | tail -15
cp $W/log.txt $W/log_$TAG.txt
