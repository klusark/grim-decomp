#!/bin/bash
# Append one line of Lua to the hook file of tools/run_game.sh and show the last lines of the log.
#   tools/lua_cmd.sh 'grimlog("hello "..GetTickCount())'
# The line runs once, in the next frame (the hook reads the file every frame); GRIM_WAIT=<seconds> sets how long
# to wait before the log is shown (default 2).
GRIM_CMD="${GRIM_CMD:-$HOME/grim_cmd.lua}"; GRIM_LOG="${GRIM_LOG:-$HOME/grim_log.txt}"
printf '%s\n' "$1" >> "$GRIM_CMD"
sleep "${GRIM_WAIT:-2}"
tail -n 3 "$GRIM_LOG"
