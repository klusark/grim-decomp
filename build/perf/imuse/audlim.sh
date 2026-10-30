#!/bin/bash
# audlim.sh <rundir> <tag> [limit blocks]: boot only (no Lua scenario unless SCN=file), stop after N committed blocks
RUN="$1"; TAG="$2"; export AUD_LIMIT=${3:-300}; export AUD_OUT=C:/Users/Joel/grimN_work/aud_$TAG.txt; export PATH=/ucrt64/bin:$PATH
W=/c/Users/Joel/grimN_work
cd /c/Users/Joel/grimN_data
if [ -n "$SCN" ]; then cat "$SCN" > $W/cmd.lua; else : > $W/cmd.lua; fi
: > $W/log.txt
cat > $W/gdblim.txt <<EOF
set pagination off
set breakpoint pending on
set environment _NO_DEBUG_HEAP=1
set environment GRIM_MULTI=agentN
set environment GRIM_ACTIVE=1
set environment GRIM_SIMTIME=17
set environment GRIM_NOMOVIE=1
set environment GRIM_LUA_FILE=C:\Users\Joel\grimN_work\cmd.lua
set environment GRIM_LUA_LOG=C:\Users\Joel\grimN_work\log.txt
source C:/Users/Joel/grimN_work/audtrace.py
run
kill
EOF
timeout ${TMO:-180} gdb -batch -x $W/gdblim.txt --args "$RUN/grimfandango.exe" > $W/audlim.out 2>&1
wc -l < $W/aud_$TAG.txt
