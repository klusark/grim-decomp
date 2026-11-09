#!/bin/bash
# dbg.sh <args of q6_test.exe...>: run the test under gdb and print the backtrace / registers of a crash
cd "$(dirname "$0")"
printf 'set pagination off\nrun\nbt 8\nx/8i $eip\ninfo registers\n' > out/gdbcmds.txt
/ucrt64/bin/gdb -batch -x out/gdbcmds.txt --args out/${OUTEXE:-q6_test}.exe "$@" 2>&1 | grep -v "^\[" | tail -40
