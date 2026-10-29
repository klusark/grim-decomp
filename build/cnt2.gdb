set pagination off
break Lua_UpdateFrame
run
delete
python
import gdb, collections
c = collections.Counter()
class T(gdb.Breakpoint):
    def __init__(self, n):
        super().__init__('*' + n, internal=True); self.nm = n
    def stop(self):
        c[self.nm] += 1; return False
for n in ('Actor_DrawCostumeMeshes','Actor_DrawCostumes','rdThing_DrawAlt','rdModel_DrawNode','rdModel_DrawMesh','rdModel_AddMeshToCache','rdCache_Flush','rdCache_AllocMesh','Frustum_TestSphere','rdPrimit3_ClipFace','rdPrimit3_CopyFaceVerts','Render_BuildActorDrawList','Costume_ApplyComponentState','ModelComponent_NewInstance','Actor_DrawShadows'):
    try: T(n)
    except Exception as e: print('>> nobp', n, e)
end
continue
