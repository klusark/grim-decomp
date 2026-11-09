#!/bin/bash
# Start the rebuilt game with the test knobs and return immediately (the game keeps running in the background).
#
#   tools/run_game.sh [-d DATADIR] [-t TAG] [-r RUNDIR]
#
#   -d  working directory of the game = highest-priority resource directory (default: C:/GOG Games/GRIMDATA)
#   -t  GRIM_MULTI tag, window title "Grim Fandango (<tag>)" (default: dev)
#   -r  folder with grimfandango.exe + the three DLLs (default: build/run)
#
# Lua test hook: append lines to $GRIM_CMD (default ~/grim_cmd.lua); every complete line runs once per frame as Lua
# (tools/lua_cmd.sh does the appending); grimlog("text") writes to $GRIM_LOG (default ~/grim_log.txt).
# Extra environment variables you set before calling this script (GRIM_WALK_SCALE=2 ...) are passed on.
set -e
ROOT="$(cd "$(dirname "$0")/.." && pwd)"
DATA="C:/GOG Games/GRIMDATA"; TAG=dev; RUN="$ROOT/build/run"
while getopts "d:t:r:" o; do case $o in d) DATA="$OPTARG";; t) TAG="$OPTARG";; r) RUN="$OPTARG";; esac; done
GRIM_CMD="${GRIM_CMD:-$HOME/grim_cmd.lua}"; GRIM_LOG="${GRIM_LOG:-$HOME/grim_log.txt}"
: > "$GRIM_CMD"; : > "$GRIM_LOG"
export GRIM_MULTI="$TAG" GRIM_NOMOVIE=1 GRIM_ACTIVE=1
export GRIM_MODS="${GRIM_MODS:-1}"   # the mod additions (docs/MODDING.md): the extra Lua functions of example mod 10 b
export GRIM_LUA_FILE="$(cygpath -w "$GRIM_CMD")" GRIM_LUA_LOG="$(cygpath -w "$GRIM_LOG")"   # Windows backslash paths!
cd "$DATA"
"$RUN/grimfandango.exe" > "$HOME/grim_stdout.txt" 2>&1 &
echo "started pid $! (window \"Grim Fandango ($TAG)\"), log: $GRIM_LOG"
