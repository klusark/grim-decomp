# Like luaerr.gdb but for an executable without our symbols: break on luaD_message once lua.dll is loaded.
python
import gdb, os
gdb.execute('set pagination off')
gdb.execute('set breakpoint pending on')
gdb.Breakpoint('luaD_message')
count = 0
gdb.execute('run')
while count < int(os.environ.get('MAXERR', '10')):
    f = gdb.newest_frame()
    if (f.name() or '') != 'luaD_message':
        print('>> stopped in', f.name()); gdb.execute('bt 6'); break
    count += 1
    msg = gdb.execute('x/s *(char**)($esp+4)', to_string=True).strip()
    print('>> Lua error #%d: %s' % (count, msg))
    try: gdb.execute('continue', to_string=True)
    except gdb.error: break
end
