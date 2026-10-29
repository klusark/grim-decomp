set pagination off
break Lua_MakeCurrentSet
run
p ((float(*)(float))Math_SinDeg)(37.589)
p ((float(*)(float))Math_SinDeg)(30.0)
p ((float(*)(float))Math_SinDeg)(90.0)
kill
