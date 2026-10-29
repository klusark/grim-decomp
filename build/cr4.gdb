set pagination off
set environment _NO_DEBUG_HEAP=1
handle SIGSEGV stop
run
bt 4
x/6i $eip
info registers eax ecx edx esi edi ebp
kill
