set pagination off
run
python
import gdb, struct
inf = gdb.selected_inferior()
def rd(a, n): return bytes(inf.read_memory(a, n))
gdb.execute('thread 1')
def raw(idx):
    p = struct.unpack('<I', rd(int(gdb.parse_and_eval('(int)&PTR_1002bf6c')), 4))[0]
    st = struct.unpack('<I', rd(p + 32, 4))[0]
    return struct.unpack('<iI', rd(st - 8 + idx * 8, 8))
gdb.execute('call (int)lua_beginblock()')
sysobj = int(gdb.parse_and_eval('(int)lua_getglobal("system")'))
print('>> system', sysobj, raw(sysobj))
for key in ('oldIndexFB', 'indexFB', 'indexFB_disabled', 'parent_object'):
    gdb.execute('call (int)lua_pushobject(%d)' % sysobj)
    gdb.execute('call (int)lua_pushstring("%s")' % key)
    o = int(gdb.parse_and_eval('(int)lua_gettable()'))
    print('>>', key, o, raw(o) if o else None)
for tg in (0, -1, -2, -3, -4, -5):
    o = int(gdb.parse_and_eval('(int)lua_gettagmethod(%d, "index")' % tg)); print('>> tagmethod index tag', tg, o, raw(o) if o else None)
for tg in (-3,):
    o = int(gdb.parse_and_eval('(int)lua_gettagmethod(%d, "gettable")' % tg)); print('>> tagmethod gettable tag', tg, o, raw(o) if o else None)
end
