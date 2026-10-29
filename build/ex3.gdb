set pagination off
set environment _NO_DEBUG_HEAP=1
break *0x41b40c
run
python
import gdb
hist=[]
for i in range(300000):
    pc=int(gdb.parse_and_eval('$pc'))&0xffffffff
    hist.append(pc)
    if len(hist)>25: hist.pop(0)
    if pc<0x401000 or pc>0xA00000: break
    gdb.execute('stepi',to_string=True)
print('steps',i)
for h in hist: print(hex(h))
end
x/30i 0x41b40c
