#!/bin/bash
# usage: cmp16.sh PID  : screenshot + raw 16bpp back buffer dump (UINT_007feae0 -> bits) and compare
P=$1
python -I /c/Users/Joel/grim-agentC/build/perf/shot.py /c/Users/Joel/agentC_cmp.png >/dev/null
BITS=$(_NO_DEBUG_HEAP=1 /mingw32/bin/gdb -batch -nx -ex "attach $P" -ex "set \$b=*(int*)0x813af0" -ex "printf \"BITS=%u\n\", \$b" -ex "dump binary memory C:/Users/Joel/agentC_dib.bin \$b \$b+614400" -ex detach 2>&1 | grep BITS)
python -I /c/Users/Joel/grim-agentC/build/perf/cmp16.py
