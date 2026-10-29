set pagination off
break Lua_UpdateFrame
run
delete
python
import gdb, collections
cur = [None]
res = collections.Counter()
log = []
class Fin(gdb.FinishBreakpoint):
    def __init__(self, info):
        super().__init__(gdb.newest_frame(), internal=True); self.info = info
    def stop(self):
        n = int(gdb.parse_and_eval('(unsigned)UINT_007f1468'))
        res[(cur[0], n)] += 1
        log.append((cur[0], self.info, n))
        return False
    def out_of_scope(self): pass
class DC(gdb.Breakpoint):
    def stop(self):
        cur[0] = int(gdb.parse_and_eval('(int)Cos_InstGetUserData(*param_1)')); return False
class CF(gdb.Breakpoint):
    def stop(self):
        if True:
            n0 = int(gdb.parse_and_eval('(unsigned)UINT_007f1468'))
            Fin(n0)
        return False
DC('Actor_DrawCostumeMeshes')
CF('rdPrimit3_ClipFace')
end
continue
