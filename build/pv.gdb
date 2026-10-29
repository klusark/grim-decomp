set pagination off
break Lua_MakeCurrentSet
run
delete
break lvm.c:1125
commands
silent
printf ">> pushnum bits=%x opcode_val=%d\n", *(unsigned*)(*(int*)param_1[7] + 4), param_1[9]
continue
end
set breakpoint pending on
continue
