set pagination off
set environment _NO_DEBUG_HEAP=1
run
thread 1
python
import gdb, struct
inf = gdb.selected_inferior()
base = int(gdb.parse_and_eval('(unsigned)&UINT_00804020'))
data = bytes(inf.read_memory(base - 8, 256 * 28 + 8))
for k in range(256):
    rec = struct.unpack('<7I', data[k*28:k*28+28])
    if rec[0] or rec[2] or rec[3] or rec[4] or rec[5] or rec[6]: print('>> key %#x rec' % k, [hex(x) for x in rec])
print('>> done')
end
kill
