python
import gdb
gdb.execute('set pagination off')
b = gdb.Breakpoint('Res_LoadInternal'); b.condition = 'type == 1414418246'
gdb.execute('run')
print('>> entry esp', hex(int(gdb.parse_and_eval('(int)$esp'))))
b.delete()
gdb.Breakpoint('res.c:445'); gdb.Breakpoint('res.c:448'); gdb.Breakpoint('res.c:453'); gdb.Breakpoint('res.c:462')
for i in range(6):
    try: gdb.execute('continue', to_string=True)
    except gdb.error: break
    try:
        print('>> stop at line', gdb.selected_frame().find_sal().line, 'esp', hex(int(gdb.parse_and_eval('(int)$esp'))), 'pvVar1', gdb.parse_and_eval('pvVar1'))
    except gdb.error as e: print('>>', e); break
end
