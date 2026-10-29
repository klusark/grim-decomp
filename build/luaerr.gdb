# gdb -batch -x build/luaerr.gdb --args <exe>
# Reports each Lua error (message plus the script file:line of the first Lua frames) and
# then the first native fault, if any. Needs the Lua DLL's debug API (lua_stackedfunction,
# lua_funcinfo), which the game ships.
python
import gdb
gdb.execute('set pagination off')
b = gdb.Breakpoint('Grim_Init'); gdb.execute('run'); b.delete()
gdb.Breakpoint('luaD_message')
count = 0
while count < 40:
    try:
        gdb.execute('continue', to_string=True)
    except gdb.error:
        break
    f = gdb.newest_frame()
    if (f.name() or '') != 'luaD_message':
        print('>> native fault in', f.name()); gdb.execute('bt 6'); break
    count += 1
    msg = gdb.execute('x/s *(char**)($esp+4)', to_string=True).strip()
    print('>> Lua error #%d: %s' % (count, msg))
    sp = int(gdb.parse_and_eval('(int)$esp')) - 2048
    for lvl in range(1, 5):
        try:
            o = int(gdb.parse_and_eval('(int)lua_stackedfunction(%d)' % lvl))
            if o < 0: break
            gdb.execute('set *(int*)%d = 0' % sp); gdb.execute('set *(int*)%d = 0' % (sp + 8))
            gdb.parse_and_eval('(int)lua_funcinfo(%d,%d,%d)' % (o, sp, sp + 8))
            name = gdb.execute('x/s *(int*)%d' % sp, to_string=True).split('\t', 1)[-1].strip()
            line = int(gdb.parse_and_eval('*(int*)%d' % (sp + 8)))
            print('>>    level %d: %s defined at line %d' % (lvl, name, line))
        except gdb.error as e:
            print('>>    level', lvl, 'unavailable'); break
end
