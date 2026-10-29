set pagination off
set breakpoint pending on
break Grim_DecodeRegKeyName
run
x/s *(char**)($esp+4)
x/20bx *(char**)($esp+4)
finish
x/s $eax
continue
