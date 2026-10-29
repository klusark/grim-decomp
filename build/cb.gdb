python
import gdb
gdb.execute('set pagination off')
b = gdb.Breakpoint('res.c:450')
b.condition = 'type == 1414418246'
gdb.execute('run')
v = int(gdb.parse_and_eval('(int)UINT_008a85e8'))
print('>> callback', hex(v), gdb.execute('info symbol %d' % v, to_string=True).strip())
gdb.execute('x/30i %d' % v)
end
