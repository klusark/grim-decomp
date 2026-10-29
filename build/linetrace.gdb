# gdb -batch -x build/linetrace.gdb --args <exe>
# Steps through EngineModule_Init line by line (stepping over calls) and
# prints each executed source line, so the branch that produces its result is
# visible. Set FUNC in the environment to trace another function.
python
import gdb, os
gdb.execute('set pagination off')
func = os.environ.get('FUNC', 'EngineModule_Init')
gdb.Breakpoint(func)
gdb.execute('run')
for i in range(400):
    try:
        f = gdb.newest_frame()
        if (f.name() or '') != func:
            print('>> left', func, '-> now in', f.name(), 'eax =', hex(int(gdb.parse_and_eval('$eax')) & 0xffffffff))
            break
        sal = f.find_sal()
        line = sal.line
        text = ''
        try:
            text = gdb.execute('list %d,%d' % (line, line), to_string=True).strip()
        except gdb.error:
            pass
        print('>> %s' % text[:150])
        gdb.execute('next', to_string=True)
    except gdb.error as e:
        print('error', e)
        break
end
