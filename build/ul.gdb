set pagination off
set environment _NO_DEBUG_HEAP=1
break SoundsFloodMusicBuffer
run
python
import gdb, struct
inf = gdb.selected_inferior()
buf = int(gdb.parse_and_eval('(unsigned)PTR_1002d83c'))
vt = struct.unpack('<I', bytes(inf.read_memory(buf, 4)))[0]
unlock = struct.unpack('<I', bytes(inf.read_memory(vt + 19*4, 4)))[0]
print('>> buffer', hex(buf), 'Unlock at', hex(unlock))
stats = {'calls': 0, 'nonzero_calls': 0, 'maxabs': 0}
class U(gdb.Breakpoint):
    def stop(self):
        sp = int(gdb.parse_and_eval('$esp'))
        a = struct.unpack('<5I', bytes(inf.read_memory(sp + 4, 20)))
        p1, b1 = a[1], a[2]
        stats['calls'] += 1
        if b1:
            d = bytes(inf.read_memory(p1, min(b1, 0x4000)))
            s = struct.unpack('<%dh' % (len(d)//2), d)
            m = max(map(abs, s))
            if m: stats['nonzero_calls'] += 1
            stats['maxabs'] = max(stats['maxabs'], m)
        return False
U('*%d' % unlock)
end
continue
python
print('>> stats', stats)
end
