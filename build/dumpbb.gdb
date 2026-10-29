set pagination off
run
python
import gdb
a = int(gdb.parse_and_eval('*(unsigned*)((char*)&g_BackBuffer + 0x5c)'))
print('>> bits', hex(a))
gdb.execute('dump binary memory C:/Users/Joel/AppData/Local/Temp/bb.bin %d %d' % (a, a + 614400))
end
