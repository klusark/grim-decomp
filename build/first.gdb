set pagination off
set breakpoint pending on
python
import gdb, collections
first = collections.OrderedDict(); n = [0]
class BP(gdb.Breakpoint):
    def stop(self):
        fn = int(gdb.parse_and_eval('*(int*)($ebp+8)'))
        try: nm = gdb.execute('info symbol %d' % fn, to_string=True).split(' in ')[0].strip()
        except gdb.error: nm = hex(fn)
        n[0] += 1
        if nm not in first: first[nm] = n[0]
        return False
BP('ldo__44e0')
gdb.execute('run')
print('>> total', n[0])
print('>> order', [(k, v) for k, v in first.items() if not k.startswith(('Lua_TypeOverride', 'FUN_100037d0'))])
end
