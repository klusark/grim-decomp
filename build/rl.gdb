set pagination off
break Res_LoadInternal if (int)type == 0x54534f43
run
printf ">> name=%s\n", name
p/x type
p (void*)ResType_Find(type)
x/6wx ResType_Find(type)
finish
p *status
p/x *(int*)status
x/8wx $esp
kill
