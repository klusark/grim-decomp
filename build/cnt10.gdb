set pagination off
set environment _NO_DEBUG_HEAP=1
python
import gdb
inf=gdb.selected_inferior()
def rd(a): return int.from_bytes(bytes(inf.read_memory(a,4)),'little')
class F(gdb.FinishBreakpoint):
    def __init__(s,p,n,before):
        super().__init__(gdb.newest_frame(),internal=True); s.p=p; s.n=n; s.b=before
    def stop(s):
        print('>> ret n=%d ret=%#x state before=%#x after=%#x f28=%d'%(s.n,int(gdb.parse_and_eval('$eax'))&0xffffffff,s.b,rd(s.p+0x34),rd(s.p+0x28))); return False
    def out_of_scope(s): pass
class C(gdb.Breakpoint):
    n=0
    def stop(s):
        C.n+=1
        sp=int(gdb.parse_and_eval('$esp'))&0xffffffff
        p=rd(sp+4)
        if C.n<=40: F(p,C.n,rd(p+0x34))
        return False
C('*FUN_004c36f0')
end
run
