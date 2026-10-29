# FUNC=<f1,f2,...> [ARGS=<n>] [HITS=<n>] gdb -batch -x build/rettrace.gdb --args <exe>
# Logs every call of the listed functions with their first ARGS stack arguments
# and the value they return (eax), until the program faults or exits.
python
import gdb, os
gdb.execute('set pagination off')
funcs = os.environ.get('FUNC', 'lua_ref').split(',')
nargs = int(os.environ.get('ARGS', '2'))
cap = int(os.environ.get('HITS', '300'))
for fn in funcs:
    gdb.Breakpoint(fn)
gdb.execute('run')
hits = 0
while hits < cap:
    try:
        f = gdb.newest_frame()
        name = f.name() or '?'
    except gdb.error:
        break
    if 'ZwClose' in name or 'NtClose' in name:
        gdb.execute('return'); gdb.execute('set $eax = 0'); gdb.execute('signal 0'); continue
    if name not in funcs:
        print('>> stopped in', name)
        gdb.execute('bt 6')
        break
    hits += 1
    # after the prologue: the arguments sit above the saved frame
    try:
        ebp = int(gdb.parse_and_eval('$ebp')) & 0xffffffff
        args = [int(gdb.parse_and_eval('*(unsigned int *)(%d + %d)' % (ebp, 8 + 4 * i))) & 0xffffffff for i in range(nargs)]
    except gdb.error:
        args = []
    caller = f.older().name() if f.older() is not None else '?'
    try:
        gdb.execute('finish', to_string=True)
        eax = int(gdb.parse_and_eval('$eax')) & 0xffffffff
        print('>> %3d %s(%s) from %s -> 0x%x' % (hits, name, ', '.join('0x%x' % a for a in args), caller, eax))
    except gdb.error as e:
        print('>> %3d %s(%s) from %s -> finish failed: %s' % (hits, name, ', '.join('0x%x' % a for a in args), caller, e))
        break
    try:
        gdb.execute('continue')
    except gdb.error as e:
        print('continue failed', e)
        break
end
