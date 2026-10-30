set pagination off
set environment _NO_DEBUG_HEAP=1
set breakpoint pending on
break MessageBoxA
run
x/s *(char**)($esp+8)
x/s *(char**)($esp+12)
