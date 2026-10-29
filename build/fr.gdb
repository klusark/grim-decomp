set pagination off
break rdModel_DrawMesh
run
delete
python
import gdb, struct
inf = gdb.selected_inferior()
def rd(a, n): return bytes(inf.read_memory(a, n))
cam = int(gdb.parse_and_eval('(unsigned)g_pRdCurrentCamera'))
print('>> cam', hex(cam))
w = struct.unpack('<32f', rd(cam, 128))
for i in range(0, 32, 8): print('>> cam+%#x' % (i*4), ' '.join('%g' % x for x in w[i:i+8]))
fr = struct.unpack('<I', rd(cam + 0x48, 4))[0]
print('>> frustum', hex(fr))
f = struct.unpack('<48f', rd(fr, 192))
for i in range(0, 48, 6): print('>> fr+%#x' % (i*4), ' '.join('%g' % x for x in f[i:i+6]))
fl = struct.unpack('<8I', rd(cam + 0x0, 32)); print('>> camwords', [hex(x) for x in fl])
end
kill
