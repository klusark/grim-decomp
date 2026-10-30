#!/bin/bash
# usage: bench.sh <exe-dir> [walk]  ; env passes through (GRIM_SLOWFLIP etc.). Prints idle and walking perf lines.
export GRIM_PERFLOG=1
P=$(WAIT=${WAIT-18} /c/Users/Joel/grim-agentC/build/perf/ctl.sh start "$1")
sleep 3; echo "idle:"; grep perf /c/Users/Joel/agentC_log.txt | tail -2
if [ "$2" = walk ]; then
  cat /c/Users/Joel/grim-agentC/build/perf/walk.lua >> /c/Users/Joel/agentC_cmd.lua
  sleep 12; echo "walking:"; grep perf /c/Users/Joel/agentC_log.txt | tail -3
fi
echo $P
