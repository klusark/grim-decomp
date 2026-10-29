set pagination off
set environment _NO_DEBUG_HEAP=1
break Grim_Init
run
python
import gdb
inf = gdb.selected_inferior()
def S(p):
    try: return bytes(inf.read_memory(p, 64)).split(bytes([0]))[0].decode('latin1') if p else None
    except Exception: return '?'
def arg(i):
    sp = int(gdb.parse_and_eval('$esp')); return int(gdb.parse_and_eval('*(unsigned*)(%d)' % (sp + 4 + 4*i))) & 0xffffffff
class WM(gdb.Breakpoint):
    def stop(self):
        self.a=(S(arg(0)),S(arg(1)))
        FB(self)
        return False
class FB(gdb.FinishBreakpoint):
    def __init__(self, p):
        super().__init__(gdb.newest_frame(), internal=True); self.a=p.a
    def stop(self):
        print('>> WM', self.a, S(int(gdb.parse_and_eval('$eax')) & 0xffffffff)); return False
    def out_of_scope(self): pass
class Res(gdb.Breakpoint):
    def stop(self):
        print('>> Resolve', S(arg(0)), S(arg(1)), 'ec=',S(int(gdb.parse_and_eval('*(unsigned*)0x8d56ec'))),'f0=',S(int(gdb.parse_and_eval('*(unsigned*)0x8d56f0'))), 'e8=', int(gdb.parse_and_eval('*(unsigned*)0x8d56e8'))); return False
class FE(gdb.Breakpoint):
    def stop(self):
        a=S(arg(0)); print('>> FindEntry', a); FF(a); return False
class FF(gdb.FinishBreakpoint):
    def __init__(self,a):
        super().__init__(gdb.newest_frame(), internal=True); self.a=a
    def stop(self):
        print('>> FE ret', hex(int(gdb.parse_and_eval('$eax')) & 0xffffffff)); return False
    def out_of_scope(self): pass
FE('*LecShare_FindEntry')
Res('*LecShare_Resolve')
end
continue
