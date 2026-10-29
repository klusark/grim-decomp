python
import gdb
gdb.execute('set pagination off')
gdb.Breakpoint('FUN_0047c7c0')
gdb.execute('run')
print('>> hit FUN_0047c7c0; UINT_00900520 =', gdb.parse_and_eval('UINT_00900520'), ' addr', gdb.parse_and_eval('&UINT_00900520'))
gdb.execute('finish')
print('>> after; UINT_00900520 =', gdb.parse_and_eval('UINT_00900520'))
gdb.execute('watch UINT_00900520')
for i in range(8):
    try: gdb.execute('continue')
    except gdb.error: break
    print('>> now', gdb.parse_and_eval('UINT_00900520'))
    gdb.execute('bt 3')
end
