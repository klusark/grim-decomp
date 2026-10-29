# gdb -batch -x build/watchbase.gdb --args <exe>
# After lua_open, watches the Lua state's stack base (L[8]) and top (L[7]) and
# prints each change with the writing function.
python
import gdb
gdb.execute('set pagination off')
bp = gdb.Breakpoint('lua_open')
gdb.execute('run')
bp.delete()
gdb.execute('finish', to_string=True)
L = int(gdb.parse_and_eval('(unsigned)PTR_1002bf6c')) & 0xffffffff
print('>> L = 0x%x  base = 0x%x  top = 0x%x' % (L, int(gdb.parse_and_eval('*(unsigned *)(0x%x+0x20)' % L)) & 0xffffffff, int(gdb.parse_and_eval('*(unsigned *)(0x%x+0x1c)' % L)) & 0xffffffff))
gdb.execute('x/8wx *(unsigned *)(0x%x+0x20)' % L)
gdb.execute('watch *(unsigned int *)0x%x' % (L + 0x20))
for i in range(12):
    try:
        gdb.execute('continue')
    except gdb.error as e:
        print('continue failed', e); break
    f = gdb.newest_frame()
    name = f.name() or '?'
    if 'ZwClose' in name or 'NtClose' in name:
        gdb.execute('return'); gdb.execute('set $eax = 0'); gdb.execute('signal 0'); continue
    base = int(gdb.parse_and_eval('*(unsigned *)(0x%x+0x20)' % L)) & 0xffffffff
    top = int(gdb.parse_and_eval('*(unsigned *)(0x%x+0x1c)' % L)) & 0xffffffff
    print('>> in %s  base = 0x%x top = 0x%x' % (name, base, top))
    gdb.execute('bt 4')
    gdb.execute('x/6wx 0x%x' % (base - 8))
end
