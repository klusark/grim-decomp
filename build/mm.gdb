set pagination off
set environment _NO_DEBUG_HEAP=1
break Lua_MakeCurrentSet
run
delete
python
import gdb, struct
inf = gdb.selected_inferior()
def rd(a, n): return bytes(inf.read_memory(a, n))
cnt = [0]
class T(gdb.Breakpoint):
    def stop(self):
        cnt[0] += 1
        if cnt[0] > 24: return False
        sp = int(gdb.parse_and_eval('$esp'))
        mat = struct.unpack('<I', rd(sp + 8, 4))[0]
        m = struct.unpack('<12f', rd(mat, 48))
        print('>> mesh%d' % cnt[0], ' '.join('%.3f' % x for x in m))
        return False
T('*rdModel_DrawMesh')
end
continue
