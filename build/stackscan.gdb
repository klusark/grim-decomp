# gdb -batch -x build/stackscan.gdb --args <exe>
# run.gdb plus a raw scan of the stack at the crash: every word that points
# into code is printed with its symbol, for when the frame chain is broken.
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
        gdb.execute('signal 0')
        continue
    break
try:
    gdb.execute('bt 6')
except gdb.error as e:
    print('no stack', e)
try:
    esp = int(gdb.parse_and_eval('$esp'))
    for k in range(0, 160):
        a = esp + 4 * k
        try:
            v = int(gdb.parse_and_eval('*(unsigned int *)%d' % a))
        except gdb.error:
            break
        try:
            s = gdb.execute('info symbol 0x%x' % v, to_string=True).strip()
        except gdb.error:
            s = ''
        if s and 'No symbol' not in s:
            print('  [esp+0x%03x] 0x%08x  %s' % (4 * k, v, s[:90]))
except gdb.error as e:
    print('scan failed', e)
end
