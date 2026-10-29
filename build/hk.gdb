set pagination off
set environment _NO_DEBUG_HEAP=1
set environment GRIM_LUA_FILE=C:/Users/Joel/grim_lua.txt
set environment GRIM_LUA_LOG=C:/Users/Joel/grim_lua.log
break GRIM_lua_cmd_poll
run








finish
p (int)lua_cmd_state
p (int)lua_cmd_file
p (int)GetLastError()
