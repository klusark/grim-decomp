set pagination off
break LecShare_Resolve
break LecShare_CountMatching
python
import gdb
gdb.execute('run')
for i in range(12):
    try:
        f = gdb.newest_frame().name()
        esp = int(gdb.parse_and_eval('(int)$esp'))
        a1 = int(gdb.parse_and_eval('*(unsigned*)%d' % (esp+4)))
        a2 = int(gdb.parse_and_eval('*(unsigned*)%d' % (esp+8)))
        s1 = gdb.execute('x/s %d' % a1, to_string=True).split('\t',1)[-1].strip() if a1 > 0x1000 else hex(a1)
        s2 = gdb.execute('x/s %d' % a2, to_string=True).split('\t',1)[-1].strip() if a2 > 0x1000 else hex(a2)
        print('>>', f, s1, '|', s2)
        gdb.execute('continue', to_string=True)
    except gdb.error as e:
        print('>> end', e); break
end
