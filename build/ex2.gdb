set pagination off
set environment _NO_DEBUG_HEAP=1
run
bt 10
x/8wx $esp
info registers
