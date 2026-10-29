set pagination off
break Lua_MakeCurrentSet
run
delete
break *'@luaV_execute@4'
continue
info registers ecx edx eip esp
x/6i $eip
x/4wx $esp
bt 4
kill
