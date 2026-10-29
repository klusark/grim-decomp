# gdb -batch -x build/run.gdb --args <exe> : runs the game, steps over the
# debugger-only STATUS_INVALID_HANDLE exceptions (RegCloseKey on a key that
# failed to open), and prints a backtrace at the first real crash.
python
import gdb
gdb.execute('set pagination off')
gdb.execute('run')
for i in range(200):
    try:
        f = gdb.newest_frame()
        name = f.name() or ''
    except gdb.error:
        break
    if 'ZwClose' in name or 'NtClose' in name:
        gdb.execute('return')
        gdb.execute('set $eax = 0')
        gdb.execute('signal 0')  # resume without delivering the exception
        continue
    break
try:
    gdb.execute('bt 12')
except gdb.error as e:
    print('no stack:', e)
try:
    gdb.execute('x/3i $pc')
    gdb.execute('info registers eax ebx ecx edx esi edi')
except gdb.error:
    pass
end
