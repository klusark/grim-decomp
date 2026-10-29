# gdb -batch -x build/ccalls.gdb --args <exe>      (env ERRN=n stops at the nth Lua error, N=history length)
# Logs the C builtins the Lua VM calls (ldo__44e0 = callC) up to the nth Lua error.
python
import gdb, collections, os
gdb.execute('set pagination off')
b = gdb.Breakpoint('Grim_Init'); gdb.execute('run'); b.delete()
gdb.Breakpoint('luaD_message')
gdb.Breakpoint('ldo__44e0')
ERRN = int(os.environ.get('ERRN', '1'))
errs = 0
hist = collections.deque(maxlen=int(os.environ.get('N', '40')))
while True:
    try:
        gdb.execute('continue', to_string=True)
    except gdb.error:
        break
    f = gdb.newest_frame()
    n = f.name() or '?'
    if n == 'luaD_message':
        errs += 1
        hist.append('--- Lua error #%d' % errs)
        if errs >= ERRN: break
        continue
    fn = int(gdb.parse_and_eval('*(int*)($ebp+8)'))
    sym = gdb.execute('info symbol %d' % fn, to_string=True).strip()
    hist.append('%x %s base=%s' % (fn, sym.split(' in ')[0], gdb.parse_and_eval('*(int*)($ebp+12)')))
for h in hist: print('>>', h)
end
