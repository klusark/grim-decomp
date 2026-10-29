set pagination off
handle SIGSEGV stop
run
bt 10
info registers eip esp ebp eax ecx edx esi edi
x/4i $eip
kill
