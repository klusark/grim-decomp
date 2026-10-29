set pagination off
set environment _NO_DEBUG_HEAP=1
handle SIGSEGV stop
run
bt 3
printf ">> verts at %x\n", *(int*)0x80a50c
x/16fw *(int*)0x80a50c
p *(int*)0x80a470
p *(int*)0x80a4f8
p *(int*)0x80a504
kill
