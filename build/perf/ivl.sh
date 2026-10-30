#!/bin/bash
# usage: ivl.sh PID  -> frame interval stats over 4 s (Display_Flip breakpoint timestamps)
_NO_DEBUG_HEAP=1 /mingw32/bin/gdb -batch -nx -ex "attach $1" -x /c/Users/Joel/grim-agentC/build/perf/ivl.py 2>&1 | grep RESULT
