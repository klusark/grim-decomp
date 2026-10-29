set pagination off
set environment _NO_DEBUG_HEAP=1
break Lua_MakeCurrentSet
run
delete
python
import gdb, collections
names = [l.strip() for l in open('C:/Users/Joel/grim-decomp/build/im_names.txt') if l.strip()]
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
first=[]
for n in seq:
    if n not in first: first.append(n)
print('>> first-use', [(n, cnt[n]) for n in first])
end
