set pagination off
break lua_pushnumber
commands
silent
python
import gdb
v = int(gdb.parse_and_eval('*(unsigned*)&n')) & 0xffffffff
if 0 < (v & 0x7fffffff) < 0x00800000:
    fr = gdb.newest_frame().older()
    print('>> denormal push %#x from %s' % (v, fr.name()))
end
continue
end
run
