# Dumps the table argument(s) of the `call` builtin (FUN_10003a60)
python
import gdb, struct
gdb.execute('set pagination off')
b = gdb.Breakpoint('Grim_Init'); gdb.execute('run'); b.delete()
gdb.Breakpoint('FUN_10003a60')
gdb.execute('continue')
inf = gdb.selected_inferior()
def rd(a, n): return bytes(inf.read_memory(a, n))
st = struct.unpack('<I', rd(int(gdb.parse_and_eval('(int)&PTR_1002bf6c')) and struct.unpack('<I', rd(int(gdb.parse_and_eval('(int)&PTR_1002bf6c')),4))[0] + 32, 4))[0]
for i in (1, 2, 3, 4):
    o = int(gdb.parse_and_eval('(int)lua_lua2C(%d)' % i))
    if o == 0: print('>> arg', i, 'none'); continue
    a = st - 8 + o * 8
    t, v = struct.unpack('<iI', rd(a, 8))
    print('>> arg %d obj=%d type=%d val=%#x' % (i, o, t, v))
    if t == -3:
        h = struct.unpack('<6I', rd(v, 24))
        print('>>   hash: node=%#x size=%d nuse=%d htag=%d' % (h[2], h[3], h[4], struct.unpack('<i', rd(v+20,4))[0]))
        for k in range(h[3]):
            kt, kv, vt, vv = struct.unpack('<iIiI', rd(h[2] + 16*k, 16))
            if vt != -7:
                print('>>     [%d] key(type %d, %s %g) = (type %d, %#x %g)' % (k, kt, hex(kv), struct.unpack('<f', struct.pack('<I', kv))[0], vt, vv, struct.unpack('<f', struct.pack('<I', vv))[0]))
end
