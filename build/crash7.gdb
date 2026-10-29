set pagination off
set breakpoint pending on
break FUN_10006b30
run
x/s *(char**)$esp+4
x/s *(char**)($esp+8)
x/s **(char***)($esp+4)
x/8wx *(int*)($esp+12)
continue
x/s *(char**)($esp+8)
x/s **(char***)($esp+4)
x/8wx *(int*)($esp+12)
