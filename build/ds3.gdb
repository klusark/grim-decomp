set pagination off
set environment _NO_DEBUG_HEAP=1
break Lua_MakeCurrentSet
run
delete
break luaL_verror
python
import gdb
try:
    gdb.execute('p (int)lua_dostring("x = 4")')
except gdb.error:
    pass
print('>> stopped; fmt arg')
end
printf ">> fmt %s
", fmt
printf ">> a1 %s
", *(char**)($ebp+12)
printf ">> a2 %s
", *(char**)($ebp+16)
printf ">> a3 %d
", *(int*)($ebp+20)
printf ">> a4 %s
", *(char**)($ebp+24)
kill
