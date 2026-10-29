set pagination off
set environment _NO_DEBUG_HEAP=1
handle SIGSEGV stop
handle SIGILL stop
break Lua_MakeCurrentSet
run
delete
continue
python
import gdb, struct
inf = gdb.selected_inferior()
def rd(a, n): return bytes(inf.read_memory(a, n))
p = struct.unpack('<I', rd(int(gdb.parse_and_eval('(int)&PTR_1002bf6c')), 4))[0]
top = struct.unpack('<I', rd(p + 28, 4))[0]
base = struct.unpack('<I', rd(p + 32, 4))[0]
print('>> top', hex(top), 'base', hex(base), 'depth', (top - base)//8)
for i in range(12):
    a = top - 8 * (i + 1)
    tag, val = struct.unpack('<iI', rd(a, 8))
    s = ''
    if tag == -2:
        try: s = rd(val + 0x14, 24).split(bytes([0]))[0].decode('latin1')
        except Exception: s = '?'
    print('>>  slot -%d tag %d val %#x %s' % (i + 1, tag, val, s))
end
kill
