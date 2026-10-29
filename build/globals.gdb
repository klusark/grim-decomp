# At the Nth Lua error, report whether the named globals exist (GLOBALS="a,b,c" ERRN=6).
python
import gdb, os
gdb.execute('set pagination off')
b = gdb.Breakpoint('Grim_Init'); gdb.execute('run'); b.delete()
gdb.Breakpoint('luaD_message')
n = int(os.environ.get('ERRN', '6'))
for i in range(n):
    gdb.execute('continue', to_string=True)
print('>> at error', n, gdb.execute('x/s *(char**)($ebp+8)', to_string=True).strip())
for g in os.environ.get('GLOBALS', 'CheckFirstTime').split(','):
    o = int(gdb.parse_and_eval('(int)lua_getglobal("%s")' % g))
    if o == 0: print('>>', g, 'obj 0'); continue
    print('>>', g, 'obj', o, 'nil' if int(gdb.parse_and_eval('(int)lua_isnil(%d)' % o)) else ('function' if int(gdb.parse_and_eval('(int)lua_isfunction(%d)' % o)) else ('table' if int(gdb.parse_and_eval('(int)lua_istable(%d)' % o)) else 'other')))
end
