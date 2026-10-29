set pagination off
set environment _NO_DEBUG_HEAP=1
break Lua_MakeCurrentSet
run
delete
python
import gdb, collections
names = [l.strip() for l in open('C:/Users/Joel/AppData/Local/Claude-Data/claude_pzs8sxrjxfjjc/scratch-workspaces/f0972061-5c14-4333-a255-b15c37c97747/dcb1fc9c-532e-4a3c-9dfb-8af95607d192/scratch-2026-10-28-bb481e/grim-decomp/build/im_names.txt') if l.strip()]
cnt = collections.Counter(); seq = []
class T(gdb.Breakpoint):
    def __init__(self, n):
        super().__init__('*' + n, internal=True); self.nm = n
    def stop(self):
        cnt[self.nm] += 1
        if not seq or seq[-1] != self.nm: seq.append(self.nm)
        return False
for n in names:
    try: T(n)
    except Exception: pass
end
continue
python
print('>> counts', cnt.most_common(40))
end
