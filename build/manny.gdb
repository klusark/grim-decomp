set pagination off
run
thread 1
python
import gdb, struct
inf = gdb.selected_inferior()
def rd(a, n): return bytes(inf.read_memory(a, n))
def raw(idx):
    p = struct.unpack('<I', rd(int(gdb.parse_and_eval('(int)&PTR_1002bf6c')), 4))[0]
    st = struct.unpack('<I', rd(p + 32, 4))[0]
    return struct.unpack('<iI', rd(st - 8 + idx * 8, 8))
gdb.execute('call (int)lua_beginblock()')
m = int(gdb.parse_and_eval('(int)lua_getglobal("manny")'))
print('>> manny', m, raw(m))
gdb.execute('call (int)lua_pushobject(%d)' % m); gdb.execute('call (int)lua_pushstring("hActor")')
h = int(gdb.parse_and_eval('(int)lua_gettable()')); print('>> hActor', h, raw(h))
handle = int(gdb.parse_and_eval('(int)lua_getuserdata(%d)' % h))
a = int(gdb.parse_and_eval('(int)Actor_FromHandle(%d)' % handle))
print('>> handle', hex(handle), 'actor', hex(a))
tab = int(gdb.parse_and_eval('*(unsigned*)&g_pActorTable'))
words = struct.unpack('<42I', rd(a, 168))
print('>> index', (a - tab) // 0xa8)
for i in range(0, 42, 6): print('>>  +%#04x' % (i*4), ' '.join('%08x' % w for w in words[i:i+6]))
print('>> pos', struct.unpack('<3f', rd(a + 0xc, 12)))
end
