python
import gdb, struct
gdb.execute('set pagination off')
b = gdb.Breakpoint('ResType_Find'); b.condition = 'fourcc == 1414418246'
gdb.execute('run')
for i in range(3):
    print('>> ResType_Find(FONT) hit, head=%#x' % int(gdb.parse_and_eval('(int)UINT_008a85cc')))
    gdb.execute('finish')
    print('>> returned', gdb.parse_and_eval('$eax'))
    gdb.execute('x/4i $pc')
    try: gdb.execute('continue')
    except gdb.error: break
end
