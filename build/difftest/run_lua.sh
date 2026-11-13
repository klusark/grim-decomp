#!/bin/bash
# Differential harness: run a Lua script in the booted game (Manny's office) of the given build and collect its log.
#   run_lua.sh <rundir> <tag> <script.lua> <outlog> [max seconds=240]
# The script runs through the Lua test hook (GRIM_LUA_FILE) via dofile; it logs with grimlog(). Output is deterministic
# (GRIM_SIMTIME fixes the frame time), so two builds can be compared with diff. Only kills the process it started.
RUN="$(realpath "$1")"; TAG="$2"; SCRIPT="$(realpath "$3")"; OUT="$(realpath -m "$4")"; MAX="${5:-240}"
HERE="$(cd "$(dirname "$0")" && pwd)"
DD="/c/Users/Joel/grim-agentI-data-$TAG"
[ -d "$DD" ] || bash "$HERE/../../tools/mkmoddir.sh" "$DD" >/dev/null
cp "$SCRIPT" "$DD/difftest.lua"
CMD="$DD/cmd.lua"; LOG="$DD/log.txt"
rm -f "$DD"/grim_crash_*.txt; : > "$CMD"; : > "$LOG"
cd "$DD"
GRIM_MULTI="$TAG" GRIM_NOMOVIE=1 GRIM_SIMTIME=17 \
  GRIM_LUA_FILE="$(cygpath -w "$CMD")" GRIM_LUA_LOG="$(cygpath -w "$LOG")" \
  "$RUN/grimfandango.exe" > "$DD/stdout.txt" 2>&1 &
PID=$!
i=0
until grep -aq '^READY' "$LOG" 2>/dev/null || [ $i -ge 24 ] || ! kill -0 $PID 2>/dev/null; do
  printf '%s\n' 'if manny and manny.hActor then grimlog("READY") end' >> "$CMD"; sleep 2; i=$((i+2))
done
if ! grep -aq '^READY' "$LOG"; then echo "boot failed"; kill $PID 2>/dev/null; cp "$LOG" "$OUT"; exit 1; fi
printf '%s\n' 'dofile("difftest.lua")' >> "$CMD"
i=0
# SHOT protocol: the script logs "SHOT <name>" and waits for SHOTOK; we capture the window to $OUT.<name>.png
SHOTDIR="${OUT}.shots"; nshot=0
until grep -aq '^DONE' "$LOG" 2>/dev/null || [ $i -ge $((MAX*2)) ] || ! kill -0 $PID 2>/dev/null; do
  sleep 0.5; i=$((i+1))
  c=$(grep -ac '^SHOT ' "$LOG" 2>/dev/null)
  if [ "${c:-0}" -gt "$nshot" ]; then
    nshot=$((nshot+1)); name=$(grep -a '^SHOT ' "$LOG" | sed -n "${nshot}p" | cut -d' ' -f3)
    mkdir -p "$SHOTDIR"; sleep 0.5
    python -I "$HERE/../perf/shot.py" "$SHOTDIR/$name.png" "Grim Fandango ($TAG)" > /dev/null 2>&1
    printf 'SHOTOK=%s
' "$nshot" >> "$CMD"
  fi
done
i=$((i/2))
# optional follow-up lines (env FOLLOW, one Lua statement per line) run after the script reported DONE, e.g. a Load() whose
# result is checked in the log; the hook runs one line per frame
if [ -n "$FOLLOW" ] && kill -0 $PID 2>/dev/null; then
  printf '%s
' "$FOLLOW" >> "$CMD"; sleep 6
fi
kill -0 $PID 2>/dev/null || echo "GAME EXITED/CRASHED" >> "$LOG"
cp "$LOG" "$OUT"; ls "$DD"/grim_crash* 2>/dev/null && cp "$DD"/grim_crash* "$OUT.crash"
kill $PID 2>/dev/null; taskkill //F //PID $PID >/dev/null 2>&1
wait $PID 2>/dev/null
echo "finished after ${i}s, log $OUT ($(wc -l < "$OUT") lines)"
