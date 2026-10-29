python
import gdb
gdb.execute('set pagination off')
b = gdb.Breakpoint('FUN_0048dbd0')
gdb.execute('run')
print('>> handler entry esp', hex(int(gdb.parse_and_eval('(int)$esp'))), 'ebp', hex(int(gdb.parse_and_eval('(int)$ebp'))))
r = gdb.Breakpoint('*0x54c194')
gdb.execute('continue')
print('>> handler ret esp', hex(int(gdb.parse_and_eval('(int)$esp'))), 'ebp', hex(int(gdb.parse_and_eval('(int)$ebp'))), 'ret addr', hex(int(gdb.parse_and_eval('*(int*)$esp'))))
gdb.execute('stepi')
print('>> after ret esp', hex(int(gdb.parse_and_eval('(int)$esp'))), 'pc', gdb.parse_and_eval('$pc'))
end
