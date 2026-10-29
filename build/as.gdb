set pagination off
set environment _NO_DEBUG_HEAP=1
handle SIGSEGV stop
break Lua_MakeCurrentSet
run
delete
break ExitProcess
break exit
break _exit
break Engine_Quit
break abort
break MessageBoxA
continue
bt 12
kill
