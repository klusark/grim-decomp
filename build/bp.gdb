set pagination off
break *rdCamera_BuildProjection
run
python
import gdb, struct
inf = gdb.selected_inferior()
def rd(a, n): return bytes(inf.read_memory(a, n))
sp = int(gdb.parse_and_eval('$esp'))
cam = struct.unpack('<I', rd(sp + 4, 4))[0]
w = struct.unpack('<32I', rd(cam, 128))
print('>> camera', hex(cam), ' '.join('%x' % x for x in w[:20]))
print('>> fl', [struct.unpack('<f', struct.pack('<I', x))[0] for x in w[14:20]])
canvas = w[1]
c = struct.unpack('<16I', rd(canvas, 64)) if canvas else None
print('>> canvas', hex(canvas), c)
end
finish
python
cam = struct.unpack('<I', rd(sp + 4, 4))[0]
fr = struct.unpack('<I', rd(cam + 0x48, 4))[0]
print('>> frustum after', struct.unpack('<14f', rd(fr, 56)))
print('>> cam f/after', struct.unpack('<2f', rd(cam + 0x38, 8)))
end
kill
