set pagination off
set breakpoint pending on
break Lua_PutActorAt
python
import gdb, struct
gdb.execute('run')
for i in range(1, 900):
    try:
        o = [int(gdb.parse_and_eval('(int)lua_lua2C(%d)' % k)) for k in (1, 2, 3, 4)]
        h = int(gdb.parse_and_eval('(int)lua_getuserdata(%d)' % o[0]))
        vals = [float(gdb.parse_and_eval('(float)lua_getnumber(%d)' % x)) for x in o[1:]]
        if i <= 6 or h == 5 or i % 150 == 0:
            print('>> PutActorAt #%d actor %d ->' % (i, h), vals)
        gdb.execute('continue', to_string=True)
    except gdb.error as e:
        print('>> end', e); break
end
