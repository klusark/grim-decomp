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
        i=rd(sp+4); iv=rd(sp+8)
        if C.n in (20,21,22):
            print(">> BT", gdb.execute("bt 5", to_string=True).replace(chr(10)," | "))
        if False:
            base=0x8da5d8+i*0x20
            print('>> rearm',C.n,'id',i,'interval',iv, 'entry:',[hex(rd(base+4*k)) for k in range(8)])
        return False
C('*FUN_004cdfa0')
end
run
