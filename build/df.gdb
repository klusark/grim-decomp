set pagination off
set environment _NO_DEBUG_HEAP=1
break Lua_MakeCurrentSet
run
python
import gdb, struct
inf = gdb.selected_inferior()
def rd(a, n): return bytes(inf.read_memory(a, n))
a = int(gdb.parse_and_eval('(unsigned)&DAT_004d5370'))
w = struct.unpack('<8I', rd(a, 32))
print('>> dfKeyboard', hex(a), [hex(x) for x in w])
rg = w[5]
for i in range(4):
    o = struct.unpack('<4I', rd(rg + i*16, 16))
    print('>>  odf', i, [hex(x) for x in o])
    if o[0]:
        print('>>    guid', rd(o[0], 16).hex())
print('>> last', [hex(x) for x in struct.unpack('<4I', rd(rg + 255*16, 16))])
end
kill
