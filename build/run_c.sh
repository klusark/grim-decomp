#!/bin/bash
# usage: run_c.sh <exe-dir> [extra env...]; starts the game detached, prints PID file
EXE=${1:-/c/Users/Joel/grim-agentC/build/run}
cd "/c/GOG Games/GRIMDATA"
GRIM_MULTI=agentC GRIM_NOMOVIE=${GRIM_NOMOVIE-1} GRIM_LUA_FILE='C:\Users\Joel\agentC_cmd.lua' GRIM_LUA_LOG='C:\Users\Joel\agentC_log.txt' "$EXE/grimfandango.exe" > /dev/null 2>&1 &
echo $!
