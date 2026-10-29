set pagination off
set breakpoint pending on
break Lua_LoadActor
python
import gdb
gdb.execute('run')
names = []
for i in range(1, 900):
    try:
        o = int(gdb.parse_and_eval('(int)lua_lua2C(1)'))
        s = gdb.parse_and_eval('(char*)lua_getstring(%d)' % o)
        names.append(str(s).split('"')[1] if '"' in str(s) else '?')
        gdb.execute('continue', to_string=True)
    except gdb.error as e:
        print('>> err', e); break
print('>> total', len(names))
print('>> first', names[:15])
print('>> 100..130', names[100:130])
import collections
print('>> most common', collections.Counter(names).most_common(8))
end
