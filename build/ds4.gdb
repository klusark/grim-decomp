set pagination off
set environment _NO_DEBUG_HEAP=1
break Lua_MakeCurrentSet
run
delete
p (int)lua_dostring("tx = 4; ty = -3; tz = 2.5; tw = tx + 1; tv = 0.5 * 8; function f(a) return a*2 end; tq = f(21)")
python
import gdb
for n in ('tx','ty','tz','tw','tv','tq'):
    gdb.execute('call (int)lua_beginblock()')
    o = int(gdb.parse_and_eval('(int)lua_getglobal("%s")' % n))
    print('>>', n, gdb.parse_and_eval('((float(*)(int))lua_getnumber)(%d)' % o))
end
kill
