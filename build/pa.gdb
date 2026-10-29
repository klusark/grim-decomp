set pagination off
set environment _NO_DEBUG_HEAP=1
break Lua_MakeCurrentSet
run
delete
python
import gdb, struct
inf = gdb.selected_inferior()
def rd(a, n): return bytes(inf.read_memory(a, n))
def num(n):
    p = struct.unpack('<I', rd(int(gdb.parse_and_eval('(int)&PTR_1002bf6c')), 4))[0]
    st = struct.unpack('<I', rd(p + 32, 4))[0]
    idx = int(gdb.parse_and_eval('(int)lua_lua2C(%d)' % n))
    tag, val = struct.unpack('<iI', rd(st - 8 + idx*8, 8))
    return tag, val
class A(gdb.Breakpoint):
    def stop(self):
        t, v = num(2)
        print('>> Lua_PlayActorChore chore slot tag=%d val=%#x (%g)' % (t, v, struct.unpack('<f', struct.pack('<I', v))[0]))
        return False
class B2(gdb.Breakpoint):
    def stop(self):
        sp = int(gdb.parse_and_eval('$esp'))
        a = struct.unpack('<2I', rd(sp + 4, 8))
        print('>>   Cos_InstPlayChore(%s)' % [hex(x) for x in a])
        return False
A('*Lua_PlayActorChore'); B2('*Cos_InstPlayChore')
end
continue
