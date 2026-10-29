set pagination off
set environment _NO_DEBUG_HEAP=1
python
import gdb
class Fin(gdb.FinishBreakpoint):
    def __init__(self, nm):
        super().__init__(gdb.newest_frame(), internal=True); self.nm = nm
    def stop(self):
        print('>> %s returned %d' % (self.nm, int(gdb.parse_and_eval('$eax')) & 0xffffffff)); return False
    def out_of_scope(self): pass
class T(gdb.Breakpoint):
    def __init__(self, n):
        super().__init__('*' + n, internal=True); self.nm = n
    def stop(self):
        print('>> enter', self.nm, 'u16a0=%d u16a4=%d' % (int(gdb.parse_and_eval('(int)UINT_008d16a0')), int(gdb.parse_and_eval('(int)UINT_008d16a4'))))
        Fin(self.nm); return False
end
break Grim_Init
run
python
for n in ('FUN_004bd440', 'LecShare_StartupModules', 'FUN_00489130'):
    T(n)
end
continue
