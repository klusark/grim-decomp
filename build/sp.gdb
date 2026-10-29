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
ex = struct.unpack('<I', rd(a + 0xa4, 4))[0]
print('>> extra', hex(ex))
w = struct.unpack('<24I', rd(ex + 0x1c0, 96))
print('>> +1c0..', [hex(x) for x in w])
print('>> str', rd(ex + 0x1d0, 12))
print('>> talking count', int(gdb.parse_and_eval('(int)g_nTalkingActorCount')))
tl = int(gdb.parse_and_eval('(unsigned)g_pTextObjectList'))
print('>> textobjs', hex(tl))
if tl:
    t = struct.unpack('<8I', rd(tl, 32)); print('>> t', [hex(x) for x in t])
    print('>> flags', hex(struct.unpack('<I', rd(tl + 0x96*4, 4))[0]), 'timer', struct.unpack('<i', rd(tl + 0x94*4, 4)))
end
kill
