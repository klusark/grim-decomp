python
import gdb
gdb.execute('set pagination off')
b = gdb.Breakpoint('Grim_Init'); gdb.execute('run'); b.delete()
gdb.Breakpoint('FUN_10003d10')
gdb.execute('continue')
for i in (1,2,3):
    o = int(gdb.parse_and_eval('(int)lua_lua2C(%d)' % i))
    st = int(gdb.parse_and_eval('*(int*)(*(int*)&PTR_1002bf6c + 32)')) if False else None
    print('>> arg', i, 'obj', o)
st = gdb.parse_and_eval('*(int*)(*(int**)&PTR_1002bf6c + 8)')
print('>> stack base', st)
for i in (1,2,3):
    o = int(gdb.parse_and_eval('(int)lua_lua2C(%d)' % i))
    a = int(st) - 8 + o * 8
    print('>> raw', i, gdb.execute('x/2wx %d' % a, to_string=True).strip(), gdb.execute('x/2f %d' % (a+4), to_string=True).strip() )
