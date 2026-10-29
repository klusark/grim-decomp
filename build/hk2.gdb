set pagination off
set environment _NO_DEBUG_HEAP=1
set environment GRIM_LUA_FILE=C:/Users/Joel/grim_lua.txt
set environment GRIM_LUA_LOG=C:/Users/Joel/grim_lua.log
break GRIM_lua_cmd_poll
run
break *CreateFileA
continue
x/s *(char**)($esp+4)
x/6wx $esp
