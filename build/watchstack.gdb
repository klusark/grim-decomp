# [VALUE=<hex>] gdb -batch -x build/watchstack.gdb --args <exe>
# After lua_open creates the Lua state, puts a hardware watchpoint on the first
# dword of the Lua stack and reports who writes VALUE (default 0x88, the heap
# header seen there at the fault) into it.
python
import gdb, os
gdb.execute('set pagination off')
value = int(os.environ.get('VALUE', '0x88'), 16)
bp = gdb.Breakpoint('lua_open')
gdb.execute('run')
bp.delete()
gdb.execute('finish', to_string=True)
L = int(gdb.parse_and_eval('(unsigned)PTR_1002bf6c')) & 0xffffffff
stack = int(gdb.parse_and_eval('*(unsigned *)(0x%x + 0x20)' % L)) & 0xffffffff
print('>> L = 0x%x stack = 0x%x' % (L, stack))
gdb.execute('watch *(unsigned int *)0x%x if *(unsigned int *)0x%x == 0x%x' % (stack, stack, value))
for i in range(20):
    try:
        gdb.execute('continue')
    except gdb.error as e:
        print('continue failed', e)
        break
    f = gdb.newest_frame()
    name = f.name() or '?'
    if 'ZwClose' in name or 'NtClose' in name:
        gdb.execute('return'); gdb.execute('set $eax = 0'); gdb.execute('signal 0'); continue
    print('>> stopped in', name)
    gdb.execute('bt 12')
    break
end
