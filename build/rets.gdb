set pagination off
set breakpoint pending on
python
import gdb
class FB(gdb.FinishBreakpoint):
    def __init__(self, name):
        gdb.FinishBreakpoint.__init__(self, gdb.newest_frame(), internal=True)
        self.nm = name
    def stop(self):
        print('>>', self.nm, 'returned', gdb.parse_and_eval('$eax'))
        return False
    def out_of_scope(self):
        pass
class BP(gdb.Breakpoint):
    def stop(self):
        FB(self.location)
        return False
for n in ['LecShare_StartupModules','LecShare_Resolve','Str_WildcardMatch','LecShare_CountMatching','LecShare_Subscribe','FUN_004bd440','FUN_00489130','Grim_Init']:
    BP(n)
gdb.execute("run")
end
