set pagination off
set breakpoint pending on
python
import gdb, collections
c = collections.Counter()
class BP(gdb.Breakpoint):
    def stop(self):
        c[self.location] += 1; return False
for n in ['Engine_UpdateFrame','Engine_RenderFrame','Engine_PresentFrame','Display_Flip','Engine_BlitToBackBuffer','Actors_UpdateAll','Lua_UpdateFrame','Win_PumpMessages','Surface_Blit']:
    BP(n)
gdb.execute('run')
gdb.execute('thread 1')
print('>> counts', dict(c))
print('>> state', gdb.parse_and_eval('UINT_008a8c40'), gdb.parse_and_eval('UINT_004e7d98'), 'rendered flag', gdb.parse_and_eval('UINT_008a8c60'))
end
