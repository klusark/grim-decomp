# gdb -batch -x build/msgtrace.gdb --args <exe>
# Logs every message reaching the window procedure (decorated stdcall symbol)
# and every hook call until the crash, and prints the window's procedure
# pointer before the display switch.
python
import gdb
gdb.execute('set pagination off')
names = {}
for s in ['Win_KernelWndProc@16', 'Win_WndProc', 'FUN_004772d0', 'Win_SetWindowedSize', 'Display_Select']:
    try:
        b = gdb.Breakpoint(s)
        names[b.number] = s
    except gdb.error as e:
        print('no symbol', s, e)
gdb.execute('run')
n = 0
while n < 600:
    n += 1
    try:
        f = gdb.newest_frame()
        name = f.name() or '?'
    except gdb.error:
        break
    if 'ZwClose' in name or 'NtClose' in name:
        gdb.execute('return'); gdb.execute('set $eax = 0'); gdb.execute('signal 0'); continue
    if name in ('Win_KernelWndProc@16', 'Win_WndProc', 'FUN_004772d0'):
        try:
            msg = int(gdb.parse_and_eval('*(unsigned int *)($esp+8)')) & 0xffffffff
            wp = int(gdb.parse_and_eval('*(unsigned int *)($esp+12)')) & 0xffffffff
        except gdb.error:
            msg = wp = -1
        print('>> %s msg=0x%x wParam=0x%x' % (name, msg, wp))
    elif name in ('Win_SetWindowedSize', 'Display_Select'):
        try:
            gdb.execute('p (void *)GetWindowLongA((int)g_pWinMainHwnd, -4)')
        except gdb.error as e:
            print('wndproc query failed', e)
        print('>>', name)
    else:
        print('>> stopped in', name)
        gdb.execute('bt 6')
        break
    try:
        gdb.execute('continue')
    except gdb.error:
        break
end
