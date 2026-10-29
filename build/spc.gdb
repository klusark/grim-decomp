set pagination off
break Actor_SetPositionClamped
commands
silent
printf ">> SPC actor=%x pos=%f %f %f raw=%x %x %x\n", param_1, param_2[0], param_2[1], param_2[2], *(unsigned*)param_2, *((unsigned*)param_2+1), *((unsigned*)param_2+2)
bt 3
continue
end
break Lua_PutActorAt
commands
silent
printf ">> PutActorAt\n"
continue
end
run
