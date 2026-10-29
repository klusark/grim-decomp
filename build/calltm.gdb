python
import gdb
gdb.execute('set pagination off')
b = gdb.Breakpoint('lua_open'); gdb.execute('run'); b.delete(); gdb.execute('finish', to_string=True)
for fn in ('*lapi__25f0', '*luaD_call'):
    gdb.Breakpoint(fn)
def L():
    return int(gdb.parse_and_eval('(unsigned)PTR_1002bf6c')) & 0xffffffff
def rd(a):
    return int(gdb.parse_and_eval('*(unsigned *)0x%x' % a)) & 0xffffffff
gdb.execute('continue')
for i in range(12):
    f = gdb.newest_frame(); name = f.name() or '?'
    if 'ZwClose' in name or 'NtClose' in name:
        gdb.execute('return'); gdb.execute('set $eax=0'); gdb.execute('signal 0'); continue
    if name not in ('lapi__25f0', 'luaD_call'):
        print('>> stopped in', name); break
    esp = int(gdb.parse_and_eval('$esp')) & 0xffffffff
    a = [rd(esp + 4 * k) for k in (1, 2, 3)]
    l = L()
    top, base = rd(l + 0x1c), rd(l + 0x20)
    print('>> %s args=%s depth=%d (top=%x base=%x)' % (name, ['%x' % x for x in a], (top - base) >> 3, top, base))
    gdb.execute('continue')
end
