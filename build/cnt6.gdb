set pagination off
set environment _NO_DEBUG_HEAP=1
python
import gdb
class C(gdb.Breakpoint):
    def __init__(s,spec,name):
        super().__init__(spec); s.n=0; s.name=name
    def stop(s):
        s.n+=1
        if s.n<=4 or s.n%50==0: print('>>',s.name,s.n)
        return False
C('*FUN_004c27a0','step'); C('*FUN_004cdfa0','rearm'); C('*FUN_004cdf10','create'); C('*FUN_004c2780','ready')
end
run
