set pagination off
set breakpoint pending on
break ExitProcess
break exit
break PostQuitMessage
break Win_Main
run
bt 12
continue
bt 12
continue
bt 12
