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
class Reg(gdb.Breakpoint):
    def stop(self):
        print('>> Register', S(arg(0)), hex(arg(1))); return False
class Res(gdb.Breakpoint):
    def stop(self):
        print('>> Resolve', S(arg(0)), S(arg(1))); return False
class Start(gdb.Breakpoint):
    def stop(self):
        print('>> Startup', arg(0), hex(arg(1)), S(arg(2)), S(arg(3))); return False
Reg('*LecShare_Register'); Res('*LecShare_Resolve'); Start('*LecShare_Startup')
end
continue
