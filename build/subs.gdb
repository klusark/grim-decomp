set pagination off
break Engine_InitSubsystems
run
continue
python
import gdb
t = int(gdb.parse_and_eval('(int)&DAT_008a8778'))
for i in range(6):
    fp = int(gdb.parse_and_eval('*(int*)%d' % (t + 8 + 32*i)))
    print('>> entry', i, hex(fp), gdb.execute('info symbol %d' % fp, to_string=True).strip().split(' in ')[0] if fp else '-')
end
