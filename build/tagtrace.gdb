# Prints the arguments of every settagmethod / tag / newtag builtin call until the first Lua error.
python
import gdb
gdb.execute('set pagination off')
b = gdb.Breakpoint('Grim_Init'); gdb.execute('run'); b.delete()
gdb.Breakpoint('luaD_message')
for fn in ('FUN_10003d10',):
    try: gdb.Breakpoint(fn)
    except gdb.error: pass
n = 0
while n < 40:
    try: gdb.execute('continue', to_string=True)
    except gdb.error: break
    f = gdb.newest_frame(); nm = f.name() or '?'
    if nm == 'luaD_message':
        print('>> error:', gdb.execute('x/s *(char**)($esp+4)', to_string=True).strip()); break
    n += 1
    out = []
    for i in (1, 2, 3):
        try:
            o = int(gdb.parse_and_eval('(int)lua_lua2C(%d)' % i))
            if o == 0: out.append('none'); continue
            if int(gdb.parse_and_eval('(int)lua_isnumber(%d)' % o)): out.append('num %s' % gdb.parse_and_eval('(float)lua_getnumber(%d)' % o))
            elif int(gdb.parse_and_eval('(int)lua_isstring(%d)' % o)): out.append('str %s' % gdb.parse_and_eval('(char*)lua_getstring(%d)' % o))
            elif int(gdb.parse_and_eval('(int)lua_isnil(%d)' % o)): out.append('nil')
            else: out.append('obj%d' % o)
        except gdb.error as e: out.append('?')
    print('>> %s(%s)' % (nm, ', '.join(out)))
end
