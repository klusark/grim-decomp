set pagination off
set breakpoint pending on
break Lua_LoadActor
python
import gdb
gdb.execute('run')
def dump(tag):
    sp = int(gdb.parse_and_eval('(int)$esp')) - 4096
    out = []
    for lvl in range(1, 14):
        o = int(gdb.parse_and_eval('(int)lua_stackedfunction(%d)' % lvl))
        if o < 0: break
        gdb.execute('set *(int*)%d = 0' % sp); gdb.execute('set *(int*)%d = 0' % (sp + 8))
        gdb.parse_and_eval('(int)lua_funcinfo(%d,%d,%d)' % (o, sp, sp + 8))
        nm = gdb.execute('x/s *(int*)%d' % sp, to_string=True).split('\t', 1)[-1].strip()
        line = int(gdb.parse_and_eval('*(int*)(%d)' % (sp + 8)))
        cur = int(gdb.parse_and_eval('(int)lua_currentline(%d)' % o)) if line >= 0 else -9
        out.append('%s:%d@%d' % (nm, line, cur))
    print('>>', tag, out)
for i in range(1, 400):
    if i in (1, 2, 3, 200, 399): dump('LoadActor #%d' % i)
    try: gdb.execute('continue', to_string=True)
    except gdb.error: break
end
