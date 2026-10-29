# gdb -batch -x build/trace.gdb --args <exe>: like run.gdb but also reports every
# hit of a few milestone functions (and of exit) with a short backtrace, so an
# early silent exit can be located.
python
import gdb
gdb.execute('set pagination off')
for b in ['exit', 'ExitProcess', 'Win_CreateMainWindow', 'Win_PumpMessages', 'Engine_OpenRenderer',
          'Grim_ShowSplash', 'Lua_RunSystemScript', 'Engine_RunSystemScript', 'Engine_ShutdownGame', 'MessageBoxA']:
    try:
        gdb.execute('break ' + b)
    except gdb.error as e:
        print('no breakpoint:', b)
gdb.execute('run')
for i in range(400):
    try:
        f = gdb.newest_frame()
        name = f.name() or ''
    except gdb.error:
        break
    if 'ZwClose' in name or 'NtClose' in name:
        gdb.execute('return')
        gdb.execute('set $eax = 0')
        gdb.execute('signal 0')
        continue
    print('=== stopped in', name)
    try:
        gdb.execute('bt 8')
    except gdb.error as e:
        print('no stack:', e)
        break
    if name in ('exit', 'ExitProcess') or 'MessageBox' in name:
        try:
            gdb.execute('info args')
        except gdb.error:
            pass
    try:
        gdb.execute('continue')
    except gdb.error:
        break
end
