set pagination off
run
thread 1
python
import gdb, struct
inf = gdb.selected_inferior()
def rd(a, n): return bytes(inf.read_memory(a, n))
tab = int(gdb.parse_and_eval('*(unsigned*)&g_pActorTable'))
cur = int(gdb.parse_and_eval('(unsigned)Set_GetCurrent()'))
print('>> table', hex(tab), 'curset', hex(cur))
lst = struct.unpack('<I', rd(cur + 0x1abc, 4))[0]
print('>> setup', hex(lst))
n = struct.unpack('<I', rd(lst + 0x80, 4))[0]
cnt = 0
while n and cnt < 50:
    idx = struct.unpack('<I', rd(n, 4))[0]
    a = tab + idx * 0xa8
    flags = struct.unpack('<I', rd(a + 4, 4))[0]
    pos = struct.unpack('<3f', rd(a + 0xc, 12))
    print('>> actor idx', idx, 'flags %#x' % flags, 'pos', pos, 'costume', hex(struct.unpack('<I', rd(a + 0xa0, 4))[0]))
    n = struct.unpack('<I', rd(n + 8, 4))[0]; cnt += 1
print('>> actors in current setup list', cnt)
end
