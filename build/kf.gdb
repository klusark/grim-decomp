set pagination off
set environment _NO_DEBUG_HEAP=1
run
thread 1
python
import gdb, struct
inf = gdb.selected_inferior()
for nm in ('ma_rest.key', 'swivel_right.key', 'mannywalk.key'):
    s = gdb.parse_and_eval('(char*)malloc(64)')
    inf.write_memory(int(s), nm.encode() + b'\0')
    p = int(gdb.parse_and_eval('(unsigned)Res_Load(0x4659454b, %d)' % int(s)))
    w = struct.unpack('<24I', bytes(inf.read_memory(p, 96)))
    print('>>', nm, hex(p), [hex(x) for x in w[:16]])
    print('>>   floats', ['%g' % struct.unpack('<f', struct.pack('<I', x))[0] for x in w[:24]])
end
kill
