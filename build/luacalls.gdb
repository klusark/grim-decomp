set pagination off
set breakpoint pending on
python
import gdb, struct, collections, os
inf = gdb.selected_inferior()
def rd(a, n): return bytes(inf.read_memory(a, n))
cnt = collections.Counter(); seq = collections.deque(maxlen=300); n = [0]
class BP(gdb.Breakpoint):
    def stop(self):
        try:
            f = int(gdb.parse_and_eval('(unsigned)$ecx'))
            line = struct.unpack('<I', rd(f + 0x14, 4))[0]
            ts = struct.unpack('<I', rd(f + 0x18, 4))[0]
            nm = rd(ts + 0x14, 48).split(b'\0')[0].decode('latin-1').replace('Scripts' + chr(92), '') if ts else '?'
            key = '%s:%d' % (nm, line)
        except Exception as e:
            print('>> err', e)
            key = 'err'
        cnt[key] += 1; seq.append(key); n[0] += 1
        return False
gdb.execute('break Lua_MakeCurrentSet')
gdb.execute('run')
gdb.execute('delete')
BP("*'@luaV_execute@4'")
gdb.execute('continue')
print('>> calls', n[0])
print('>> top', cnt.most_common(14))
print('>> last', list(seq)[-40:])
end
