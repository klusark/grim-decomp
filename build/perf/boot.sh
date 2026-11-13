#!/bin/bash
# usage: boot.sh <exe-dir> : seconds from launch until the hook is live and until Manny's office exists
export GRIM_PERFLOG=1
D=/c/Users/Joel
WAIT=0 ./ctl.sh stop; : > $D/agentC_cmd.lua; rm -f $D/agentC_log.txt
S=$(date +%s.%N)
(cd "/c/GOG Games/GRIMDATA"; GRIM_MULTI=agentC GRIM_NOMOVIE=1 GRIM_LUA_FILE='C:\Users\Joel\agentC_cmd.lua' GRIM_LUA_LOG='C:\Users\Joel\agentC_log.txt' "$1/grimfandango.exe" >/dev/null 2>&1 &)
hook=; for i in $(seq 1 600); do
  if [ -z "$hook" ] && grep -q "lua hook active" $D/agentC_log.txt 2>/dev/null; then hook=$(echo "$(date +%s.%N) - $S" | bc); fi
  if [ -n "$hook" ]; then echo 'if manny and GetCurrentSet and GetCurrentSet() then grimlog("OFFICE "..tostring(GetCurrentSet().setFile)) end' >> $D/agentC_cmd.lua; fi
  if grep -q "^OFFICE" $D/agentC_log.txt 2>/dev/null; then echo "hook live at ${hook}s, office at $(echo "$(date +%s.%N) - $S" | bc)s"; break; fi
  sleep 0.25
done
