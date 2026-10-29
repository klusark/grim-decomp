set pagination off
break Lua_MakeCurrentSet
run
delete
python
import gdb
inf = gdb.selected_inferior()
def cstr(p):
    return inf.read_memory(p, 40).tobytes().split(chr(0).encode())[0].decode('latin1') if p else '(null)'
class Fin(gdb.FinishBreakpoint):
    def __init__(self, info):
        super().__init__(gdb.newest_frame(), internal=True); self.info = info
    def stop(self):
        try: rv = int(gdb.parse_and_eval('$eax')) & 0xffffffff
        except Exception: rv = None
        print('>> %s -> %s' % (self.info, hex(rv) if rv is not None else rv)); return False
    def out_of_scope(self): pass
class T(gdb.Breakpoint):
    def stop(self):
        sp = int(gdb.parse_and_eval('$esp'))
        a = int(gdb.parse_and_eval('*(unsigned*)(%d)' % (sp+4)))
        nmp = int(gdb.parse_and_eval('*(unsigned*)(%d)' % (sp+8)))
        tab = int(gdb.parse_and_eval('(unsigned)g_pActorTable'))
        Fin('SetCostume idx=%d %s' % ((a - tab)//0xa8, cstr(nmp))); return False
T('*Actor_SetCostume')
end
continue
