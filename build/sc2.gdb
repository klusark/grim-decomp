set pagination off
break Lua_MakeCurrentSet
run
set $f = (float*)malloc(16)
set $d = (int*)malloc(16)
set $s = (char*)malloc(64)
set $i = ((int(*)(char*,char*,...))0x0051c018)("2.5 7 abc","%f %d %s",$f,$d,$s)
p $i
p *$f
p *$d
p (char*)$s
kill
