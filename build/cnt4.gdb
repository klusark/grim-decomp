set pagination off
set environment _NO_DEBUG_HEAP=1
set breakpoint pending on
break CreateFileA
run
bt 3
x/s *(char**)($esp+4)
finish
print/x $eax
print (int)((int(*)())GetLastError)()
