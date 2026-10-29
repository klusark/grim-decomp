set pagination off
set breakpoint pending on
python
import gdb
state = {'n': 0, 'on': False}
def rd(a):
    try:
        return gdb.selected_inferior().read_memory(a, 48).tobytes().split(b'\0')[0].decode('latin1')
    except Exception:
        return '?'
class Fin(gdb.FinishBreakpoint):
    def __init__(self, name, argstr):
        super().__init__(gdb.newest_frame(), internal=True)
        self.name = name; self.argstr = argstr
    def stop(self):
        try: rv = int(self.return_value) & 0xffffffff
        except Exception: rv = None
        print('>> %s(%s) -> %s' % (self.name, self.argstr, hex(rv) if rv is not None else rv))
        return False
    def out_of_scope(self): pass
class Tr(gdb.Breakpoint):
    def __init__(self, name, fmt):
        super().__init__(name); self.nm = name; self.fmt = fmt
    def stop(self):
        sp = int(gdb.parse_and_eval('$esp'))
        pc = int(gdb.parse_and_eval('$pc')) & 0xffffffff
        sa = int(gdb.parse_and_eval('(unsigned)&%s' % self.nm)) & 0xffffffff
        off = 4 if pc == sa else 8
        def arg(i): return int(gdb.parse_and_eval('*(unsigned*)(%d)' % (sp + off + 4*i))) & 0xffffffff
        if self.nm == 'Cos_Load': state['on'] = True
        if not state['on'] or state['n'] > 80: return False
        state['n'] += 1
        a = self.fmt(arg, sp)
        Fin(self.nm, a)
        return False
Tr('Cos_Load', lambda arg, sp: rd(arg(0)))
Tr('FUN_10004bb0', lambda arg, sp: '%x,%x,%x' % (arg(0), arg(1), arg(2)))
Tr('FUN_10005810', lambda arg, sp: '"%s" , "%s"' % (rd(arg(0))[:30], rd(arg(1))[:30]))
for n in ('FUN_100041e0','FUN_10004390','FUN_100047f0','FUN_10004970','Cos_LoadEntry','FUN_10004e50','FUN_10005740'):
    Tr(n, lambda arg, sp: '%x,%x,%x' % (arg(0), arg(1), arg(2)))
end
run
