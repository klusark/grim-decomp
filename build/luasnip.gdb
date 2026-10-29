# SNIP='lua code' gdb -batch -x build/luasnip.gdb --args <exe>
# Runs a Lua snippet with lua_dostring once the builtins exist (before _system.lua) and prints the
# result code, the first Lua error message and the native backtrace if it fails.
python
import gdb, os
gdb.execute('set pagination off')
b = gdb.Breakpoint('Grim_Init'); gdb.execute('run'); b.delete()
b = gdb.Breakpoint('lua_dofile', internal=True); gdb.execute('continue'); b.delete()
gdb.Breakpoint('luaD_message')
snip = os.environ.get('SNIP', 't1 = 5').replace('"', '\\"')
try:
    r = gdb.parse_and_eval('(int)lua_dostring("%s")' % snip)
    print('>> rc =', r)
except gdb.error as e:
    print('>> stopped inside lua_dostring')
    try:
        print('>> message:', gdb.execute('x/s *(char**)($esp+4)', to_string=True).strip())
        print(gdb.execute('bt 10', to_string=True))
    except gdb.error as e2:
        print('>> no message', e2)
end
