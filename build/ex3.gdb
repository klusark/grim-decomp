set pagination off
set environment _NO_DEBUG_HEAP=1
break FUN_004d1180
run
python
import gdb
hist=[]
for i in range(2000000):
    pc=int(gdb.parse_and_eval('$pc'))&0xffffffff
    hist.append(pc)
    if len(hist)>12: hist.pop(0)
    if pc<0x401000 or pc>0x9fffff and False:
        break
    gdb.execute('stepi',to_string=True)
print('steps',i)
for h in hist:
    print(hex(h))
gdb.execute('x/6i %d'%hist[-2])
end
