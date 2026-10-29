set pagination off
set environment _NO_DEBUG_HEAP=1
set environment GRIM_LUA_FILE=C:/Users/Joel/grim_lua.txt
set environment GRIM_LUA_LOG=C:/Users/Joel/grim_lua.log
handle SIGSEGV stop
handle SIGILL stop
run
bt 12
info registers eip
x/4i $eip
