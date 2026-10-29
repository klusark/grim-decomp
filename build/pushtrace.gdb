python
import gdb, collections
gdb.execute('set pagination off')
b = gdb.Breakpoint('Grim_Init'); gdb.execute('run'); b.delete()
gdb.Breakpoint('luaD_message')
gdb.Breakpoint('lua_pushnumber')
hist = collections.deque(maxlen=25)
while True:
    try: gdb.execute('continue', to_string=True)
    except gdb.error: break
    nm = gdb.newest_frame().name()
    if nm == 'luaD_message': break
    v = gdb.parse_and_eval('*(float*)($ebp+8)')
    caller = gdb.newest_frame().older().name()
    hist.append('%s <- %s' % (v, caller))
for h in hist: print('>>', h)
end
