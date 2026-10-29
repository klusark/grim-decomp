set pagination off
run
python
import gdb, struct
inf = gdb.selected_inferior()
def rd(a, n): return bytes(inf.read_memory(a, n))
gdb.execute('thread 1')
def obj(idx):
    p = struct.unpack('<I', rd(int(gdb.parse_and_eval('(int)&PTR_1002bf6c')), 4))[0]
    st = struct.unpack('<I', rd(p + 32, 4))[0]
    t, v = struct.unpack('<iI', rd(st - 8 + idx * 8, 8))
    s = ''
    if t == -2:
        try:
            a = v + 0x14
            b = rd(a, 40); s = b.split(b'\0')[0].decode('latin-1')
        except Exception: s = '?'
    if t == -1: s = str(struct.unpack('<f', struct.pack('<I', v))[0])
    return (t, hex(v), s)
for lvl in range(1, 7):
    o = int(gdb.parse_and_eval('(int)lua_stackedfunction(%d)' % lvl))
    if o < 0: break
    print('>> level', lvl, 'func obj', o, [obj(o + k) for k in range(1, 4)])
end
