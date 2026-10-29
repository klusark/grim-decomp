set pagination off
set environment _NO_DEBUG_HEAP=1
run
python
import gdb
inf=gdb.selected_inferior()
sp=int(gdb.parse_and_eval('$esp'))&0xffffffff
for i in range(-8,48):
    try:
        v=int.from_bytes(bytes(inf.read_memory(sp+4*i,4)),'little')
    except Exception: continue
    if 0x401000<=v<0x4f0000:
        print(i, hex(sp+4*i), hex(v), gdb.execute('info symbol %d'%v,to_string=True).strip())
end
