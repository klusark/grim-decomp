set pagination off
set environment _NO_DEBUG_HEAP=1
break Lua_MakeCurrentSet
run
python
import gdb
s = gdb.parse_and_eval('(float*)malloc(16)')
import math
for a in (0.0, 10.0, 45.3, 89.9, 90.0, 100.0, 180.0, 200.0, 270.0, 300.0, 359.0, -10.0, -100.0, 370.0, 12.5):
    gdb.execute('call ((void(*)(float,float*,float*))Math_SinCosTable)(%f, (float*)%d, (float*)%d)' % (a, int(s), int(s)+4))
    sn = float(gdb.parse_and_eval('*(float*)%d' % int(s))); cs = float(gdb.parse_and_eval('*(float*)%d' % (int(s)+4)))
    ok = abs(sn - math.sin(math.radians(a))) < 0.01 and abs(cs - math.cos(math.radians(a))) < 0.01
    print('>> %8.2f sin=%9.5f cos=%9.5f %s' % (a, sn, cs, 'ok' if ok else 'BAD'))
end
kill
