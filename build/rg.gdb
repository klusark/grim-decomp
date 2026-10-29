set pagination off
set environment _NO_DEBUG_HEAP=1
handle SIGILL stop
handle SIGSEGV stop
break Lua_MakeCurrentSet
run
delete
python
import gdb
class P(gdb.Breakpoint):
    def stop(self):
        sp = int(gdb.parse_and_eval('$esp'))
        fn = int(gdb.parse_and_eval('*(unsigned*)(%d)' % (sp+4))) & 0xffffffff
        ra = int(gdb.parse_and_eval('*(unsigned*)(%d)' % sp)) & 0xffffffff
        if fn >= 0x4f0000 or fn < 0x401000:
            print('>> BAD pushCclosure fn %#x ret %#x' % (fn, ra))
        return False
P('*%d' % int(gdb.parse_and_eval('(unsigned)&lua_pushCclosure')))
end
continue
