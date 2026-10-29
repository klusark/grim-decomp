python
import gdb
gdb.execute('set pagination off')
b = gdb.Breakpoint('Res_LoadInternal'); b.condition = 'type == 1414418246'
gdb.execute('run')
gdb.execute('next'); gdb.execute('next'); gdb.execute('next')
addr = int(gdb.parse_and_eval('(int)&pvVar1'))
print('>> &pvVar1 =', hex(addr), 'value', gdb.parse_and_eval('pvVar1'), ' _frame=', hex(int(gdb.parse_and_eval('(int)_frame'))), 'size', 0x40)
gdb.execute('watch *(int*)%d' % addr)
for i in range(6):
    try: gdb.execute('continue')
    except gdb.error: break
    print('>> value now', gdb.parse_and_eval('*(int*)%d' % addr))
    gdb.execute('bt 4')
end
