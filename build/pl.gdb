set pagination off
set environment _NO_DEBUG_HEAP=1
break Lua_MakeCurrentSet
run
delete
python
import gdb, struct
class Fin(gdb.FinishBreakpoint):
    def __init__(self, info, h, c):
        super().__init__(gdb.newest_frame(), internal=True); self.info = info; self.h = h; self.c = c
    def stop(self):
        eax = int(gdb.parse_and_eval('$eax')) & 0xffffffff
        print('>> %s -> %d' % (self.info, eax)); return False
    def out_of_scope(self): pass
class T(gdb.Breakpoint):
    def __init__(self, n):
        super().__init__('*' + n, internal=True); self.nm = n
    def stop(self):
        sp = int(gdb.parse_and_eval('$esp'))
        a = [int(gdb.parse_and_eval('*(unsigned*)(%d)' % (sp + 4 + 4*i))) for i in range(3)]
        Fin('%s%s' % (self.nm, [hex(x) for x in a]), a[0], a[1]); return False
for n in ('Cos_InstPlayChore','Cos_InstStopChore','Cos_InstSetChoreLoop','Cos_InstCompleteChore','Cos_InstStopChores','Cos_InstCompleteChores'):
    try: T(n)
    except Exception as e: print('>> nobp', n)
end
continue
