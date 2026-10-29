# gdb -batch -x build/luacrash.gdb --args <exe>
# Runs to the first fault and dumps the Lua 3.1 state: L (PTR_1002bf6c), its
# stack (fields 7..9), the tag-method table (DAT_1002bf48) and the stack slot
# luaD_call was about to call.
python
import gdb
gdb.execute('set pagination off')
gdb.execute('run')
for i in range(50):
    f = gdb.newest_frame()
    name = f.name() or '?'
    if 'ZwClose' in name or 'NtClose' in name:
        gdb.execute('return'); gdb.execute('set $eax = 0'); gdb.execute('signal 0'); continue
    break
print('>> stopped in', name)
gdb.execute('info locals')
L = int(gdb.parse_and_eval('(unsigned)PTR_1002bf6c')) & 0xffffffff
print('>> L = 0x%x' % L)
gdb.execute('x/14wx 0x%x' % L)
tm = int(gdb.parse_and_eval('(unsigned)DAT_1002bf48')) & 0xffffffff
print('>> TMtable DAT_1002bf48 = 0x%x' % tm)
stack = int(gdb.parse_and_eval('*(unsigned *)(0x%x + 0x20)' % L)) & 0xffffffff
top = int(gdb.parse_and_eval('*(unsigned *)(0x%x + 0x1c)' % L)) & 0xffffffff
print('>> stack = 0x%x top = 0x%x  (%d objects)' % (stack, top, (top - stack) // 8))
gdb.execute('x/%dwx 0x%x' % (min(48, max(2, (top - stack) // 4 + 4)), stack))
try:
    print('>> eax (effective tag) =', hex(int(gdb.parse_and_eval('$eax')) & 0xffffffff))
except gdb.error:
    pass
end
