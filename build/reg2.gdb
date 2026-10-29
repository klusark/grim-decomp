set pagination off
set breakpoint pending on
break RegOpenKeyExA
break RegQueryValueExA
break RegCreateKeyExA
python
import gdb
gdb.execute('run')
for i in range(40):
    try:
        f = gdb.newest_frame().name()
        esp = int(gdb.parse_and_eval('(int)$esp'))
        a = [int(gdb.parse_and_eval('*(unsigned*)%d' % (esp + 4 + 4*k))) for k in range(4)]
        s = ''
        try: s = gdb.execute('x/s %d' % a[1], to_string=True).split('\t',1)[1].strip()
        except Exception: pass
        gdb.execute('finish', to_string=True)
        print('>>', f, hex(a[0]), s, '->', gdb.parse_and_eval('$eax'))
        gdb.execute('continue', to_string=True)
    except gdb.error as e:
        print('>> end', e); break
end
