set pagination off
set environment _NO_DEBUG_HEAP=1
python
import gdb
inf=gdb.selected_inferior()
def rd(a): return int.from_bytes(bytes(inf.read_memory(a,4)),'little')
class C(gdb.Breakpoint):
    n=0
    def stop(s):
        C.n+=1
        sp=int(gdb.parse_and_eval('$esp'))&0xffffffff
        p=rd(sp+4)
        if C.n<=3 or C.n%25==0:
            print('>> step',C.n,'state68=',rd(p+0x68),'st34=',hex(rd(p+0x34)),'frm28=',rd(p+0x28),'n2c=',rd(p+0x2c),'14=',rd(p+0x14),'5=',rd(p+0x14),'10=',rd(p+0x10),'18=',hex(rd(p+0x18)))
        return False
C('*FUN_004c27a0')
end
run
