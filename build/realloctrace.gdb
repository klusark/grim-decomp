python
import gdb
gdb.execute('set pagination off')
b = gdb.Breakpoint('Grim_Init'); gdb.execute('run'); b.delete()
gdb.Breakpoint('luaD_message'); gdb.Breakpoint('stdMemory_Realloc')
n = 0
while True:
    try: gdb.execute('continue', to_string=True)
    except gdb.error: break
    f = gdb.newest_frame()
    if f.name() == 'luaD_message': print('>> error'); break
    n += 1
    print('>> realloc p=%s size=%s from %s' % (gdb.parse_and_eval('p'), gdb.parse_and_eval('size'), f.older().name()))
print('>> total', n)
end
