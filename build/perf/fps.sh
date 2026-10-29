#!/bin/bash
# usage: fps.sh <PID(win)> ; counts Engine_RenderFrame/Display_Flip for DUR seconds
export _NO_DEBUG_HEAP=1
/mingw32/bin/gdb -batch -nx -ex "set pagination off" -ex "attach $1" -x /c/Users/Joel/grim-agentC/build/perf/fps.py 2>&1 | grep -v "^\[" | tail -8
