set pagination off
set environment _NO_DEBUG_HEAP=1
break *rdThing_DrawAlt
run
python
import gdb, struct
inf = gdb.selected_inferior()
def rd(a, n): return bytes(inf.read_memory(a, n))
sp = int(gdb.parse_and_eval('$esp'))
thing = struct.unpack('<I', rd(sp + 4, 4))[0]
mat = struct.unpack('<I', rd(sp + 8, 4))[0]
print('>> thing', hex(thing), 'mat', hex(mat))
print('>> frame', ['%.3f' % x for x in struct.unpack('<12f', rd(mat, 48))])
end
continue
python
sp = int(gdb.parse_and_eval('$esp'))
mat = struct.unpack('<I', rd(sp + 8, 4))[0]
print('>> frame2', ['%.3f' % x for x in struct.unpack('<12f', rd(mat, 48))])
end
kill
