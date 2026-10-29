set pagination off
break Lua_UpdateFrame
run
delete
python
import gdb, collections
res = collections.Counter()
log = []
class Fin(gdb.FinishBreakpoint):
    def __init__(self, nm, info):
        super().__init__(gdb.newest_frame(), internal=True); self.nm = nm; self.info = info
    def stop(self):
        eax = int(gdb.parse_and_eval('$eax')) & 0xffffffff
        cnt = int(gdb.parse_and_eval('(unsigned)UINT_007f1468'))
        res[(self.nm, eax, cnt)] += 1
        return False
    def out_of_scope(self): pass
class T(gdb.Breakpoint):
    def __init__(self, n):
        super().__init__('*' + n, internal=True); self.nm = n
    def stop(self):
        Fin(self.nm, 0); return False
for n in ('rdModel_AddMeshToCache','rdPrimit3_ClipFace','rdPrimit3_CopyFaceVerts'):
    T(n)
end
continue
