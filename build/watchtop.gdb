# gdb -batch -x build/watchtop.gdb --args <exe>
# Inside lua_dofile, watches L->top (L[7]) and reports each change with the writing function
# until the value stops being sane (a pointer outside the Lua stack block).
python
import gdb
gdb.execute('set pagination off')
b = gdb.Breakpoint('lua_dofile'); gdb.execute('run'); b.delete()
L = int(gdb.parse_and_eval('(unsigned)PTR_1002bf6c')) & 0xffffffff
base = int(gdb.parse_and_eval('*(unsigned*)(0x%x+0x20)' % L)) & 0xffffffff
gdb.execute('watch *(unsigned*)0x%x' % (L + 0x1c))
n = 0
while n < 4000:
    try:
        gdb.execute('continue', to_string=True)
    except gdb.error:
        break
    f = gdb.newest_frame(); name = f.name() or '?'
    if 'ZwClose' in name or 'NtClose' in name:
        gdb.execute('signal 0', to_string=True); continue
    top = int(gdb.parse_and_eval('*(unsigned*)0x%x' % (L + 0x1c))) & 0xffffffff
    n += 1
    if top < base or top > base + 0x2000:
        print('>> BAD top 0x%x (base 0x%x) written in %s, caller %s' % (top, base, name, f.older().name() if f.older() else '?'))
        gdb.execute('bt 6')
        gdb.execute('x/3i $pc')
        break
print('>> %d top changes checked' % n)
end
