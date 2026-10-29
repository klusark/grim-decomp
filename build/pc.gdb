set pagination off
set environment _NO_DEBUG_HEAP=1
break Lua_MakeCurrentSet
run
delete
python
import gdb, struct, collections
cnt = collections.Counter()
class T(gdb.Breakpoint):
    def __init__(self, n):
        super().__init__('*' + n, internal=True); self.nm = n
    def stop(self):
        cnt[self.nm] += 1
        if cnt[self.nm] <= 6:
            sp = int(gdb.parse_and_eval('$esp'))
            a = [int(gdb.parse_and_eval('*(unsigned*)(%d)' % (sp + 4 + 4*i))) for i in range(4)]
            print('>> %s %s' % (self.nm, [hex(x) for x in a]))
        return False
for n in ('Cos_InstPlayChore','Cos_InstUpdateChores','Cos_InstUpdateChore','Cos_InstStopChore','Cos_InstChoreStatus','Cos_InstSetChoreLoop','Chore_AdvanceTime','rdPuppet_AddTrack','rdPuppet_PlayTrack','rdPuppet_FadeInTrack'):
    try: T(n)
    except Exception as e: print('>> nobp', n)
end
continue
