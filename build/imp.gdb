set pagination off
break Lua_UpdateFrame
run
p/x *(int*)&__imp__lua_updatetasks
info symbol *(int*)&__imp__lua_updatetasks
x/4i *(int*)&__imp__lua_updatetasks
info symbol lua_updatetasks
