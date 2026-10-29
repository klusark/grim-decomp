set pagination off
set breakpoint pending on
break Reg_GetString
break RegOpenKeyExA@20
break RegQueryValueExA@24
run
bt 3
x/s *(char**)($esp+4)
continue
bt 3
x/s *(char**)($esp+8)
continue
bt 3
continue
bt 3
x/s *(char**)($esp+4)
continue
x/s *(char**)($esp+8)
