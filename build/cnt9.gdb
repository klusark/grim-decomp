set pagination off
set environment _NO_DEBUG_HEAP=1
python
import gdb
class C(gdb.Breakpoint):
    def __init__(s,spec,name):
        super().__init__(spec); s.n=0; s.name=name
    def stop(s):
        s.n+=1
        if s.n in (1,2,3,100,500,1000,3000): print('>>',s.name,s.n)
        return False
for sp,n in [('Movie_PollPlayback','poll'),('Smush_Advance','adv'),('FUN_00489420','lock'),('FUN_004894b0','unlock'),('Surface_Lock','slock'),('Surface_Unlock','sunlock'),('Render_InvalidateRect','inval'),('FUN_004c3c00','frame'),('FUN_004ccd00','blocky')]:
    C('*'+sp,n)
end
run
