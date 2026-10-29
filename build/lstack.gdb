set pagination off
run
python
import gdb
gdb.execute('thread 1')
sp = int(gdb.parse_and_eval('(int)$esp')) - 4096
for lvl in range(1, 12):
    try:
        o = int(gdb.parse_and_eval('(int)lua_stackedfunction(%d)' % lvl))
        if o < 0: break
        gdb.execute('set *(int*)%d = 0' % sp); gdb.execute('set *(int*)%d = 0' % (sp + 8))
        gdb.parse_and_eval('(int)lua_funcinfo(%d,%d,%d)' % (o, sp, sp + 8))
        name = gdb.execute('x/s *(int*)%d' % sp, to_string=True).split('\t', 1)[-1].strip()
        line = int(gdb.parse_and_eval('*(int*)(%d)' % (sp + 8)))
        cur = int(gdb.parse_and_eval('(int)lua_currentline(%d)' % o))
        print('>> level', lvl, name, 'defined', line, 'current', cur)
    except gdb.error as e:
        print('>> err', e); break
end
