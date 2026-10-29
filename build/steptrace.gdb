# FUNC=<function> [HIT=<n>] gdb -batch -x build/steptrace.gdb --args <exe>
# Runs to the n-th hit of FUNC, then single-steps logging every function
# transition until the fault (or a step cap). Use when the frame chain is
# broken or a call goes through a bad pointer.
python
import gdb, os
gdb.execute('set pagination off')
func = os.environ.get('FUNC', 'Engine_RegisterSubsystems')
hit = int(os.environ.get('HIT', '1'))
cap = int(os.environ.get('STEPS', '40000'))
gdb.Breakpoint(func)
gdb.execute('run')
for k in range(hit - 1):
    gdb.execute('continue')
print('>> tracing from', func, 'hit', hit)
last = None
for steps in range(1, cap):
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
        print('>> step %5d  %-36s pc=0x%08x' % (steps, name, pc))
        last = name
        if name.startswith('?'):
            gdb.execute('x/3i $pc')
            break
end
