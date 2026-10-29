set pagination off
break Lua_MakeCurrentSet
run
set $a = (char*)malloc(64)
set $f = (float*)malloc(16)
set $d = (int*)malloc(16)
set $s = (char*)malloc(64)
set $i = (int)sscanf("2.5 7 abc","%f %d %s",$f,$d,$s)
p $i
p *$f
p *$d
p (char*)$s
p (double)atof("3.25")
p (double)strtod("3.25",0)
p (int)atoi("42")
kill
