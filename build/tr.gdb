set pagination off
set environment _NO_DEBUG_HEAP=1
break Lua_MakeCurrentSet
run
set $m = (float*)malloc(128)
set $a = (float*)malloc(16)
set $p = (float*)malloc(16)
set $a[0]=0.0
set $a[1]=0.0
set $a[2]=30.0
set $p[0]=1.0
set $p[1]=2.0
set $p[2]=3.0
call ((void(*)(float*,float*,float*))Angles_ToMatrix)($m, $a, $p)
x/12fw $m
set $a[0]=45.0
set $a[1]=10.0
set $a[2]=100.0
call ((void(*)(float*,float*,float*))Angles_ToMatrix)($m, $a, $p)
x/12fw $m
kill
