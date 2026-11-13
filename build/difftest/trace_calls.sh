#!/bin/bash
# trace_calls.sh <rundir> <symbol> <script.lua> <outfile> [nargs=1]: log the float arguments of every call of <symbol> while <script.lua> runs
RUN="$(realpath "$1")"; SYM="$2"; SCRIPT="$(realpath "$3")"; OUT="$(realpath -m "$4")"; N="${5:-1}"
export PATH=/ucrt64/bin:$PATH
DD=/c/Users/Joel/grim-agentI-data-tr
[ -d "$DD" ] || bash "$(dirname "$0")/../../tools/mkmoddir.sh" "$DD" >/dev/null
cp "$SCRIPT" "$DD/difftest.lua"; cd "$DD"; : > cmd.lua; : > log.txt
{ echo "set pagination off"; echo "set environment _NO_DEBUG_HEAP=1"; echo "set environment GRIM_MULTI=tr"
  echo "set environment GRIM_NOMOVIE=1"; echo "set environment GRIM_SIMTIME=17"
  echo "set environment GRIM_LUA_FILE=C:\Users\Joel\grim-agentI-data-tr\cmd.lua"; echo "set environment GRIM_LUA_LOG=C:\Users\Joel\grim-agentI-data-tr\log.txt"

  echo "break *$SYM"; echo "commands"; echo "silent"; [ -n "$RET" ] && { echo "set \$ra = *(int*)\$esp"; echo "tbreak *\$ra"; echo "commands"; echo "silent"; echo "printf \"A9 ret=%x\n\", \$eax"; echo "continue"; echo "end"; }
  for ((k=1;k<=N;k++)); do echo "printf \"A$k %x\n\", *(unsigned*)(\$esp+$((4*k)))"; done
  echo "continue"; echo "end"; echo "run"; } > gdbcmds.txt
( i=0; until grep -aq '^READY' log.txt || [ $i -ge 30 ]; do echo 'if manny and manny.hActor then grimlog("READY") end' >> cmd.lua; sleep 1; i=$((i+1)); done
  echo 'dofile("difftest.lua")' >> cmd.lua
  i=0; until grep -aq '^DONE' log.txt || [ $i -ge 90 ]; do sleep 1; i=$((i+1)); done; sleep 1
  powershell -c "Get-Process grimfandango -ea 0 | ? { \$_.Path -like '*$(basename "$RUN")*' -or \$_.Path -eq '$(cygpath -w "$RUN")\grimfandango.exe' } | Stop-Process -Force" ) &
gdb -batch -x gdbcmds.txt --args "$RUN/grimfandango.exe" 2>&1 | grep -a "^A[0-9]" > "$OUT"
wait; echo "traced: $(grep -c '^A1' "$OUT") calls"
