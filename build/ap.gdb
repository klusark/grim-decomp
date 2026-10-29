set pagination off
run
thread 1
python
import gdb, struct
inf = gdb.selected_inferior()
def rd(a, n): return bytes(inf.read_memory(a, n))
tab = int(gdb.parse_and_eval('(unsigned)g_pActorTable'))
for idx in (5, 539, 541, 543, 547, 884):
    a = tab + idx*0xa8
    print('>> actor', idx, 'pos', ['%.3f' % x for x in struct.unpack('<3f', rd(a + 0xc, 12))], 'rot', ['%.3f' % x for x in struct.unpack('<3f', rd(a + 0x18, 12))])
cs = int(gdb.parse_and_eval('(unsigned)g_pCameraSetup'))
print('>> tab', hex(tab))
print('>> cs', hex(cs), ['%.3f' % x for x in struct.unpack('<24f', rd(cs, 96))])
end
kill
