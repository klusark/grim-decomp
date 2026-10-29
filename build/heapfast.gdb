# gdb -batch -x build/heapfast.gdb --args <exe>
# Fast heap check: validates the process heap at every stdMemory_Alloc / stdMemory_Free
# (cheap bookkeeping only) and, when it first sees corruption, prints the last allocation
# records (size, file, line, caller) so the code that ran in between can be identified.
python
import gdb, collections
gdb.execute('set pagination off')
gdb.execute('set unwindonsignal on')
for fn in ('stdMemory_Alloc', 'stdMemory_Free'):
    gdb.Breakpoint(fn)
gdb.execute('run')
hist = collections.deque(maxlen=6)
n = 0
while n < 200000:
    try:
        f = gdb.newest_frame(); name = f.name() or '?'
    except gdb.error:
        break
    if 'ZwClose' in name or 'NtClose' in name:
        gdb.execute('return'); gdb.execute('set $eax=0'); gdb.execute('signal 0'); continue
    if not name.startswith('stdMemory_'):
        print('>> stopped in', name, 'after', n, 'hits'); gdb.execute('bt 6'); break
    n += 1
    try:
        ok = int(gdb.parse_and_eval('(int)HeapValidate((void*)GetProcessHeap(),0,0)'))
    except gdb.error:
        ok = 0
    if not ok:
        print('>> HEAP CORRUPT at hit', n, 'in', name)
        for h in hist: print('   earlier:', h)
        gdb.execute('bt 6')
        break
    try:
        caller = f.older().name() if f.older() is not None else '?'
    except gdb.error:
        caller = '?'
    try:
        if name == 'stdMemory_Alloc':
            rec = 'alloc size=%s line=%s file=%s caller=%s' % (gdb.parse_and_eval('size'), gdb.parse_and_eval('line'), str(gdb.parse_and_eval('file')).split('"')[1][-30:] if '"' in str(gdb.parse_and_eval('file')) else '?', caller)
        else:
            rec = 'free p=%s caller=%s' % (gdb.parse_and_eval('p'), caller)
    except gdb.error:
        rec = name
    hist.append('#%d %s' % (n, rec))
    gdb.execute('continue')
end
