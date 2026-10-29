set pagination off
break gz_open
run
x/s *(char**)($esp+4)
x/s *(char**)($esp+8)
p *(int*)($esp+12)
finish
p/x $eax
bt 5
