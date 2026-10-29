# For the last luaH_set(table, key 1.0) calls before the first `call` builtin: watch the returned slot for writes.
python
import gdb, struct
gdb.execute('set pagination off')
inf = gdb.selected_inferior
def rd(a, n): return bytes(inf().read_memory(a, n))
b = gdb.Breakpoint('Grim_Init'); gdb.execute('run'); b.delete()
bs = gdb.Breakpoint('luaH_set')
bc = gdb.Breakpoint('FUN_10003a60')
bm = gdb.Breakpoint('luaD_message')
slot = None
last = None
for _ in range(100000):
    try: gdb.execute('continue', to_string=True)
    except gdb.error: break
    f = gdb.newest_frame().name()
    if f == 'luaD_message':
        print('>> error reached'); break
    if f == 'FUN_10003a60':
        print('>> call builtin reached; last 1.0-set slot', last); break
    tab = int(gdb.parse_and_eval('*(int*)($ebp+8)')); kp = int(gdb.parse_and_eval('*(int*)($ebp+12)'))
    kt, kv = struct.unpack('<iI', rd(kp, 8))
    if kt == -1 and kv == 0x3f800000:
        # finish to get the slot
        bs.enabled = False
        gdb.execute('finish', to_string=True)
        slot = int(gdb.parse_and_eval('(int)$eax'))
        last = slot
        print('>> luaH_set(table %#x, 1.0) -> slot %#x' % (tab, slot))
        bs.enabled = True
print('>> done scan')
end
