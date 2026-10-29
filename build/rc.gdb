set pagination off
set environment _NO_DEBUG_HEAP=1
break Lua_MakeCurrentSet
run
delete
python
import gdb, struct
inf = gdb.selected_inferior()
def rd(a, n): return bytes(inf.read_memory(a, n))
n = [0]
class Fin(gdb.FinishBreakpoint):
    def __init__(self, info):
        super().__init__(gdb.newest_frame(), internal=True); self.info = info
    def stop(self):
        eax = int(gdb.parse_and_eval('$eax')) & 0xffffffff
        print('>> %s -> %d' % (self.info, eax)); return False
    def out_of_scope(self): pass
class T(gdb.Breakpoint):
    def stop(self):
        n[0] += 1
        sp = int(gdb.parse_and_eval('$esp'))
        lo = struct.unpack('<I', rd(sp + 4, 4))[0]
        cl = struct.unpack('<I', rd(sp + 8, 4))[0]
        # names in the costume list
        names = []
        p = cl
        for i in range(6):
            if not p: break
            inst = struct.unpack('<I', rd(p, 4))[0]
            nm = int(gdb.parse_and_eval('(unsigned)Cos_InstGetCostume(%d, 0)' % inst)) if False else 0
            names.append(hex(inst))
            p = struct.unpack('<I', rd(p + 0xb0, 4))[0]
        Fin('ResolveCostumeArg #%d list=%s' % (n[0], names)); return False
T('*Lua_ResolveCostumeArg')
end
continue
