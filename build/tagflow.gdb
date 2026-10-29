python
import gdb, struct
gdb.execute('set pagination off')
b = gdb.Breakpoint('Grim_Init'); gdb.execute('run'); b.delete()
for f in ('FUN_10003a30', 'FUN_10003a60', 'FUN_10003d50', 'FUN_10003d10', 'FUN_10003930', 'FUN_100037d0'):
    gdb.Breakpoint(f)
gdb.Breakpoint('luaD_message')
inf = gdb.selected_inferior()
def rd(a, n): return bytes(inf.read_memory(a, n))
def stackbase():
    p = struct.unpack('<I', rd(int(gdb.parse_and_eval('(int)&PTR_1002bf6c')), 4))[0]
    return struct.unpack('<I', rd(p + 32, 4))[0]
def show(o):
    st = stackbase(); a = st - 8 + o * 8
    t, v = struct.unpack('<iI', rd(a, 8))
    return 'type=%d val=%#x(%g)' % (t, v, struct.unpack('<f', struct.pack('<I', v))[0])
for _ in range(40):
    try: gdb.execute('continue', to_string=True)
    except gdb.error: break
    nm = gdb.newest_frame().name()
    if nm == 'luaD_message':
        print('>> ERROR', gdb.execute('x/s *(char**)($ebp+8)', to_string=True).strip()); break
    args = []
    for i in (1, 2, 3, 4):
        o = int(gdb.parse_and_eval('(int)lua_lua2C(%d)' % i))
        args.append('none' if o == 0 else '%d:%s' % (o, show(o)))
    print('>>', nm, args)
end
