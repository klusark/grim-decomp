# gdb -batch -x build/steptrace2.gdb --args <exe>
# Runs to Win_SetWindowedSize, then to the next window-procedure call, and
# single-steps from there logging each function transition until the fault.
python
import gdb
gdb.execute('set pagination off')
gdb.Breakpoint('Win_SetWindowedSize')
gdb.execute('run')
b = gdb.Breakpoint('Win_KernelWndProc@16')
gdb.execute('continue')
try:
    msg = int(gdb.parse_and_eval('*(unsigned int *)($ebp+12)')) & 0xffffffff
    wp = int(gdb.parse_and_eval('*(unsigned int *)($ebp+16)')) & 0xffffffff
    print('>> window procedure entered with msg=0x%x wParam=0x%x' % (msg, wp))
except gdb.error as e:
    print('args unavailable', e)
b.delete()
last = None
for steps in range(1, 20000):
    try:
        gdb.execute('stepi', to_string=True)
    except gdb.error as e:
        print('stepi failed:', e)
        break
    try:
        f = gdb.newest_frame()
        name = f.name() or ('?%x' % int(gdb.parse_and_eval('$pc')))
    except gdb.error:
        print('no frame')
        break
    if name != last:
        pc = int(gdb.parse_and_eval('$pc')) & 0xffffffff
        print('>> step %5d  %-34s pc=0x%08x' % (steps, name, pc))
        last = name
        if name == 'lua_getnumber' or name.startswith('?'):
            gdb.execute('x/4i $pc')
            break
end
