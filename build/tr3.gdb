set pagination off
set environment _NO_DEBUG_HEAP=1
break Lua_MakeCurrentSet
run
python
import gdb
for a in (10.0, 270.0, 300.0, 359.0, -10.0, 725.0):
    print('>> norm360(%g) = %g' % (a, float(gdb.parse_and_eval('((float(*)(float))Math_NormalizeAngle360)(%f)' % a))))
for a in (1.4, 1.5, 2.5, 100.7, 12000.3, 13650.2):
    print('>> round(%g) = %g' % (a, float(gdb.parse_and_eval('((float(*)(float))Math_Round)(%f)' % a))))
end
kill
