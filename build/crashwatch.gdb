set pagination off
set environment _NO_DEBUG_HEAP=1
handle SIGSEGV stop
run
bt 10
info registers eip eax ecx edx esi edi ebp esp
x/5i $eip
kill
