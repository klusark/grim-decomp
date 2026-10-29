set pagination off
set environment _NO_DEBUG_HEAP=1
set breakpoint pending on
break *0x4eb658
break ExitProcess
run
bt 10
