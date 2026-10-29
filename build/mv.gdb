set pagination off
set environment _NO_DEBUG_HEAP=1
break *rdModel_DrawMesh
run
python
import gdb, struct
inf = gdb.selected_inferior()
def rd(a, n): return bytes(inf.read_memory(a, n))
sp = int(gdb.parse_and_eval('$esp'))
mesh = struct.unpack('<I', rd(sp + 4, 4))[0]
mat = struct.unpack('<I', rd(sp + 8, 4))[0]
w = struct.unpack('<32I', rd(mesh, 128))
print('>> mesh', hex(mesh), 'nfaces', w[9], 'nverts', w[0x12], 'verts ptr', hex(w[0xc]), 'radius', struct.unpack('<f', struct.pack('<I', w[0x18]))[0])
vp = w[0xc]; nv = w[0x12]
v = struct.unpack('<%df' % (3*min(nv,8)), rd(vp, 12*min(nv, 8)))
print('>> first verts', ['%.3f' % x for x in v])
m = struct.unpack('<12f', rd(mat, 48))
print('>> matrix', ['%.3f' % x for x in m])
end
kill
