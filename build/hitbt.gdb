# FUNC=<function> [ARGS=<n>] [HITS=<n>] [BT=<depth>] gdb -batch -x build/hitbt.gdb --args <exe>
# Logs every call of FUNC with its return address (resolved to a function), the
# first ARGS stack arguments and a short backtrace, until the program faults
# or exits. Use it when `bt` at the fault cannot name the caller (SEH frames).
python
import gdb, os
gdb.execute('set pagination off')
func = os.environ.get('FUNC', 'luaD_call')
nargs = int(os.environ.get('ARGS', '3'))
cap = int(os.environ.get('HITS', '400'))
depth = int(os.environ.get('BT', '6'))

def where(pc):
    try:
        b = gdb.block_for_pc(pc)
        while b is not None and b.function is None:
            b = b.superblock
        if b is not None:
            sal = gdb.find_pc_line(pc)
            return '%s (%s:%d)' % (b.function.name, os.path.basename(sal.symtab.filename) if sal.symtab else '?', sal.line)
    except gdb.error:
        pass
    try:
        return gdb.execute('info symbol 0x%x' % pc, to_string=True).strip()
    except gdb.error:
        return '?'

# the function may live in a DLL that is not mapped before `run`: break by name
# first, then move the breakpoint to the first instruction (*func), where *$esp
# is still the return address
first = gdb.Breakpoint(func)
gdb.execute('run')
first.delete()
gdb.Breakpoint('*' + func)
hits = 0
try:
    f = gdb.newest_frame()
    if (f.name() or '') == func:
        print('>> hit   0 %s (prologue breakpoint)' % func)
        gdb.execute('bt %d' % depth)
    gdb.execute('continue')
except gdb.error as e:
    print('first continue failed', e)
while hits < cap:
    try:
        f = gdb.newest_frame()
        name = f.name() or '?'
    except gdb.error:
        break
    if 'ZwClose' in name or 'NtClose' in name:
        gdb.execute('return'); gdb.execute('set $eax = 0'); gdb.execute('signal 0'); continue
    if name != func:
        print('>> stopped in', name)
        gdb.execute('x/4i $pc')
        gdb.execute('bt 8')
        break
    hits += 1
    ret = int(gdb.parse_and_eval('*(unsigned int *)$esp')) & 0xffffffff
    args = [int(gdb.parse_and_eval('*(unsigned int *)($esp + %d)' % (4 * (i + 1)))) & 0xffffffff for i in range(nargs)]
    print('>> hit %3d %s(%s) from 0x%08x %s' % (hits, func, ', '.join('0x%x' % a for a in args), ret, where(ret)))
    if depth:
        gdb.execute('bt %d' % depth)
    try:
        gdb.execute('continue')
    except gdb.error as e:
        print('continue failed', e)
        break
end
