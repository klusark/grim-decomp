set pagination off
set environment _NO_DEBUG_HEAP=1
run
info registers eax
x/4wx $eax
x/wx 0x91cc40
x/wx 0x8ecf30
x/6wx $esp
