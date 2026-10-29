set pagination off
run
thread 1
python
import gdb, struct
inf = gdb.selected_inferior()
def rd(a, n): return bytes(inf.read_memory(a, n))
cnt = struct.unpack('<I', rd(int(gdb.parse_and_eval('(int)&UINT_008a952c')), 4))[0]
arr = int(gdb.parse_and_eval('(int)&UINT_008c9568'))
print('>> drawlist count', cnt)
for i in range(min(cnt, 20)):
    p = struct.unpack('<I', rd(arr + 4*i, 4))[0]
    e = struct.unpack('<IfI', rd(p, 12))
    print('>>  entry', i, hex(p), e)
tab = int(gdb.parse_and_eval('*(unsigned*)&g_pActorTable'))
n = 0
for i in range(0, 60):
    a = tab + i*0xa8
    w = struct.unpack('<42I', rd(a, 168))
    if w[0] or w[1]:
        n += 1
        print('>> actor', i, 'flags4=%x pos=%s cost=%x set=%s' % (w[1], struct.unpack('<3f', rd(a+0xc, 12)), w[0x28], w[0x29]))
end
kill
