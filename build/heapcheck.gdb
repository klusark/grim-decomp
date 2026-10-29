# [FUNCS=f1,f2,...] gdb -batch -x build/heapcheck.gdb --args <exe>
# Validates the process heap (HeapValidate) at every game allocation/free and at
# each function in FUNCS, and reports the first hit after which the heap is
# corrupt, with the previous good hit's backtrace: the corrupting write
# happened between the two.
python
import gdb, os
gdb.execute('set pagination off')
gdb.execute('set unwindonsignal on')
watch = ([] if os.environ.get('NOMEM') else ['stdMemory_Alloc', 'stdMemory_Free']) + [f for f in os.environ.get('FUNCS', '').split(',') if f]
for fn in watch:
    try: gdb.Breakpoint(fn)
    except gdb.error: print('no', fn)
gdb.execute('run')
last = None
n = 0
while n < 40000:
    f = gdb.newest_frame(); name = f.name() or '?'
    if 'ZwClose' in name or 'NtClose' in name:
        gdb.execute('return'); gdb.execute('set $eax=0'); gdb.execute('signal 0'); continue
    if name not in watch:
        print('>> stopped in', name, 'after', n, 'checks'); gdb.execute('bt 8'); break
    n += 1
    try:
        ok = int(gdb.parse_and_eval('(int)HeapValidate((void*)GetProcessHeap(),0,0)'))
    except gdb.error:
        ok = 0
    bt = '%s\n%s' % (name, gdb.execute('bt 4', to_string=True))
    if not ok:
        print('>> HEAP CORRUPT at check', n)
        print('>> previous good hit:\n' + (last or '(none)'))
        print('>> this hit:\n' + bt)
        break
    last = bt
    gdb.execute('continue')
end
