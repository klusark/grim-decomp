#!/bin/bash
# usage: bootok.sh <run dir>  -> prints OK/BAD (boots to the office within 15 s, not stuck in a fatal message box)
cd "/c/GOG Games/GRIMDATA"
GRIM_MULTI=bis GRIM_NOMOVIE=1 "$1/grimfandango.exe" &
sleep 14
R=$(powershell -c "(Get-Process grimfandango -ea 0 | ? { \$_.Path -like '*run_t*' } | % { [int](\$_.WorkingSet64/1MB) }) -join ','")
powershell -c "Get-Process grimfandango -ea 0 | ? { \$_.Path -like '*run_t*' } | Stop-Process -Force" >/dev/null 2>&1
echo "ws=$R"; [ -n "$R" ] && [ "${R%%,*}" -gt 40 ] && echo OK || echo BAD
