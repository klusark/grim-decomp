# Opcode + C-builtin trace of the Lua VM after the Nth Lua error (env ERRN, default 5) until the
# process ends or the next error; prints the last N (default 60) entries.
python
import gdb, struct, collections, os
gdb.execute('set pagination off')
b = gdb.Breakpoint('Grim_Init'); gdb.execute('run'); b.delete()
gdb.Breakpoint('luaD_message')
ERRN = int(os.environ.get('ERRN', '5'))
for i in range(ERRN):
    gdb.execute('continue', to_string=True)
bp = gdb.Breakpoint('lvm.c:577')
cb = gdb.Breakpoint('ldo__44e0')
inf = gdb.selected_inferior()
def rd(a, n): return bytes(inf.read_memory(a, n))
hist = collections.deque(maxlen=int(os.environ.get('N', '60')))
cnt = 0
while True:
    try: gdb.execute('continue', to_string=True)
    except gdb.error: break
    try: f = gdb.newest_frame()
    except gdb.error: break
    nm = f.name()
    if nm == 'luaD_message':
        hist.append('--- Lua error'); break
    cnt += 1
    if nm == 'ldo__44e0':
        fn = int(gdb.parse_and_eval('*(int*)($ebp+8)'))
        hist.append('   C call %s' % gdb.execute('info symbol %d' % fn, to_string=True).strip().split(' in ')[0]); continue
    pc = int(gdb.parse_and_eval('(int)pbVar2'))
    ob = rd(pc, 4)
    p = struct.unpack('<I', rd(int(gdb.parse_and_eval('(int)&PTR_1002bf6c')), 4))[0]
    top, base = struct.unpack('<II', rd(p + 28, 8))
    hist.append('%#x op=%d [%s] depth=%d' % (pc, ob[0], ob[1:4].hex(), (top - base) // 8))
print('>> ops after error', ERRN, ':', cnt)
for h in hist: print('>>', h)
end
