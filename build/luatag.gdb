python
import gdb
gdb.execute('set pagination off')
b = gdb.Breakpoint('Grim_Init'); gdb.execute('run'); b.delete()
gdb.Breakpoint('luaD_message')
gdb.Breakpoint('lua_tag')
n = 0
while n < 30:
    try: gdb.execute('continue', to_string=True)
    except gdb.error: break
    nm = gdb.newest_frame().name()
    if nm == 'luaD_message':
        print('>> error'); break
    arg = int(gdb.parse_and_eval('*(int*)($ebp+8)'))
    base = int(gdb.parse_and_eval('*(int*)(*(int*)&lua_state + 32)')) if False else 0
    gdb.execute('finish', to_string=True)
    eax = int(gdb.parse_and_eval('(int)$eax'))
    print('>> lua_tag(obj=%d) -> %d' % (arg, eax))
    n += 1
end
