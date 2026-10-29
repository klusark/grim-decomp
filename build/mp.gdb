set pagination off
set environment _NO_DEBUG_HEAP=1
run
thread 1
python
import gdb, struct
inf = gdb.selected_inferior()
def rd(a, n): return bytes(inf.read_memory(a, n))
tab = int(gdb.parse_and_eval('(unsigned)g_pActorTable'))
a = tab + 5*0xa8
print('>> manny pos', ['%.3f' % x for x in struct.unpack('<3f', rd(a + 0xc, 12))], 'flags', hex(struct.unpack('<I', rd(a + 4, 4))[0]), 'frame', ['%.2f' % x for x in struct.unpack('<9f', rd(a + 0x30, 36))])
cnt = struct.unpack('<I', rd(int(gdb.parse_and_eval('(unsigned)&UINT_008a952c')), 4))[0]
print('>> drawlist', cnt)
print('>> setup', int(gdb.parse_and_eval('(int)Lua_GetCurrentSetup')) if False else '')
end
kill
