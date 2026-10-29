set pagination off
break Lua_UpdateFrame
run
delete
python
import gdb, struct
inf = gdb.selected_inferior()
def rd(a, n): return bytes(inf.read_memory(a, n))
tab = int(gdb.parse_and_eval('*(unsigned*)&g_pActorTable'))
for idx in (5, 539, 541, 543, 547):
    a = tab + idx*0xa8
    pos = struct.unpack('<3f', rd(a + 0xc, 12))
    buf = int(gdb.parse_and_eval('(int)malloc(64)'))
    inf.write_memory(buf, struct.pack('<3f', *pos))
    r = int(gdb.parse_and_eval('(int)rdCamera_ProjectPoint(%d, %d)' % (buf, buf + 16)))
    out = struct.unpack('<3f', rd(buf + 16, 12))
    print('>> actor', idx, 'pos', pos, 'ret', r, 'screen', out)
cam = int(gdb.parse_and_eval('*(unsigned*)&g_pCameraSetup'))
print('>> camsetup', struct.unpack('<3f', rd(cam, 12)))
end
kill
