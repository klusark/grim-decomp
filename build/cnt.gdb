set pagination off
set breakpoint pending on
python
import gdb, collections
c = collections.Counter()
class BP(gdb.Breakpoint):
    def stop(self):
        c[self.location] += 1; return False
for n in ['Render_BuildActorDrawList','Actor_DrawCostumes','rdCache_DrawMesh','rdModel_AddMeshToCache','rdroid_BeginFrame','Costume_TouchComponents','ObjectState_Draw','DirtyRect_Flush','Surface_Blit','Render_Present','Actors_UpdateAll','Walker_Update','Actor_Update']:
    BP(n)
gdb.execute('run')
gdb.execute('thread 1')
print('>> counts', dict(c))

end
