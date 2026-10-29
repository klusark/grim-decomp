set pagination off
break Lua_MakeCurrentSet
run
delete
p (int)lua_dostring("tx = 4; ty = -3; tz = 2.5; tw = tx + 1; tv = 0.5 * 8")
python
import gdb
for n in ('tx','ty','tz','tw','tv'):
    gdb.execute('call (int)lua_beginblock()')
    o = int(gdb.parse_and_eval('(int)lua_getglobal("%s")' % n))
    f = gdb.parse_and_eval('((float(*)(int))lua_getnumber)(%d)' % o)
    print('>>', n, f)
end
kill
