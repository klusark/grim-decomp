set pagination off
set environment _NO_DEBUG_HEAP=1
python
import gdb,time
t0=time.time()
class C(gdb.Breakpoint):
    def __init__(s,spec,name):
        super().__init__(spec); s.n=0; s.name=name
    def stop(s):
        s.n+=1
        if s.n<=5 or s.n%20==0: print('>>',s.name,s.n,'t=%.1f'%(time.time()-t0))
        return False
for sp,n in [('Engine_RenderFrame','render'),('Lua_UpdateFrame','luaupd'),('Mixer_Update','mixer'),('Timer_GetFrameSeconds','tfs')]:
    C('*'+sp,n)
end
run
