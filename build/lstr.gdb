set pagination off
break Lua_MakeCurrentSet
run
delete
python
import gdb, struct
inf = gdb.selected_inferior()
def rd(a, n): return bytes(inf.read_memory(a, n))
def slotinfo(n):
    p = struct.unpack('<I', rd(int(gdb.parse_and_eval('(int)&PTR_1002bf6c')), 4))[0]
    st = struct.unpack('<I', rd(p + 32, 4))[0]
    idx = int(gdb.parse_and_eval('(int)lua_lua2C(%d)' % n))
    tag, val = struct.unpack('<iI', rd(st - 8 + idx*8, 8))
    if tag == -2:
        try: s = rd(val + 0x14, 40).split(b'\0')[0].decode('latin1')
        except Exception: s = '?'
        return '"%s"' % s
    if tag == -1: return '%g' % struct.unpack('<f', struct.pack('<I', val))[0]
    return 't%d:%x' % (tag, val)
class T(gdb.Breakpoint):
    def __init__(self, name, n):
        super().__init__(name, internal=True); self.nm = name; self.n = n
    def stop(self):
        try: print('>> %s(%s)' % (self.nm, ', '.join(slotinfo(i) for i in range(1, self.n + 1))))
        except Exception as e: print('>> %s err %s' % (self.nm, e))
        return False
for nm, n in [('Lua_PlayActorChore',4),('Lua_SetActorRestChore',3),('Lua_SetActorWalkChore',3),('Lua_SetActorTalkChore',3),('Lua_SetActorVisibility',2),('Lua_PutActorInSet',2),('Lua_LoadCostume',1),('Lua_StopActorChore',3),('Lua_CompleteActorChore',3),('Lua_SayLine',3),('Lua_StartMovie',2),('Lua_StartFullscreenMovie',2),('Lua_PushActorCostume',3),('Lua_SetActorMumblechore',3),('Lua_SetActorTurnChores',4)]:
    T(nm, n)
end
continue
