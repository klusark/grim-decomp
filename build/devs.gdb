set pagination off
break Display_Select
run
python
import gdb
for i in range(int(gdb.parse_and_eval('g_dwDisplayDeviceCount'))):
    base = int(gdb.parse_and_eval('(int)&DAT_00902c60')) + i*0x298
    print('>> dev', i, 'name:', gdb.execute('x/s %d' % base, to_string=True).strip(), 'type+0x100 =', gdb.parse_and_eval('*(int*)%d' % (base+0x100)), 'win+0x110 =', gdb.parse_and_eval('*(int*)%d' % (base+0x110)), 'modes@', gdb.parse_and_eval('*(int*)((int)g_pDisplayModes + %d)' % (i*0x10)))
print('>> windowed', gdb.parse_and_eval('g_bWindowedMode'), 'dev flag', gdb.parse_and_eval('INT_004f5a24'), 'UINT_004f5a28', gdb.parse_and_eval('UINT_004f5a28'))
end
