set pagination off
set environment _NO_DEBUG_HEAP=1
break Lua_MakeCurrentSet
run
delete
python
import gdb, struct
inf = gdb.selected_inferior()
def cstr(p):
    try: return inf.read_memory(p, 48).tobytes().split(chr(0).encode())[0].decode('latin1')
    except Exception: return '?'
class Fin(gdb.FinishBreakpoint):
    def __init__(self, info):
        super().__init__(gdb.newest_frame(), internal=True); self.info = info
    def stop(self):
        eax = int(gdb.parse_and_eval('$eax')) & 0xffffffff
        print('>> %s -> %#x' % (self.info, eax)); return False
    def out_of_scope(self): pass
class T(gdb.Breakpoint):
    def stop(self):
        sp = int(gdb.parse_and_eval('$esp'))
        t = int(gdb.parse_and_eval('*(unsigned*)(%d)' % (sp+4)))
        nm = int(gdb.parse_and_eval('*(unsigned*)(%d)' % (sp+8)))
        tag = struct.pack('<I', t).decode('latin1')
        Fin('Res_Load(%s, %s)' % (tag, cstr(nm))); return False
T('*Res_Load')
end
continue
