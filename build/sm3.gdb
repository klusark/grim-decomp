set pagination off
set environment _NO_DEBUG_HEAP=1
break Grim_Init
run
python
import gdb, re
dis = gdb.execute('disassemble LecShare_StartupModules', to_string=True)
calls = [l for l in dis.splitlines() if re.search(r'call\s+\*%e', l)]
addr = int(calls[0].split()[0].replace('=>','').strip(), 16)
last = {}
class C(gdb.Breakpoint):
    def stop(self):
        last['t'] = int(gdb.parse_and_eval('$eax')) & 0xffffffff
        return False
class R(gdb.Breakpoint):
    def stop(self):
        eax = int(gdb.parse_and_eval('$eax')) & 0xffffffff
        sym = gdb.execute('info symbol %d' % last['t'], to_string=True).strip().split(' in ')[0]
        print('>> startup', sym, '->', eax)
        return False
C('*%d' % addr); R('*%d' % (addr + 2))
end
continue
