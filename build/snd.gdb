set pagination off
set environment _NO_DEBUG_HEAP=1
run
thread 1
python
import gdb, struct
inf = gdb.selected_inferior()
buf = int(gdb.parse_and_eval('(unsigned)PTR_1002d83c'))
print('>> buffer obj', hex(buf))
mem = int(gdb.parse_and_eval('(unsigned)malloc(64)'))
r = int(gdb.parse_and_eval('((int(*)(void*,int,int,void*,void*,void*,void*,int))(*(void***)%d)[11])((void*)%d,0,0x1800,(void*)%d,(void*)%d,(void*)%d,(void*)%d,0)' % (buf, buf, mem, mem+4, mem+8, mem+12)))
p1, b1 = struct.unpack('<II', bytes(inf.read_memory(mem, 8)))
print('>> lock hr', hex(r & 0xffffffff), hex(p1), hex(b1))
if r == 0:
    d = bytes(inf.read_memory(p1, b1))
    s = struct.unpack('<%dh' % (len(d)//2), d)
    print('>> samples', len(s), 'nonzero', sum(1 for x in s if x), 'max', max(map(abs, s)))
    gdb.execute('call ((int(*)(void*,void*,int,void*,int))(*(void***)%d)[19])((void*)%d,(void*)%d,%d,0,0)' % (buf, buf, p1, b1))
end
kill
