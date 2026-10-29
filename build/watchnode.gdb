# Two phases: find the address of node[1].value of the table given to `call`, then rerun with a watchpoint on it.
python
import gdb, struct, os
gdb.execute('set pagination off')
inf = lambda: gdb.selected_inferior()
def rd(a, n): return bytes(inf().read_memory(a, n))
addr = os.environ.get('NODEADDR')
b = gdb.Breakpoint('Grim_Init'); gdb.execute('run'); b.delete()
if not addr:
    gdb.Breakpoint('FUN_10003a60'); gdb.execute('continue')
    p = struct.unpack('<I', rd(int(gdb.parse_and_eval('(int)&PTR_1002bf6c')), 4))[0]
    st = struct.unpack('<I', rd(p + 32, 4))[0]
    o = int(gdb.parse_and_eval('(int)lua_lua2C(2)'))
    t, v = struct.unpack('<iI', rd(st - 8 + o * 8, 8))
    node = struct.unpack('<I', rd(v + 8, 4))[0]
    print('>> NODEADDR=%#x' % (node + 16 * 1 + 8))
else:
    a = int(addr, 16)
    gdb.execute('watch *(int*)%#x' % (a + 4))
    gdb.execute('watch *(int*)%#x' % a)
    gdb.Breakpoint('luaD_message')
    for _ in range(20):
        try: gdb.execute('continue', to_string=True)
        except gdb.error: break
        f = gdb.newest_frame()
        print('>> hit', f.name(), 'val now', gdb.parse_and_eval('*(int*)%#x' % a), gdb.parse_and_eval('*(int*)%#x' % (a+4)))
        gdb.execute('bt 4')
        if f.name() == 'luaD_message': break
end
