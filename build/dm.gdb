set pagination off
break Lua_UpdateFrame
run
delete
python
import gdb, collections
cur = [None]
stat = collections.defaultdict(collections.Counter)
class DC(gdb.Breakpoint):
    def stop(self):
        cur[0] = int(gdb.parse_and_eval('(int)Cos_InstGetUserData(*param_1)'))
        stat[cur[0]]['drawcostume'] += 1
        return False
class Cnt(gdb.Breakpoint):
    def __init__(self, n):
        super().__init__(n, internal=True); self.nm = n
    def stop(self):
        stat[cur[0]][self.nm] += 1
        if self.nm == 'rdModel_DrawMesh':
            nv = int(gdb.parse_and_eval('*(int*)((char*)*(int*)($esp+4)+0x24)'))
            stat[cur[0]]['mesh_nverts_%d' % (nv>0)] += 1
        return False
DC('Actor_DrawCostumeMeshes')
for n in ('rdModel_DrawMesh','rdModel_AddMeshToCache','rdCache_AllocMesh','rdPrimit3_CopyFaceVerts','rdPrimit3_ClipFace','Polygon_ClipToPlane','rdCache_Flush','Frustum_TestSphere'):
    try: Cnt(n)
    except Exception as e: print('>> nobp', n)
end
continue
