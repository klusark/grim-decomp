set pagination off
set breakpoint pending on
python
import gdb
class FB(gdb.FinishBreakpoint):
    def __init__(self, nm, args):
        gdb.FinishBreakpoint.__init__(self, gdb.newest_frame(), internal=True)
        self.nm = nm; self.args = args
    def stop(self):
        print('>>', self.nm, self.args, '->', gdb.parse_and_eval('$eax'))
        return False
    def out_of_scope(self): pass
class BP(gdb.Breakpoint):
    n = 0
    def stop(self):
        BP.n += 1
        if BP.n > 12 and BP.n % 200: return False
        esp = int(gdb.parse_and_eval('(int)$esp'))
        a = int(gdb.parse_and_eval('*(unsigned*)%d' % (esp+4)))
        FB(self.location, hex(a))
        return False
for n in ['Timer_GetFrameMs','Engine_UpdateFrame']:
    BP(n)
gdb.execute('run')
end
