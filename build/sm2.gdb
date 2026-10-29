set pagination off
set environment _NO_DEBUG_HEAP=1
break Grim_Init
run
break *LecShare_StartupModules
continue
python
import gdb
class N(gdb.Breakpoint):
    def stop(self):
        sp = int(gdb.parse_and_eval('$esp'))
        a = int(gdb.parse_and_eval('*(unsigned*)(%d)' % (sp+4))) & 0xffffffff
        b = int(gdb.parse_and_eval('*(unsigned*)(%d)' % (sp+8))) & 0xffffffff
        inf = gdb.selected_inferior()
        f = lambda p: inf.read_memory(p, 48).tobytes().split(bytes([0]))[0]
        print('>> LecShare_Nop', f(a), f(b)); return False
N('*LecShare_Nop')
class S(gdb.Breakpoint):
    def stop(self):
        # print module entries: table at UINT_008d56fc, count UINT_008d56f8, 12-byte entries {name, iface, ?}
        inf = gdb.selected_inferior()
        n = int(gdb.parse_and_eval('(int)UINT_008d56f8'))
        base = int(gdb.parse_and_eval('(unsigned)&UINT_008d56fc'))
        import struct
        for i in range(n):
            nm, iface, x = struct.unpack('<3I', bytes(inf.read_memory(base + 12*i, 12)))
            s = bytes(inf.read_memory(nm, 24)).split(bytes([0]))[0] if nm else b''
            fn = struct.unpack('<I', bytes(inf.read_memory(iface + 8, 4)))[0] if iface else 0
            print('>> module', i, s, hex(iface), 'startup fn', hex(fn))
        return False
end
continue
