set pagination off
set environment _NO_DEBUG_HEAP=1
break SoundsFloodMusicBuffer
run
python
import gdb, struct, collections
inf = gdb.selected_inferior()
buf = int(gdb.parse_and_eval('(unsigned)PTR_1002d83c'))
vt = struct.unpack('<I', bytes(inf.read_memory(buf, 4)))[0]
slot = lambda i: struct.unpack('<I', bytes(inf.read_memory(vt + i*4, 4)))[0]
res = collections.Counter(); log = []
class Fin(gdb.FinishBreakpoint):
    def __init__(self, nm, info):
        super().__init__(gdb.newest_frame(), internal=True); self.nm = nm; self.info = info
    def stop(self):
        eax = int(gdb.parse_and_eval('$eax')) & 0xffffffff
        res[(self.nm, hex(eax))] += 1
        if len(log) < 12: log.append((self.nm, self.info, hex(eax)))
        return False
    def out_of_scope(self): pass
class T(gdb.Breakpoint):
    def __init__(self, nm, idx):
        super().__init__('*%d' % slot(idx), internal=True); self.nm = nm
    def stop(self):
        sp = int(gdb.parse_and_eval('$esp'))
        a = struct.unpack('<4I', bytes(inf.read_memory(sp + 4, 16)))
        Fin(self.nm, [hex(x) for x in a[1:]]); return False
T('Lock', 11); T('Unlock', 19); T('GetCurrentPosition', 4); T('Play', 12); T('GetStatus', 9)
end
continue
python
print('>> results', dict(res)); print('>> log', log)
end
