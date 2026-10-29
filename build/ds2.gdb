set pagination off
break Lua_MakeCurrentSet
run
delete
break luaL_verror
python
import gdb
try:
    gdb.execute('p (int)lua_dostring("tx = 4; ty = -3")')
except gdb.error as e:
    print('>> stopped')
end
bt 8
x/4wx $esp
x/s *(char**)($esp+8)
x/s *(char**)($esp+12)
x/s *(char**)($esp+16)
kill
