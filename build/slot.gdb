set pagination off
break Lua_PutActorAt
run
python
import gdb, struct
inf = gdb.selected_inferior()
p = struct.unpack('<I', bytes(inf.read_memory(int(gdb.parse_and_eval('(int)&PTR_1002bf6c')), 4)))[0]
st = struct.unpack('<I', bytes(inf.read_memory(p + 32, 4)))[0]
for n in range(1, 5):
    idx = int(gdb.parse_and_eval('(int)lua_lua2C(%d)' % n))
    a = st - 8 + idx*8
    tag, val = struct.unpack('<iI', bytes(inf.read_memory(a, 8)))
    print('>> arg', n, 'idx', idx, hex(a), 'tag', tag, 'val', hex(val))
end
kill
