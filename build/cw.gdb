set pagination off
set environment _NO_DEBUG_HEAP=1
break Lua_MakeCurrentSet
run
x/6hx &DAT_00900524
x/6hx 0x900524
kill
