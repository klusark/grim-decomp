#!/bin/bash
# agentC game control. usage: ctl.sh start <exe-dir> | stop | pid
ROOT='C:\Users\Joel\grim-agentC'
pid() { powershell -NoProfile -Command "Get-Process grimfandango -ea 0 | ? { \$_.Path -like '${ROOT}\*' } | % { \$_.Id }" | tr -d '\r'; }
case "$1" in
 stop) for p in $(pid); do powershell -NoProfile -Command "Stop-Process -Id $p -Force"; done; sleep 1;;
 pid) pid;;
 start) "$0" stop; : > /c/Users/Joel/agentC_cmd.lua; rm -f /c/Users/Joel/agentC_log.txt
   cd "/c/GOG Games/GRIMDATA"
   if [ "${GRIM_NOMOVIE-1}" = 0 ]; then unset GRIM_NOMOVIE; else export GRIM_NOMOVIE=1; fi   # GRIM_NOMOVIE=0 here means movies on
   GRIM_MULTI=agentC GRIM_LUA_FILE='C:\Users\Joel\agentC_cmd.lua' GRIM_LUA_LOG='C:\Users\Joel\agentC_log.txt' "$2/grimfandango.exe" >/dev/null 2>&1 &
   sleep ${WAIT-14}; pid;;
esac
