set pagination off
set environment _NO_DEBUG_HEAP=1
break Lua_MakeCurrentSet
run
delete
python
import gdb, struct
inf = gdb.selected_inferior()
def rd(a, n): return bytes(inf.read_memory(a, n))
seen = [0]
class T(gdb.Breakpoint):
    def stop(self):
        seen[0] += 1
        if seen[0] > 3: return False
        sp = int(gdb.parse_and_eval('$esp'))
        model = struct.unpack('<I', rd(sp + 4, 4))[0]
        w = struct.unpack('<12I', rd(model, 48))
        print('>> model', hex(model), [hex(x) for x in w])
        tr = w[5]
        if tr:
            h = struct.unpack('<2I', rd(tr, 8))
            print('>>  tracks hdr', h)
            for t in range(6):
                base = tr + 8 + t*0x134
                tw = struct.unpack('<16I', rd(base, 64))
                print('>>  track', t, 'status', tw[0], 'time(+0x10..)', [('%g' % struct.unpack('<f', struct.pack('<I', x))[0]) for x in tw[1:8]], 'w[8..12]', [('%g' % struct.unpack('<f', struct.pack('<I', x))[0]) for x in tw[8:14]])
        return False
T('*rdPuppet_UpdateFrame')
end
continue
