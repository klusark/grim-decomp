#!/bin/bash
# gdbrun.sh <rundir> <script.lua>: run the game under gdb with the Lua hook feeding <script.lua>; prints the backtrace of a crash
RUN="$(realpath "$1")"; SCRIPT="$(realpath "$2")"
export PATH=/ucrt64/bin:$PATH
DD=/c/Users/Joel/grim-agentI-data-tr
[ -d "$DD" ] || bash "$(dirname "$0")/../../tools/mkmoddir.sh" "$DD" >/dev/null
cp "$SCRIPT" "$DD/difftest.lua"; cd "$DD"; : > cmd.lua; : > log.txt
{ echo "set pagination off"; echo "set environment _NO_DEBUG_HEAP=1"; echo "set environment GRIM_MULTI=tr"
  echo "set environment GRIM_NOMOVIE=1"; echo "set environment GRIM_SIMTIME=17"
  echo "set environment GRIM_LUA_FILE=C:\Users\Joel\grim-agentI-data-tr\cmd.lua"; echo "set environment GRIM_LUA_LOG=C:\Users\Joel\grim-agentI-data-tr\log.txt"
  echo "run"; echo "bt 12"; echo "x/6i \$eip"; echo "info registers eax ecx edx esi edi"; } > gdbcmds2.txt
( i=0; until grep -aq '^READY' log.txt || [ $i -ge 30 ]; do echo 'if manny and manny.hActor then grimlog("READY") end' >> cmd.lua; sleep 1; i=$((i+1)); done
  echo 'dofile("difftest.lua")' >> cmd.lua
  i=0; until grep -aq '^DONE' log.txt || [ $i -ge 40 ]; do sleep 1; i=$((i+1)); done; sleep 1
  powershell -c "Get-Process grimfandango -ea 0 | ? { \$_.Path -eq '$(cygpath -w "$RUN")\grimfandango.exe' } | Stop-Process -Force" ) &
timeout 120 gdb -batch -x gdbcmds2.txt --args "$RUN/grimfandango.exe" 2>&1 | grep -v "^\[" | tail -25
wait
