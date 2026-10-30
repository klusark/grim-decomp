#!/bin/bash
# Append one line of Lua to the hook file of tools/run_game.sh; waits for the log line the hook writes back.
#   tools/lua_cmd.sh 'grimlog("hello "..GetTickCount())'
GRIM_CMD="${GRIM_CMD:-$HOME/grim_cmd.lua}"; GRIM_LOG="${GRIM_LOG:-$HOME/grim_log.txt}"
echo "$1" >> "$GRIM_CMD"
sleep "${GRIM_WAIT:-2}"
tail -n 3 "$GRIM_LOG"
