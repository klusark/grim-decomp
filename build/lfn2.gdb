set pagination off
set environment _NO_DEBUG_HEAP=1
handle SIGSEGV stop
handle SIGILL stop
break Lua_MakeCurrentSet
run
delete
python
import gdb, collections
names = [l.strip() for l in open('C:/Users/Joel/grim-decomp/build/lua_names.txt') if l.strip()]
seq = []
class T(gdb.Breakpoint):
    def __init__(self, n):
        super().__init__('*' + n, internal=True); self.nm = n
    def stop(self):
        seq.append(self.nm)
        if len(seq) > 400: del seq[:200]
        return False
for n in names:
    try: T(n)
    except Exception: pass
end
continue
bt 6
info registers eip
python
tail = [s for s in seq if s not in ('Lua_TypeOverride','Lua_GetActorPos','Lua_IsActorInSector','Lua_GetActorSector','Lua_GetCurrentSetup','Lua_GetVisibleThings','Lua_IsMessageGoing','Lua_IsActorChoring','Lua_DispatchControlHandlers','Lua_UpdateFrame','Lua_GetControlState','Lua_IsActorMoving','Lua_IsActorTurning','Lua_PerSecond')]
print('>> tail', tail[-25:])
end
bt 4
kill
